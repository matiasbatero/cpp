/*
 * Value Class Prototype Experiment
 *  
 * Copyright 2016 Matías Gastón Santiago <matiasbatero.mdq@gmail.com>
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
#include <typeinfo>

using namespace std;

class AnyCastException
{
	public:
	AnyCastException(const char* name, int line, const char* file)
	{
		cout << "Exception :: '" << name << "' expected at line " << line << " :: [" << file <<"]" <<  endl;
	};
	
	AnyCastException()
	{
		cout << "Exception :: Requested type is not accessible from 'Any' object" <<  endl;

	};
};

class value
{
	private:
	
	struct INull { virtual ~INull() = default; };
	
	template<class T>
	struct Null : public INull
	{
		const T v;
		
		Null(T in): v(in) {};
		
		virtual ~Null() = default;
	};
	
	INull* k;
		
	public:
	
	virtual ~value(){ delete k; };
	
	template<typename Type>
	value(Type input) : k(new Null<Type>(input))
	{
			
	};
	
	template<typename Type>
	operator Type()
	{
		auto ptr = dynamic_cast< Null<Type>* >(k);		
		return (ptr)? ptr->v : throw AnyCastException();
	};
	
	template<typename Type>
	Type as()
	{
		auto ptr = dynamic_cast< Null<Type>* >(k);	
		return (ptr)? ptr->v : throw AnyCastException();
		
	};
};



template<typename Type>
Type _adquire( value input, const char* name, int line, const char* file )
{
	try
	{
		return input;
	}
	catch (const char* message)
	{
		cout << message << " '" << name << "' expected at line " << line << " :: [" << file <<"]" <<  endl;
		return Type();
	};
};

#define adquire(Type, source ) _adquire<Type>(source, #Type, __LINE__, __FILE__ )

//#define as(x) as<x>()

class A
{
	public:
	virtual void a() = 0;
};

class AA : public A
{
	public:
	virtual void a(){ cout << "aa" << endl;};
};

value f( value input )
{
	A* b = input;
	b->a();
	
	return string("chau");
}



int main()
{
	string d = f( (A*)new AA );
	
	cout << sizeof(value) << endl;
	
	return 0;
};
