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
 * Autor: 	 Santiago, Matías Gastón
 *
 * File:	 QueueCircular.hpp
 *
 */

#ifndef QUEUE_HPP
#define QUEUE_HPP

#include "../../interface/IQueue.hpp"
#include "../../interface/IFactory.hpp"

#include <cstring>

class QueueCircular : public IQueue
{
	private:

	enum { MAX_ITEMS = 256, DEFAULT_ITEM_SIZE = 32 };

	IFactory* _factory;
	int itemsize;
	char* container;
	int first, last, items;

	int lastMemoryPos()
	{
		return last*itemsize;
	};

	int firstMemoryPos()
	{
		return first*itemsize;
	};

	public:

	virtual bool isEmpty()
	{
		return ( items == 0 )? true : false;
	};

	virtual bool isFull()
	{
		return ( items == MAX_ITEMS )? true : false;
	};

	virtual void add( void* ditem )
	{
		if ( !isFull() )
		{
			memcpy( &container[ lastMemoryPos() ], _factory->create(ditem) , itemsize ); //
			last++; items++;
			if ( last == MAX_ITEMS ) last = 0;
		};
	};

	virtual void* front()
	{
		return &container[ firstMemoryPos() ];
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

	QueueCircular( IFactory* factory ) :
		_factory( factory ),
		itemsize( DEFAULT_ITEM_SIZE ),
		container( new char[ itemsize*MAX_ITEMS ] ),
		first(0),
		last(0),
		items(0)

	{};

	~QueueCircular()
	{
		delete[] container;
	};




};

#endif

