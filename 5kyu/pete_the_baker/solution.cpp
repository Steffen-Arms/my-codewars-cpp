#include <iostream>
#include <limits>
#include <string>
#include <unordered_map>

using Ingredients = std::unordered_map<std::string, int>;

// assume each ingredients amount is > 0
int cakes(const Ingredients& recipe, const Ingredients& available)
{
    if (recipe.empty())
        return 0;

    int ans = std::numeric_limits<int>::max();

    for (const auto& [name, amount] : recipe)
    {
        auto it = available.find(name);
        if (it == available.end())
            return 0;
        ans = std::min(ans, it->second / amount);
    }
    return ans;
}

int main()
{
    Ingredients recipe = {{"flour", 500}, {"sugar", 200}, {"eggs", 1}},
                available = {{"flour", 1200},
                             {"sugar", 1200},
                             {"eggs", 5},
                             {"milk", 200}};

    int result = cakes(recipe, available);
    std::cout << "amount of cake: " << result << '\n';
}
