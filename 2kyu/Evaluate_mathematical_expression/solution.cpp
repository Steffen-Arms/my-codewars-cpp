#include <cctype>
#include <iostream>
#include <string>

namespace
{

struct Parser
{
    const std::string& s;
    std::size_t i = 0;

    void skipSpaces()
    {
        while (i < s.size() && std::isspace(static_cast<unsigned char>(s[i])))
            ++i;
    }

    // expression = term (('+' | '-') term)*
    double expression()
    {
        double value = term();
        while (true)
        {
            skipSpaces();
            if (i >= s.size() || (s[i] != '+' && s[i] != '-'))
                return value;
            char op = s[i++];
            double rhs = term();
            value = (op == '+') ? value + rhs : value - rhs;
        }
    }

    // term = factor (('*' | '/') factor)*
    double term()
    {
        double value = factor();
        while (true)
        {
            skipSpaces();
            if (i >= s.size() || (s[i] != '*' && s[i] != '/'))
                return value;
            char op = s[i++];
            double rhs = factor();
            value = (op == '*') ? value * rhs : value / rhs;
        }
    }

    // factor = '-' factor | '(' expression ')' | number
    double factor()
    {
        skipSpaces();
        if (s[i] == '-')
        {
            ++i;
            return -factor();
        }
        if (s[i] == '(')
        {
            ++i; // skip '('
            double value = expression();
            skipSpaces();
            ++i; // skip ')'
            return value;
        }
        std::size_t start = i;
        while (i < s.size() &&
               (std::isdigit(static_cast<unsigned char>(s[i])) || s[i] == '.'))
        {
            ++i;
        }
        return std::stod(s.substr(start, i - start));
    }
};

} // namespace

double calc(std::string expression)
{
    Parser parser{expression};
    return parser.expression();
}

int main() { std::cout << calc("8/16") << '\n'; }
