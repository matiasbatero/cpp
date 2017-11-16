/*
 * C++ Tricks (Matías Gastón Santiago)
 * 
 */


#include <iostream>
#include <list>
#include <functional>
#include <type_traits>

using namespace std;


class Object
{
	private:
	
	const type_info& typeId;
	void* data;
		
	public:
	
		
	template<typename instType >
	Object( instType instance ) : typeId( typeid(instance) ) , data( instance )
	{
	
	};
	
	const type_info& getType() const
	{
		return typeId;
	};
	
	bool sameTypeOf( const Object& object ) const
	{
		return ( typeId == object.getType() );
	};
	
	template<class T>
	const T as()
	{
		return (T&)(*(T*)data);
	};
	
	template<class T>
	bool is()
	{
		return true;		
		
	};
	
	
};



class IType
{
	public:
	
	virtual void methodA() = 0;
	virtual void methodB() = 0;
	virtual void methodC() = 0;
};

class IExtensibleType : public IType
{
	
	
	
};

extern "C" void create( Object input, ...)
{
	
};

int main()
{
	Object source = new string("Hola mundo");
	
	

	return 0;
}

