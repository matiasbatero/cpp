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
 *           Revision 1.1  (15/9/2015)
 *
 * Log:      max_items is defined outside.
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

	int first, last, items, max_items;

	Type* container;


	public:

	virtual bool isEmpty()
	{
		return ( items == 0 )? true : false;
	};

	virtual bool isFull()
	{
		return ( items == max_items )? true : false;
	};

	virtual void add( const Type& item )
	{
		if ( !isFull() )
		{
			container[ last++ ] = item;
			items++;
			if ( last == max_items ) last = 0;
		};

	};

	virtual void pop()
	{
		if ( !isEmpty() )
		{
			first++;
			items--;
			if ( first == max_items ) first = 0;
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

	Queue(int nitems) : first(0), last(0), items(0), max_items(nitems), container( new Type[max_items] )
	{

	};

	virtual ~Queue()
	{
		delete[]  container;
	};

};

#endif

