/*
 * Instituto Superior de Formación Técnica 151
 * Tecnicatura Superior en Análisis de Sistemas
 *
 * Programación II
 *
 * Queue Project ( without parametrization )
 * Queue Variant : circular
 *
 * Version:  Revision 1.0  (23/8/2015)
 * 		     Revision 1.1  (24/8/2015)
 *           Revision 1.2  (31/8/2015)
 *
 * Grupo:
 *
 * Santiago, Matías Gastón
 * Molina Burgos, Álvaro
 * Mato, Santiago
 * Sosa, Luis
 *
 *
 * File:	CircularQueue.hpp (TDC)
 *
 */


#ifndef QUEUE_HPP
#define QUEUE_HPP

#include "IQueue.hpp"
#include <iostream>
#include <assert.h>
#include <malloc.h>
#include <string.h>

using namespace std;

class Queue : public IQueue
{
	private:
	
	enum { MAX_ITEMS = 256, MAX_HEAD=MAX_ITEMS, SIZE_DEFAULT = 32 };
	
	
	int head_pos;
	
	int counter;
	int itemsize;
	
	char* block;
	
	int size() const
	{
		return itemsize*MAX_ITEMS;
	};
	
	bool haveSpace() const
	{
		return ( counter < MAX_ITEMS )? true : false;
	};
	
	int& validHead(int& counterValue )
	{
		if ( head_pos == MAX_ITEMS )
		{
			head_pos = 0;
		};
		
		counterValue--;
		return head_pos;
	};
	
	
	
	int indexToSize(int index) const
	{
		return itemsize*index;
	};
	
	bool isValidSize( const Queue& queue ) const
	{
		return ( queue.size() <= size() )? true : false;
	};
	
	public:
	
	virtual void add( void* item )
	{ 
		if ( haveSpace() ) 
		memcpy( &block[ indexToSize(counter++) ], item, itemsize );
	};
		
	virtual bool isEmpty()
	{
		return ( counter == 0 )? true : false;
	};
	
	virtual bool isFull()
	{
		return ( counter == MAX_ITEMS )? true : false;
	};
	
	virtual void* pop()
	{
		return &block[ indexToSize( validHead(counter)++ ) ];
	};
	
	//assignment operator
	Queue& operator=( const Queue& queue )
	{
		if ( isValidSize(queue) )
		{
			head_pos = queue.head_pos;
			counter = queue.counter;
			itemsize = queue.itemsize;
			memcpy( block, queue.block, queue.size() );
		};

		return *this;
	};

	//copy constructor
	Queue( const Queue& queue ) :
		
		head_pos(queue.head_pos),
		counter(queue.counter),
		itemsize(queue.itemsize),
		
		block( (char*)memcpy( malloc( size() ), queue.block, size() ))

	{};

	//void constructor (with default parameter)
	Queue( size_t typesize = SIZE_DEFAULT ) :
		
		head_pos(0),
		counter(0),
		itemsize(typesize),
		block( (char*)malloc( size() ) )

	{};

	
	
	
	
	//destructor
	~Queue()
	{
		free( block );
	};
	
	
	
};
	
#endif
	
