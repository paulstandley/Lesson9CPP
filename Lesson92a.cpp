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

class Point1
{
private:
    double m_x{};
    double m_y{};
    double m_z{};

public:
    Point1(double x = 0.0, double y = 0.0, double z = 0.0)
        : m_x{ x }, m_y{ y }, m_z{ z }
    {
    }

    friend std::ostream& operator<< (std::ostream& out, const Point1& point);
};

std::ostream& operator<< (std::ostream& out, const Point1& point)
{
    // Since operator<< is a friend of the Point class, we can access Point's members directly.
    out << "Point(" << point.m_x << ", " << point.m_y << ", " << point.m_z << ')'; // actual output done here

    return out; // return std::ostream so we can chain calls to operator<<
}

class Point2
{
private:
    double m_x{};
    double m_y{};
    double m_z{};

public:
    Point2(double x = 0.0, double y = 0.0, double z = 0.0)
        : m_x{ x }, m_y{ y }, m_z{ z }
    {
    }

    friend std::ostream& operator<< (std::ostream& out, const Point2& point);
    friend std::istream& operator>> (std::istream& in, Point2& point);
};

std::ostream& operator<< (std::ostream& out, const Point2& point)
{
    // Since operator<< is a friend of the Point class, we can access Point's members directly.
    out << "Point(" << point.m_x << ", " << point.m_y << ", " << point.m_z << ')';

    return out;
}

std::istream& operator>> (std::istream& in, Point2& point)
{
    // Since operator>> is a friend of the Point class, we can access Point's members directly.
    // note that parameter point must be non-const so we can modify the class members with the input values
    in >> point.m_x;
    in >> point.m_y;
    in >> point.m_z;

    return in;
}

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

    //////////////////////////////////////////////////////////////////////////////////

    Overloading operator>>

    It is also possible to overload the input operator.
    This is done in a manner analogous to overloading the output operator.
    The key thing you need to know is that std::cin is an object of type std::istream.

    Conclusion

    Overloading operator<< and operator>> make it extremely easy to output your class
    to screen and accept user input from the console.

    */

    const Point1 point11{ 2.0, 3.0, 4.0 };

    std::cout << point11 << '\n';

    std::cout << "Enter a point: \n";

    Point2 point2{};
    std::cin >> point2;

    std::cout << "You entered: " << point2 << '\n';
}

