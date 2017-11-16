/* Matías Gastón Santiago:
 * 
 * TDA/TDC/Factory design & implementation
 * 
 * 29/6/2015
 *
 * IFactory.hpp
 *  
 */

#ifndef FACTORY_HPP
#define FACTORY_HPP

#include "Type.hpp"

//Parametrized factory

template < typename Interface > class Factory;

template <> class Factory< IType >
{
	public:
	
	static IType* get()
	{
		return (IType*) new Type;
	}
	
};

#endif
