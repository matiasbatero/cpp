/*
 * C++11 Object Model (Version 1.0)
 * Autor: Matías Gastón Santiago
 * 
 * Copyright 2017 matt <matiasbatero.mdq@gmail.com>
 * 
 * This program is not free software; you can't redistribute it and/or modify
 * it under the terms of the creator, but you can try win some money and redirect 
 * to the creator of this fucking inefficient class if you write some a(d)allocator
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

class object
{
	public:
	
	class ObjectInterfaceException
	{
		public:
		
		ObjectInterfaceException( )
		{
			cout << "Instance does not conform the required interface [FAIL] " << endl;
			abort();
		};
	};
		
	class IEncapsulator
	{ 
		public:
		
		virtual ~IEncapsulator() = default; 
	};
	
	template<class EncapsulatedType>
	class encapsulator : public IEncapsulator
	{
		public:
		
		EncapsulatedType& ptr_reference;
		
		encapsulator(EncapsulatedType& in): ptr_reference(in)
		{ 
			cout << "        |--> The instance implements the \"" << typeid(EncapsulatedType).name() << "\" interface! " << endl;
		};
		
		virtual ~encapsulator()
		{
			cout << " |--> Automatic destruction of 'object.delegator' requested" << endl;
			
			delete &ptr_reference;
			
			cout << "       |--> 'object.delegator' is destroyed " << endl;
		};
	};
	
	IEncapsulator* encapsulated_instance;
	
	int refcount;
	void* instance;
	const type_info& typeID;
		
	
	template<typename TypeInterface>
	object( TypeInterface constructor ) : refcount(0), typeID( typeid( decltype( *constructor() ) ) ) 
	{
		cout << "[*] Passing object constructor" << endl;
		cout << " |--> " << "Expects for a instance that verify the \"" << typeID.name() << "\" interface" << endl; 			

		encapsulated_instance = new encapsulator< decltype( *constructor() ) >( *constructor() );	
		
		cout << "           |--> Incrementing reference counter from 0 to 1" << endl; 
		refcount++;
		cout << "           |--> Instance is ready for use! [READY]" << endl;
	};
	
	object( object& obj ) : refcount( obj.refcount ), instance( obj.instance ), typeID( obj.typeID )
	{
		cout << endl << "[*] Object is passed [IN] to function/object" << endl;
		cout << " |--> Incrementing reference counter from " << refcount << " to ";
		
		refcount++;
				
		cout << refcount << endl << endl;
		
		encapsulated_instance = obj.encapsulated_instance;
	};
	
	template<typename ExpectedInterface>
	ExpectedInterface& as()
	{
		cout << "[*] Requesting instance to be used through \"" << typeid(ExpectedInterface).name() << "\" interface" << endl;
		
		static ExpectedInterface* ptr = 0;
		static ExpectedInterface& ref = *ptr;
		
		
		cout << " |--> Checking if required interface is supplied by instance..." << endl << endl;
			
		if ( typeid(ExpectedInterface) == typeID )
		{
			return (dynamic_cast< encapsulator<ExpectedInterface&>* >( encapsulated_instance ) )->ptr_reference;
		}
		else
		{
			throw ObjectInterfaceException();
			return ref;
		}
		
		

	};
	
	
	~object()
	{
		cout << endl << "[*] Object is passed [OUT] from function/object" << endl;

		cout << " |--> Decrementing reference counter from " << refcount << " to ";
		
		refcount--;
		
		cout << refcount << endl << endl;
		
		if ( refcount == 0 )
		{
			cout << "[*] Automatic destruction of 'object' requested by counter = 0" << endl;
			
			delete encapsulated_instance;
			
			cout << "       |--> 'object' is destroyed " << endl;
		};
		

	};
};

class List
{
	public:
	
	virtual void add() = 0;
	virtual void insert() = 0;
	virtual void pop() = 0;
	
	virtual ~List() = default;
};

class Vector
{
	public:
	
	virtual void add() = 0;
	
	virtual ~Vector() = default;
};

List* staticList()
{
	class _staticList : public List
	{
		public:
		
		virtual void add()
		{ 
			cout << "'static-list object' says :: add method executed!" << endl;
		};
		
		virtual void pop()
		{ 
			cout << "'static-list object' says :: pop method executed!" << endl;
		};
		
		virtual void insert()
		{ 
			cout << "'static-list object' says :: insert method executed!" << endl;
		};
		
		_staticList()
		{
			cout << "     |--> (Executing constructor): Building static-list concretion instance" << endl;
		};
		
		virtual ~_staticList()
		{
			cout << "    |--> Invoking destructor of 'static-list' instance" << endl; 
			cout << "       |--> 'static-list' instance destroyed" << endl;
		};
	};
	
	return new _staticList;
};


void someFunction( object K )
{
	
	
};



int main()
{ 
	cout << "(1) Instantation process..." << endl << endl;
	
	object anObject( staticList );	
	
	cout << endl << endl;
	cout << "(2) [START] Code section " << endl;
	
	anObject.as<List>().add();
	someFunction( anObject );
	
	cout << endl << endl;
	cout << "(3) [END] Code section " << endl << endl; 

	
	return 0;
};
