#ifndef IQUEUE_HPP
#define IQUEUE_HPP

//Interfaz de uso
class IQueue
{
	public:
	
	virtual bool add(void* item) = 0;
	
	virtual bool isEmpty() = 0;
	
	virtual bool isFull() = 0;
	
	virtual void* read() = 0;
	
	virtual void* pop() = 0;
	
};




#endif
