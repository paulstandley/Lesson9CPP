#include "pch.h"
#include "Header.h"
#include <iostream>


class Point1
{
private:
    double m_x{};
    double m_y{};
    double m_z{};

    public Point1(double x = 0, double y = 0, double z = 0) : m_x{ x }, m_y{ y }, m_z{ z } {}

    friend std::ostream& operator<< (std::ostream& out, const Point1 point);
    std::ostream& operator<<(std::ostream& out, const Point1& point)
    {
        // Since operator<< is a friend of the Point class, 
        //we can access Point's members directly.
        out << "Point(" << point.m_x << ", " << point.m_y << ", " << point.m_z << ')';
        // actual output done here

        return out; // return std::ostream so we can chain calls to operator<<
    }
};

void overloading_the_IO_operators()
{
    /*For classes that have multiple member variables, 
    printing each of the individual variables on the screen can get tiresome fast.

    Overloading operator<<

    Overloading operator<< is similar to overloading operator+ 
    (they are both binary operators), except that the parameter types are different.

    Consider the expression std::cout << point. 
    If the operator is <<, what are the operands?
    The left operand is the std::cout object, 
    and the right operand is your Point class object. 
    
    std::cout is actually an object of type std::ostream. 
    Therefore, our overloaded function will look like this:

    // std::ostream is the type for object std::cout
    friend std::ostream& operator<< (std::ostream &out, const Point &point);

    Implementation of operator<< for our Point class is fairly straightforward
    -- because C++ already knows how to output doubles using operator<<,
    and our members are all doubles, 
    we can simply use operator<< to output the member variables of our Point.
    Here is the above Point class with the overloaded operator<<.

    This is pretty straightforward 
    -- note how similar our output line is to the line in the print()
    function we wrote previously. 
    The most notable difference is that std::cout has become parameter out
    (which will be a reference to std::cout when the function is called).

    The trickiest part here is the return type. 
    With the arithmetic operators, 
    we calculated and returned a single answer by value 
    (because we were creating and returning a new result).
    However, if you try to return std::ostream by value, you’ll get a compiler error. 
    This happens because std::ostream specifically disallows being copied.

    In this case, we return the left hand parameter as a reference.
    This not only prevents a copy of std::ostream from being made, 
    it also allows us to “chain” output commands together, 
    such as std::cout << point << std::endl;

    You might have initially thought that since operator<< doesn’t return a value
    to the caller, we should define the function as returning void. 
    But consider what would happen if our operator<< returned void. 
    When the compiler evaluates std::cout << point << std::endl;,
    due to the precedence/associativity rules, 
    it evaluates this expression as (std::cout << point) << std::endl;. 
    std::cout << point would call our void-returning overloaded operator<< function, 
    which returns void. 
    
    Then the partially evaluated expression becomes: 
    void << std::endl;, which makes no sense!

    By returning the out parameter as the return type instead,
    (std::cout << point) returns std::cout.
    Then our partially evaluated expression becomes: 
    std::cout << std::endl;, which then gets evaluated itself!

    Any time we want our overloaded binary operators to be chainable in such a manner,
    the left operand should be returned (by reference). 
    Returning the left-hand parameter by reference is okay in this case
    -- since the left-hand parameter was passed in by the calling function, 
    it must still exist when the called function returns.
    
    Therefore, we don’t have to worry about referencing something that will
    go out of scope and get destroyed when the operator returns.

    
    */

    const Point1 point11{ 2.0, 3.0, 4.0 };

    std::cout << point11 << '\n';
}

int main()
{
    //overloading_operators_using_normal_functions();

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu