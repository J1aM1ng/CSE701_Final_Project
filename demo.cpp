#include "bigint.hpp"
#include <iostream>
#include <exception>

using namespace std;

int main()
{
    try
    {
        // Demonstrates the use of the default constructor.
        BigInt defaultBigInt;
        cout << "Default constructor: " << defaultBigInt << endl;

        // Demonstrates construction from a string representing a large integer.
        BigInt fromStr("-12345678901234567890");
        cout << "Constructor from string: " << fromStr << endl;

        // Demonstrates construction from the maximum value of int64_t.
        BigInt fromInt64(numeric_limits<int64_t>::max());
        cout << "Constructor from int64_t: " << fromInt64 << endl;

        // Demonstrates the addition of two BigInts.
        BigInt sum = fromStr + fromInt64;
        cout << "Addition: " << fromStr << " + " << fromInt64 << " = " << sum << endl;

        // Demonstrates the subtraction of two BigInts.
        BigInt difference = fromStr - fromInt64;
        cout << "Subtraction: " << fromStr << " - " << fromInt64 << " = " << difference << endl;

        // Demonstrates the multiplication of two BigInts.
        BigInt product = fromStr * fromInt64;
        cout << "Multiplication: " << fromStr << " * " << fromInt64 << " = " << product << endl;

        // Demonstrates negating the value of a BigInt.
        BigInt negation = -fromStr;
        cout << "Unary minus: -(" << fromStr << ") = " << negation << endl;

        // Demonstrates compound addition (+=) with BigInts.
        BigInt compoundAdd;
        compoundAdd += fromInt64;
        cout << "Compound addition (+=): " << compoundAdd << endl;

        // Demonstrates compound subtraction (-=) with BigInts.
        BigInt compoundSubtract(fromInt64);
        compoundSubtract -= fromStr;
        cout << "Compound subtraction (-=): " << compoundSubtract << endl;

        // Demonstrates compound multiplication (*=) with BigInts.
        BigInt compoundMultiply(12345);
        compoundMultiply *= fromStr;
        cout << "Compound multiplication (*=): " << compoundMultiply << endl;

        // Demonstrates the equality operator (==) with BigInts.
        cout << "Equality (==): " << (fromInt64 == fromStr ? "true" : "false") << endl;

        // Demonstrates the inequality operator (!=) with BigInts.
        cout << "Inequality (!=): " << (fromInt64 != fromStr ? "true" : "false") << endl;

        // Demonstrates the less-than operator (<) with BigInts.
        cout << "Less than (<): " << (fromInt64 < fromStr ? "true" : "false") << endl;

        // Demonstrates the greater-than operator (>) with BigInts.
        cout << "Greater than (>): " << (fromInt64 > fromStr ? "true" : "false") << endl;

        // Demonstrates the less-than-or-equal-to operator (<=) with BigInts.
        cout << "Less than or equal to (<=): " << (fromInt64 <= fromStr ? "true" : "false") << endl;

        // Demonstrates the greater-than-or-equal-to operator (>=) with BigInts.
        cout << "Greater than or equal to (>=): " << (fromInt64 >= fromStr ? "true" : "false") << endl;

        // Demonstrates the assignment operator (=) with BigInts.
        BigInt assignmentOperator;
        assignmentOperator = fromStr;
        cout << "Assignment (=): " << assignmentOperator << endl;
    }
    catch (const invalid_argument &e)
    {
        // Handles exceptions thrown due to invalid arguments.
        cerr << "Invalid argument exception: " << e.what() << endl;
        return 1;
    }
    catch (const overflow_error &e)
    {
        // Handles exceptions thrown due to arithmetic overflow.
        cerr << "Overflow error: " << e.what() << endl;
        return 1;
    }
    catch (const exception &e)
    {
        // Handles any other standard exceptions.
        cerr << "General exception: " << e.what() << endl;
        return 1;
    }
    catch (...)
    {
        // Handles any non-standard exceptions.
        cerr << "An unknown error occurred!" << endl;
        return 1;
    }
    return 0;
}