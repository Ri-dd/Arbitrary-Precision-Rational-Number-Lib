# Arbitrary-Precision Rational Number Library

An object-oriented C++17 library for exact arbitrary-precision integer and rational arithmetic. The library implements custom `BigInteger` and `BigRational` classes capable of performing precise calculations on numbers of arbitrary size while avoiding floating-point precision errors through exact fractional representation.

## Highlights

- Exact arbitrary-precision integer and rational arithmetic using custom `BigInteger` and `BigRational` classes
- Automatic switching between schoolbook multiplication and **Karatsuba multiplication** for improved performance on large operands
- Exact decimal conversion with **automatic recurring decimal detection** using hash-based remainder tracking
- Clean object-oriented design leveraging encapsulation, composition, and operator overloading
- Built with modern **C++17**, STL, and CMake

---

## Features

### BigInteger

- Arbitrary-precision signed integer arithmetic
- Addition, subtraction, multiplication, division, and modulo
- Automatic switching between schoolbook multiplication and Karatsuba multiplication for large operands
- Efficient binary exponentiation
- Euclidean GCD implementation
- Complete comparison and relational operators
- Stream input/output support

### BigRational

- Exact rational arithmetic using arbitrary-precision integers
- Automatic fraction normalization using GCD
- Addition, subtraction, multiplication, division, and exponentiation
- Exact decimal conversion
- Automatic detection of recurring decimals using hash-based remainder tracking
- Comparison operators
- String and stream conversion utilities

---

## Project Structure

```text
.
├── include/
│   ├── BigInteger.h
│   └── BigRational.h
├── src/
│   ├── BigInteger.cpp
│   └── BigRational.cpp
├── tests/
├── examples/
├── CMakeLists.txt
└── README.md
```

---

## Design

The library follows an object-oriented architecture.

- **Encapsulation** keeps the internal digit representation hidden behind a clean public API.
- **Composition** is used by `BigRational`, which stores its numerator and denominator as `BigInteger` objects.
- **Operator overloading** enables arithmetic expressions to resemble native C++ numeric types.
- **Automatic normalization** ensures every rational number is stored in its reduced canonical form.

---

## Algorithms Used

| Component | Algorithm |
|-----------|-----------|
| Addition / Subtraction | Grade-school arithmetic |
| Multiplication | Schoolbook multiplication + Karatsuba multiplication |
| Division | Long division |
| GCD | Euclidean algorithm |
| Exponentiation | Binary exponentiation |
| Fraction Reduction | GCD normalization |
| Decimal Conversion | Long division |
| Recurring Decimal Detection | Hash-based remainder tracking (`std::unordered_map`) |

---

## Complexity

| Operation | Complexity |
|-----------|------------|
| Addition / Subtraction | O(n) |
| Multiplication | O(n²) for small operands, O(n^1.585) using Karatsuba for large operands |
| Division | O(n²) |
| GCD | Euclidean algorithm |
| Exponentiation | O(log p) multiplications |

---

## Example

```cpp
#include "BigInteger.h"
#include "BigRational.h"

using namespace bigint;

int main()
{
    BigInteger a("123456789123456789123456789");
    BigInteger b("987654321987654321987654321");

    std::cout << a * b << '\n';

    BigRational r1("22/7");

    std::cout << r1 << '\n';
    std::cout << r1.toDecimal() << '\n';

    BigRational r2("1/6");
    std::cout << r2.toDecimal() << '\n';
}
```

Example output

```text
22/7
3.(142857)

1/6
0.1(6)
```

---

## Building

Clone the repository

```bash
git clone <repository-url>
cd Arbitrary-Precision-Rational-Number-Library
```

Build using CMake

```bash
mkdir build
cd build

cmake ..
cmake --build .
```

Run

```bash
./YourExecutable
```

---

## Technologies

- C++17
- Standard Template Library (STL)
- CMake

---

## Future Improvements

- FFT-based multiplication for extremely large integers
- Faster division algorithms
- Additional mathematical functions
- Expanded benchmarking and test suite

---

## License

This project is licensed under the MIT License.
