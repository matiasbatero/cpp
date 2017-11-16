#include <iostream>
#include <typeinfo>

using namespace std;


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



int main()
{
	Something anExample;
	
	//encapsulation of type
	value aText = string("Testing...");
	
	anExample.doSomething( aText );
	
	
	
	
	
	return 0;
};
