#ifndef TYPE_SO_X_CXX
#define TYPE_SO_X_CXX

#include "core.hxx"

/* default delegation */


extern "C"
{
	ClassHandler self();
	
	ClassHandler type()
	{
		return self();	
	}
}

#endif
