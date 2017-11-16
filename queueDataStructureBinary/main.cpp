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
 * File:	 main.cpp (test file)
 *
 */

#include "./interface/IQueue.hpp"
#include "./types/factories/QueueFactory.hpp"

#include "./interface/IFactory.hpp"
#include "./types/factories/IntegerFactory.hpp"


#include <iostream>

using namespace std;

int AsInt(void* input)
{
	return *((int*)input);
}

int main()
{
	cout << "Queue Without Parametrization Test: \n\n" ;

    IFactory*  factory = new IntegerFactory;
    IFactory* qfactory = new QueueFactory;

    IQueue* test = qfactory->create( "circular", factory );

    int value = 0;

	while( !test->isFull() )
    {
        test->add( &value );
        value++;
    }

	while( !test->isEmpty() )
    {
        cout << AsInt( test->front() ) << " ";
        test->pop();
    }



	return 0;
}
