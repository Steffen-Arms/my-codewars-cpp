#include <array>
#include <iostream>
#include <numeric>
#include <vector>

int nextValueHorizontal(std::size_t row, std::size_t columns,
                        std::vector<std::vector<int>>& field)
{
    if (columns + 1 == field.size() - 1)
    {
        return 0;
    }
    else
    {
        return field[row][columns + 1];
    }
}

int nextValueVertical(std::size_t row, std::size_t columns,
                      std::vector<std::vector<int>>& field)
{
    if (row + 1 == field.size() - 1)
    {
        return 0;
    }
    else
    {
        return field[row + 1][columns];
    }
};

// return the ship class of the founded ship and turn every 1 of this ship into
// a 0 so it will not be found again.
int foundShip(std::size_t row, std::size_t columns,
              std::vector<std::vector<int>>& field)
{

    // first we set the current coordinat to 0;
    field[row][columns] = 0;

    int shipClass{1}; // we increment this value for each new 1 we find.

    // the ship can only go to the right or down as we already scan the field
    // from up to down and left to right so we check in which direction the ship
    // go
    if (nextValueHorizontal(row, columns, field) == 1)
    {
        ++shipClass;
        ++columns;
        field[row][columns] = 0;
        if (nextValueHorizontal(row, columns, field) == 1)
        {
            ++shipClass;
            ++columns;
            field[row][columns] = 0;
            if (nextValueHorizontal(row, columns, field) == 1)
            {
                ++shipClass;
                ++columns;
                field[row][columns] = 0;
                if (nextValueHorizontal(row, columns, field) == 1)
                {
                    return -1; // ship is longer than 4
                }

                return shipClass;
            }
            else
            {
                return shipClass;
            }
        }
        else
        {
            return shipClass;
        }
    }
    else if (nextValueVertical(row, columns, field) == 1)
    {
        ++shipClass;
        ++row;
        field[row][columns] = 0;
        if (nextValueVertical(row, columns, field) == 1)
        {
            ++shipClass;
            ++row;
            field[row][columns] = 0;
            if (nextValueVertical(row, columns, field) == 1)
            {
                ++shipClass;
                ++row;
                field[row][columns] = 0;
                if (nextValueVertical(row, columns, field) == 1)
                {
                    return -1;
                }
                return shipClass;
            }
            else
            {
                return shipClass;
            }
        }
        else
        {
            return shipClass;
        }
    }
    else
    {
        return shipClass; // if there isn't a 1 right or down we know its a
                          // submarine
    }
}

////////////
int nextValueDiagonalRight(std::size_t row, std::size_t columns,
                           std::vector<std::vector<int>>& field)
{

    if (row + 1 == field.size() - 1)
    {
        return 0;
    }
    else if (columns + 1 == field.size() - 1)
    {
        return 0;
    }
    else
    {
        return field[row + 1][columns + 1];
    }
}

int nextValueDiagonalLeft(std::size_t row, std::size_t columns,
                          std::vector<std::vector<int>>& field)
{

    if (row + 1 == field.size() - 1)
    {
        return 0;
    }
    else if (columns == 0)
    {
        return 0;
    }
    else
    {
        return field[row + 1][columns - 1];
    }
}

bool validPositionOfShips(std::vector<std::vector<int>>& field)
{
    for (std::size_t row{0}; row < field.size() - 1; ++row)
    {
        for (std::size_t columns{0}; columns < field.size(); ++columns)
        {
            if (field[row][columns] == 1)
            {
                if (nextValueDiagonalRight(row, columns, field) == 1)
                {
                    return false;
                }
                else if (nextValueDiagonalLeft(row, columns, field) == 1)
                {
                    return false;
                }
                else if (nextValueHorizontal(row, columns, field) == 1 &&
                         nextValueVertical(row, columns, field) == 1)
                {
                    return false;
                }
            }
        }
    }
    return true;
}

bool validate_battlefield(std::vector<std::vector<int>> field)
{
    // first check if there are more ships presents that it is allow
    int sum{0};
    for (const auto& row : field)
    {
        sum += std::accumulate(row.begin(), row.end(), 0);
    }
    if (sum != 20)
    {
        return false;
    }
    if (!validPositionOfShips(field))
    {
        return false;
    }

    std::array<int, 4> foundShipClasses{};

    auto foundall = [&]()
    {
        return foundShipClasses[3] == 1 && foundShipClasses[2] == 2 &&
               foundShipClasses[1] == 3 && foundShipClasses[0] == 4;
    };

    std::size_t row{0};
    std::size_t columns{0};

    while (!foundall())
    {
        if (columns == field.size() - 1)
        {
            columns = 0;
            ++row;
        }
        if (row >= field.size())
        {
            return false; // something went wrong here
        }

        if (field[row][columns] == 1)
        {
            int shipClass = foundShip(row, columns, field);
            if (shipClass == -1)
            {
                return false;
            }
            ++foundShipClasses[static_cast<std::size_t>(shipClass) - 1];
        }

        ++columns;
    }

    return true;
}

int main()
{
    std::vector<std::vector<int>> battlefield{
        std::vector<int>{1, 0, 0, 0, 0, 1, 1, 0, 0, 0},
        std::vector<int>{1, 0, 1, 0, 0, 0, 0, 0, 1, 0},
        std::vector<int>{1, 0, 1, 0, 1, 1, 1, 0, 1, 0},
        std::vector<int>{1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        std::vector<int>{0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
        std::vector<int>{0, 0, 0, 0, 1, 1, 1, 0, 0, 0},
        std::vector<int>{0, 0, 0, 1, 0, 0, 0, 0, 1, 0},
        std::vector<int>{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        std::vector<int>{0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
        std::vector<int>{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

    std::cout << "battlefield is: " << validate_battlefield(battlefield)
              << '\n';

    return 1;
}
