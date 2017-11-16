#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cstdint>

#include <iostream>

using namespace std;

class byte
{
	uint8_t _value;
	uint8_t _is_null;
	
	public:
	
	byte() : _value(0), _is_null(true)
	{
		
	};
	
	//byte( const byte& in )
	//{
		//_value = in._value;
		//_is_null = 
	//};
	
	byte( uint8_t value ) : _value(value), _is_null(false)
	{
		
	};
	
	bool operator == ( const byte& in )
	{
		return ( in._is_null == _is_null && in._value == _value )? true : false;
	};
	
	byte& operator = ( const byte& in )
	{
		if ( in._is_null != 0 )
		{
			_value = in._value;
			_is_null = 1;
		};
		
		return *this;
	};
	
	uint8_t raw()
	{
		return _value;
	};
		
};

class data_holder
{
	private:
	
	#define HEAP_DEFAULT_INIT_SIZE 256
	
	
	uint32_t 	_size;
	uint32_t 	_capacity;
	void* 		_data;
	
	
	bool have_space()
	{
		return ( _capacity > _size )? true : false;
	};
	
	void grow()
	{
		_data = realloc( _data, _capacity*2 );
		_capacity = _capacity*2;
		memset( ((uint8_t*)_data+_size), 0, _capacity - _size );
	};		
	
	public:
	
	data_holder() : _size( 0 ), _capacity( 0 ), _data( 0 )
	{
		_data = malloc( HEAP_DEFAULT_INIT_SIZE );
		_capacity = HEAP_DEFAULT_INIT_SIZE;
		memset( _data, 0, _capacity );		
	};
	
	void push_byte( byte value )
	{
		if ( !( value == byte() ) )
		{
			if ( have_space()  )
			{
				*((uint8_t*)_data +  _size ) = value.raw();
				_size++;
			}
			else
			{
				grow();
				push_byte( value.raw() );
			};
		};
	};
	
	byte peek_byte()
	{
		if ( !is_empty() )
		{
			uint8_t byte_value = *((uint8_t*)_data +  (_size-1) );
			return byte_value;
		}
		else
		{
			return {};
		};
	};
	
	byte pop_byte()
	{
		
		if ( !is_empty() )
		{
			uint8_t byte_value = ( *((uint8_t*)_data +  (--_size) ) );
			return byte_value;
		}
		else
		{
			return {};
		};
	};
	
	uint8_t& operator[](int index)
	{
		if ( !is_empty() )
		{
			return *((uint8_t*)_data +  index );
		}
		else
		{
			return EOF;
		};
	};
	
	uint32_t size()
	{
		return _size;
	};
	
	uint32_t capacity()
	{
		return _capacity;
	};
	
	void* raw()
	{
		return _data;
	};
	
	bool is_empty()
	{
		return ( _size == 0 )? true : false;
	};
	
	void clear( )
	{
		memset( _data, 0, _capacity );
		_size = 0;
	};
	
	~data_holder()
	{
		free( _data );
		printf("\n\n:: byte_stack automatically deallocated sucessfully" );
	};
	 
	
};


class random_accessor
{
	public:
	
	virtual int get(int pos)
	{
		return pos;
	}
};

class io
{
	public:
	
	virtual void put( byte value ) = 0;
	virtual byte get() = 0;
};


class io_byte_fifo_accessor : io
{
	int count;
	
	public:
	
	io_byte_fifo_accessor( data_holder& ) : count(0)
	{
		
	};
	
	void put( byte value )
	{
		
	};
	
	byte get()
	{
		return {};
	};
	
};




void fill_with_c_string( data_holder& stack, const char* cstring ) //fillable with c string
{
	for( uint32_t byte_count=0; byte_count <= strlen(cstring); byte_count++ )
		stack.push_byte( *( cstring + byte_count ) );
};

void fill_from_stdin( data_holder& stack, uint32_t end_delimiter = '\n' ) //fillable with stdin
{
	uint32_t byte_value = getc( stdin );
	
	while( byte_value != end_delimiter )
	{
		stack.push_byte( byte_value );
		byte_value = getc( stdin );		
	};
};

void dump_as_cstring( data_holder& stack ) //dumpeable
{
	printf("%*.*s", 0, stack.size(), (uint8_t*)stack.raw() );
};

void dump_raw( data_holder& stack ) //dumpeable
{
	for( uint32_t byte_count=0; byte_count <= stack.size(); byte_count++ )
		putc( *( (uint8_t*)stack.raw() + byte_count ), stdout );
};

int main()
{
	

	
	return 0;	
};
