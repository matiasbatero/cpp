/*
 * Instituto Superior de Formación Técnica 151
 * Tecnicatura Superior en Análisis de Sistemas
 * 
 * Programación II
 *  
 * Queue Project ( without parametrization )
 * Queue Variant : simple
 * 
 * Version:  Refactoring 1 (23/8/2015)
 * 		     Revision 1.1  (24/8/2015)
 * 
 * Grupo: 
 * 
 * Santiago, Matías Gastón
 * Molina Burgos, Álvaro	
 * Mato, Santiago
 * Sosa, Luis
 * 
 * 
 * File:	main.cpp (testing file)
 * 
 */ 

#include <iostream>
#include "QueueGeneric.hpp"

using namespace std;

template<class type> type cast ( void* input )
{
	return *( (type*)input );
};

template<class type> size_t $(void)
{
	return sizeof (type);
};

template<class TType> class Type
{
	operator size_t()
	{
		return sizeof(TType);
	}
};

int AsInt( void* input )
{
	return *( (int*) input );
};

//virtual int hun() =0;

int main()
{
	//Default
	cout << "TEST A : Default Queue Construction using default parameter " << endl;
	cout << "------------------------------------------------------------" << endl << endl;
	
	cout << "::Initialization..." << endl;
	Queue testA;
	
	int valueA = 0;
	
	cout << "::Fill 100% with int's [Available items = 256]... " << endl;
	//Fill all possible items.
	while ( testA.add( new int(valueA++) ) );
	
	cout << "::Pop all items until queue be empty...\n\nResult:\n " << endl;
	//Pop all items from queue.
	while ( !testA.isEmpty() ) cout << AsInt( testA.pop() ) << " ";
	
	
	//With size defined
	cout << "\n\n\nTEST B : Construction by sizeof(type) " << endl;
	cout << "------------------------------------------------------------" << endl << endl;
	
	cout << "::Initialization..." << endl;
	
	Queue testB( sizeof(int) );
	
	cout << "::Fill with int's (1..10)... " << endl;
	for (int i=1; i<=10; i++ ) testB.add( new int(i) );
	
	cout << "::Pop all items until queue be empty...\n\nResult:\n " << endl;
	while( !testB.isEmpty() ) cout << AsInt( testB.pop() ) << endl;
	
	
	//Copy Constructor TEST
	cout << "\n\nTEST C : Copy Construction " << endl;
	cout << "------------------------------------------------------------" << endl << endl;
	
	cout << "::Initialization default (A)..." << endl;
	Queue testC;
	
	cout << "::Fill (A) with int's (10..20)... " << endl;
	for (int i=10; i<=20; i++ ) testC.add( new int(i) );
	
	cout << "::Initialization (B) using copy of (A)..." << endl;
	Queue testD( testC );
	
	cout << "::Pop all items of queue (B)...\n\nResult:\n " << endl;
	while( !testD.isEmpty() ) cout << AsInt( testD.pop() ) << endl;
	
	//Operator assignment TEST
	cout << "\n\nTEST D : Assignment operation " << endl;
	cout << "------------------------------------------------------------" << endl << endl;
	
	cout << "::Initialization default (A)..." << endl;
	Queue testE;
	
	cout << "::Initialization default (B)..." << endl;
	Queue testF;
	
	cout << "::Fill (A) with int's (20..30)... " << endl;
	for (int i=20; i<=30; i++ ) testE.add( new int(i) );
	
	cout << "::Assignment of B = A... " << endl;
	testF = testE;
	
	cout << "::Pop all items until queue be empty...\n\nResult:\n " << endl;
	while( !testF.isEmpty() ) cout << AsInt( testF.pop() ) << endl;
	
	return 0;
}
