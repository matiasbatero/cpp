#ifndef _PREDICATE_H
#define _PREDICATE_H

using namespace std;

template< class Type >
struct Predicate
{
    typedef bool (*Evaluate)( Type item ) ;

    Evaluate evaluate ;
};

#endif
