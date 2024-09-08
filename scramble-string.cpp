#include <string>
#include <vector>
#include <functional>
#include <numeric>

#include "utils.h"

using namespace std;

enum MemoizationResult
{
    UNSET = 0,
    TRUE,
    FALSE
};

class Solution
{
    // length->s1_index->s2_index->isScrambled
    vector<vector<vector<MemoizationResult>>> mMemoization;
    const char *mS1Start = nullptr;
    const char *mS2Start = nullptr;

public:
    bool isLetterCountEqual(const string_view &s1, const string_view &s2)
    {
        // Clock c("isLetterCountEqual");
        constexpr size_t lettercount = 'z' - 'a' + 1;
        vector<int> count1(lettercount, 0);
        vector<int> count2(lettercount, 0);
        for (const char &c : s1)
        {
            count1[c - 'a']++;
        }
        for (const char &c : s2)
        {
            count2[c - 'a']++;
        }
        for (int i = 0; i < lettercount; i++)
        {
            if (count1[i] != count2[i])
            {
                return false;
            }
        }
        return true;
    }
    bool letterCountApproxEqual(const string_view &s1, const string_view &s2)
    {
        // Clock c("letterCountApproxEqual");
        // Sum of letters approximation to know if both contain the same letters.
        return reduce(s1.begin(), s1.end()) == reduce(s2.begin(), s2.end());
    }

    // Return if s2 is a scrambled string of s1
    bool isScramble(string s1, string s2)
    {
        size_t size = s1.size();
        if (size != s2.size())
            return false;
        this->mS1Start = s1.c_str();
        this->mS2Start = s2.c_str();
        this->mMemoization = vector<vector<vector<MemoizationResult>>>(size,
                                                                       vector<vector<MemoizationResult>>(size, vector<MemoizationResult>(size, MemoizationResult::UNSET)));
        string_view sv1{s1};
        string_view sv2{s2};
        return isScramble(sv1, sv2);
    }

private:
    bool isScramble(string_view &s1, string_view &s2)
    {
        size_t size = s1.size();
        // heuristically compare letter numbers for long strings
        if (size == 1)
            return s1[0] == s2[0];
        if (!letterCountApproxEqual(s1, s2) || !isLetterCountEqual(s1, s2))
            return false;
        auto &memoizationRef = this->mMemoization[size-1][s1.data() - mS1Start][s2.data() - mS2Start];
        if (memoizationRef != MemoizationResult::UNSET)
            return memoizationRef == MemoizationResult::TRUE;

        for (int i = 1; i < size; i++)
        {
            auto remainder = size - i;
            // divide s1 into AB where A is of size i and B is of size remainder
            // then compare to CD or EF where C&F are of size i, and D&E are of size remainder in s2.
            auto A = s1.substr(0, i);
            auto B = s1.substr(i, remainder);
            auto C = s2.substr(0, i);
            auto D = s2.substr(i, remainder);
            if (isScramble(A, C) && isScramble(B, D))
            {
                memoizationRef = MemoizationResult::TRUE;
                return true;
            }
            auto E = s2.substr(0, remainder);
            auto F = s2.substr(remainder, i);
            if (isScramble(A, F) && isScramble(B, E))
            {
                memoizationRef = MemoizationResult::TRUE;
                return true;
            }
        }
        memoizationRef = MemoizationResult::FALSE;
        return false;
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
    ASSERT(!s.isScramble("eebaacbcbcadaaedceaaacadccd", "eadcaacabaddaceacbceaabeccd"));
    return 0;
}