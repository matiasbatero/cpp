/* Any class across DLL boundary
 * Study and Code in progress
 * 
 * Matías Gastón Santiago
 * 
 */

#ifndef ANY_HPP
#define ANY_HPP

#include <iostream>
#include <cstring>

class anyException
{
	typedef void(*ExceptionMessage)();
	ExceptionMessage message;
	
	public:
	
	anyException( ExceptionMessage _message ) : message(_message)
	{
	
	}
	
	void what() const
	{
		message();
	}
};

void badCast()
{
	std::cout << "Error : Expected type not found" << std::endl;
};

class any
{
	private:
	
	class INull
	{
		public: 
		
		virtual ~INull() = default; 
	};
	
	template<typename Type>
	class Null : public INull
	{
		public:
		
		Type data;
		
		Null( const Type& input )
		{
			memcpy( &data, &input, sizeof(Type) );
		};
		
		~Null()
		{ 
			//cout << "null dtor" << endl;
		}
	};
	
	INull* object;
		
	public:
	
	template<typename Type>
	any( const Type& input )
	{
		object = new Null<Type>(input);
	}
	
	template<typename Type>
	operator Type()
	{
		auto valid = dynamic_cast< Null<Type>* >(object);		
		return (valid)? valid->data : throw anyException( badCast );
	}
	
	~any()
	{
		//cout << "any dtor" << endl;
		delete object;
	}
	
};

#endif
