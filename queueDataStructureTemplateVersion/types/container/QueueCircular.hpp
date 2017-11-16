/*
 * Instituto Superior de Formación Técnica 151
 * Tecnicatura Superior en Análisis de Sistemas
 *
 * Programación II
 *
 * Queue Project ( Template )
 * Queue Variant : circular
 *
 * Version:  Revision 1.0  (1/9/2015)
 *
 * Autor:    Santiago, Matías Gastón
 *
 * File:	 CircularQueue.hpp (TDC)
 *
 */

#ifndef QUEUE_HPP
#define QUEUE_HPP

#include "../../interface/IQueue.hpp"


template < typename Type >
class Queue : public IQueue< Type >
{
	private:
	
	enum { MAX_ITEMS = 256 };
	
	int first, last, items;

	Type* container;
	
			
	public:
	
	virtual bool isEmpty()
	{
		return ( items == 0 )? true : false;
	};
	
	virtual bool isFull()
	{
		return ( items == MAX_ITEMS )? true : false;
	};
	
	virtual void add( const Type& item )
	{ 
		if ( !isFull() )
		{ 
			container[ last++ ] = item;
			items++; 
			if ( last == MAX_ITEMS ) last = 0;
		};
		
	};
	
	virtual void pop()
	{
		if ( !isEmpty() ) 
		{ 
			first++;
			items--; 
			if ( first == MAX_ITEMS ) first = 0;
		};
	};
	
	virtual Type& front()
	{
		return container[first];
		
	};
	
	virtual const Type& front() const
	{
		return container[first];
		
	};
	
	~Queue()
	{
		delete[]  container;
	};
	
	Queue() : first(0), last(0), items(0), container( new Type[MAX_ITEMS] ) 
	{
		
	};
	
	
};
	
#endif
	
