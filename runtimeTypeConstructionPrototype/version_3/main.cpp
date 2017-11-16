#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

using namespace std;

//application status code
#define ERROR_UNIMPLEMENTED     501
#define ERROR_INTERNAL_ERROR    500
#define SUCESS_OK               200
#define SUCESS_NO_CONTENT       204
#define NULL_INSTANCE_ID 0
#define NULL_ACTION_ID 0
#define UNDEFINED_ERROR_ID -1

 bool is_a_list_of_strings(int);

int request_handler_for_list_of_strings( int my_instance, int action_id )
{
    int response_code = ERROR_INTERNAL_ERROR;

    list<string>* instance = 0;

    if ( is_a_list_of_strings( my_instance ) )
        instance = (list<string>*) my_instance;


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

                instance->push_back(stringToSave);
                response_code = SUCESS_OK;
            }

            break;

        //request(pop) without data passing and no response
        case POP :

            instance->pop_back();
            response_code = SUCESS_NO_CONTENT;

            break;

        //request(peek_back) without passing data and data response
        case PEEK_BACK :

            cout << "output: " << (string)instance->back() << endl;
            response_code = SUCESS_OK;

            break;

        default :

            cout << "unrecognizable action_id" << endl;
            response_code = ERROR_UNIMPLEMENTED;

            break;

    }

    return response_code;
}

vector<int> list_of_strings_export;

bool is_a_list_of_strings( int id )
{
        return SUCESS_OK;
}

int create_local_list_of_strings( int& target_id )
{
     void* ptr = new list<string>;
     target_id = (int)ptr;

     return SUCESS_OK;
}

int selected_instance_id = NULL_INSTANCE_ID;
int action_id = NULL_ACTION_ID;
int my_instance_id = NULL_INSTANCE_ID;
int response_code = UNDEFINED_ERROR_ID;

int select_instance()
{
    cout << "[current available system objects]" << endl;
    cout << "objectID : " << my_instance_id << endl <<endl;
    cout << "select [objectID]: ";
    cin >> selected_instance_id;

    return SUCESS_OK;
}

int request_action()
{
     cout << "request [actionID]: ";
    cin >> action_id;
    cout << endl;

    cout << "requested [ actionID : " << action_id << " ]  to selected [ objectID : " << selected_instance_id << endl;

    return request_handler_for_list_of_strings( my_instance_id, action_id );
}

int main()
{
    create_local_list_of_strings( my_instance_id );
    list_of_strings_export.push_back( my_instance_id );

    select_instance();

    return request_action();
}
