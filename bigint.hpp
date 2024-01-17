#ifndef CSE701_FINALPROJ_BIGINT_HPP
#define CSE701_FINALPROJ_BIGINT_HPP
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
/**
 * @class BigInt
 * @brief A class to represent large integers and perform arithmetic operations.
 *
 * The BigInt class can handle integers larger than those supported natively by C++ data types.
 * It uses strings to store the magnitude of the integer and a boolean to represent its sign.
 */
class BigInt
{
private:
    string number;    ///< The string representation of the integer's magnitude in reverse order.
    bool is_negative; ///< Flag indicating whether the integer is negative.

    BigInt add(const BigInt &other) const;                                 ///< Private helper function for addition.
    BigInt subtract(const BigInt &other) const;                            ///< Private helper function for subtraction.
    BigInt multiply(const BigInt &other) const;                            ///< Private helper function for multiplication.
    static string addStrings(const string &num1, const string &num2);      ///< Helper for string-based addition.
    static string subtractStrings(const string &num1, const string &num2); ///< Helper for string-based subtraction.
    static bool isSmaller(const string &num1, const string &num2);         ///< Compare two reversed string numbers.

public:
    BigInt();                           ///< Default constructor initializing to zero.
    explicit BigInt(const string &num); ///< Constructor from string.
    explicit BigInt(int64_t num);       ///< Constructor from int64_t.

    // Arithmetic operators
    BigInt operator+(const BigInt &other) const;
    BigInt operator-(const BigInt &other) const;
    BigInt &operator+=(const BigInt &other);
    BigInt &operator-=(const BigInt &other);
    BigInt operator*(const BigInt &other) const;
    BigInt &operator*=(const BigInt &other);

    // Unary minus operator
    BigInt operator-() const;

    // Comparison operators
    bool operator==(const BigInt &other) const;
    bool operator!=(const BigInt &other) const;
    bool operator<(const BigInt &other) const;
    bool operator>(const BigInt &other) const;
    bool operator<=(const BigInt &other) const;
    bool operator>=(const BigInt &other) const;

    // Assignment operator
    BigInt &operator=(const BigInt &other);

    // Stream insertion operator to support direct output to streams
    friend ostream &operator<<(ostream &out, const BigInt &bigInt);
};

// Definitions of the BigInt member functions with Doxygen comments

/**
 * @brief Default constructor for BigInt.
 * Initializes the BigInt to zero.
 */
BigInt::BigInt() : number("0"), is_negative(false) {}

/**
 * @brief Constructs a BigInt from a 64-bit signed integer.
 * @param num The integer to convert to a BigInt.
 */
BigInt::BigInt(int64_t num)
{
    // Handle the sign and special case of INT64_MIN
    is_negative = num < 0;
    if (num == INT64_MIN)
    {
        number = "9223372036854775808";
    }
    else
    {
        num = abs(num);
        number = to_string(num);
    }
    // Reverse the string to facilitate operations
    reverse(number.begin(), number.end());
}

/**
 * @brief Constructs a BigInt from a string.
 *
 * This constructor parses a string to initialize the BigInt object. The string
 * can optionally start with '+' or '-' to denote positive or negative numbers
 * respectively and should contain only digit characters thereafter. Leading zeroes
 * are ignored.
 *
 * @param num The string representation of the integer.
 * @throws invalid_argument If the input string is empty or contains non-digit characters.
 */
BigInt::BigInt(const string &num)
{
    if (num.empty())
    {
        throw invalid_argument("Input string is empty");
    }
    size_t start = 0;
    if (num[0] == '-')
    {
        is_negative = true;
        start = 1;
    }
    else
    {
        is_negative = false;
        if (num[0] == '+')
        {
            start = 1;
        }
    }
    while (start < num.size() && num[start] == '0')
    {
        start++;
    }
    if (start == num.size())
    {
        is_negative = false;
        number = "0";
    }
    else
    {
        number.reserve(num.size() - start);
        for (size_t i = start; i < num.size(); ++i)
        {
            if (!isdigit(num[i]))
            {
                throw invalid_argument("Invalid character in number string");
            }
            number += num[i];
        }
        reverse(number.begin(), number.end());
    }
}

