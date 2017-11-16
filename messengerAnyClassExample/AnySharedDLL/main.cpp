#include "any.hpp"
#include <iostream>

using namespace std;

extern "C" any create()
{
    return new int(999);
}
