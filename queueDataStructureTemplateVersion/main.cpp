/*
 * Instituto Superior de Formación Técnica 151
 * Tecnicatura Superior en Análisis de Sistemas
 *
 * Programación II
 *
 * Queue Project ( Template )
 * Queue Variant : circular
 *
 * Version:  Revision 1.0  (1/9/2015)
 *
 * Autor:    Santiago, Matías Gastón
 *
 * File:	 main.cpp (test file)
 *
 */

#include <iostream>
#include "./types/container/QueueCircular.hpp"

using namespace std;

int main()
{
	cout << "Queue Template Test: \n\n" ;
	
	Queue<int> test;
	
	for ( int i=0; !test.isFull(); i++ ) test.add(i);
		
	while ( !test.isEmpty() )
	{
		cout << test.front() << ' ';
		test.pop();
	};

	return 0;
}
