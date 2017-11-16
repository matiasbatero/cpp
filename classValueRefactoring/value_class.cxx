#include <iostream>
#include <type_traits>
#include <typeinfo>

using namespace std;

class Value
{
	private:
	
	void* instance;
	const type_info& type;
	
	public:
	
	template<typename T>
	Value( T& input ) : type(typeid(input) )
	{
	
		if ( is_pointer<T>::value )
		{
			//linea muy jodida esta.. parece un casteo inecesario pero hay que ponerlo
			instance = (T*)input;
			cout << typeid(input).name() << " " << typeid(T).name() << " (pointer) instance address " << instance << endl;
		}
		else
		{
			instance = &input;
			cout << typeid(input).name() << " " << typeid(T).name() << " (not pointer) instance address " << instance << endl;
		}

		
	}
	
	template<typename T>
	void get()
	{
		
	};
	
};

int main(int argc, char **argv,  char* envp[] )
{
	auto a = int(90);
	auto b = new int(91);
	
	void* pa = &a;
	cout << pa << endl;
	
	cout << "a address (stack) : " << &a << endl;
	cout << "b address (heap) : " << b << endl;
	
	auto aValue = Value(a);
	auto bValue = Value(b);
	
	
	return 0;
}

