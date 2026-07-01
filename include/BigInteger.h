#pragma once

#include <iostream>
#include <string>
#include <vector>

namespace bigint
{

class BigInteger
{
public:

    BigInteger();
    BigInteger(long long value);
    explicit BigInteger(const std::string& value);

    std::string toString() const;

    bool isZero() const;
    BigInteger abs() const;

    BigInteger operator+(const BigInteger&) const;
    BigInteger operator-(const BigInteger&) const;
    BigInteger operator*(const BigInteger&) const;
    BigInteger operator/(const BigInteger&) const;
    BigInteger operator%(const BigInteger&) const;

    BigInteger& operator+=(const BigInteger&);
    BigInteger& operator-=(const BigInteger&);
    BigInteger& operator*=(const BigInteger&);
    BigInteger& operator/=(const BigInteger&);
    BigInteger& operator%=(const BigInteger&);

    bool operator==(const BigInteger&) const;
    bool operator!=(const BigInteger&) const;
    bool operator<(const BigInteger&) const;
    bool operator>(const BigInteger&) const;
    bool operator<=(const BigInteger&) const;
    bool operator>=(const BigInteger&) const;

    friend std::ostream& operator<<(std::ostream&, const BigInteger&);
    friend std::istream& operator>>(std::istream&, BigInteger&);

    static BigInteger gcd(BigInteger, BigInteger);

private:

    static constexpr int BASE = 1000000000;

    std::vector<int> digits;
    bool negative;

    void trim();
    void read(const std::string&);

    static int compareAbs(const BigInteger&, const BigInteger&);
};

}
