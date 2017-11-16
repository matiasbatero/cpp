#ifndef IQUEUE_HPP
#define IQUEUE_HPP

//Interfaz de uso
template < class Type >
class IQueue
{
	public:
	
	virtual bool add(const Type& item) = 0;
	
	virtual bool isEmpty() = 0;
	
	virtual bool isFull() = 0;
	
	virtual Type read() = 0;
	
	//virtual const Type& read() const = 0;
	
	virtual Type pop() = 0;
	
};




#endif