/**
 * @brief Adds two BigInt numbers.
 *
 * This private member function is used to perform addition of two BigInt numbers.
 * It handles different sign scenarios and delegates to string addition or subtraction
 * functions as necessary.
 *
 * @param other The BigInt to add to the current BigInt object.
 * @return A new BigInt representing the sum.
 */
BigInt BigInt::add(const BigInt &other) const
{
    if (!is_negative && !other.is_negative)
    {
        return BigInt(addStrings(number, other.number));
    }
    else if (is_negative && other.is_negative)
    {
        return BigInt("-" + addStrings(number, other.number));
    }
    else if (is_negative)
    {
        if (isSmaller(number, other.number))
        {
            return BigInt(subtractStrings(other.number, number));
        }
        else
        {
            return BigInt("-" + subtractStrings(number, other.number));
        }
    }
    else
    {
        if (isSmaller(other.number, number))
        {
            return BigInt(subtractStrings(number, other.number));
        }
        else
        {
            return BigInt("-" + subtractStrings(other.number, number));
        }
    }
}

/**
 * @brief Overloads the addition operator for BigInt.
 *
 * Utilizes the private add function to calculate the sum of two BigInt objects.
 *
 * @param other The BigInt to add to the current object.
 * @return A new BigInt representing the sum.
 */
BigInt BigInt::operator+(const BigInt &other) const
{
    return add(other);
}

/**
 * @brief Overloads the addition assignment operator for BigInt.
 *
 * Adds the other BigInt to the current object and assigns the result to the current object.
 *
 * @param other The BigInt to add to the current object.
 * @return A reference to the current object after addition.
 */
BigInt &BigInt::operator+=(const BigInt &other)
{
    *this = *this + other;
    return *this;
}

/**
 * @brief Adds two numbers represented as reversed strings.
 *
 * This static private helper function performs the addition of two reversed strings that
 * represent numbers. It can be used to implement addition for the BigInt class.
 *
 * @param num1 The first reversed string representing a number.
 * @param num2 The second reversed string representing a number.
 * @return A string representing the sum of the two numbers, in reverse order.
 */
string BigInt::addStrings(const string &num1, const string &num2)
{
    string result;
    int carry = 0;
    auto it1 = num1.rbegin();
    auto it2 = num2.rbegin();
    while (it1 != num1.rend() || it2 != num2.rend() || carry)
    {
        int sum = carry;
        if (it1 != num1.rend())
        {
            sum += (*it1 - '0');
            ++it1;
        }
        if (it2 != num2.rend())
        {
            sum += (*it2 - '0');
            ++it2;
        }
        carry = sum / 10;
        result.push_back(static_cast<char>((sum % 10) + '0'));
    }
    reverse(result.begin(), result.end());
    return result;
}

/**
 * @brief Subtracts two numbers represented as reversed strings.
 *
 * This static private helper function performs the subtraction of two reversed strings that
 * represent numbers, ensuring num1 is greater than or equal to num2.
 *
 * @param num1 The first reversed string representing a larger or equal number.
 * @param num2 The second reversed string representing a smaller or equal number.
 * @return A string representing the difference of the two numbers, in reverse order.
 */
string BigInt::subtractStrings(const string &num1, const string &num2)
{
    string result;
    int borrow = 0;
    auto it1 = num1.rbegin();
    auto it2 = num2.rbegin();
    while (it1 != num1.rend() || it2 != num2.rend())
    {
        int digit1 = it1 != num1.rend() ? (*it1 - '0') : 0;
        int digit2 = it2 != num2.rend() ? (*it2 - '0') : 0;
        int diff = digit1 - digit2 - borrow;
        if (diff < 0)
        {
            diff += 10;
            borrow = 1;
        }
        else
        {
            borrow = 0;
        }
        result.push_back(static_cast<char>(diff + '0'));
        if (it1 != num1.rend())
            ++it1;
        if (it2 != num2.rend())
            ++it2;
    }
    while (result.size() > 1 && result.back() == '0')
    {
        result.pop_back();
    }
    reverse(result.begin(), result.end());
    return result;
}

/**
 * @brief Determines if one string representing a number is smaller than another.
 *
 * This static private helper function compares two strings representing numbers to determine
 * if the first is smaller than the second.
 *
 * @param num1 The first string representing a number.
 * @param num2 The second string representing a number.
 * @return A boolean value that is true if num1 is smaller than num2.
 */
