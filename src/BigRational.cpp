
#include "BigRational.h"

#include <sstream>
#include <stdexcept>
#include <unordered_map>

namespace bigint
{

//--------------------------------------------------------------
// Constructors
//--------------------------------------------------------------

BigRational::BigRational()
    : numerator(0), denominator(1)
{
}

BigRational::BigRational(long long value)
    : numerator(value), denominator(1)
{
}

BigRational::BigRational(const BigInteger& num)
    : numerator(num), denominator(1)
{
}

BigRational::BigRational(const BigInteger& num,
                         const BigInteger& den)
    : numerator(num), denominator(den)
{
    if (denominator.isZero())
        throw std::runtime_error("Denominator cannot be zero");

    normalize();
}

BigRational::BigRational(const std::string& value)
{
    read(value);
}

//--------------------------------------------------------------
// Input Parsing
//--------------------------------------------------------------

void BigRational::read(const std::string& value)
{
    std::size_t slash = value.find('/');

    if (slash == std::string::npos)
    {
        numerator = BigInteger(value);
        denominator = BigInteger(1);
    }
    else
    {
        numerator = BigInteger(value.substr(0, slash));
        denominator = BigInteger(value.substr(slash + 1));

        if (denominator.isZero())
            throw std::runtime_error("Denominator cannot be zero");
    }

    normalize();
}

//--------------------------------------------------------------
// Normalization
//--------------------------------------------------------------

void BigRational::normalize()
{
    if (denominator.isZero())
        throw std::runtime_error("Denominator cannot be zero");

    BigInteger g = BigInteger::gcd(numerator.abs(),
                                   denominator.abs());

    numerator /= g;
    denominator /= g;

    // Keep denominator positive
    if (denominator.toString()[0] == '-')
    {
        denominator = -denominator;
        numerator = -numerator;
    }
}

//--------------------------------------------------------------
// String Conversion
//--------------------------------------------------------------

std::string BigRational::toString() const
{
    if (denominator == BigInteger(1))
        return numerator.toString();

    return numerator.toString() + "/" + denominator.toString();
}

//--------------------------------------------------------------
// Arithmetic Operators
//--------------------------------------------------------------

BigRational BigRational::operator+(const BigRational& rhs) const
{
    BigInteger num =
        numerator * rhs.denominator +
        rhs.numerator * denominator;

    BigInteger den =
        denominator * rhs.denominator;

    return BigRational(num, den);
}

BigRational BigRational::operator-(const BigRational& rhs) const
{
    BigInteger num =
        numerator * rhs.denominator -
        rhs.numerator * denominator;

    BigInteger den =
        denominator * rhs.denominator;

    return BigRational(num, den);
}

BigRational BigRational::operator*(const BigRational& rhs) const
{
    BigInteger num =
        numerator * rhs.numerator;

    BigInteger den =
        denominator * rhs.denominator;

    return BigRational(num, den);
}

BigRational BigRational::operator/(const BigRational& rhs) const
{
    if (rhs.numerator.isZero())
        throw std::runtime_error("Division by zero");

    BigInteger num =
        numerator * rhs.denominator;

    BigInteger den =
        denominator * rhs.numerator;

    return BigRational(num, den);
}

//--------------------------------------------------------------
// Compound Assignment
//--------------------------------------------------------------

BigRational& BigRational::operator+=(const BigRational& rhs)
{
    *this = *this + rhs;
    return *this;
}

BigRational& BigRational::operator-=(const BigRational& rhs)
{
    *this = *this - rhs;
    return *this;
}

BigRational& BigRational::operator*=(const BigRational& rhs)
{
    *this = *this * rhs;
    return *this;
}

BigRational& BigRational::operator/=(const BigRational& rhs)
{
    *this = *this / rhs;
    return *this;
}
//--------------------------------------------------------------
// Comparison Operators
//--------------------------------------------------------------

bool BigRational::operator==(const BigRational& rhs) const
{
    return numerator == rhs.numerator &&
           denominator == rhs.denominator;
}

bool BigRational::operator!=(const BigRational& rhs) const
{
    return !(*this == rhs);
}

bool BigRational::operator<(const BigRational& rhs) const
{
    return numerator * rhs.denominator <
           rhs.numerator * denominator;
}

bool BigRational::operator>(const BigRational& rhs) const
{
    return rhs < *this;
}

bool BigRational::operator<=(const BigRational& rhs) const
{
    return !(*this > rhs);
}

bool BigRational::operator>=(const BigRational& rhs) const
{
    return !(*this < rhs);
}

//--------------------------------------------------------------
// Power
//--------------------------------------------------------------

BigRational BigRational::pow(int exponent) const
{
    if (exponent == 0)
        return BigRational(1);

    if (exponent < 0)
    {
        BigRational inv(denominator, numerator);
        return inv.pow(-exponent);
    }

    BigRational base = *this;
    BigRational result(1);

    while (exponent > 0)
    {
        if (exponent & 1)
            result *= base;

        base *= base;
        exponent >>= 1;
    }

    return result;
}

//--------------------------------------------------------------
// Decimal Conversion
//--------------------------------------------------------------

std::string BigRational::toDecimal(int precision) const
{
    if (precision < 0)
        throw std::invalid_argument("Negative precision");

    BigInteger absoluteNumerator = numerator.abs();
    BigInteger integerPart = absoluteNumerator / denominator;
    BigInteger remainder = absoluteNumerator % denominator;

    std::string result = integerPart.toString();

    if (numerator < BigInteger(0))
        result.insert(result.begin(), '-');

    if (precision == 0 || remainder.isZero())
        return result;

    result += ".";
    std::string fractionalPart;
    std::unordered_map<std::string, int> remainderPositions;
    int repeatPosition = -1;

    while (static_cast<int>(fractionalPart.size()) < precision &&
           !remainder.isZero())
    {
        std::string key = remainder.toString();
        auto repeated = remainderPositions.find(key);

        if (repeated != remainderPositions.end())
        {
            repeatPosition = repeated->second;
            break;
        }

        remainderPositions.emplace(
            std::move(key),
            static_cast<int>(fractionalPart.size()));

        remainder *= BigInteger(10);

        BigInteger digit = remainder / denominator;
        remainder %= denominator;

        fractionalPart += digit.toString();
    }

    if (repeatPosition >= 0)
    {
        fractionalPart.insert(
            static_cast<std::size_t>(repeatPosition), "(");
        fractionalPart += ")";
    }

    result += fractionalPart;
    return result;
}

//--------------------------------------------------------------
// Stream Operators
//--------------------------------------------------------------

std::ostream& operator<<(std::ostream& out,
                         const BigRational& value)
{
    out << value.toString();
    return out;
}

std::istream& operator>>(std::istream& in,
                         BigRational& value)
{
    std::string s;
    in >> s;
    value.read(s);
    return in;
}

} // namespace bigint
