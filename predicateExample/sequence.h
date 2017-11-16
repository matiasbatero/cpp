#ifndef _SEQUENCE_H
#define _SEQUENCE_H

#include <iostream>
#include <memory.h>
#include "predicate.h"

using namespace std;

template < class Type >
struct Sequence
{
    enum {
            SEQUENCE_MAX_ITEMS = 512,
            SEQUENCE_EMPTY = -1
    } ;

    Type rep[ SEQUENCE_MAX_ITEMS ] ;
    int first ;
    int last ;
    Type* current ;
    bool initialized ;

    bool Initialize( void ) ;
    bool CreateWith( Type data[], int size ) ;
    int Count( void ) ;
    bool IsEmpty( void ) ;
    bool IsFull( void ) ;
    bool Add( const Type& item ) ;
    Type* First( void ) ;
    Type* Next( void ) ;
    void Dump( void ) ;
    void Free( void ) ;
    void Select( Predicate<Type>& isConditionTrue, Sequence& output ) ;
} ;

template< class Type >
bool Sequence<Type>::Initialize( void )
{
    ::memset( rep, 0, SEQUENCE_MAX_ITEMS) ;
    first = last = SEQUENCE_EMPTY ;
    current = 0 ;
    initialized = true ;
    return initialized ;
}

template< class Type >
bool Sequence<Type>::CreateWith( Type data[], int size )
{
    bool sucess = Initialize() ;
    for( int index = 0; ( index < size ) && ( sucess ); index++ )
    {
        sucess = Add( data[ index ] ) ;
    }
    return sucess ;
}

template< class Type >
int Sequence<Type>::Count( void )
{
    return initialized ? last + 1 : 0 ;
}

template< class Type >
bool Sequence<Type>::IsEmpty( void )
{
    return initialized ? ( first == SEQUENCE_EMPTY ) : true ;
}

template< class Type >
bool Sequence<Type>::IsFull( void )
{
    return initialized ? ( last == SEQUENCE_MAX_ITEMS ) : true ;
}

template< class Type >
bool Sequence<Type>::Add( const Type& item )
{
    bool result = false ;
    if ( initialized ) {
        if ( !IsFull() ) {
            rep[ ++last ] = item ;
            if ( IsEmpty() ) {
                first = last ;
            }
            result = true ;
        }
    }
    return result ;
}

template< class Type >
Type* Sequence<Type>::First( void )
{
    return ( !IsEmpty() ) ? ( current = rep ) : 0 ;
}

template< class Type >
Type* Sequence<Type>::Next( void )
{
    Type* result = 0 ;
    if ( initialized ) {
        current++ ;
        if ( current <= &rep[ last ] ) result = current ;
    }
    return result ;
}

template< class Type >
void Sequence<Type>::Dump( void )
{
    Type* item = First() ;
    while ( item ) {
        cout << *item <<  " " ;
        item = Next() ;
    }
    cout << endl ;
}

template< class Type >
void Sequence<Type>::Free( void )
{
    Initialize() ;
}

template <class Type >
void Sequence<Type>::Select( Predicate<Type>& isConditionTrue, Sequence& output )
{
    Type* item = First() ;
    while ( item )
    {
        if ( isConditionTrue.evaluate( *item ) ) output.Add( *item ) ;
        item = Next() ;
    }
}

#endif // _SEQUENCE_H
