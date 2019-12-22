#include <romanNumeralConverter.h>
#include <string>
#include <iostream>

#define RNC RomanNumeralConverter

using namespace std;

string RNC::get(int input) {
    if(input <= 0) return "";

    string result = "";
    int val = input;

    while(val > 0) {
        int mviu = maxValueIndexUnder(val);
        val -= RNC::value[mviu];
        result = result + RNC::key[mviu];
    }

    return result;
}

int RNC::maxValueIndexUnder(int val) {
    int index = (sizeof(RNC::value) / sizeof(int)) - 1;

    for(; index >= 0; index--) {
        if(val >= RNC::value[index]) return index;
    }
}