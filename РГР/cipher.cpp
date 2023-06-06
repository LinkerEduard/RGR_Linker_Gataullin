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


