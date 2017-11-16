/*
 * Template recursion
 * 
 * Code from: ISFT151 Gabriel Pimentel
 * 
 * 
 */

#include <iostream>

template< bool C, typename TrueBranch, typename FalseBranch >
struct IfThenElse;

template< typename TrueBranch, typename FalseBranch >
struct IfThenElse < true, TrueBranch, FalseBranch >
{
    typedef TrueBranch BranchResult;
};


template< typename TrueBranch, typename FalseBranch >
struct IfThenElse < false, TrueBranch, FalseBranch >
{
    typedef FalseBranch BranchResult;
};

template< int N >
struct Value
{
    enum { result = N };

};

template< int N, int I = 1 >
struct CountOfDigits
{

    typedef typename IfThenElse< (N<10), Value<I>, CountOfDigits< N/10, I+1 >
                      > ::BranchResult value;

    enum { result = value::result };

};


int main()
{
    std::cout << "Digits in 12459 : \t" << CountOfDigits< 12459 >::result << std::endl;

    return  0;
}
