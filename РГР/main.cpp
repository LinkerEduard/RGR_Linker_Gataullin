#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <windows.h>
#include "cipher.h"
#include "password.h"
using namespace std;
int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    string pas, password, key;
    uint_fast64_t  p, q;
    Invalidpassword:
    cout << "Enter password (0 - Exit): ";
    getline(cin, pas);
    stringstream ss(pas);
    if (pas == "0") goto exit; 
    ss >> password >> key >> p >> q;
    if (password != get_password(key, p, q)) {
        cout << "Invalid password. Please try again." << endl;
        goto Invalidpassword;
    }
    else {
        cout << "Welcome!" << endl;
        string mode_2;
        cout << "Choose mode (0 - Exit, 1 - Manual input, 2 - Encrypt file, 3 - Decrypt file): ";
        getline(cin, mode_2);
        while (mode_2 != "0") {
            if (mode_2 == "1") {
                cout << "Enter valid choice (0 - Back, 1 - Atbash Method, 2 - Gronsfeld Method, 3 - RSA Method, 4-Skitala Method, 5-Vigener Method, 6-Polybius Method): ";
                string choice;
                getline(cin, choice);
                try {
                    if (choice != "0" && choice != "1" && choice != "2" && choice != "3" && choice != "4" && choice != "5" && choice != "6")
                        throw "Invalid choice";
                }
                catch (const char* msg) {
                    cout << msg << endl;
                    continue;
                }
                if (choice != "0") {
                    string inputFileName = "input.txt";
                    string outputFileName = "output.txt";
                    string mode_1;
                Invalidmode:
                    cout << "Choose mode (0 - Back, 1 - Encrypt, 2 - Decrypt): ";
                    getline(cin, mode_1);
                    if (mode_1 != "0" && mode_1 != "1" && mode_1 != "2") {
                        cout << "Invalid mode" << endl;
                        goto Invalidmode;
                    }
                    if (mode_1 == "0") continue;
                    if (mode_1 == "1" || mode_1 == "2") encrypt_decryptConsole(inputFileName, outputFileName, mode_1, choice);
                }
            }
            else if (mode_2 == "2" || mode_2 == "3") encrypt_decryptFile(mode_2);
            else {
                cout << "Invalid mode" << endl;
            }
            cout << "Choose mode (0 - Exit, 1 - Manual input, 2 - Encrypt file, 3 - Decrypt file): ";
            getline(cin, mode_2);
        }
    }
    exit:
    cout << "Exiting program";
    return 0;
}