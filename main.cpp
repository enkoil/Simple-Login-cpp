/*
simple file based login system based on: https://www.youtube.com/watch?v=I_aWPGCaaFA
*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

bool isLoggedIn() {
    string username, password, un, pw;

    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    ifstream read("data\\" + username + ".txt");
    getline(read, un);
    getline(read, pw);

    if (un == username && pw == password) {
        return true;
    } else {
        return false;
    }
}