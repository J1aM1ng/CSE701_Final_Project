# BigInt Class Documentation

## Overview

The `BigInt` class is a C++ implementation of arbitrary-precision arithmetic for integer numbers. It enables calculations with integers larger than those natively supported by the standard primitive types of C++, such as `int` or `int64_t`.

This implementation offers basic arithmetic operations such as addition, subtraction, and multiplication, as well as comparison operations between `BigInt` instances. The internal representation of the number is a `std::string`, where the least significant digit is at the beginning of the string, facilitating arithmetic operations.

## Usage

### Initialization

```cpp
BigInt();                         // Initializes a BigInt with value 0.
explicit BigInt(const string& num);   // Initializes a BigInt with a string.
explicit BigInt(int64_t num);         // Initializes a BigInt with an int64_t.
```

- The default constructor initializes the `BigInt` to zero.
- The `BigInt` can be initialized with a `std::string` or `int64_t`. The string can optionally start with a '+' or '-' sign, followed by digits. Leading zeros are ignored.

### Arithmetic Operations

```cpp
BigInt operator + (const BigInt& other) const; // Adds two BigInts.
BigInt operator - (const BigInt& other) const; // Subtracts two BigInts.
BigInt operator * (const BigInt& other) const; // Multiplies two BigInts.

BigInt& operator += (const BigInt& other); // Adds another BigInt to this one.
BigInt& operator -= (const BigInt& other); // Subtracts another BigInt from this one.
BigInt& operator *= (const BigInt& other); // Multiplies this BigInt by another one.
```

- Addition, subtraction, and multiplication are supported both as binary operators and compound assignment operators.

### Unary Operations

```cpp
BigInt operator - () const; // Negates the BigInt.
```

- The unary minus operator negates the value of the `BigInt`.

### Comparison Operations

```cpp
bool operator == (const BigInt& other) const; // Checks if two BigInts are equal.
bool operator != (const BigInt& other) const; // Checks if two BigInts are not equal.
bool operator < (const BigInt& other) const;  // Checks if this BigInt is less than another.
bool operator > (const BigInt& other) const;  // Checks if this BigInt is greater than another.
bool operator <= (const BigInt& other) const; // Checks if this BigInt is less or equal to another.
bool operator >= (const BigInt& other) const; // Checks if this BigInt is greater or equal to another.
```

- Comparison operators are provided to compare two `BigInt` instances.

### Assignment Operation

```cpp
BigInt& operator = (const BigInt& other); // Assigns another BigInt to this one.
```

- The assignment operator allows setting one `BigInt` to the value of another.

### Output Stream

```cpp
friend ostream& operator << (ostream& out, const BigInt& bigInt); // Outputs the BigInt to a stream.
```

The << operator is overloaded to provide easy streaming of the BigInt to output streams such as std::cout.

## Internal Representation

- The `BigInt` stores its digits in a `std::string` with the least significant digit at the front (little-endian).
- A boolean `is_negative` indicates the sign of the number.
- Private utility functions are used to perform arithmetic operations and comparisons on the string representation of the numbers.

## Compilation

To use the `BigInt` class, include `bigint.hpp` in your C++ project and ensure your compiler supports C++20 or later.

## Usage Examples

### Initialization

```cpp
BigInt a; // Default initializes to 0
BigInt b("123456789012345678901234567890"); // Initializes from a string
BigInt c(-1234567890123456789LL); // Initializes from a 64-bit integer
```

### Arithmetic Operations

```cpp
BigInt x("100000000000000000000");
BigInt y("-99999999999999999999");
BigInt z = x + y; // z will be "1"
BigInt w = x * y; // w will be "-9999999999999999999900000000000000000001"
```

### Comparison Operations

```cpp
BigInt n1("12345");
BigInt n2("12345");
bool areEqual = (n1 == n2); // areEqual will be true

BigInt n3("54321");
bool isLess = (n1 < n3); // isLess will be true
```

### Output

```cpp
BigInt num("123456789");
std::cout << num << std::endl; // Output will be: 123456789
```

For more examples, run `demo.cpp` to see a feature demonstration.

## Error Handling

- Throws `std::invalid_argument` if the string used for initialization is empty or contains invalid characters (anything other than digits and an optional leading '+' or '-').
- The behavior for overflow in arithmetic operations is notspecified since `BigInt` is designed to handle numbers larger than standard data types, but memory limitations can still result in an `std::bad_alloc` exception if the resulting number cannot be stored in available memory.

## Limitations

- Performance may be slower compared to native integer operations, especially as the number size increases.
- Division and modulus operations are not implemented in this version of `BigInt`.
- The `BigInt` class does not currently support operations with floating-point numbers or conversion to and from floating-point types.

## Further Improvements

- Implement division and modulus operations.
- Optimize internal algorithms for better performance with very large numbers.
- Add support for more complex mathematical operations such as exponentiation, square root, or GCD.
- Provide conversion functions to and from floating-point types.
- Implement serialization and deserialization to support saving and loading `BigInt` instances.