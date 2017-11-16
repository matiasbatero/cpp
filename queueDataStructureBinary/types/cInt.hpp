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
 * File:	 IntegerFactory.hpp
 *
 */

#ifndef INTEGER_HPP
#define INTEGER_HPP

class cInt
{
    private:

    int rep;

    public:

    cInt operator+(int value)
    {
        rep+=value;
        return this;
    }

    operator int()
    {
        return rep;
    }

    operator void*()
    {
        return this;
    }
};
