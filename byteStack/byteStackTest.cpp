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
	
	byte() : _value(EOF), _is_null(true)
	{
		
	};
	
	byte( uint8_t value ) : _value(value), _is_null(false)
	{
		
	};
	
	bool operator == ( const byte& in )
	{
		return ( in._is_null == _is_null && in._value == _value )? true : false;
	};
	
	byte& operator = ( const byte& in )
	{
		_value = in._value;
		return *this;
	};
		
};

class byte_stack
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
	
	byte_stack() : _size( 0 ), _capacity( 0 ), _data( 0 )
	{
		_data = malloc( HEAP_DEFAULT_INIT_SIZE );
		_capacity = HEAP_DEFAULT_INIT_SIZE;
		memset( _data, 0, _capacity );		
	};
	
	void push_byte( uint32_t byte )
	{
		if ( have_space() )
		{
			*((uint8_t*)_data +  _size ) = byte;
			_size++;
		}
		else
		{
			grow();
			push_byte( byte );
		};
	};
	
	uint32_t peek_byte()
	{
		if ( !is_empty() )
		{
			uint8_t byte_value = *((uint8_t*)_data +  (_size-1) );
			return byte_value;
		}
		else
		{
			return EOF;
		};
	};
	
	uint32_t pop_byte()
	{
		
		if ( !is_empty() )
		{
			uint8_t byte_value = ( *((uint8_t*)_data +  (--_size) ) );
			return byte_value;
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
	
	void* memory_block()
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
	
	~byte_stack()
	{
		free( _data );
		printf("\n\n:: byte_stack automatically deallocated sucessfully" );
	};
};



void fill_with_c_string( byte_stack& stack, const char* cstring )
{
	for( uint32_t byte_count=0; byte_count <= strlen(cstring); byte_count++ )
		stack.push_byte( *( cstring + byte_count ) );
};

void fill_from_stdin( byte_stack& stack, uint32_t end_delimiter = '\n' )
{
	uint32_t byte_value = getc( stdin );
	
	while( byte_value != end_delimiter )
	{
		stack.push_byte( byte_value );
		byte_value = getc( stdin );		
	};
};

void dump( byte_stack& stack )
{
	printf("%*.*s", 0, stack.size(), (uint8_t*)stack.memory_block() );
};



int main()
{
	byte_stack stack;
	
	fill_from_stdin(stack);
	
	stack.pop_byte();
	
	cout << sizeof(byte) << endl;

	
	return 0;	
};
