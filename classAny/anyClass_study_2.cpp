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
#include <cassert>
#include <typeinfo>
#include <list>
#include <type_traits>


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

class Any
{
    private:
    
    class INull
    {
        public:
        virtual ~INull() = default;
    };

    template<typename T>
    class Null : public INull
    {
        private:
        
        T* instance;

        public:
        virtual ~Null() = default;
        Null( T* input ) : instance(input)
        { 

		};

        operator T()
        {
            return *instance;
        }
    };

    INull* object;

public:

    virtual ~Any()
    { 
		cout << "destructor" << endl;
		delete object;		
	};

    template<typename T>
    Any( T input ) : object( new Null<T>(&input) )
    {
		cout << "constructor parameter " << typeid(input).name() << endl;
    }
	
		
	Any( const Any& input ) 
	{
		cout << "copy constructor " << typeid(input).name() << endl;
		object = input.object;
		
	};
	
	template<typename T>
    operator T()
    {
		cout << "requested type " << typeid(T).name() << endl;
		
        auto ptr = ( Null<T>* )(object);        
        return (ptr)? *ptr : throw AnyCastException();
			
    }
	
	template<typename T>
	T as( const char* name, int line, const char* file )
	{
		cout << "requested type " << typeid(T).name() << endl;

		auto ptr = ( Null<T>* )(object);
        
        return (ptr)? *ptr : 
			throw AnyCastException(name,line,file);
		
	}
    
    template<typename T>
    void operator =(T input)
    {
		delete object;
		object = new Null<T>(&input); 
	};
};

#define as(Type ) as<Type>( #Type, __LINE__, __FILE__ )


Any printThis( Any a )
{
	cout << a.as(const char*) << endl;
	
	return Any(8);
};

int main()
{
    Any a = string("hola");
    
    string b = a;
    
    cout << b << endl;
    
    
    
	
	return 0;
};
