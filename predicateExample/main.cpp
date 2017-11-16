#include <iostream>
#include <memory.h>
#include "sequence.h"

using namespace std;

typedef int TType ;

bool LessThanFive( TType item )
{
    return ( item < 5 ) ;
}

bool GreaterThanFour( TType item )
{
    return ( item > 4 ) ;
}

bool DivisibleByTwo( TType item )
{
    return ( item % 2 == 0 ) ;
}

bool DivisibleByFive( TType item )
{
    return ( item % 5 == 0 ) ;
}

bool WrongPredicate( int* item )
{
    return false;
}

int main(int argc, char* argv[])
{
    TType array[] = { 2, 6, 3, 9, 6, 23, 4, 16, 34, 13 }  ;
    TType array2[] = { 2, 3, 6, 8, 10, 12, 14, 16, 18, 20 }  ;

    Sequence< int > input, input2, result ;
    Predicate< int > predicate ;

    input.Initialize() ;
    input2.Initialize() ;
    result.Initialize() ;

    input.CreateWith( array, 10 ) ;
    cout << "Input data ..." << endl ;
    input.Dump() ;

    input2.CreateWith( array2, 10 ) ;
    cout << "Input2 data ..." << endl ;
    input2.Dump() ;

    predicate.evaluate = GreaterThanFour ;
    cout << endl << "Select GreaterThanFour from input ..." << endl << endl ;
    input.Select( predicate, result ) ;
    result.Dump() ;
    result.Free() ;

    predicate.evaluate =  LessThanFive  ;
    cout << endl << "Select LessThanFive from input ..." << endl << endl ;
    input.Select( predicate, result ) ;
    result.Dump() ;
    result.Free() ;

    predicate.evaluate =  DivisibleByTwo  ;
    cout << endl << "Select DivisibleByTwo from input ..." << endl << endl ;
    input.Select( predicate, result ) ;
    result.Dump() ;
    result.Free() ;

    predicate.evaluate =  DivisibleByFive  ;
    cout << endl << "Select DivisibleByFive from input ..." << endl << endl ;
    input.Select( predicate, result ) ;
    result.Dump() ;
    result.Free() ;

  /*  cout << endl << "Common Items from input and input2 ..." << endl << endl ;
    CommonItem( input, input2, result ) ;
    result.Dump() ;
    result.Free() ; */

    return 0;
}


