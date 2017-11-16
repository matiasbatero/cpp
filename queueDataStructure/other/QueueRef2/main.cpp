#include <iostream>
#include "QueueGeneric.hpp"

using namespace std;

int AsInt( void* input )
{
	return *( (int*) input );
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
	
	//while( !testB.isEmpty() ) cout << AsInt( testB.pop() ) << endl;
	
	
	//Other Queue construction
	
	Queue testC( testB );
	while( !testC.isEmpty() ) cout << AsInt( testC.pop() ) << endl;
	
	return 0;
}
