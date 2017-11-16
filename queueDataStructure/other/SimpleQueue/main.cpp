#include <iostream>
#include "Queue.hpp"

using namespace std;



int main()
{
	Queue<int> test;
	
	cout << "Adding [0..10] int's to queue..." << endl;
	
	for (int i=1; i<=10; i++) test.add(i);
	
	
	cout << "Show element from queue..." << endl;
	cout << "first: " << test.read() << endl;
	
	cout << "\nShow all elements of the queue.." << endl;
	while( !test.isEmpty() ) { cout << "first: " << test.pop() << endl; };
	
	//cout << "\nAgain, show element from queue..." << endl;
	//cout << "first: " << test.get() << endl; //show error, because all is removed.
	
	cout << "\nAdding a new element.." << endl;
	test.add(10);
	cout << "first: " << test.read() << endl;
	
	return 0;
}
