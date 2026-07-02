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
    BigInteger operator-() const;

    BigInteger& operator+=(const BigInteger&);
    BigInteger& operator-=(const BigInteger&);
    BigInteger& operator*=(const BigInteger&);
    BigInteger& operator/=(const BigInteger&);
    BigInteger& operator%=(const BigInteger&);

    BigInteger& operator++();
    BigInteger operator++(int);
    BigInteger& operator--();
    BigInteger operator--(int);

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
    static std::vector<int> multiplySchoolbook(
        const std::vector<int>&,
        const std::vector<int>&);
    static std::vector<int> multiplyKaratsuba(
        const std::vector<int>&,
        const std::vector<int>&);
    static std::vector<int> addDigits(
        const std::vector<int>&,
        const std::vector<int>&);
    static std::vector<int> subtractDigits(
        const std::vector<int>&,
        const std::vector<int>&);
    static void addShifted(std::vector<int>&,
                           const std::vector<int>&,
                           std::size_t);
    static void trimDigits(std::vector<int>&);
};

}
