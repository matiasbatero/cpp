#include <stdint.h>
#include <string.h>
#include <malloc.h>

class bin
{
	private:
	
	#define		defaultCapacity 	00256
	#define		growFactor  		00002
	#define		firstIndex			00000
	#define		defaultByteValue	00000
			
	uint32_t	currentCapacity;
	int8_t*		blockAddress;
				
	void grow()
	{
		uint32_t newCapacity = currentCapacity*growFactor;
		realloc( (void*)blockAddress, newCapacity );
		memset( ( blockAddress + currentCapacity ), defaultByteValue, (newCapacity - currentCapacity) );
		currentCapacity = newCapacity;
	};
	
	
	public:
	
	bin() : currentCapacity( defaultCapacity )
	{
		blockAddress = (int8_t*) malloc( currentCapacity );
		memset( blockAddress, defaultByteValue, currentCapacity );
	};
	
	
	void getByteAt( uint32_t index, int8_t& out )
	{
		if ( index < currentCapacity && blockAddress )
			out = *( blockAddress + index );						
	};
				
	void setByteAt( uint32_t index, int8_t in )
	{
		if ( index < currentCapacity && blockAddress )
			*( blockAddress + index ) = in;
		else
		{
			grow();
			setByteAt( index, in );
		};			
	};
	
	
	~bin()
	{
		if( blockAddress )
			free( blockAddress );
	};
	
};



int main()
{
	bin anArray;
	
	anArray.setByteAt(300, 'a' );
	anArray.setByteAt(301, 'a' );

	
	return 0;
};
