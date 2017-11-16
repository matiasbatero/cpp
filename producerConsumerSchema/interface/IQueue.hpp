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
 * File:	 IQueue.hpp (TDA)
 *
 */

#ifndef IQUEUE_HPP
#define IQUEUE_HPP

template< typename Type >
class IQueue
{
	public:

	virtual void add( const Type& item ) = 0;

	virtual bool isEmpty() = 0;

	virtual bool isFull() = 0;

	virtual Type& front() = 0;
	
	virtual const Type& front() const = 0;

	virtual void pop() = 0;
};



#endif
