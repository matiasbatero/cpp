/*
 * Any Class Prototype Experiment
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
#include <cstring>

using namespace std;

class Interface
{
	public:
	
	virtual void someFunction() = 0;
};

class Implementation : public Interface
{
	private:
	double a;
	
	public:
	
	Implementation(){ cout << "ctor" << endl; };
	Implementation( const Implementation& input ){ cout << "cctor" << endl; };
	Implementation( const Implementation* input ){ cout << "pctor" << endl; };
	~Implementation(){ cout << "dtor" << endl; };
	
	virtual void someFunction()
	{
		a = 100.0;
		cout << "number is " << a << endl;
	};
};

void badCast()
{
	cout << "Error : Expected type not found" << endl;
};

class anyException
{
	typedef void(*ExceptionMessage)();
	
	public:
	
	anyException( ExceptionMessage message )
	{
		message();
	}
};

class any
{
	private:
	
	class INull { public: virtual ~INull() = default; };
	
	template<typename Type>
	struct Null : public INull
	{
		Type data;
		
		Null( const Type& input )
		{
			memcpy( &data, &input, sizeof(Type) );
		};
		
		~Null(){ cout << "null dtor" << endl; }
	};
	
	INull* object;
		
	public:
	
	template<typename Type>
	any( const Type& input )
	{
		object = new Null<Type>(input);
	}
	
	template<typename Type>
	operator Type()
	{
		auto valid = dynamic_cast< Null<Type>* >(object);		
		return (valid)? valid->data : throw anyException( badCast );
	}
	
	template<typename Type>
	Type as()
	{
		auto valid = dynamic_cast< Null<Type>* >(object);		
		return (valid)? valid->data : throw anyException( badCast );
	}
	
	~any()
	{
		cout << "any dtor" << endl;
		delete object;
	}
	
};

Interface* buildObject()
{
	return new Implementation;
};


int main()
{
	any aNumber = buildObject();
	
	Interface* other = aNumber.as<Interface*>();
	other->someFunction();
	
	
	
	return 0;
};

