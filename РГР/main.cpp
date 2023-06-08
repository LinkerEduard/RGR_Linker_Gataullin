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
    int64_t  p, q;
    do {
        cout << "Enter password (0 - Exit): ";
        getline(cin, pas);
        if (pas == "0") {
            p = q = 0;
            break;
        }
        stringstream ss(pas);
        ss >> password >> key >> p >> q;
        if (password != get_password(key, p, q))
            cout << "Invalid password. Please try again." <<endl;
    } while (password != get_password(key, p, q));
    if (password == get_password(key, p, q)) {
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
                    string text;
                    string mode_1;
                    do {
                        cout << "Choose mode (0 - Back, 1 - Encrypt, 2 - Decrypt): ";
                        getline(cin, mode_1);
                        if (mode_1 != "0" && mode_1 != "1" && mode_1 != "2")
                            cout << "Invalid mode" << endl;
                    } while (mode_1 != "0" && mode_1 != "1" && mode_1 != "2");
                    if (mode_1 == "0")
                        continue;
                    if (mode_1 == "1") {
                        cout << "Enter text to encrypt:" << endl;
                        getline(cin, text);
                        ofstream inputFile(inputFileName);
                        if (inputFile.is_open())
                        {
                            inputFile << text;
                            inputFile.close();
                        }
                        encryptFile(inputFileName, outputFileName, choice);
                        ifstream outputFile(outputFileName);
                        if (outputFile.is_open())
                        {
                            string encryptedText;
                            while (getline(outputFile, encryptedText))
                            {
                                cout << encryptedText << endl;
                            }
                            outputFile.close();
                        }
                    }
                    if (mode_1 == "2") {
                        cout << "Enter text to decrypt:" << endl;
                        getline(cin, text);
                        ofstream inputFile(inputFileName);
                        if (inputFile.is_open())
                        {
                            inputFile << text;
                            inputFile.close();
                        }
                        decryptFile(inputFileName, outputFileName, choice);
                        ifstream outputFile(outputFileName);
                        if (outputFile.is_open())
                        {
                            string decryptedText;
                            while (getline(outputFile, decryptedText))
                            {
                                cout << decryptedText << endl;
                            }
                            outputFile.close();
                        }
                    }
                }
            }
            else if (mode_2 == "2") {
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
                    string inputFileName, outputFileName;
                    bool inputFileExists = false;
                    do {
                        cout << "Enter input file name (in .txt format, in ANSI encoding, for proper encryption) (0 - Back): ";
                        getline(cin, inputFileName);
                        if (inputFileName == "0")
                            break;
                        inputFileExists = fileExists(inputFileName);
                        if (!inputFileExists) {
                            cout << "Input file doesn't exist. Please try again." << endl;
                        }
                        if ((inputFileName.substr(inputFileName.find_last_of(".") + 1)) != "txt")
                            cout << "Input file is not a text file. Please try again." << endl;
                    } while (!inputFileExists || ((inputFileName.substr(inputFileName.find_last_of(".") + 1)) != "txt"));
                    if (inputFileName == "0")
                        continue;
                    do {
                        cout << "Enter output file name (in .txt format, in ANSI encoding, for proper encryption) (0 - Back): ";
                        getline(cin, outputFileName);
                        if (outputFileName == "0")
                            break;
                        if (fileDifferent(inputFileName, outputFileName)) {
                            cout << "The output file must't have the same name as the input file. Please try again." << endl;
                        }
                        if ((outputFileName.substr(outputFileName.find_last_of(".") + 1)) != "txt")
                            cout << "Output file is not a text file. Please try again." << endl;
                    } while (fileDifferent(inputFileName, outputFileName) || ((outputFileName.substr(outputFileName.find_last_of(".") + 1)) != "txt"));
                    if (outputFileName == "0")
                        continue;
                    encryptFile(inputFileName, outputFileName, choice);
                    cout << "File is encrypted!" << endl;
                }
            }
            else if (mode_2 == "3") {
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
                    string inputFileName, outputFileName;
                    bool inputFileExists = false;
                    do {
                        cout << "Enter input file name (in ANSI encoding, for proper decryption) (0 - Back): ";
                        getline(cin, inputFileName);
                        if (inputFileName == "0")
                            break;
                        inputFileExists = fileExists(inputFileName);
                        if (!inputFileExists) {
                            cout << "Input file doesn't exist. Please try again." << endl;
                        }
                        if ((inputFileName.substr(inputFileName.find_last_of(".") + 1)) != "txt")
                            cout << "Input file is not a text file. Please try again." << endl;
                    } while (!inputFileExists || ((inputFileName.substr(inputFileName.find_last_of(".") + 1)) != "txt"));
                    if (inputFileName == "0")
                        continue;
                    do {
                        cout << "Enter output file name (in .txt format, in ANSI encoding, for proper encryption) (0 - Back): ";
                        getline(cin, outputFileName);
                        if (outputFileName == "0")
                            break;
                        if (fileDifferent(inputFileName, outputFileName)) {
                            cout << "The output file must't have the same name as the input file. Please try again." << endl;
                        }        
                        if ((outputFileName.substr(outputFileName.find_last_of(".") + 1)) != "txt")
                            cout << "Output file is not a text file. Please try again." << endl;
                    } while (fileDifferent(inputFileName, outputFileName) || ((outputFileName.substr(outputFileName.find_last_of(".") + 1)) != "txt"));
                    if (outputFileName == "0")
                        continue;
                    decryptFile(inputFileName, outputFileName, choice);
                    cout << "File is decrypted!" << endl;
                }
            }
            else {
                cout << "Invalid mode" << endl;
            }

            cout << "Choose mode (0 - Exit, 1 - Manual input, 2 - Encrypt file, 3 - Decrypt file): ";
            getline(cin, mode_2);
        }
    }
    cout << "Exiting program";
    return 0;
}