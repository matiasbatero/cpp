/* Matías Gastón Santiago:
 * 
 * TDA/TDC/Factory design & implementation V 1.00
 * 
 * 29/6/2015
 * 
 */

#include "IType.hpp"
#include "IFactory.hpp"

//Here in main, you only know about interfaces and factories to create objects.

int main()
{
	IType* test = Factory<IType>::get();
	
	test->methodA();
	test->methodB();
	test->methodC();
	
	return 0;
};
