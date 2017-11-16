#include <iostream>
#include <typeinfo>

using namespace std;

class ex
{
	private:
	
	class NullInterface{};
	
	template<class Type>
	class TypedVar : NullInterface
	{
		public:
		
		Type& instance;
		
		TypedVar(Type input): instance(input) {};
	};
		
	static NullInterface& ninstance;
	
	public:
	
	//template<typename Type>
	//ex(Type input) : 
	
};

class value
{
	private:
	
	struct _null_ { virtual ~_null_() = default; };
	
	template<class T>
	struct tvalue : public _null_
	{
		T v;
		
		tvalue(T in): v(in) {};
		
		virtual ~tvalue() = default;
	};
	
	_null_* k;
	const type_info& type;	
		
	public:
	
	template<typename Type>
	value(Type input) : type( typeid(input) )
	{
		k = new tvalue<Type>(input);		
	};
	
	template<typename Type>
	operator Type()
	{
		return ( type == typeid( ((tvalue<Type>*)k)->v ) )? ((tvalue<Type>*)k)->v : throw "error:";
	};
	
	template<typename Type>
	Type as()
	{
		try
		{
			return ( type == typeid( ((tvalue<Type>*)k)->v ) )? ((tvalue<Type>*)k)->v : throw "error:";	
		}
		catch (const char* message)
		{
			cout << message << endl;
			return Type();
		};
	};
	
	template<typename Type>
	value operator()(Type arg)
	{
		//if arg is primitive types.... pass directly.. if not.. all can be processed as value type.
		return value(arg);
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

#define as(x) as<x>()

class Something
{
	public:
	
	void doSomething( value aText )
	{
		//adquire parameters
		auto a = adquire(int, aText);
		
		//decapsulation of type
		cout << a << endl;
		
	};
	
	
};

class other : value
{
	
	public:
	
	void otherAction()
	{
		cout << "other Action method" << endl;
	}
	
	other():value(this) {};	
	
};


class other2 : value
{
	
	public:
	
	void otherActions()
	{
		cout << "other Action method!!!!" << endl;
	}
	
	other2():value(this) {};	
	
};


void func( value a)
{
	a.as(other).otherAction();

};

class other3 : value
{
	public:
	
	value methodA;
	value methodB;
	
	
	other3(value a, value b ):
	value(this), methodA(a), methodB(b)
	
	{};
};

int main()
{
		
	Something anExample;
	
	//encapsulation of type
	value aText = string("Testing...");
	
	list<int> hk;
	value a = hk ;
	anExample.doSomething( aText );
	
	other obj;
	other2 obj2;
	
	obj.otherAction();
	
	func( obj );
	
	other3 Obj( obj, obj2 );
	
	Obj.methodA.as(other).otherAction();
	Obj.methodB.as(other2).otherActions();
	
	value obj3 = anExample;
	
	value h = obj3(6.98798);
	
	//cout << h.as(float) << endl;
	
	return 0;
};
