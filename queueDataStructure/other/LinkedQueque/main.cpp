#include <iostream>
#include <string>
#include "QueueGeneric.hpp"
#include "ISizable.hpp"

using namespace std;

class MyType : public ISizable
{
	public:
	
	typedef int type;
	
	
};


int AsInt( void* input )
{
	return *( (int*) input );
};

string AsString( void* input )
{
	return *( (string*) input );
};

int main()
{
	//Default
	cout << "Default sized Queue TEST " << endl;
	Queue testA;
	
	int valueA = 0;
	
	//Fill all possible items.
	while ( testA.add( new int(++valueA) ) );
	
	//Pop all items from queue.
	while ( !testA.isEmpty() ) cout << AsInt( testA.pop() ) << endl;
	
	
	//With size defined
	cout << "\n\nUser-Defined size Queue TEST" << endl;
	
	Queue testB( sizeof(int) );
	
	for (int i=1; i<=10; i++ ) testB.add( new int(i) );
	
	while( !testB.isEmpty() ) cout << AsInt( testB.pop() ) << endl;
	
	//Testing with other types
	//cout << "\n\nTesting with other types" << endl;
	
	//Queue testC( new string("Hola") );
	
	//testC.add( new string("Chau") );
	
	//cout << AsString( testC.pop() ) << endl;
	//cout << AsString( testC.pop() ) << endl;
	
	
	return 0;
}
