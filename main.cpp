/*
simple file based login system based on: https://www.youtube.com/watch?v=I_aWPGCaaFA
*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int CHAR_COUNT = 94; // ASCII characters 33 - 126 will be considered valid in a password
const int SHIFT = 5;       // hard-coded Caesar cipher shift
const int ASCII_MIN = 33; // smallest ASCII character considered valid in a password
const string TEST_STRING = "!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";

bool isLoggedIn() {
    string username, password, un, pw;

    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    ifstream read(".\\data\\" + username + ".txt");
    getline(read, un);
    getline(read, pw);

    if (un == username && pw == password) {
        return true;
    } else {
        return false;
    }
}

string caesarCipher(string word, int shift, bool encrypt) {
    string result = "";
    for (int i = 0; i < word.length(); i++){
        if (encrypt){
            // shift to range 0..94, apply cipher, shift to range 33..126
            result += static_cast<char>((((static_cast<int>(word[i]) - ASCII_MIN) + SHIFT) % CHAR_COUNT) + ASCII_MIN);
        } else {
            // shift to range 0..94, apply cipher (accounting for negative numbers), shift to range 33..126
            result += static_cast<char>(((((static_cast<int>(word[i]) - ASCII_MIN) - SHIFT) % CHAR_COUNT + CHAR_COUNT) % CHAR_COUNT) + ASCII_MIN);
        }
    }
    return result;
}

int main() {
    int choice;

    cout << "1: Register\n2: Login\nYour Choice: ";
    cin >> choice;

    if (choice == 1) {
        string username, password;

        cout << "Enter a username: ";
        cin >> username;
        cout << "Enter a password: ";
        cin >> password;

        ofstream file;
        file.open(".\\data\\" + username + ".txt");
        file << username << endl << password;
        file.close();

        main();
    } else if (choice == 2) {
        bool status = isLoggedIn();

        if (!status) {
            cout << "Login failed!" << endl;
            system("PAUSE");
            return 0;
        } else {
            cout << "Successfully logged in!" << endl;
            system("PAUSE");
            return 1;
        }
    }
}