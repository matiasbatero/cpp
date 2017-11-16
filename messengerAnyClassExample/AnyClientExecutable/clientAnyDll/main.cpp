#include <iostream>
#include "../../AnySharedDLL/any.hpp"
#include <dlfcn.h>

using namespace std;

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

class IExample
{
public:
virtual void print() = 0;

};

class example : public IExample
{
public:
virtual void print(){ cout << "print!" << endl;};
};

int main()
{
    auto dll = Loader("/home/matt/C++/IMessenger/AnySharedDLL/bin/Debug/libAnySharedDLL.so");
    void* func = dll.getFunction("create");

    typedef any(*funcCreate)(void);

    auto K = (funcCreate)func;

    //------------------
    //any t = new int(2999);

    return 0;
}
