#include <iostream>
#include <main.hpp>
#include <romanNumeralConverter.h>

using namespace std;

int main(void) {
    RomanNumeralConverter converter;

    cout << "[YEAR] " << converter.get(2019) << endl;
    cout << "[MONTH] " << converter.get(12) << endl;
    cout << "[DAY] " << converter.get(22) << endl;
}