bool BigInt::isSmaller(const string &num1, const string &num2)
{
    if (num1.size() != num2.size())
    {
        return num1.size() < num2.size();
    }
    for (auto it1 = num1.rbegin(), it2 = num2.rbegin(); it1 != num1.rend(); ++it1, ++it2)
    {
        if (*it1 != *it2)
        {
            return *it1 < *it2;
        }
    }
    return false;
}

/**
 * @brief Subtracts another BigInt from this BigInt.
 *
 * This function subtracts another BigInt from the current BigInt object and
 * accounts for different sign scenarios by using internal add and subtract helpers.
 *
 * @param other The BigInt to subtract from the current object.
 * @return A new BigInt representing the difference.
 */
BigInt BigInt::subtract(const BigInt &other) const
{
    if (!is_negative && !other.is_negative)
    {
        if (isSmaller(number, other.number))
        {
            return BigInt("-" + subtractStrings(other.number, number));
        }
        else
        {
            return BigInt(subtractStrings(number, other.number));
        }
    }
    else if (is_negative && other.is_negative)
    {
        if (isSmaller(number, other.number))
        {
            return BigInt(subtractStrings(other.number, number));
        }
        else
        {
            return BigInt("-" + subtractStrings(number, other.number));
        }
    }
    else if (is_negative)
    {
        return BigInt("-" + addStrings(number, other.number));
    }
    else
    {
        return BigInt(addStrings(number, other.number));
    }
}

/**
 * @brief Overloads the subtraction operator for BigInt.
 *
 * Utilizes the subtract function to calculate the difference of two BigInt objects.
 *
 * @param other The BigInt to subtract from the current object.
 * @return A new BigInt representing the difference.
 */
BigInt BigInt::operator-(const BigInt &other) const
{
    return subtract(other);
}

/**
 * @brief Overloads the subtraction assignment operator for BigInt.
 *
 * Subtracts the other BigInt from the current object and assigns the result to the current object.
 *
 * @param other The BigInt to subtract from the current object.
 * @return A reference to the current object after subtraction.
 */
BigInt &BigInt::operator-=(const BigInt &other)
{
    *this = *this - other;
    return *this;
}

/**
 * @brief Overloads the stream insertion operator for BigInt.
 *
 * This operator allows the BigInt object to be written to output streams, such as `std::cout`.
 * It handles the sign and outputs the digits in the correct order.
 *
 * @param out The output stream.
 * @param bigInt The BigInt object to output.
 * @return A reference to the output stream.
 */
ostream &operator<<(ostream &out, const BigInt &bigInt)
{
    if (bigInt.is_negative)
    {
        out << '-';
    }
    for (auto it = bigInt.number.rbegin(); it != bigInt.number.rend(); ++it)
    {
        out << *it;
    }
    return out;
}

/**
 * @brief Multiplies this BigInt with another BigInt.
 *
 * This function performs a multiplication of two BigInts using the classic
 * grade school algorithm. It handles large numbers by storing intermediate
 * results in a result vector and then combining them into the final product.
 *
 * @param other The BigInt to multiply with this BigInt.
 * @return A BigInt representing the product of this and other BigInts.
 */
BigInt BigInt::multiply(const BigInt &other) const
{
    int n1 = static_cast<int>(number.size());
    int n2 = static_cast<int>(other.number.size());
    if (n1 == 0 || n2 == 0)
    {
        return BigInt("0");
    }
    vector<int> result(n1 + n2, 0);
    for (int i = n1 - 1; i >= 0; i--)
    {
        int carry = 0;
        int n1_digit = number[i] - '0';
        for (int j = n2 - 1; j >= 0; j--)
        {
            int n2_digit = other.number[j] - '0';
            int sum = n1_digit * n2_digit + result[i + j + 1] + carry;
            carry = sum / 10;
            result[i + j + 1] = sum % 10;
        }
        result[i + n2] += carry;
    }
    int start = 0;
    while (start < result.size() && result[start] == 0)
    {
        start++;
    }
    if (start == result.size())
    {
        return BigInt("0");
    }
    string s;
    for (int i = start; i < result.size(); i++)
    {
        s += to_string(result[i]);
    }
    BigInt productResult(s);
    productResult.is_negative = is_negative != other.is_negative;
    return productResult;
}

