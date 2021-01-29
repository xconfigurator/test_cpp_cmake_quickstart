#include <iostream>
#include "swap.h"

using namespace std;

int main (int argc, char* const argv[]) {
    int a = 10, b = 20;
    cout << "Before swap" << endl;
    cout << "a = " << a << ", b = " << b << endl;
    swap(a, b);
    cout << "After swap" << endl;
    cout << "a = " << a << ", b = " << b << endl;
    cout << "hello, cmake" << endl;
    return 0;
}