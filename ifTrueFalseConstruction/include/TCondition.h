#ifndef TCONDITION_H
#define TCONDITION_H

#include <iostream>

using namespace std;

class TCondition
{
	private:
	bool m_value;
    void isTrue();
    void isFalse();
    TCondition* condition;

	public:

    TCondition(){ m_value = false; };
	TCondition* operator() (bool expression);

	//Next refactoring... IfTrue( Action* action );
    TCondition* IfTrue();
    TCondition* IfFalse();

};

void TCondition::isTrue()
{
    m_value = true;
};

void TCondition::isFalse()
{
    m_value = false;
};


TCondition* TCondition::operator()(bool expression)
{
    (expression)? isTrue() : isFalse();
    return this;
};

TCondition* TCondition::IfTrue()
{
    if ( m_value == true )
    {
        cout << "Expression is: TRUE" << endl;

        //Actions for true branch...
        cout << "Executing true function block code..." << endl;

        //End execution of true branch...

        cout << "End of true branch code execution." << endl << endl;

    };

    return this;
};

TCondition* TCondition::IfFalse()
{
    if ( m_value == false )
    {
        cout << "Expression is: FALSE" << endl;

        //Actions for false branch...
        cout << "Executing false function block code..." << endl;

        //End execution of false branch...

        cout << "End of false branch code execution." << endl << endl;

    };

    return this;
};



#endif // TCONDITION_H

