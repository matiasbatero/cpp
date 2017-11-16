#define _EXCEPTION

class _exception
{
public:
    string message = "Default exception message";

    _exception(const char* msg) : message(msg) {};
};
