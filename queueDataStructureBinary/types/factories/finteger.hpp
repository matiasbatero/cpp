/*
 * Instituto Superior de Formación Técnica 151
 * Tecnicatura Superior en Análisis de Sistemas
 *
 * Programación II
 *
 * Integer Factory
 *
 * Version:  Revision 1.0  (23/8/2015)
 * 		     Revision 1.1  (24/8/2015)
 *           Revision 1.2  (31/8/2015)
 *
 *
 * Autor: 	 Santiago, Matías Gastón
 *
 * File:	 integer.hpp
 *
 */

#ifndef INTEGER_FACTORY_HPP
#define INTEGER_FACTORY_HPP

#include "../../interface/IFactory.hpp"
#include "../../interface/ISizable.hpp"


class finteger : public IFactory, public ISizable
{
	private:

	int _value;
	~finteger() {};

	public:

	virtual void* create()
	{
		return new int( _value );
	};

	virtual int getSize()
	{
		return sizeof(int);
	};

	//Not visible through factory interface
	void* withValue(int value)
	{
		_value = value;
		return this;
	};

	finteger() : _value(0) {};


};

#endif
