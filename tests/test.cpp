
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
    std::cout << "2/5 = " << e.toDecimal(10) << '\n';

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
