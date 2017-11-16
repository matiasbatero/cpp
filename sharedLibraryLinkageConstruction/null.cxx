#ifndef NULL_SO_0_CXX
#define NULL_SO_0_CXX

#include "core.hxx"


static ClassObjectID constructor()
{
	return 0;
};

static void destructor( ClassObjectID objectToDestroy )
{
	
};


extern "C"
{
	ClassHandler null()
	{
		return { constructor, destructor };	
	}
}


#endif
