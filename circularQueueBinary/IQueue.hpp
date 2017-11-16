/*
 * Instituto Superior de Formación Técnica 151
 * Tecnicatura Superior en Análisis de Sistemas
 *
 * Programación II
 *
 * Queue Project ( without parametrization )
 * Queue Interface
 *
 * Version:  Revision 1.0  (23/8/2015) 		
 *
 * Grupo:
 *
 * Santiago, Matías Gastón
 * Molina Burgos, Álvaro
 * Mato, Santiago
 * Sosa, Luis
 *
 *
 * File:	IQueue.hpp (TDA)
 *
 */


#ifndef IQUEUE_HPP
#define IQUEUE_HPP


class IQueue
{
	public:

	virtual void add(void* item) = 0;

	virtual bool isEmpty() = 0;

	virtual bool isFull() = 0;

	virtual void* pop() = 0;
};



#endif
