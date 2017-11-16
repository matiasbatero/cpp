#include <iostream>

using namespace std;

class Value
{
	private:
	
	class __Value { public: };
	
	template<typename T>
	class _Value : public __Value
	{
		private:
		
		T _value;
		
		public:
		
		operator T()
		{
			return _value;
		};
		
		void get()
		{
			cout << _value << endl;
			
			//return _value;
		};
		
		_Value( T input) : _value(input){};
	};
	
	__Value _value;
	
	public:
	
	template<typename Type>
	Value( Type input ) : _value( _Value<Type>(input) )
	{
		
	};
	
	template<typename Type>
	operator Type()
	{
				
		return int(8)	;	
	};
};

class null
{

};

template<typename T>
class A : public null
{
	public:
	
	T v;
	
	A(T _v): v(_v) {};
};

int main()
{
	A<int> W = 1000;
	
	cout << W.v << endl;
	
	null& NW = W;	
	
	A<int>& jj = (A<int>&)NW;
	
	cout << jj.v << endl;
	
	
	return 0;
};
