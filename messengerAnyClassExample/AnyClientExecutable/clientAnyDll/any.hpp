#include <iostream>
#include <typeinfo>
#include <cstring>

/*R1/R2 50%
R3.1 a R3.3 30%
R3.4 20% */

using namespace std;

class any
{
	private:

	class INull { public: virtual ~INull() = default; };

	template<typename Type>
	struct Null : public INull
	{
		virtual ~Null() = default;
	};

	INull* object;
	int size;

	public:

	template<typename Type>
	any( Type input ) : size( sizeof(Type) )
	{
		object = new Null<Type>();
	}

	template<typename Type>
	void cast()
	{
		( dynamic_cast< Null<Type>* >(object) )? cout << "true" : cout << "false";
	}

};


