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
 * File:	 QueueFactory.hpp
 *
 */

#ifndef QUEUE_FACTORY_HPP
#define QUEUE_FACTORY_HPP

#include <iostream>
#include <cstdarg>

#include "../../interface/IQueue.hpp"
#include "../../interface/IFactory.hpp"

//All available implementations
#include "../../types/container/QueueCircular.hpp"

using namespace std;


class QueueFactory : public IFactory
{
    private:
    IFactory* factory;
    IQueue* object;

    public:

	virtual void* create( void* arg, ... );

	QueueFactory() : factory(nullptr), object(nullptr) {};

};

void* QueueFactory::create( void* arg, ... )
{
	string implementation( (const char*)arg );

    va_list args;
    va_start (args, arg );

    factory = va_arg( args, IFactory* );

    va_end(args);


    //Add implementations here...
    if ( implementation == "circular" )
    { object = (IQueue*) new QueueCircular(factory); };


    return object;
};

#endif
