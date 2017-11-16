#ifndef TYPE_SO_1_CXX
#define TYPE_SO_1_CXX

#include "core.hxx"

/* this type extends type.0 */

static ClassObjectID constructor()
{
	return (ClassObjectID) new std::string();
};

static void destructor( ClassObjectID objectToDestroy )
{
	if ( objectToDestroy != 0 )
		delete ( std::string* ) objectToDestroy;
};


extern "C"
{
	ClassHandler self()
	{
		cout << "loaded type v 1.0 " << endl;
		return { constructor, destructor };	
	}
}

#endif
