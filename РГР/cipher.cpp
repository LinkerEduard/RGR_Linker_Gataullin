#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <thread>
#include <sstream>
#include "cipher.h"
#include "rsa.h"
#include "atb.h"
#include "gro.h"
#include "skitala.h"
#include "vigener.h"
#include "polybius.h"
using namespace std;

bool fileDifferent(string& inputFileName, string& outputFileName) {
    return (inputFileName == outputFileName);
}

bool fileExists(string& inputFileName) {
    ifstream file(inputFileName);
    return file.good();
}

void encryptFile(string& inputFileName, string& outputFileName, string& choice)
{
    string line;
    if (choice == "0") 
        return;
    else if (choice == "1") {
        atb_encrypt(inputFileName, outputFileName);
        return;
    }
    else if (choice == "2") {
        gro_encrypt(inputFileName, outputFileName);
        return;
    }
    else if (choice == "3") {
        rsa_encrypt(inputFileName, outputFileName);
        return;
    }
    else if (choice == "4") {
        skital_encrypt(inputFileName, outputFileName);
        return;
    }
    else if (choice == "5") {
        vigener_encrypt(inputFileName, outputFileName);
        return;
    }
    else if (choice == "6") {
        polybius_encrypt(inputFileName, outputFileName);
        
        return;
    }
}

void decryptFile(string& inputFileName, string& outputFileName, string& choice)
{
    if (choice == "0")
        return;
    else if (choice == "1") {
        atb_decrypt(inputFileName, outputFileName);
        return;
    }
    else if (choice == "2") {
        gro_decrypt(inputFileName, outputFileName);
        return;
    }
    else if (choice == "3") {
        rsa_decrypt(inputFileName, outputFileName);
        return;
    }
    else if (choice == "4") {
        skital_decrypt(inputFileName, outputFileName);
        return;
    }
    else if (choice == "5") {
        vigener_decrypt(inputFileName, outputFileName);
        return;
    }
    else if (choice == "6") {
        polybius_decrypt(inputFileName, outputFileName);
        return;
    }
}
void encrypt_decryptFile(string& mode_2) {
    while (true) {
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
        Inputfile:
            cout << "Enter input file name (in .txt format, in ANSI encoding, for proper encryption) (0 - Back): ";
            getline(cin, inputFileName);
            if (inputFileName == "0") return;
            if (!fileExists(inputFileName)) {
                cout << "Input file doesn't exist. Please try again." << endl;
                goto  Inputfile;
            }
            if ((inputFileName.substr(inputFileName.find_last_of(".") + 1)) != "txt") {
                cout << "Input file is not a text file. Please try again." << endl;
                goto  Inputfile;
            }
        Outfile:
            cout << "Enter output file name (in .txt format, in ANSI encoding, for proper encryption) (0 - Back): ";
            getline(cin, outputFileName);
            if (outputFileName == "0") goto Inputfile;
            if (fileDifferent(inputFileName, outputFileName)) {
                cout << "The output file must't have the same name as the input file. Please try again." << endl;
                goto Outfile;
            }
            if ((outputFileName.substr(outputFileName.find_last_of(".") + 1)) != "txt") {
                cout << "Output file is not a text file. Please try again." << endl;
                goto Outfile;
            }
            if (mode_2 == "2") {
                encryptFile(inputFileName, outputFileName, choice);
                cout << "File is encrypted!" << endl;
            }
            else {
                decryptFile(inputFileName, outputFileName, choice);
                cout << "File is decrypted!" << endl;
            }
        }
        return;
    }
}
void encrypt_decryptConsole(string& inputFileName, string& outputFileName, string& mode_1, string& choice) {
    string text;
    cout << "Enter text to encrypt:" << endl;
    getline(cin, text);
    ofstream inputFile(inputFileName);
    if (inputFile.is_open())
    {
        inputFile << text;
        inputFile.close();
    }
    if (mode_1 == "1") encryptFile(inputFileName, outputFileName, choice);
    else decryptFile(inputFileName, outputFileName, choice);
    ifstream outputFile(outputFileName);
    if (outputFile.is_open())
    {
        string en_decryptedText;
        while (getline(outputFile, en_decryptedText))
        {
            cout << en_decryptedText << endl;
        }
        outputFile.close();
    }
}

