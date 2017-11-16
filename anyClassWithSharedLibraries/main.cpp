/* Any class across DLL boundary
 * Study and Code in progress
 * 
 * Matías Gastón Santiago
 * 
 */

#include <iostream>
#include "./src/any.hpp"
#include "./src/loader.hpp"

using namespace std;

typedef any(*Creator)(void);	

int main()
{
	Loader someDLL("./someSharedObject");
	auto create = (Creator)someDLL.getFunction("create");
	
	string* aMessage = create();
	
	cout << "The message is: " << *aMessage << endl;
	
	return 0;
};
