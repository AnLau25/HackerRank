#include <iostream>
#include <vector>
#include <string>
#include <algorithm>  // for ltrim, rtrim
#include <sstream>    // for split
#include <compare>    // for spaceship operator (C++20)
#include <iomanip> 
using namespace std;

/*
 * Debug the given function findPrimeDates and/or other lines of code, to find the correct lucky dates from the given input.
 *
 * You can modify at most five lines in the given code.
 * You cannot add or remove lines to the code.
 */

int month[15];

void updateLeapYear(int year) {
    if(year % 400 == 0) {
        month[2] = 29; // mod 4
    } else if(year % 100 == 0) {
        month[2] = 29; // mod 5 
    } else if(year % 4 == 0) {
        month[2] = 29;
    } else {
        month[2] = 28;
    }
}

void storeMonth() {
    month[1] = 31;
    month[2] = 28;
    month[3] = 31;
    month[4] = 30;
    month[5] = 31;
    month[6] = 30;
    month[7] = 31;
    month[8] = 31;
    month[9] = 30;
    month[10] = 31;
    month[11] = 30;
    month[12] = 31;
}

int findLuckyDates(int d1, int m1, int y1, int d2, int m2, int y2) {
    storeMonth();

    int result = 0;

    while(true) {
        int x = d1;
        x = x * 100 + m1;
        x = x * 10000 + y1; // mod 1
        if(x % 4 == 0 || x % 7 == 0) { // mod 2
            result = result + 1;
        }
        if(d1 == d2 && m1 == m2 && y1 == y2) {
            break;
        }
        updateLeapYear(y1);
        d1 = d1 + 1;
        if(d1 > month[m1]) {
            m1 = m1 + 1;
            d1 = 1;
            if(m1 > 12) {
                y1 =  y1 + 1;
                m1 = 1; // mod 3
            }
        }
    }
    return result;
}

int main() {
    string str;
    int d1, m1, y1, d2, m2, y2;
    getline(cin, str);
    for(int i = 0; i < str.size(); i++) {
        if(str[i] == '-') {
            str[i] = ' ';
        }
    }
    stringstream ss;
    ss << str;
    ss >> d1 >> m1 >> y1 >> d2 >> m2 >> y2;

    int result = findLuckyDates(d1, m1, y1, d2, m2, y2);
    cout << result << endl;
}


/* 
Input format:
1. 6 <length of array>
2. 5 5 6 7 6 5 <space separated array>
*/