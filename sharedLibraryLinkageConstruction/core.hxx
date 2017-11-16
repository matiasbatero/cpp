#ifndef CORE_HXX
#define CORE_HXX

#include <iostream>

using namespace std;

typedef int64_t ClassTypeID;
typedef int64_t ClassObjectID;

struct ClassHandler;


struct ClassObject
{
	ClassObjectID id;
	const ClassHandler* classHandler;
	int refCounter;
};

typedef ClassObjectID(*ObjectConstructor)();
typedef void (*ObjectDestructor)(ClassObjectID);

struct ClassHandler
{
	ObjectConstructor construct;
	ObjectDestructor  destruct;
};



#endif
