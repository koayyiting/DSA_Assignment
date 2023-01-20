// DSA_Assignment.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;

int main()
{
    cout << "Welcome to C++ forum" << endl;
    cout << "1. Log in" << endl;
    cout << "2. Sign up" << endl;
    cout << "0. Exit program" << endl;
    string option;
    cout << "Enter an option: ";
    cin >> option;
    if (option == "1") {
        cout << "Log in" << endl;
    }
    else if (option == "2") {
        cout << "Sign up" << endl;
    }
    else if (option == "0") {
        cout << "Exit program" << endl;
    }
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
