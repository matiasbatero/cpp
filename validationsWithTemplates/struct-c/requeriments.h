#define _REQUERIMENTS


template< typename type, void(*required)(const type&) = 0 >
class requires
{
private:
    type value;

public:

    requires(type i) : value( i )
    {
        required(i);
    }

    operator type()
    {
        return value;
    }
};
