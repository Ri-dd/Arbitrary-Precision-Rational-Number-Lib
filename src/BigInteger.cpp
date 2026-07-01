
#include "BigInteger.h"

#include <algorithm>
#include <iomanip>
#include <sstream>
#include <stdexcept>

namespace bigint
{

//--------------------------------------------------------------
// Constructors
//--------------------------------------------------------------

BigInteger::BigInteger()
    : digits(1, 0), negative(false)
{
}

BigInteger::BigInteger(long long value)
{
    negative = value < 0;

    unsigned long long num;

    if (negative)
        num = static_cast<unsigned long long>(-(value + 1)) + 1;
    else
        num = static_cast<unsigned long long>(value);

    if (num == 0)
    {
        digits = {0};
        negative = false;
        return;
    }

    while (num)
    {
        digits.push_back(num % BASE);
        num /= BASE;
    }
}

BigInteger::BigInteger(const std::string& value)
{
    read(value);
}

//--------------------------------------------------------------
// Input Parsing
//--------------------------------------------------------------

void BigInteger::read(const std::string& value)
{
    digits.clear();
    negative = false;

    if (value.empty())
        throw std::invalid_argument("Invalid integer");

    int pos = 0;

    if (value[pos] == '-')
    {
        negative = true;
        ++pos;
    }
    else if (value[pos] == '+')
    {
        ++pos;
    }

    if (pos >= static_cast<int>(value.size()))
        throw std::invalid_argument("Invalid integer");

    while (pos < static_cast<int>(value.size()) && value[pos] == '0')
        ++pos;

    if (pos == static_cast<int>(value.size()))
    {
        digits = {0};
        negative = false;
        return;
    }

    for (int i = pos; i < static_cast<int>(value.size()); i++)
    {
        if (!std::isdigit(value[i]))
            throw std::invalid_argument("Invalid integer");
    }

    for (int end = value.size(); end > pos; end -= 9)
    {
        int start = std::max(pos, end - 9);

        digits.push_back(
            std::stoi(value.substr(start, end - start))
        );
    }

    trim();
}

//--------------------------------------------------------------
// Utility
//--------------------------------------------------------------

void BigInteger::trim()
{
    while (digits.size() > 1 && digits.back() == 0)
        digits.pop_back();

    if (digits.size() == 1 && digits[0] == 0)
        negative = false;
}

bool BigInteger::isZero() const
{
    return digits.size() == 1 && digits[0] == 0;
}

BigInteger BigInteger::abs() const
{
    BigInteger result(*this);
    result.negative = false;
    return result;
}

std::string BigInteger::toString() const
{
    std::ostringstream out;

    if (negative)
        out << '-';

    out << digits.back();

    for (int i = static_cast<int>(digits.size()) - 2; i >= 0; --i)
    {
        out << std::setw(9)
            << std::setfill('0')
            << digits[i];
    }

    return out.str();
}

//--------------------------------------------------------------
// Comparison Helpers
//--------------------------------------------------------------

int BigInteger::compareAbs(const BigInteger& lhs,
                           const BigInteger& rhs)
{
    if (lhs.digits.size() != rhs.digits.size())
    {
        return lhs.digits.size() < rhs.digits.size() ? -1 : 1;
    }

    for (int i = static_cast<int>(lhs.digits.size()) - 1; i >= 0; --i)
    {
        if (lhs.digits[i] != rhs.digits[i])
        {
            return lhs.digits[i] < rhs.digits[i] ? -1 : 1;
        }
    }

    return 0;
}

//--------------------------------------------------------------
// Comparison Operators
//--------------------------------------------------------------

bool BigInteger::operator==(const BigInteger& rhs) const
{
    return negative == rhs.negative &&
           digits == rhs.digits;
}

bool BigInteger::operator!=(const BigInteger& rhs) const
{
    return !(*this == rhs);
}

bool BigInteger::operator<(const BigInteger& rhs) const
{
    if (negative != rhs.negative)
        return negative;

    int cmp = compareAbs(*this, rhs);

    if (!negative)
        return cmp < 0;

    return cmp > 0;
}

bool BigInteger::operator>(const BigInteger& rhs) const
{
    return rhs < *this;
}

bool BigInteger::operator<=(const BigInteger& rhs) const
{
    return !(*this > rhs);
}

bool BigInteger::operator>=(const BigInteger& rhs) const
{
    return !(*this < rhs);
}

//--------------------------------------------------------------
// Addition
//--------------------------------------------------------------

BigInteger BigInteger::operator+(const BigInteger& rhs) const
{
    // Same sign -> normal addition
    if (negative == rhs.negative)
    {
        BigInteger result;
        result.digits.clear();
        result.negative = negative;

        long long carry = 0;

        size_t n = std::max(digits.size(), rhs.digits.size());

        for (size_t i = 0; i < n || carry; ++i)
        {
            long long cur = carry;

            if (i < digits.size())
                cur += digits[i];

            if (i < rhs.digits.size())
                cur += rhs.digits[i];

            result.digits.push_back(cur % BASE);
            carry = cur / BASE;
        }

        result.trim();
        return result;
    }

    // a + (-b) = a - b
    if (negative)
    {
        BigInteger temp = *this;
        temp.negative = false;
        return rhs - temp;
    }

    // (-a) + b = b - a
    BigInteger temp = rhs;
    temp.negative = false;
    return *this - temp;
}

BigInteger& BigInteger::operator+=(const BigInteger& rhs)
{
    *this = *this + rhs;
    return *this;
}

//--------------------------------------------------------------
// Subtraction
//--------------------------------------------------------------

BigInteger BigInteger::operator-(const BigInteger& rhs) const
{
    // a - (-b)
    if (!negative && rhs.negative)
    {
        BigInteger temp = rhs;
        temp.negative = false;
        return *this + temp;
    }

    // (-a) - b
    if (negative && !rhs.negative)
    {
        BigInteger temp = *this;
        temp.negative = false;

        BigInteger result = temp + rhs;
        result.negative = true;
        result.trim();
        return result;
    }

    // (-a) - (-b)
    if (negative && rhs.negative)
    {
        BigInteger a = rhs;
        BigInteger b = *this;

        a.negative = false;
        b.negative = false;

        return a - b;
    }

    // Both positive

    if (compareAbs(*this, rhs) < 0)
    {
        BigInteger result = rhs - *this;
        result.negative = true;
        result.trim();
        return result;
    }

    BigInteger result;
    result.digits.clear();

    long long borrow = 0;

    for (size_t i = 0; i < digits.size(); ++i)
    {
        long long cur = digits[i] - borrow;

        if (i < rhs.digits.size())
            cur -= rhs.digits[i];

        if (cur < 0)
        {
            cur += BASE;
            borrow = 1;
        }
        else
        {
            borrow = 0;
        }

        result.digits.push_back(cur);
    }

    result.trim();
    return result;
}

BigInteger& BigInteger::operator-=(const BigInteger& rhs)
{
    *this = *this - rhs;
    return *this;
}
//--------------------------------------------------------------
// Multiplication
//--------------------------------------------------------------

BigInteger BigInteger::operator*(const BigInteger& rhs) const
{
    BigInteger result;

    result.negative = (negative != rhs.negative);
    result.digits.assign(digits.size() + rhs.digits.size(), 0);

    for (size_t i = 0; i < digits.size(); ++i)
    {
        long long carry = 0;

        for (size_t j = 0; j < rhs.digits.size() || carry; ++j)
        {
            long long cur = result.digits[i + j] + carry;

            if (j < rhs.digits.size())
                cur += 1LL * digits[i] * rhs.digits[j];

            result.digits[i + j] = cur % BASE;
            carry = cur / BASE;
        }
    }

    result.trim();

    if (result.isZero())
        result.negative = false;

    return result;
}

BigInteger& BigInteger::operator*=(const BigInteger& rhs)
{
    *this = *this * rhs;
    return *this;
}

//--------------------------------------------------------------
// Unary Minus
//--------------------------------------------------------------

BigInteger BigInteger::operator-() const
{
    BigInteger result(*this);

    if (!result.isZero())
        result.negative = !result.negative;

    return result;
}

//--------------------------------------------------------------
// Increment / Decrement
//--------------------------------------------------------------

BigInteger& BigInteger::operator++()
{
    *this += BigInteger(1);
    return *this;
}

BigInteger BigInteger::operator++(int)
{
    BigInteger temp(*this);
    ++(*this);
    return temp;
}

BigInteger& BigInteger::operator--()
{
    *this -= BigInteger(1);
    return *this;
}

BigInteger BigInteger::operator--(int)
{
    BigInteger temp(*this);
    --(*this);
    return temp;
}
//--------------------------------------------------------------
// Division
//--------------------------------------------------------------

BigInteger BigInteger::operator/(const BigInteger& rhs) const
{
    if (rhs.isZero())
        throw std::runtime_error("Division by zero");

    BigInteger dividend = this->abs();
    BigInteger divisor = rhs.abs();

    if (compareAbs(dividend, divisor) < 0)
        return BigInteger(0);

    BigInteger quotient;
    quotient.digits.assign(dividend.digits.size(), 0);

    BigInteger current;

    for (int i = static_cast<int>(dividend.digits.size()) - 1; i >= 0; --i)
    {
        current.digits.insert(current.digits.begin(), dividend.digits[i]);
        current.trim();

        int low = 0;
        int high = BASE - 1;
        int best = 0;

        while (low <= high)
        {
            int mid = low + (high - low) / 2;

            BigInteger prod = divisor * BigInteger(mid);

            if (compareAbs(prod, current) <= 0)
            {
                best = mid;
                low = mid + 1;
            }
            else
            {
                high = mid - 1;
            }
        }

        quotient.digits[i] = best;
        current -= divisor * BigInteger(best);
    }

    quotient.trim();

    quotient.negative = (negative != rhs.negative);

    if (quotient.isZero())
        quotient.negative = false;

    return quotient;
}

//--------------------------------------------------------------
// Modulo
//--------------------------------------------------------------

BigInteger BigInteger::operator%(const BigInteger& rhs) const
{
    if (rhs.isZero())
        throw std::runtime_error("Modulo by zero");

    BigInteger q = (*this) / rhs;
    BigInteger r = (*this) - q * rhs;

    if (r.negative)
        r += rhs.abs();

    return r;
}

BigInteger& BigInteger::operator/=(const BigInteger& rhs)
{
    *this = *this / rhs;
    return *this;
}

BigInteger& BigInteger::operator%=(const BigInteger& rhs)
{
    *this = *this % rhs;
    return *this;
}
//--------------------------------------------------------------
// Greatest Common Divisor
//--------------------------------------------------------------

BigInteger BigInteger::gcd(BigInteger a, BigInteger b)
{
    a.negative = false;
    b.negative = false;

    while (!b.isZero())
    {
        BigInteger rem = a % b;
        a = b;
        b = rem;
    }

    return a;
}

//--------------------------------------------------------------
// Stream Operators
//--------------------------------------------------------------

std::ostream& operator<<(std::ostream& out,
                         const BigInteger& value)
{
    out << value.toString();
    return out;
}

std::istream& operator>>(std::istream& in,
                         BigInteger& value)
{
    std::string s;
    in >> s;
    value.read(s);
    return in;
}

} // namespace bigint
