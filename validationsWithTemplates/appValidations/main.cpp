#include <string>
#include <sstream>
#include <iostream>
#include "../struct-c/simple_exception.h"
#include "../struct-c/validations.h"

using namespace std;

static void biggerThanFour(const int& value )
    {
       if ( !(value > 4) ) throw _exception( string("Se requiere un numero mayor que 4.") );
    }

    static void between(const int& value, int limit_low, int limit_high )
    {
       if ( !( (value > limit_low )&&(value<limit_high) ) ) throw _exception( string("El numero debe estar comprendido en el rango ( 100 y 200 )") );
    }

extern "C"
{
    void printNumberRules( const int& in )
    {
        biggerThanFour(in);
        between(in, 100, 200);
    }

}

//
//
//extern "C" DLL_EXPORT BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
//{
//    switch (fdwReason)
//    {
//        case DLL_PROCESS_ATTACH:
//            // attach to process
//            // return FALSE to fail DLL load
//            break;
//
//        case DLL_PROCESS_DETACH:
//            // detach from process
//            break;
//
//        case DLL_THREAD_ATTACH:
//            // attach to thread
//            break;
//
//        case DLL_THREAD_DETACH:
//            // detach from thread
//            break;
//    }
//    return TRUE; // succesful
//}
