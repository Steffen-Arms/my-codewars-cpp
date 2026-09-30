#include <array>
#include <cctype>
#include <iostream>
#include <map>
#include <string>

// return true if he finds the same character in a later index than i.
bool accureOnce(const std::string& word, std::size_t i)
{
    if (word.size() == i)
    {
        return true;
    }

    for (std::size_t j{i + 1}; j < word.size(); ++j)
    {
        if (std::tolower(word[j]) == std::tolower(word[i]))
        {
            return false;
        }
    }
    return true;
}

void replaceCloseBrace(std::string& encodedWord, std::size_t i)
{
    for (std::size_t j{encodedWord.size() - 1}; j >= i; --j)
    {
        if (std::tolower(encodedWord[j]) == (std::tolower(encodedWord[i])))
        {
            encodedWord[j] = ')';
        }
        if (j == 0)
        {
            break;
        }
    }
}

std::string duplicate_encoder(const std::string& word)
{

    std::string encodedWord{word};

    for (std::size_t i{0}; i < static_cast<std::size_t>(word.size()); ++i)
    {
        // if they are not the same it mean we already change the character in a
        // previous round.
        if (encodedWord[i] == word[i])
        {
            if (!accureOnce(word, i))
            {
                replaceCloseBrace(encodedWord, i);
            }
            else
            {
                // as we know there is only one accurance of this character we
                // can only change this.
                encodedWord[i] = '(';
            }
        }
    }

    return encodedWord;
}

// most elegang version from solution
// downside of this. create database map
// only replace one character at a time
// useless counting of character appearing mowe than two times
std::string duplicate_encoder_refactor(const std::string& word)
{
    std::map<int, int> table;

    for (auto x : word)
    {
        table[std::tolower(x)]++;
    }

    std::string result;
    for (auto x : word)
        result += (table[std::tolower(x)] == 1) ? '(' : ')';

    return result;
}

// another refactor solution. map may not be the optimal data structur here
// since there are only 256 possible char
std::string duplicate_encoder_refactor2(const std::string& word)
{
    std::array<int, 256> count{};

    for (char x : word)
    {
        ++count[static_cast<unsigned char>(
            std::tolower(static_cast<unsigned char>(x)))];
    }
    std::string result;
    result.reserve(word.size());
    for (char x : word)
    {
        result += (count[static_cast<unsigned char>(
                       std::tolower(static_cast<unsigned char>(x)))] == 1)
                      ? '('
                      : ')';
    }
    return result;
}

int main()
{
    std::cout << duplicate_encoder("Success") << '\n';
    std::cout << duplicate_encoder_refactor("Success") << '\n';
    std::cout << duplicate_encoder_refactor2("Success") << '\n';
}
