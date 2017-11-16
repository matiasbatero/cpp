#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cstdint>
#include <mysql/mysql.h>
#include <mysql++/mysql++.h>
#include <iostream>


using namespace std;

namespace ctype
{
	class array
	{
		private:
		
		uint32_t 	_capacity;
		char* 		_data;
		
		uint32_t default_heap_size()
		{
			return 256;
		};
		
		char* raw()
		{
			return _data;
		};
			
		void grow()
		{
			_data = (char*) realloc( (void*)raw(), capacity()*2 );
					
			if ( _data  )
			{
				memset( (raw() + capacity() + 1), 0, (capacity()*2 - capacity() -1)); 
				_capacity = capacity()*2;
			};		
		};		
		
		public:
		
		array() :  _capacity( 0 ), _data( (char*) malloc( default_heap_size() ) )
		{
			if ( _data )
			{
				memset( raw(), 0, _capacity );
				_capacity = default_heap_size();
			}
		};
		
			
		char& operator[]( uint32_t index )
		{
			if ( index > capacity() )
			{
				grow();
				return (*this)[index];
			}
			else
			{	
				return *(raw() +  index );
			};
		};
		
		uint32_t capacity() const
		{
			return _capacity;
		};
		
		void clear()
		{
			memset( raw(), 0, capacity() );
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



	void dump( const array& pkg )
	{
		for( uint byte_count=0; byte_count <= pkg.capacity(); byte_count++ )
		{
			putc( ((array&)pkg)[byte_count] , stdout );
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
		
		lifo( const lifo& in );
		lifo& operator = ( const lifo& in );
		
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
		
	};



	class fifo
	{
		array data;
		uint32_t counter;
		uint32_t writer_index;
		uint32_t reader_index;
		
		fifo( const fifo& in );
		fifo& operator = ( const fifo& in );
		
		public:
		
		fifo() : counter(0), writer_index(0), reader_index(0)
		{
			
		};
		
		void push( char value )
		{
			data[ writer_index++ ] = value;
			counter++;
		};
		
		char pop()
		{
			if ( !is_empty() )
			{
				if ( reader_index == writer_index )
				{
					reader_index = writer_index = 0;				
					return data[ 0 ];
					
				}
				else
				{
					char value = data[ reader_index++ ];
					counter--;
					return value;
				};	
						
			}
			else
			{
				return data[ 0 ];
			};
		};
		
		char peek()
		{
			if ( !is_empty() )
				return data[ reader_index ];			
			else
				return data[ 0 ];
		};
		
		bool is_empty()
		{
			return ( counter == 0 )? true : false;
		};
		
		
		
	};

	void flush( fifo& _fifo )
	{
		while ( !(_fifo.is_empty()) )
		{
			putc( _fifo.pop(), stdout );
		};
	};
};



int main()
{
	
	
	
	
	return 0;	
};
