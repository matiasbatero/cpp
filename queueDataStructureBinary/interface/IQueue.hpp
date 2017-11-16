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
 * File:	 IQueue.hpp (test file)
 *
 */

#ifndef IQUEUE_HPP
#define IQUEUE_HPP

class IQueue
{
	public:

	virtual void add(void*) = 0;

	virtual bool isEmpty() = 0;

	virtual bool isFull() = 0;

	virtual void* front() = 0;

	virtual void pop() = 0;
};



#endif
