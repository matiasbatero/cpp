#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cstdint>

#include <iostream>
#include <new> 

using namespace std;


class array
{
	private:
	
	uint32_t    _size;
	uint32_t 	_capacity;
	void* 		_data;
	
	uint32_t default_heap_size()
	{
		return 256;
	};
	
	void* raw() const
	{
		return _data;
	};
		
	void grow()
	{
		_data = realloc( _data, capacity()*2 );
				
		if ( !_data  )
		{
			_capacity = capacity()*2;
			*((char*)raw() +  capacity() ) = EOF;
		}
	};		
	
	
	public:
	
	array() : _size( 0 ), _capacity( 0 ), _data( 0 )
	{
		_data = malloc( default_heap_size() );
		_capacity = default_heap_size();
		memset( raw(), 0, _capacity );
		*((char*)raw() +  _capacity ) = EOF;	
	};
	
		
	char& operator[]( uint32_t index )
	{
		if ( index < capacity() )
		{
			if ( index >= used() )
				_size = index;
				
			return *((char*)raw() +  index );
		}
		else
		{
			grow();
			return (*this)[index];
		};
	};
	
		
	uint32_t used() const
	{
		return _size;
	};
	
	uint32_t capacity() const
	{
		return _capacity;
	};
	
	void clear()
	{
		memset( raw(), 0, capacity() );
		_size = 0;
	};
	
	operator const char*() const
	{
		return (const char*)raw();
	};
	
	operator char*()
	{
		return (char*)raw();
	};
	
	~array()
	{
		free( raw() );
	};
	 
	
};

bool are_equal( const array& b1, const array& b2 )
{
	return 0;
};

void print_cstring( const array& pkg )
{
	printf("%*.*s", 0, pkg.used(), (const char*)pkg );
};

void dump( const array& pkg )
{
	for( uint byte_count=0; byte_count <= pkg.used(); byte_count++ )
	{
		putc( pkg[byte_count] , stdout );
	};
};	

void fill_with_c_string( array& stack, const char* cstring )
{
	for( uint byte_count=0; byte_count <= strlen(cstring); byte_count++ )
	{
		stack[byte_count] = *( cstring + byte_count );
	};
};

class lifo
{
	array data;
	uint32_t counter;
	
	public:
	
	lifo() : counter(0)
	{
				
	};
	
	void push( char value )
	{
		data[ counter++ ] = value;
	};
	
	char pop()
	{
		if ( counter > 0 )
			return data[ --counter ];
		else
			return data[ 0 ];
	};
	
	char peek()
	{
		return data[ counter ];
	};
	
	operator const char*() const
	{
		return (const char*)data;
	};
	
	operator char*()
	{
		return (char*)data;
	};
};


int main()
{
	
	
	
	
	return 0;	
};
