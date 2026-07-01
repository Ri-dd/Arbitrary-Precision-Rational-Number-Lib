# BigRational

An object-oriented C++17 library for performing **exact arithmetic on rational numbers of arbitrary size** using a custom arbitrary-precision integer implementation. The library avoids floating-point precision errors by representing rational numbers as a numerator and denominator composed of `BigInteger` objects.

## Features

- Arbitrary-precision integer arithmetic
- Exact rational number representation
- Automatic fraction simplification using Euclidean GCD
- Arithmetic operators (`+`, `-`, `*`, `/`)
- Comparison operators
- Stream input/output support
- Decimal conversion with configurable precision
- Recurring decimal detection
- Binary exponentiation for rational powers
- Optimized multiplication using Karatsuba algorithm
- Clean object-oriented API

## Project Structure

```
BigRational/
│
├── include/
│   ├── BigInteger.h
│   └── BigRational.h
│
├── src/
│   ├── BigInteger.cpp
│   └── BigRational.cpp
│
├── examples/
│   └── calculator.cpp
│
├── tests/
│   └── test.cpp
│
├── CMakeLists.txt
├── README.md
└── LICENSE
```

## Architecture

```
               BigInteger
         (Arbitrary Precision Integer)
                    ▲
                    │
        used internally by
                    │
              BigRational
                    │
      Rational Arithmetic Library
                    │
   Decimal Conversion / GCD / Power
```

## Technologies Used

- **Language:** C++17
- **Build System:** CMake
- **Compiler:** GCC / Clang
- **Version Control:** Git, GitHub
- **IDE:** VS Code / CLion
- **Standard Library:** `vector`, `string`, `unordered_map`, `algorithm`

## Object-Oriented Design

The project demonstrates several object-oriented programming concepts:

- Encapsulation
- Abstraction
- Composition
- Operator Overloading
- Function Overloading
- Modular Class Design
- Const Correctness

## BigInteger

`BigInteger` stores signed integers of practically unlimited size using a dynamic array of digit blocks.

### Supported Operations

- Addition
- Subtraction
- Multiplication
- Division
- Modulo
- Comparisons
- Absolute value
- Negation

Internally, numbers are stored in **base 10⁹** to reduce storage overhead and improve arithmetic performance.

## BigRational

`BigRational` represents rational numbers using two `BigInteger` objects:

```cpp
BigInteger numerator;
BigInteger denominator;
```

Every object is automatically normalized by:

- Moving the sign to the numerator
- Making the denominator positive
- Dividing numerator and denominator by their GCD

## Algorithms

### Euclidean Algorithm

Used for:

- Fraction simplification
- Greatest Common Divisor (GCD)

### Long Division

Used for:

- Integer division
- Modulo
- Decimal expansion

### Binary Exponentiation

Used to compute powers in **O(log n)** multiplications.

### Karatsuba Multiplication

Large integer multiplication automatically switches to Karatsuba multiplication after a configurable threshold to improve performance.

### Remainder Tracking

Recurring decimal detection is implemented using an `unordered_map` that stores previously encountered remainders while generating decimal digits.

## Complexity

| Operation | Complexity |
|------------|------------|
| Addition | O(n) |
| Subtraction | O(n) |
| Comparison | O(n) |
| Multiplication | O(n²) |
| Karatsuba Multiplication | O(n^1.585) |
| Division | O(n²) |
| GCD | Depends on operand size |
| Binary Exponentiation | O(log p) multiplications |

## Example

```cpp
#include "BigInteger.h"
#include "BigRational.h"

using namespace bigint;

int main()
{
    BigRational a("22/7");
    BigRational b("5/8");

    std::cout << a + b << '\n';
    std::cout << a * b << '\n';
    std::cout << a.pow(10) << '\n';
    std::cout << a.toDecimal(30) << '\n';
}
```

## Building

```bash
mkdir build
cd build

cmake ..
make
```

Run the example program:

```bash
./calculator
```

## Future Improvements

- FFT-based multiplication for extremely large integers
- Arbitrary-precision decimal type
- Continued fraction support
- Expression parser
- GoogleTest unit tests
- Performance benchmarking
- Doxygen-generated API documentation

## License

This project is released under the MIT License.
