#ifndef DYNAMIC_LOADER_H
#define DYNAMIC_LOADER_H

#include <dlfcn.h>

class Loader
{
    private:

    void* handler;

    public:

    Loader(const char* src ) : handler( dlopen(src, RTLD_NOW ))
    {

    }
	
	void* getFunction( const char* func )
    {
        return dlsym( handler, func);
    }

    ~Loader(){ dlclose(handler); }

};

#endif
