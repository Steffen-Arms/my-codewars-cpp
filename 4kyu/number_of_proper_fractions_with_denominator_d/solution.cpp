#include <iostream>
#include <numeric>
#include <vector>

void setNotCompatible(std::size_t i, std::vector<long>& compatibleNum)
{
    for (std::size_t j = i; j < compatibleNum.size(); j += i)
    {
        compatibleNum[j] = 0;
    }
};

long properFractions(long n)
{
    if (n == 1)
    {
        return 0;
    }
    else if (n == 2)
    {
        return 1;
    }
    const auto size = static_cast<std::size_t>(n);

    std::vector<long> compatibleNum(
        size + 1,
        1); // we will set not compatible numbers to 0
    // we will use the fact that the index is the same number represented in the
    // vector of this index
    // note index 0 we will set manual to 0 as we only do this so the index is
    // equal to the value it represent
    compatibleNum[0] = 0;

    for (std::size_t i{2}; i <= size; ++i)
    {

        if (compatibleNum[i] == 0)
        {
            continue;
        }
        if (size % i == 0)
        {
            setNotCompatible(i, compatibleNum);
        }
    }

    return std::accumulate(compatibleNum.begin(), compatibleNum.end(), 0L);
}

long refactor_properFractions(long n)
{
    if (n == 1)
        return 0;

    long result = n;
    for (long p = 2; p <= n / p; ++p)
    {
        if (n % p == 0)
        {
            while (n % p == 0)
                n /= p; // remove this prime factor completely. smart n contain
                        // the information indirectly which prime factors it
                        // contains, which division we delete all multiples of
                        // this prime factor in this number.
            result -= result / p;
        }
    }
    if (n > 1)
        result -= result / n; // one prime factor larger than sqrt(n) is left

    return result;
}

int main()
{
    long test{25};
    std::cout << "test: " << properFractions(test) << '\n';
    std::cout << "test: " << refactor_properFractions(test) << '\n';
}
