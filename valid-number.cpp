#include <string>
#include <vector>
using namespace std;


class Solution
{
public:
    const char *skipDigits(const char *c)
    {
        while (*c && *c >= '0' && *c <= '9')
        {
            ++c;
        }
        return c;
    }

    bool isNumber_c(const char *c)
    {
        bool can_have_sign = true, can_have_dot = true, can_have_exponent = true, had_digits=false;
        while (*c)
        {
            if (*c == '+' || *c == '-')
            {
                if (!can_have_sign)
                    return false;
                can_have_sign = false;
                had_digits = false;
                ++c;
                continue;
            }
            if (*c == '.')
            {
                if (!can_have_dot)
                    return false;
                can_have_dot = false;
                can_have_sign = false;
                ++c;
                continue;
            }
            const char *skipped = this->skipDigits(c);
            can_have_sign = false;
            if (c == skipped)
            {
                // is this exponent?
                if (*c == 'e' || *c == 'E')
                {
                    ++c;
                    if (!can_have_exponent || *c == '\0' || !had_digits)
                        return false;
                    can_have_exponent = false;
                    can_have_dot = false;
                    can_have_sign = true;
                    continue;
                }
                else
                {
                    return false;
                }
            } else {
                had_digits = true;
            }
            c = skipped;
        }
        return had_digits;
    }
    bool isNumber(string s)
    {
        return this->isNumber_c(s.c_str());
    }
};

#define ASSERT(x)                                               \
    if (!(x))                                                   \
    {                                                           \
        printf("Assertion failed! %s Line %d\n", #x, __LINE__); \
    };
#define ASSERT_V(x)                                                      \
    if (!(x))                                                            \
    {                                                                    \
        printf("Assertion failed! %s Line %d\n", val.c_str(), __LINE__); \
    };



int main(int argc, char **argv)
{
    auto s = Solution();
    ASSERT(!s.isNumber(".-4"));
    ASSERT(!s.isNumber("abc"));
    ASSERT(s.isNumber("+1.24E23"))
    ASSERT(s.isNumber("+1.24e23"))
    ASSERT(s.isNumber("-01.24e23"))
    ASSERT(!s.isNumber("-01.24.23"))
    vector<string> valids = {"2", "0089", "-0.1", "+3.14", "4.", "-.9", "2e10", "-90E3", "3e+7", "+6e-1", "53.5e93", "-123.456e789", "10.", "14e31"};
    vector<string> invalids = {"abc", "1a", "1e", "e3", "99e2.5", "--6", "-+3", "95a54e53", ".", ".e.e1", "-.", "4e+", ".-4"};
    for (auto &val : valids)
    {
        ASSERT_V(s.isNumber(val));
    }
    for (auto &val : invalids)
    {
        ASSERT_V(!s.isNumber(val));
    }

    return 0;
}