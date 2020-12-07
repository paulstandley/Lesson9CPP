#include "pch.h"
#include "Header.h"
#include <iostream>


class Cents
{
private:
    int m_cents{};

public:
    Cents(int cents)
        : m_cents{ cents }
    {}

    int getCents() const { return m_cents; }
};

// note: this function is not a member function nor a friend function!
Cents operator+(const Cents& c1, const Cents& c2)
{
    // use the Cents constructor and operator+(int, int)
    // we don't need direct access to private members here
    return Cents{ c1.getCents() + c2.getCents() };
}

void overloading_operators_using_normal_functions()
{
    /*Using a friend function to overload an operator is convenient 
    because it gives you direct access to the internal members of the classes 
    you’re operating on. 
    
    In the initial Cents example, 
    our friend function version of operator+
    accessed member variable m_cents directly.

    However, if you don’t need that access, 
    you can write your overloaded operators as normal functions. 
    
    Note that the Cents class contains an access function 
    (getCents()) that allows us to get at m_cents without
    having to have direct access to private members. 
    Because of this, we can write our overloaded operator+ as a non-friend

    Because the normal and friend functions work almost identically 
    (they just have different levels of access to private members),
    we generally won’t differentiate them. 
    
    The one difference is that the friend function declaration
    inside the class serves as a prototype as well. 
    With the normal function version, 
    you’ll have to provide your own function prototype.

    In general,
    a normal function should be preferred over a friend function 
    if it’s possible to do so with the existing member functions
    available (the less functions touching your classes’s internals, the better).
    However, 
    don’t add additional access functions just to overload an operator 
    as a normal function instead of a friend function!

    Rule

    Prefer overloading operators as normal functions instead of friends
    if it’s possible to do so without adding additional functions.
    
    */

    Cents cents1{ 6 };
    Cents cents2{ 8 };
    Cents centsSum{ cents1 + cents2 };
    std::cout << "I have " << centsSum.getCents() << " cents.\n";
}

int main()
{
    

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu