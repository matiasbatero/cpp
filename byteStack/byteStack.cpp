#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cstdint>



class byteStack
{
	private:
	
	#define HEAP_DEFAULT_INIT_SIZE 256
		
	uint32_t 	_size;
	uint32_t 	_capacity;
	void* 		_data;

	bool is_empty()
	{
		return ( _size == 0 )? true : false;
	};
	
	bool have_space()
	{
		return ( _capacity > _size )? true : false;
	};
	
	void grow()
	{
		_data = realloc( _data, _capacity*2 );
		_capacity = _capacity*2;
		memset( ((char*)_data+_size), 0, _capacity - _size );
	};		
	
	public:
	
	byteStack() : _size( 0 ), _capacity( 0 ), _data( 0 )
	{
		_data = malloc( HEAP_DEFAULT_INIT_SIZE );
		_capacity = HEAP_DEFAULT_INIT_SIZE;
		memset( _data, 0, _capacity );		
	};
	
	void push_byte( int byte )
	{
		if ( have_space() )
		{
			*((char*)_data +  _size ) = byte;
			_size++;
		}
		else
		{
			grow();
			push_byte( byte );
		};
	};
	
	void dump()
	{
		printf("%s", (char*)_data );
	};
	
	void clear()
	{
		memset( _data, 0, _capacity );
		_size = 0;
	};
	
	~byteStack()
	{
		free( _data );
		printf("\n\n:: byte_stack automatically deallocated sucessfully" );
	};
};

void fill_with_c_string( byteStack& stack, const char* cstring )
{
	for( uint byte_count=0; byte_count <= strlen(cstring); byte_count++ )
		stack.push_byte( *( cstring + byte_count ) );
};

void fill_from_stdin( byteStack& stack, char end_delimiter = '\n' )
{
	char byte_value = getc( stdin );
	
	while( byte_value != end_delimiter )
	{
		stack.push_byte( byte_value );
		byte_value = getc( stdin );		
	};
};


int main()
{
	byteStack stack;
	
	printf( "string from stdin test ( default end delimiter '\\n' [new line] ) \n" );
	printf( "set: " );
	
	fill_from_stdin( stack );
		
	printf( "\nget: " );
	
	stack.dump();
	stack.clear();
	
	printf( "\nstring from stdin test ( custom end delimiter ' ' [space] )\n" );
	printf( "set: " );
	
	fill_from_stdin( stack, ' ' );
		
	printf( "\nget: " );
	
	stack.dump();
	stack.clear();
	
	printf( "\nstring from const char* [cstring]\n" );
	
	fill_with_c_string( stack, "This Is A Test From C-String (Null Terminated) From Code" );
	
	stack.dump();
	
	return 0;	
};
