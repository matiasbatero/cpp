#include <iostream>
#include <list>

using namespace std;

int main()
{
    list<string> list_of_strings;

    do
    {
        int option = 1;

        cout << "1. push string" << endl;
        cout << "2. pop string" << endl;
        cout << "any other : invalid" << endl << endl;

        cin >> option;

        switch( option )
        {
            case 1 :
                {
                    string stringToSave;
                    cout << "write your string: " << endl;
                    cin >> stringToSave;
                    list_of_strings.push_back(stringToSave);
                }
                break;

            case 2 :
                cout << (string)list_of_strings.back() << endl;
                break;

            default :
                cout << "cannot execute that message" << endl;
                break;

        }

    } while( option != 0 );


    return 0;
}
