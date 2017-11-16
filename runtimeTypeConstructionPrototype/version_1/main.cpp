#include <iostream>
#include <list>

using namespace std;

int main()
{
    list<string> list_of_strings;

    int action_id = 0;

    do
    {

        cout << "list_of_strings" << endl << endl;
        cout << "action_id = 1 :: push" << endl;
        cout << "action_id = 2 :: pop" << endl;
        cout << "action_id = ? :: <invalid>" << endl << endl;

        cout << "do: ";
        cin >> action_id;
        cout << endl;

        cout << "requested action_id:" << action_id << " over: list_of_strings" << endl;

        switch( action_id )
        {
            case 1 :
                {
                    string stringToSave;
                    cout << "input: " ;
                    cin >> stringToSave;
                    cout << endl << endl;

                    list_of_strings.push_back(stringToSave);
                }
                break;

            case 2 :
                cout << "output: " << (string)list_of_strings.back() << endl;
                list_of_strings.pop_back();
                break;

            default :
                cout << "unrecognizable action_id. try again." << endl;
                cout << "do: ";
                cin >> action_id;
                cout << endl;
                cout << "requested action_id:" << action_id << " over: list_of_strings" << endl;

                break;

        }

    } while( action_id >= 0 );


    return 0;
}
