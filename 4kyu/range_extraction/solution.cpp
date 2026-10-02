#include <iostream>
#include <string>
#include <vector>

std::string range_extraction(std::vector<int> args)
{
    std::vector<std::vector<int>> sequences;
    for (int x : args)
    {
        if (sequences.empty() || x != sequences.back().back() + 1)
        {
            sequences.emplace_back();
        }
        sequences.back().push_back(x);
    }

    std::string solution;

    for (auto range : sequences)
    {
        if (range.size() == 1)
        {
            solution.append(std::to_string(range[0]));
            solution.append(", ");
        }
        else if (range.size() == 2)
        {
            solution.append(std::to_string(range[0]));
            solution.append(",");
            solution.append(std::to_string(range[1]));
            solution.append(",");
        }
        else
        {
            solution.append(std::to_string(range.front()));
            solution.append("-");
            solution.append(std::to_string(range.back()));
            solution.append(",");
        }
    }
    solution.pop_back(); // remove the last , symbol

    return solution;
}

// benefit of refactored solution is that you don't have to save all
// subsequences but only the index range. keep one single point of truth which
// is args
std::string refactor_range_extraction(std::vector<int> args)
{

    using Range = std::pair<int, int>;
    std::vector<Range> ranges;
    for (auto& i : args)
    {
        if (ranges.empty() || ranges.back().second + 1 != i)
        {
            ranges.push_back({i, i});
        }
        else
        {
            ++ranges.back().second;
        }
    }
    std::string result;
    for (auto& r : ranges)
    {
        if (r.first == r.second)
        {
            result.append(std::to_string(r.first) + ",");
        }
        else
        {
            result.append(std::to_string(r.first) +
                          ((r.first + 1 == r.second) ? ',' : '-') +
                          std::to_string(r.second) + ',');
        }
    }
    result.pop_back();
    return result;
}

int main()
{
    std::vector<int> test = {-6, -3, -2, -1, 0,  1,  3,  4,  5,  7,
                             8,  9,  10, 11, 14, 15, 17, 18, 19, 20};
    std::cout << "test: " << range_extraction(test) << '\n';

    std::cout << "test2: " << refactor_range_extraction(test) << '\n';
}
