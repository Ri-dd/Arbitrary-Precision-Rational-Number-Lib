
#include "BigInteger.h"
#include "BigRational.h"

#include <cassert>
#include <iostream>

using namespace bigint;

void testBigInteger()
{
    BigInteger a("123456789");
    BigInteger b("987654321");

    assert((a + b).toString() == "1111111110");
    assert((b - a).toString() == "864197532");
    assert((a * b).toString() == "121932631112635269");
    assert((BigInteger("-123456789") * b).toString() ==
           "-121932631112635269");

    std::string largeValue(400, '9');
    BigInteger large(largeValue);
    assert((large * large).toString() ==
           std::string(399, '9') + "8" +
           std::string(399, '0') + "1");

    BigInteger c("100");
    BigInteger d("25");

    assert((c / d).toString() == "4");
    assert((c % d).toString() == "0");

    BigInteger e("-50");
    BigInteger f("20");

    assert((e + f).toString() == "-30");
    assert((e - f).toString() == "-70");
    assert((f - e).toString() == "70");

    assert(BigInteger::gcd(BigInteger("48"), BigInteger("18")).toString() == "6");

    std::cout << "[PASS] BigInteger Tests\n";
}

void testBigRational()
{
    BigRational a("1/2");
    BigRational b("1/3");

    assert((a + b).toString() == "5/6");
    assert((a - b).toString() == "1/6");
    assert((a * b).toString() == "1/6");
    assert((a / b).toString() == "3/2");

    BigRational c("4/8");
    assert(c.toString() == "1/2");

    BigRational d("2");
    assert(d.toString() == "2");

    assert(a > b);
    assert(b < a);
    assert(a != b);

    BigRational e("2/5");
    assert(e.toDecimal(10) == "0.4");
    assert(BigRational("1/2").toDecimal() == "0.5");
    assert(BigRational("1/4").toDecimal() == "0.25");
    assert(BigRational("1/3").toDecimal() == "0.(3)");
    assert(BigRational("2/3").toDecimal() == "0.(6)");
    assert(BigRational("1/6").toDecimal() == "0.1(6)");
    assert(BigRational("22/7").toDecimal() == "3.(142857)");
    assert(BigRational("1/11").toDecimal() == "0.(09)");
    assert(BigRational("50/8").toDecimal() == "6.25");
    assert(BigRational("-1/6").toDecimal() == "-0.1(6)");

    BigRational f("3/2");
    assert(f.pow(2).toString() == "9/4");

    std::cout << "[PASS] BigRational Tests\n";
}

int main()
{
    std::cout << "=============================\n";
    std::cout << " BigRational Library Tests\n";
    std::cout << "=============================\n\n";

    testBigInteger();
    testBigRational();

    std::cout << "\nAll tests passed successfully.\n";

    return 0;
}
