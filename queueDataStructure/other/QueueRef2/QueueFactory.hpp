#ifndef FACTORY_IQUEUE_HPP
#define FACTORY_IQUEUE_HPP

//Interface TDA
#include "IFactory.hpp"
#include "IQueue.hpp"

//Concretion TDC
#include "QueueGeneric.hpp"

class QueueFactory : IFactory
{
	public:
	
	virtual void* build(){ return new Queue ;}
	
	virtual size_t getSize(){ return sizeof(Queue); };

};

#endif
