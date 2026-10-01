#include <iostream>
#include <numeric>
#include <vector>
using namespace std;

int find_even_index(const std::vector<int> numbers)
{
    if (numbers.size() < 2)
    {
        return 0;
    }

    int leftSum{0};
    int rightSum{std::accumulate(numbers.begin() + 1, numbers.end(), 0)};

    if (rightSum == 0)
    {
        return 0;
    }
    for (std::size_t i{1}; i < numbers.size(); ++i)
    {
        leftSum += numbers[i - 1];
        rightSum -= numbers[i];
        std::cout << "intex " << i << " leftsum " << leftSum << " rightsum "
                  << rightSum << '\n';
        if (leftSum == rightSum)
        {
            return static_cast<int>(i);
        }
    }

    return -1;
}

int main()
{
    vector<int> numbers{1, 2, 3, 4, 3, 2, 1};
    int index{find_even_index(numbers)};
    std::cout << "Thats the even index: " << index << '\n';
}
