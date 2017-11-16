#ifndef _SET_H
#define _SET_H

#include "sequence.h"

template < class Type >
struct Set
{
    Sequence<Type> rep;

    bool Initialize( void ) ;
    bool CreateWith( Type data[], int size ) ;
    bool CreateFrom( Sequence<type>& sequence ) ;

    int Count( void );
    bool IsEmpty( void );
    bool IsFull( void );
    bool Contain( Type item );
    bool Add ( const Type& item ) ;
    bool Contain ( Type item ) ;
    void Intersect ( Set<Type>& thisSet, Set<Type>& resultSet ) ;
    void Dump ( void );
    void Free ( void );
} ;

template < class Type >
bool Set<Type>::Initialize( void );
{
    return rep.Initialize();
}

template < class Type >
bool Set<Type>::CreateWith( Type data[], int size ) ;
{
    return rep.CreateWith( data[], size ) ;
}

template < class Type >
bool Set<Type>::CreateFrom( Sequence<type>& sequence ) ;
{

}

template < class Type >
int Set<Type>::Count( void );
{

}

template < class Type >
bool Set<Type>::IsEmpty( void );
{

}

template < class Type >
bool Set<Type>::IsFull( void );
{

}

template < class Type >
bool Set<Type>::Contain( Type item );
{

}

template < class Type >
bool Set<Type>::Add ( const Type& item ) ;
{

}

template < class Type >
bool Set<Type>::Contain ( Type item ) ;
{
    bool contain = false;
    Type* item = rep.First
}

template < class Type >
void Set<Type>::Intersect ( Set<Type>& thisSet, Set<Type>& resultSet ) ;
{

}

template < class Type >
void Set<Type>::Dump ( void );
{

}

template < class Type >
void Set<Type>::Free ( void );
{

}

#endif // _SET_H
