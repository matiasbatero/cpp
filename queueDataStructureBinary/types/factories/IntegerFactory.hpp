/*
 * Instituto Superior de Formación Técnica 151
 * Tecnicatura Superior en Análisis de Sistemas
 *
 * Programación II
 *
 * Integer Factory
 *
 * Version:  Revision 1.0  (1/9/2015)
 *
 * Autor: 	 Santiago, Matías Gastón
 *
 * File:	 IntegerFactory.hpp
 *
 */

#ifndef INTEGER_FACTORY_HPP
#define INTEGER_FACTORY_HPP

#include "../../interface/IFactory.hpp"


class IntegerFactory : public IFactory
{
	private:

	~IntegerFactory();

	public:

	virtual void* create( void* arg, ... );

};

IntegerFactory::~IntegerFactory()
{

};

void* IntegerFactory::create(void* arg, ...)
{
	return new int( *((int*)arg) );
};


#endif
