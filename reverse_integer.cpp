#include <math.h>
#include <limits>

using namespace std;

class Solution {
public:
    int reverse(int x) {
        constexpr int MAX_TO_MULT = numeric_limits<int>::max() / 10;
        if (x == numeric_limits<int>::min())
        {
            return 0;
        }
        int sign = x < 0 ? -1 : 1;
        x = abs(x);
        int ret = 0;
        while (x)
        {
            auto res = div(x, 10);
            x = res.quot;
            if (ret > MAX_TO_MULT)
                return 0;
            ret = ret * 10;
            if (ret > numeric_limits<int>::max() - res.rem)
                return 0;
            ret += res.rem;
        }
        return sign * ret;
    }
};