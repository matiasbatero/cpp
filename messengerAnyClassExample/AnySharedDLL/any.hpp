#include <iostream>
#include <typeinfo>
#include <cstring>

using namespace std;

class any
{
	private:

	class INull { public: virtual ~INull() = default; };

	template<typename Type>
	struct Null : public INull
	{
		Type object;

		virtual ~Null() = default;

		Null(void* input )
		{
            memcpy( &object, input, sizeof(Type) );
		}

	};

	INull* object;

	public:

	template<typename Type>
	any( const Type& input ) : object( new Null<Type>(&input) )
	{

	}

	template<typename Type>
	void cast()
	{
		( dynamic_cast< Null<Type>* >(object) )? cout << "true" : cout << "false";
	}

};
