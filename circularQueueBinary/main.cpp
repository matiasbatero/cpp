/*
 * Instituto Superior de Formación Técnica 151
 * Tecnicatura Superior en Análisis de Sistemas
 *
 * Programación II
 *
 * Queue Project ( without parametrization )
 * Queue Variant : simple
 *
 * Version:  Revision 1.0  (23/8/2015)
 * 		     Revision 1.1  (31/8/2015) 
 *
 * Grupo:
 *
 * Santiago, Matías Gastón
 *
 * File:	main.cpp (testing file)
 *
 */


#include <iostream>
#include "QueueCircular.hpp"


using namespace std;


int AsInt( void* input )
{
	return *( (int*) input );
};


int main()
{
	//Default
	cout << "TEST A : Default Construction using default parameter\n";
	cout << "----------------------------------------------------\n\n";

	cout << "::Initialization...\n";
	Queue testA;

	cout << "::Fill 100% with int's [Available items = 256]... \n";
	//Fill all possible items.
	for( int i=0; !testA.isFull(); i++ ) testA.add( new int(i) );

	cout << "::Pop all items until queue be empty...\n\nResult:\n\n";
	//Pop all items from queue.
	while ( !testA.isEmpty() ) cout << AsInt( testA.pop() ) << " ";


	//With size defined
	cout << "\n\n\nTEST B : Construction by sizeof(type)\n";
	cout << "----------------------------------------------------\n\n";

	cout << "::Initialization...\n";

	Queue testB( sizeof(int) );


	cout << "::Fill with int's (1..10)...\n";
	for (int i=1; i<=10; i++ ) testB.add( new int(i) );

	cout << "::Pop all items until queue be empty...\n\nResult:\n\n";
	while( !testB.isEmpty() ) cout << AsInt( testB.pop() ) << endl;


	
	
	//Copy Constructor TEST
	cout << "\n\nTEST C : Copy Construction\n";
	cout << "----------------------------------------------------\n\n";

	cout << "::Initialization default (A)...\n";
	Queue testC;

	cout << "::Fill (A) with int's (10..20)...\n";
	for (int i=10; i<=20; i++ ) testC.add( new int(i) );

	cout << "::Initialization (B) using copy of (A)...\n";
	Queue testD( testC );

	cout << "::Pop all items of queue (B)...\n\nResult:\n\n";
	while( !testD.isEmpty() ) cout << AsInt( testD.pop() ) << endl;

	//Operator assignment TEST
	cout << "\n\nTEST D : Assignment operation \n";
	cout << "----------------------------------------------------\n\n";

	cout << "::Initialization default (A)...\n";
	Queue testE;

	cout << "::Initialization default (B)...\n";
	Queue testF;

	cout << "::Fill (A) with int's (20..30)...\n";
	for (int i=20; i<=30; i++ ) testE.add( new int(i) );

	cout << "::Assignment of B = A...\n";
	testF = testE;

	cout << "::Pop all items until queue be empty...\n\nResult:\n\n";
	while( !testF.isEmpty() ) cout << AsInt( testF.pop() ) << endl;

	return 0;
}
