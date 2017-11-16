#include "IQueue.hpp"

#include <assert.h>
#include <malloc.h>
#include <string.h>


class Queue : public IQueue
{
	private:
	
	typedef char byte;
	
	enum { FIRST = 1, MAX_ITEMS = 255, TOTAL_ITEMS=256, NO_ITEMS=0, SIZE_DEFAULT = 32 };
	
	size_t size_item;
	int items;
	
	byte* block;
	
	int indexToSize(int index)
	{
		return size_item*index;
	};
	
	
	
	public:
	
	virtual bool add(void* item)
	{
		bool state = !isFull();
		
		if ( state )
		{
			memcpy( &block[ indexToSize(++items) ], item, size_item );
		};
		
		return state;
	}
	
	virtual bool isFull()
	{
		return ( items == MAX_ITEMS )? true : false;
	}
	
	virtual bool isEmpty()
	{
		return ( items == NO_ITEMS )? true : false;
	}
	
	virtual void* read()
	{
		assert( !isEmpty() );
		return &block[ indexToSize(FIRST) ];
	}
	
	virtual void* pop()
	{
		assert( !isEmpty() );
		memcpy( &block[0], &block[indexToSize(FIRST)], size_item*(--items+1) );
		return &block[0];
	}
	
	Queue( const Queue& queue, size_t bytes = SIZE_DEFAULT ) :
	
		size_item(bytes),
		items(0),
		block( (byte*)malloc(bytes*TOTAL_ITEMS) )
		
	{
		memcpy( &block[0], queue.block, queue.size_item );
	};
	
	Queue( size_t bytes = SIZE_DEFAULT ) : 
		
		size_item(bytes),
		items(0),
		block( (byte*)malloc(bytes*TOTAL_ITEMS) ) 
	
	{};

	~Queue()
	{
		free( block );
	};
	
		
};



