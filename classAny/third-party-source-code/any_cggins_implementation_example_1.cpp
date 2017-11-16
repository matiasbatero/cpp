
/*
 * (C) Copyright Christopher Diggins 2005-2011
 * (C) Copyright Pablo Aguilar 2005
 * (C) Copyright Kevlin Henney 2001
 *
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt
 */

#include <iostream>
#include <typeinfo>
#include <stdexcept>
#include <list>

using namespace std;


struct bad_any_cast
    {
    };

    struct empty_any
    {
    };

    struct base_any_policy
    {
        virtual void static_delete(void** x) = 0;
        virtual void copy_from_value(void const* src, void** dest) = 0;
        virtual void clone(void* const* src, void** dest) = 0;
        virtual void move(void* const* src, void** dest) = 0;
        virtual void* get_value(void** src) = 0;
        virtual size_t get_size() = 0;
    };

    template<typename T>
    struct typed_base_any_policy : base_any_policy
    {
        virtual size_t get_size() { return sizeof(T); }
    };

    template<typename T>
    struct small_any_policy : typed_base_any_policy<T>
    {
        virtual void static_delete(void** x) { }
        virtual void copy_from_value(void const* src, void** dest)
            { new(dest) T(*reinterpret_cast<T const*>(src)); }
        virtual void clone(void* const* src, void** dest) { *dest = *src; }
        virtual void move(void* const* src, void** dest) { *dest = *src; }
        virtual void* get_value(void** src) { return reinterpret_cast<void*>(src); }
    };

    template<typename T>
    struct big_any_policy : typed_base_any_policy<T>
    {
        virtual void static_delete(void** x) { if (*x)
            delete(*reinterpret_cast<T**>(x)); *x = NULL; }
        virtual void copy_from_value(void const* src, void** dest) {
           *dest = new T(*reinterpret_cast<T const*>(src)); }
        virtual void clone(void* const* src, void** dest) {
           *dest = new T(**reinterpret_cast<T* const*>(src)); }
        virtual void move(void* const* src, void** dest) {
          (*reinterpret_cast<T**>(dest))->~T();
          **reinterpret_cast<T**>(dest) = **reinterpret_cast<T* const*>(src); }
        virtual void* get_value(void** src) { return *src; }
    };

    template<typename T>
    struct choose_policy
    {
        typedef big_any_policy<T> type;
    };

    template<typename T>
    struct choose_policy<T*>
    {
        typedef small_any_policy<T*> type;
    };

    struct any;

    /// Choosing the policy for an any type is illegal, but should never happen.
    /// This is designed to throw a compiler error.
    template<>
    struct choose_policy<any>
    {
        typedef void type;
    };

    /// Specializations for small types.
    #define SMALL_POLICY(TYPE) template<> struct \
       choose_policy<TYPE> { typedef small_any_policy<TYPE> type; };

    SMALL_POLICY(signed char);
    SMALL_POLICY(unsigned char);
    SMALL_POLICY(signed short);
    SMALL_POLICY(unsigned short);
    SMALL_POLICY(signed int);
    SMALL_POLICY(unsigned int);
    SMALL_POLICY(signed long);
    SMALL_POLICY(unsigned long);
    SMALL_POLICY(float);
    SMALL_POLICY(bool);

    #undef SMALL_POLICY

    /// This function will return a different policy for each type.
    template<typename T>
    base_any_policy* get_policy()
    {
        static typename choose_policy<T>::type policy;
        return &policy;
    };


struct any
{
private:
    // fields
    base_any_policy* policy;
    void* object;

public:
    /// Initializing constructor.
    template <typename T>
    any(const T& x)
        : policy(get_policy<empty_any>()), object(NULL)
    {
        assign(x);
    }

    /// Empty constructor.
    any()
        : policy(get_policy<empty_any>()), object(NULL)
    { }

    /// Special initializing constructor for string literals.
    any(const char* x)
        : policy(get_policy<empty_any>()), object(NULL)
    {
        assign(x);
    }

    /// Copy constructor.
    any(const any& x)
        : policy(get_policy<empty_any>()), object(NULL)
    {
        assign(x);
    }

    /// Destructor.
    ~any() {
        policy->static_delete(&object);
    }

    /// Assignment function from another any.
    any& assign(const any& x) {
        reset();
        policy = x.policy;
        policy->clone(&x.object, &object);
        return *this;
    }

    /// Assignment function.
    template <typename T>
    any& assign(const T& x) {
        reset();
        policy = get_policy<T>();
        policy->copy_from_value(&x, &object);
        return *this;
    }

    /// Assignment operator.
    template<typename T>
    any& operator=(const T& x) {
        return assign(x);
    }

    /// Assignment operator, specialed for literal strings.
    /// They have types like const char [6] which don't work as expected.
    any& operator=(const char* x) {
        return assign(x);
    }

    /// Utility functions
    any& swap(any& x) {
        std::swap(policy, x.policy);
        std::swap(object, x.object);
        return *this;
    }

    /// Cast operator. You can only cast to the original type.
    template<typename T>
    T& cast(){
        if (policy != get_policy<T>())
            throw bad_any_cast();
        T* r = reinterpret_cast<T*>(policy->get_value(&object));
        return *r;
    }

    /// Returns true if the any contains no value.
    bool empty() const {
        return policy == get_policy<empty_any>();
    }

    /// Frees any allocated memory, and sets the value to NULL.
    void reset() {
        policy->static_delete(&object);
        policy = get_policy<empty_any>();
    }

    /// Returns true if the two types are the same.
    bool compatible(const any& x) const {
        return policy == x.policy;
    }
};


class List
{
    list<any> rep;

public:

    void add(const any& input)
    {
        rep.push_front(input);
    }

    const any& front()
    {
        return rep.front();
    }
    
    const any& back()
    {
		return rep.back();
	}
};



any create( any input )
{
	auto arg = input.cast<List>();
	
	auto argA = arg.front();
	auto argB = arg.back();
	
	return new int( argB.cast<int>() );	
};



int main()
{
	List aList;
	aList.add(89);
	aList.add("request.txt");
	
	auto k = create(aList);
	
	cout << *k.cast<int*>() << endl;
	
	 
	
    return 0;
}
