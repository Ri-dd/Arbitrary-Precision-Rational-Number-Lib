
#pragma once

#include "BigInteger.h"

#include <iostream>
#include <string>

namespace bigint
{

class BigRational
{
public:

    // Constructors
    BigRational();
    BigRational(long long value);
    BigRational(const BigInteger& numerator);
    BigRational(const BigInteger& numerator,
                const BigInteger& denominator);
    explicit BigRational(const std::string& value);

    // Conversion
    std::string toString() const;
    std::string toDecimal(int precision = 20) const;

    // Arithmetic
    BigRational operator+(const BigRational& rhs) const;
    BigRational operator-(const BigRational& rhs) const;
    BigRational operator*(const BigRational& rhs) const;
    BigRational operator/(const BigRational& rhs) const;

    BigRational& operator+=(const BigRational& rhs);
    BigRational& operator-=(const BigRational& rhs);
    BigRational& operator*=(const BigRational& rhs);
    BigRational& operator/=(const BigRational& rhs);

    // Comparison
    bool operator==(const BigRational& rhs) const;
    bool operator!=(const BigRational& rhs) const;
    bool operator<(const BigRational& rhs) const;
    bool operator>(const BigRational& rhs) const;
    bool operator<=(const BigRational& rhs) const;
    bool operator>=(const BigRational& rhs) const;

    // Utility
    BigRational pow(int exponent) const;

    // Stream Operators
    friend std::ostream& operator<<(std::ostream& out,
                                    const BigRational& value);

    friend std::istream& operator>>(std::istream& in,
                                    BigRational& value);

private:

    BigInteger numerator;
    BigInteger denominator;

    void normalize();
    void read(const std::string& value);
};

} // namespace bigint
