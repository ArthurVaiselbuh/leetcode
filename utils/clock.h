#include <chrono>
#include <iostream>
#include <string>

using namespace std::chrono;
using namespace std;

class Clock
{
public:
    high_resolution_clock::time_point start, end;
    string name;
    Clock(const string &name)
    {
        this->start = high_resolution_clock::now();
        this->name = name;
    }
    ~Clock()
    {
        auto end = high_resolution_clock::now();
        auto msec = duration_cast<nanoseconds>(end - this->start).count();
        cout << name << " took " << msec << endl;
    }
};