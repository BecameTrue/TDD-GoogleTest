#include <string>

using namespace std;

class RomanNumeralConverter {
public:
    string get(int input);
    const string key[7] = {"I", "V", "X", "L", "C", "D", "M"};
    const int value[7] = {1, 5, 10, 50, 100, 500, 1000};
private:
    int maxValueIndexUnder(int val);
};