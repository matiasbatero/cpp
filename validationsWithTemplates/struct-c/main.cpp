#include <iostream>
#include "simple_exception.h"
#include "validations.h"
#include "requeriments.h"

using namespace std;


void printNumber( requires<int, printNumberRules> value )
{
    cout << "<int>" << value << "</int>" << endl;
}




int main()
{
    try
    {
        cout << "Ingrese un numero valido" << endl;

        int number;

        cin >> number;

        printNumber(number);
    }
    catch (_exception e)
    {
        cout << e.message << endl;
    }

    int a;
    cin >> a;
    return 0;
}
