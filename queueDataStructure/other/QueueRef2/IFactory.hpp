#ifndef IFACTORY_HPP
#define IFACTORY_HPP

class IFactory
{
	public:
	
	virtual void* build() = 0;
	virtual int getSize() = 0;
};

#endif
