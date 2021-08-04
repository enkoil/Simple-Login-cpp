/*
simple file based login system based on: https://www.youtube.com/watch?v=I_aWPGCaaFA
*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int CHAR_COUNT = 94; // ASCII characters 33 - 126 will be considered valid in a password
const int ASCII_MIN = 33; // smallest ASCII character considered valid in a password

string caesarCipher(string word, int shift) {
    string result = "";
    for (int i = 0; i < word.length(); i++){
        // shift to range 0..94, apply cipher, shift to range 33..126
        result += static_cast<char>((((static_cast<int>(word[i]) - ASCII_MIN) + shift) % CHAR_COUNT) + ASCII_MIN);
    }
    return result;
}

bool isLoggedIn() {
    string username, password, un, pw;

    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    ifstream read(".\\data\\" + username + ".txt");
    getline(read, un);
    getline(read, pw);

    if (un == username && pw == caesarCipher(password, password.length())) {  // compare usernames and encrypted passwords
        return true;
    } else {
        return false;
    }
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
        file << username << endl << caesarCipher(password, password.length());  // store username and encrypted password in file
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


// NEXT STEPS:
// add option to reset/change password
// add option to exit
// add option to delete account
// repeat program until exit
// connect to database instead of using .txt files