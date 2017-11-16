/*
 * Example of property implementation without templates
 * 
 * Copyright 2015 Matías Gastón Santiago <matiasbatero.mdq@gmail.com>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */
#include <iostream>

using namespace std;


//Without templates (Ex: int property)
class Property
{
	private:
	
	int p_value;
	
	int get(){ return p_value; };
	void set(int value){ p_value=value; };
	
	
	public:
	
	Property() : p_value(0) { p_value = 50; };
	
	
	//Wrapper operator : Setter
	void operator =( int value ){ set(value); };
	
	//Wrapper operator : Getter
	operator int(){ return get(); };
		
};

//Parametrized Property
//

template <typename type> class PProperty
{
	private:
	
	type p_value;
	
	type get(){ return p_value; };
	void set(type value){ p_value=value; };
	
	
	public:
	
	PProperty(){};
	
	
	//Wrapper operator : Setter
	void operator =( type value ){ set(value); };
	
	//Wrapper operator : Getter
	operator type(){ return get(); };
	
	//Alternative Wrapper operator: Getter ::: 	type* operator->()
		
};


/*Notes:
 * 
 * 1. With template: It's more easy to use because the dynamic of get/set always is the same and differ only for their types.
 * 2. operator type() .. always is a secure cast, because in this case set-type is always the same type of get-type return.
 * 3. overload -> operator is an alternative, requires a return pointer-type value, so, it needs a manual derreferencing.
 * 4. This templetized property-class requires get/set values of the same type.. if you can set a type and get another this aproach is not valid.
 * 5. For the moment there is no way to avoid templates, to simplify the code. You can use macros, but they are unsafe.
 * 
 * Warnings:
 * 
 * 1. Line 43. This approach, have a '=' asignation, and there is not guarantee that any class have already defined this operator.
 *    so, it works for any C++ concrete types.
 * 
 * 2. Property is not initialized here. A default value is more better.. This requires to implement the constructor.
 *    So: (warning 1) you cannot use '=' asignations, if you don't know if the type is a concrete type.
 * 	  ¿Using initialization lists? I don't know how their work with types that are not concrete.
 *    
 * 
 * 
 */
 
class Employer
{
	public:
	
	void MakeMoney(void);
	
	Property money;
	
};

class Employer2
{
	public:
	
	void MakeMoney(void);
	
	PProperty<int> money;
};

void Employer::MakeMoney(void)
{
	cout << "Making money.. $$$" << endl;
};

void Employer2::MakeMoney(void)
{
	cout << "Making money.. $$$$$$$" << endl;
};

//--------------------------------------

int main()
{
	
	Employer* person = new Employer;
	Employer2* person2 = new Employer2;
	
	person->MakeMoney();
	person->money = 90;
	cout <<  person->money << endl;
	
	person2->MakeMoney();
	person2->money = 78;
	cout << person2->money << endl;
	
	
	
	return 0;
}

