#include <algorithm>
#include <iostream>
#include <vector>

std::vector<int> move_zeroes(const std::vector<int>& input)
{
    auto solution{input};
    std::stable_partition(solution.begin(), solution.end(),
                          [](int x) { return x != 0; });
    return solution;
}

int main()
{
    std::vector<int> vectorTMP{1, 2, 0, 1, 0, 1, 0, 3, 0, 1};
    std::vector<int> solution{move_zeroes(vectorTMP)};
    for (auto v : solution)
    {
        std::cout << v << " ";
    }
}
