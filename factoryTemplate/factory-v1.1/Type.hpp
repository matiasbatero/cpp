/* Matías Gastón Santiago:
 * 
 * TDA/TDC/Factory design & implementation
 * 
 * 29/6/2015
 *
 * Type.hpp
 *  
 */


//Interface implementation ("Concrete Type *" : TDC)
//[*] "Concrete Type" : For C++ Concrete Type its a type that can be used as a primitive type.
//In this case, it is a simplification.

#ifndef TYPE_HPP
#define TYPE_HPP

#include "IType.hpp"
#include <iostream>

class Type : public IType
{
	public:
	
	void methodA();
	void methodB();
	void methodC();
	
	
	Type(){};
		
};

//You can put the implementations in a Type.cpp file.

void Type::methodA()
{
	std::cout << "methodA" << std::endl;
};

void Type::methodB()
{
	std::cout << "methodB" << std::endl;
};

void Type::methodC()
{
	std::cout << "methodC" << std::endl;
};

#endif
