#include <iostream>
#include <list>

using namespace std;

//application status code
#define ERROR_UNIMPLEMENTED     501
#define ERROR_INTERNAL_ERROR    500
#define SUCESS_OK               200
#define SUCESS_NO_CONTENT       204

int request_handler_for_list_of_strings( list<string>& instance, int action_id )
{
    int response_code = ERROR_INTERNAL_ERROR;

    enum
    {
        PUSH = 1,
        POP = 2,
        PEEK_BACK = 3
    };

    switch( action_id )
    {
        //request(push) with data passing and no response
        case PUSH :

            {
                string stringToSave;
                cout << "expected [string]: " ;
                cin >> stringToSave;
                cout << endl << endl;

                instance.push_back(stringToSave);
                response_code = SUCESS_OK;
            }

            break;

        //request(pop) without data passing and no response
        case POP :

            instance.pop_back();
            response_code = SUCESS_NO_CONTENT;

            break;

        //request(peek_back) without passing data and data response
        case PEEK_BACK :

            cout << "output: " << (string)instance.back() << endl;
            response_code = SUCESS_OK;

            break;

        default :

            cout << "unrecognizable action_id" << endl;
            response_code = ERROR_UNIMPLEMENTED;

            break;

    }

    return response_code;
}



int extended_handler_for_list_of_strings( list<string>& instance, int action_id )
{
    return ERROR_UNIMPLEMENTED;
}


int main()
{
    list<string> instance;

    int action_id = 0;
    int response_code = ERROR_INTERNAL_ERROR;

    cout << "list_of_strings" << endl << endl;
    cout << "action_id = 1 :: push" << endl;
    cout << "action_id = 2 :: pop" << endl;
    cout << "action_id = ? :: <invalid>" << endl << endl;

    //request
    cout << "do: ";
    cin >> action_id;
    cout << endl;

    cout << "requested action_id:" << action_id << " over: list_of_strings" << endl;

    response_code = request_handler_for_list_of_strings( instance, action_id );

    if ( response_code == ERROR_UNIMPLEMENTED )
    {
        response_code = extended_handler_for_list_of_strings( instance, action_id );
    }

    cout << "status code -> " << response_code << endl;

    return 0;
}