/**
 * @brief Overloads the multiplication operator for BigInt.
 *
 * Utilizes the multiply function to calculate the product of two BigInt objects.
 *
 * @param other The BigInt to multiply with this BigInt.
 * @return A new BigInt representing the product.
 */
BigInt BigInt::operator*(const BigInt &other) const
{
    return multiply(other);
}

/**
 * @brief Overloads the multiplication assignment operator for BigInt.
 *
 * Multiplies the other BigInt with the current object and assigns the result to the current object.
 *
 * @param other The BigInt to multiply with this BigInt.
 * @return A reference to the current object after multiplication.
 */
BigInt &BigInt::operator*=(const BigInt &other)
{
    *this = *this * other;
    return *this;
}

/**
 * @brief Overloads the unary minus operator for BigInt.
 *
 * Creates a copy of the current BigInt and changes its sign.
 *
 * @return A BigInt with the opposite sign of this BigInt.
 */
BigInt BigInt::operator-() const
{
    BigInt result(*this);
    if (result.number != "0")
    {
        result.is_negative = !is_negative;
    }
    return result;
}

/**
 * @brief Overloads the equality operator for BigInt.
 *
 * Compares this BigInt with another BigInt for equality.
 *
 * @param other The BigInt to compare with this BigInt.
 * @return True if this BigInt is equal to other, false otherwise.
 */
bool BigInt::operator==(const BigInt &other) const
{
    return number == other.number && is_negative == other.is_negative;
}

/**
 * @brief Overloads the inequality operator for BigInt.
 *
 * Compares this BigInt with another BigInt for inequality.
 *
 * @param other The BigInt to compare with this BigInt.
 * @return True if this BigInt is not equal to other, false otherwise.
 */
bool BigInt::operator!=(const BigInt &other) const
{
    return !(*this == other);
}

/**
 * @brief Overloads the less-than operator for BigInt.
 *
 * Compares this BigInt with another BigInt to determine if this is less than other.
 *
 * @param other The BigInt to compare with this BigInt.
 * @return True if this BigInt is less than other, false otherwise.
 */
bool BigInt::operator<(const BigInt &other) const
{
    if (is_negative != other.is_negative)
        return is_negative;
    if (number.size() != other.number.size())
    {
        return is_negative ? (number.size() > other.number.size()) : (number.size() < other.number.size());
    }
    for (int i = static_cast<int>(number.size()) - 1; i >= 0; --i)
    {
        if (number[i] != other.number[i])
        {
            return is_negative ? (number[i] > other.number[i]) : (number[i] < other.number[i]);
        }
    }
    return false;
}

/**
 * @brief Overloads the greater-than operator for BigInt.
 *
 * Compares this BigInt with another BigInt to determine if this is greater than other.
 *
 * @param other The BigInt to compare with this BigInt.
 * @return True if this BigInt is greater than other, false otherwise.
 */
bool BigInt::operator>(const BigInt &other) const
{
    return other < *this;
}

/**
 * @brief Overloads the less-than-or-equal-to operator for BigInt.
 *
 * Compares this BigInt with another BigInt to determine if this is less than or equal to other.
 *
 * @param other The BigInt to compare with this BigInt.
 * @return True if this BigInt is less than or equal to other, false otherwise.
 */
bool BigInt::operator<=(const BigInt &other) const
{
    return !(*this > other);
}

/**
 * @brief Overloads the greater-than-or-equal-to operator for BigInt.
 *
 * Compares this BigInt with another BigInt to determine if this is greater than or equal to other.
 *
 * @param other The BigInt to compare with this BigInt.
 * @return True if this BigInt is greater than or equal to other, false otherwise.
 */
bool BigInt::operator>=(const BigInt &other) const
{
    return !(*this < other);
}

/**
 * @brief Overloads the assignment operator for BigInt.
 *
 * Assigns the value of another BigInt to this BigInt.
 *
 * @param other The BigInt to assign to this BigInt.
 * @return A reference to this BigInt after assignment.
 */
BigInt &BigInt::operator=(const BigInt &other)
{
    if (this != &other)
    {
        number = other.number;
        is_negative = other.is_negative;
    }
    return *this;
}
#endif // CSE701_FINALPROJ_BIGINT_HPP