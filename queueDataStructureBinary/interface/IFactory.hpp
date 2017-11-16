/*
 * Instituto Superior de Formación Técnica 151
 * Tecnicatura Superior en Análisis de Sistemas
 *
 * Programación II
 *
 * Factory Interface
 *
 * Version:  Revision 1.0  (30/8/2015)
 *
 * Autor: 	 Santiago, Matías Gastón
 *
 * File:	 IFactory.hpp
 *
 */

#ifndef IFACTORY_HPP
#define IFACTORY_HPP

class IFactory
{
	public:

	virtual void* create( void* arg, ... ) = 0;

};

#endif
