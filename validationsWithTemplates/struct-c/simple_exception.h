#define _EXCEPTION
#include <iostream>

using namespace std;

class _exception
{
public:
    string message = "Default exception message";

    _exception(string msg) : message(msg) {};
};
