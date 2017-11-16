/*
 * Instituto Superior de Formación Técnica 151
 * Tecnicatura Superior en Análisis de Sistemas
 *
 * Programación II
 *
 * String Factory
 *
 * Version:  Revision 1.0  (23/8/2015)
 * 		     Revision 1.1  (24/8/2015)
 *           Revision 1.2  (31/8/2015)
 *
 *
 * Autor: 	 Santiago, Matías Gastón
 *
 * File:	 StringFactory.hpp
 *
 */

#ifndef STRING_FACTORY_HPP
#define STRING_FACTORY_HPP

#include "../../interface/IFactory.hpp"

#include <iostream>

using namespace std;

class StringFactory : public IFactory
{
	private:

	int _value;
	~IntegerFactory() {};

	public:

	virtual void* create(void* arg, ... )
	{
		return new string;
	};


};

#endif
