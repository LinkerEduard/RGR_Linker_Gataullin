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

void checkfiles() {
    while (true) {
        std::vector<std::string> files = { "atb.obj", "cipher.obj", "gro.obj", "input.txt", "main.obj", "MDTFCipher.ilk", "MDTFCipher.pdb", "output.txt", "password.obj", "password.txt", "rsa.obj", "vc143.idb", "vc143.pdb", "skitala.obj", "vigener.obj", "polybius.obj"};
        for (const auto& file : files) {
            std::ifstream checkFile(file);
            if (!checkFile.good()) {
                cout << "File '" << file << "' does NOT exist." << endl;
                checkFile.close();
                cout << "Exit the programme after 5 seconds" << endl;
                this_thread::sleep_for(chrono::milliseconds(5000));
                exit(EXIT_FAILURE);
            }
        }
        this_thread::sleep_for(chrono::milliseconds(100));
    }
}

bool fileDifferent(string inputFileName, string outputFileName) {
    return (inputFileName == outputFileName);
}

bool fileExists(std::string inputFileName) {
    ifstream file(inputFileName);
    return file.good();
}

void encryptFile(string inputFileName, string outputFileName, string choice)
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

void decryptFile(string inputFileName, string outputFileName, string choice)
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


