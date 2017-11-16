/*
 * C++ Tricks (Matías Gastón Santiago)
 * 
 */


#include <iostream>
#include <list>
#include <functional>
#include <type_traits>

using namespace std;

// Substitution Failure is not a error example 1.

class IsAPointer
{
	private:
	
	template <class U>
	char is_ptr( U* )
	{
		return 'a';
	}

	template <class X, class Y>
	char is_ptr(Y X::*){ return 'a'; }

	template <class U>
	char is_ptr( U (*)() ){ return 'a'; }

	private: double is_ptr(...){ return 0; }

		
	public:
	
	bool value;	
	
	template<typename Type>
	IsAPointer( Type obj )
	{
		( sizeof(is_ptr(obj)) == sizeof(char) )? value = true : value = false;
	};
	
	operator bool()
	{
		return value;
	};
	
};


class Object
{
	private:
	
	void* rep;
	const type_info& typeId;
	

	public:
	
			
	template<typename Type>
	Object(Type instance) : rep( (void*)(Type)instance ), typeId( typeid(instance) )
	{
		
	};
	
	
	virtual Object& getRef(){ return *this; };
	//template<typename Type> //seems to return void* as operator.
	//operator Type()
	//{	
		//return (Type)rep;			
	//};
	
	
	template<class Type>
	bool is()
	{
		Type typePtr;
		return ( typeid(typePtr) == typeId );		
	};
	
	const type_info& getType() const
	{
		return typeId;
	};
	
	bool sameTypeOf( const Object& object ) const
	{
		return ( typeId == object.getType() );
	};
	
	template<class Type>
	Type getInstance() const
	{
		return (Type)rep;
	};
	
	//addref
	//release
	
};



class ObjectMessage
{
	public:
	
			
	template<typename Type>
	ObjectMessage(Type instance)
	{
		cout << typeid(instance).name() << endl;
	};
	
	
		
};

class MyClass
{
	private:
	
	int		_number;
	string  _text;
	
	void printSomeNumber(){ cout << rand() << endl; };
	void shutdownApp(){ cout << "shutdown app!" << endl; };
	int printNumber(){ cout << _number << endl; return 0; };
	void printString(){ cout << _text << endl; };
	
	
	public:
	

	MyClass( int number, string text ): _number(number), _text(text) 
	{
		
	};
	
	void operator[]( ObjectMessage msj )
	{
	
	};
	
	//auto printNumber = std::mem_fn(&MyClass::printNumber);
};

template<class U = int>
class Test
{ };

template<typename ObjectType>
class TObject
{
	private:
	
	ObjectType* instance;	

	
	public:
	
	TObject( const Object& object ) : instance( object.getInstance<ObjectType*>() )
	{

		//cout << object.getType().name() << endl;

	};
	
	operator ObjectType*()
	{
		return instance;
	};
	
	

};

struct Foo {
    void display_greeting() {
        std::cout << "Hello, world.\n";
    }
    void display_number(int i) {
        std::cout << "number: " << i << '\n';
    }
    int data = 7;
};

//messages
typedef Test<> Obj;


int main()
{
	//Substituion failure is not a error.
	//( IsAPointer(new int) )? cout << "yes!" : cout << "no!";
	ObjectMessage run = &Foo::display_greeting;
	
	MyClass objA(1, "hola");
	
	objA[ run ];
	
	
	//MyClass* ask = TObject<MyClass>(objA); //Fija tipo para usar.
	
	//ask->printSomeNumber();	
	
	//SObject k = new MyClass(1, "ww");
	

	
	return 0;
}

