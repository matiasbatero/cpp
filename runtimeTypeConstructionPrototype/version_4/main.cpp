#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <windows.h>

using namespace std;



struct object;
struct type;
struct typeInformation;

typedef  int (*adquirer)(void);
typedef  int (*releaser)(int);
typedef  int (*handler)(int, int);
typedef typeInformation(*descriptor)(void);

struct typeInformation
{
       int id;
       handler instanceHandler;
       adquirer instanceAdquirer;
       releaser instanceReleaser;
};

struct type
{
    private:

    static vector<typeInformation> registeredTypes;

    public:

    static int registerType( typeInformation typeInfoToRegister )
    {
        registeredTypes.push_back( typeInfoToRegister );
        return 0;
    }

    static  typeInformation getTypeInformationFromTypeID(int type_id )
    {
        int _index = 0;

        for( vector<int>::size_type index = 0; index != registeredTypes.size(); index++)
        {
            if ( registeredTypes[index].id == type_id )
                _index = index;
        }

        return registeredTypes[_index];

    }


};

struct object
{
    int id;
    typeInformation typeInfo;

    object( const typeInformation& typeInfo ) : typeInfo( typeInfo )
    {

    }

    object( const object& _object ) :  typeInfo( _object.typeInfo )
    {

    }

    ~object()
    {
        typeInfo.instanceReleaser( id );
    }
};

//application status code
#define ERROR_UNIMPLEMENTED     501
#define _ERROR_INTERNAL_ERROR    500
#define SUCESS_OK               200
#define SUCESS_NO_CONTENT       204
#define NULL_INSTANCE_ID 0
#define NULL_ACTION_ID 0
#define UNDEFINED_ERROR_ID -1

 bool is_a_list_of_strings(int);

int request_handler_for_list_of_strings( int my_instance, int action_id )
{
    int response_code = _ERROR_INTERNAL_ERROR;

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



bool is_a_list_of_strings( int id )
{
        return SUCESS_OK;
}

//object list_of_strings( )
//{
//     #define LIST_OF_STRING 10
//
//     void* ptr = new list<string>;
//
//     typeInformation listInfo;
//     listInfo.id = LIST_OF_STRING;
//     listInfo.instanceAdquirer =
//
//     return object(  );
//}

struct runtimeMetaInformation
{
    private:

    static vector<int> runtime_modules;

    public:

    static void import( int type_id )
    {

        runtime_modules.push_back(type_id);
    }
};



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
    //type loading
    void* typeModuleHandler =  LoadLibrary("1.dll");
    descriptor typeInformationGetter = 0;

    typeInformation loadedTypeInfo;

    if ( typeModuleHandler )
    {
        typeInformationGetter = (descriptor)GetProcAddress( (HINSTANCE)typeModuleHandler, "getTypeInformation" );
    }

    //type description loading
    if ( typeInformationGetter )
        loadedTypeInfo = typeInformationGetter();

    object createdInstance = loadedTypeInfo.instanceAdquirer();

    createdInstance.


    return 0;
}
