#include "../../Any/Any.hpp"

class IMessenger : public Any
{
    public:

    virtual void say(const std::string& input) = 0;
    virtual ~IMessenger() = default;
};
