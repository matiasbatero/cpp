#include "IQueue.hpp"
#include <assert.h>
#include <iostream>
using namespace std;

template <class Type> 
class Queue : IQueue<Type>
{
	private:
	
	enum { FIRST = 1, MAX_ITEMS = 255, TOTAL_ITEMS=256, NO_ITEMS=0 };

	Type rep[TOTAL_ITEMS];
	
	int items;
	//int count;
	
	public:
	
	virtual bool add(const Type& item)
	{
		bool state = !isFull();
		
		if ( state )
		{
			rep[ items+1 ] = item;
			items++;
		};
		
		return state;
	}
	
	virtual bool isFull()
	{
		return ( items == MAX_ITEMS )? true : false;
	}
	
	virtual bool isEmpty()
	{
		return ( items == 0 )? true : false;
	}
	
	virtual Type read()
	{
		assert( !isEmpty() );
		return rep[FIRST];
	}
	
	//virtual const Type& read() const
	//{
		//assert( !isEmpty() );
		//return &rep[FIRST];
	//}
	
	virtual Type pop()
	{
		assert( !isEmpty() );
		
		for( int i=0; i<MAX_ITEMS; i++ )
		{
			rep[i] = rep[i+1];
		}
			
		items--;
		return rep[0];
	}
	
	Queue() : items(0) {};
	
		
};


