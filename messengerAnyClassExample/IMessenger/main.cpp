#include <iostream>
#include "../../Any/Any.hpp"
#include "IMessenger.hpp"

class BinaryInterface : public Any
{
    public:

    virtual Any* build()
    {

    }
}

class SomeMessenger : public IMessenger
{
    public:

    virtual void say( const std::string& input )
    {
        std::cout << "Hi i'm SomeMessenger object and my msg is : " << input << std::endl;
    }

};

extern "C"
