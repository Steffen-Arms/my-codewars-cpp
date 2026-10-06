#include <iostream>
#include <string>

// Notes for decoding
// Symbols !@#$%^&*()_+- don't get encoded at all
// All time same encoding scrint, so no random seed.

// assuming encoding algorithm:
// the symbols that are endocded are ordered like "a...z A .. Z 0 ... 9  "." ","
// "?" " " (the last ist the empty string) new character is computet with c +
// 2⁽p+1) here c is the character number and p is the position the character
// numbers start with 1 and the position start with 0.
//  so "a" have character value 1 and position 0

struct Decoder
{
    static std::string decode(const std::string& p_what)
    {
        static const std::string alpha = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJK"
                                         "LMNOPQRSTUVWXYZ0123456789.,? ";
        std::string out;
        std::size_t inv = 1;
        // 34 is the inverse of 2 in the modulo 67 space
        for (char ch : p_what)
        {
            inv = inv * 34 %
                  67; // here we compute the number to decode the character
            auto pos = alpha.find(ch);
            if (pos == std::string::npos)
            {
                out += ch; // character is not encoded. We take it as it is.
            }
            else
            {
                out += alpha[(pos + 1) * inv % 67 - 1];
            }
        }
        return out;
    }
};

int main()
{
    std::string test{"atC5kc.uKAr"};
    std::cout << "test: " << Decoder::decode(test) << '\n';
}
