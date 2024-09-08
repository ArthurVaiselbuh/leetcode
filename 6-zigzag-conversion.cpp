#include <string>
#include <vector>
#include <iostream>
#include <sstream>

using std::cout;
using std::ostringstream;
using std::string;
using std::vector;

#define DEBUG

class Solution
{
public:
    string convert(string s, int numRows)
    {
        vector<ostringstream> lines(numRows);
        int row = 0;
        bool directionIsDown = true;
        for (char &c : s)
        {
            
#ifdef DEBUG
            if (row != 0 && !directionIsDown)
            {
                for (int i = 0; i < numRows; i++)
                {
                    if (i != row)
                    {
                        lines[i] << ' ';
                    }
                    lines[i] << ' ';
                }
            }
#endif
            lines[row] << c;

            if (directionIsDown)
            {
                if (row == numRows - 1)
                {
                    directionIsDown = false;
                    --row;
                }
                else
                {
                    ++row;
                }
            }
            else
            {
                if (row == 0)
                {
                    directionIsDown = true;
                    ++row;
                }
                else
                {
                    --row;
                }
            }
            row = row % numRows;
        }
        ostringstream output;
        for (ostringstream &line : lines)
        {
            string str = line.str();
            cout << str << std::endl;
            output << str;
        }
        return output.str();
    }
};

int main(int argc, char **argv)
{
    auto s = Solution();
    auto output = s.convert("ABCDEFGHIJK", 4);
    printf("\n");
    cout << output << std::endl;
    return 0;
}