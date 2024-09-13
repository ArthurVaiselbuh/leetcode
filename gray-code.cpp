#include <vector>
#include <cstdlib>
#include <cmath>
#include <bitset>
#include <iostream>

using namespace std;

bool areNeighbors(int x, int y)
{
    int bitcount = 0;
    x = x ^ y;
    while (x && bitcount <= 1)
    {
        div_t res = div(x, 2);
        if (res.rem == 1)
        {
            bitcount++;
        }
        x = res.quot;
    }
    return bitcount == 1;
}

class Solution
{
public:
    vector<int> grayCode(int n)
    {
        if (n == 1)
            return vector<int>{0, 1};
        auto max_val = 1 << n; // non-inclusive
        auto base = grayCode(n - 1);
        vector<int> res;
        res.reserve(max_val);
        auto mask = max_val >> 1;
        for (auto cur = base.begin(); cur != base.end(); cur++)
        {
            res.push_back(*cur);
            res.push_back(mask | *cur);
            cur++;
            res.push_back(mask | *cur);
            res.push_back(*cur);
        }
        return res;
    }
};

void printGreyCode(vector<int> &gc)
{
    for (auto v : gc)
    {
        cout << bitset<8>(v) << '\t' << v << endl;
    }
    cout << endl;
}

int main(int argc, char **argv)
{
    auto s = Solution();
    auto res = s.grayCode(3);
    printGreyCode(res);
    return 0;
}