#include "skitala.h"
#include <limits>
#include <iostream>

void skital_encrypt(std::string inputFileFileName, std::string outputFileFileName)
{
    std::ifstream inputFile(inputFileFileName);
    std::ofstream outputFile(outputFileFileName);
    std::string line;
    jump:
    std::string temp_diameter="";
    int diameter=0;
    std::cout << "Enter the diameter (enter the number >=1): " << std::endl;
    std::cin >> temp_diameter;
    for (int i = 0; i < temp_diameter.length(); ++i) {
        if ((temp_diameter[i] - '0' >= 0) && (temp_diameter[i] - '0' <= 9)) {
            diameter = diameter * 10 + (temp_diameter[i] - '0');
        }
    }
    if (diameter < 1) { std::cout << "Error, please enter the number >=1!" << std::endl;  goto jump; }

    getline(std::cin, line);
    while (getline(inputFile, line)) {
        std::string encryptedLine;
        int lineLength = line.length();
        int numRows = (lineLength + diameter - 1) / diameter;
        for (int i = 0; i < numRows; i++) {
            for (int j = i; j < lineLength; j += numRows) {
                encryptedLine += line[j];
            }
        }
        outputFile << encryptedLine << std::endl;
    }
    inputFile.close();
    outputFile.close();
}

void skital_decrypt(std::string inputFileFileName, std::string outputFileFileName)
{
    std::ifstream inputFile(inputFileFileName);
    std::ofstream outputFile(outputFileFileName);
    std::string line;
    jump:
    std::string temp_diameter = "";
    int diameter = 0;
    std::cout << "Enter the diameter (enter the number >=1): " << std::endl;
    std::cin >> temp_diameter;
    for (int i = 0; i < temp_diameter.length(); ++i) {
        if ((temp_diameter[i] - '0' >= 0) && (temp_diameter[i] - '0' <= 9)) {
            diameter = diameter * 10 + (temp_diameter[i] - '0');
        }
    }
    if (diameter < 1) { std::cout << "Error, please enter the number >=1!" << std::endl;  goto jump; }

    getline(std::cin, line);
    while (getline(inputFile, line)) {
        std::string decryptedLine(line.length(), ' ');
        int lineLength = line.length();
        int numRows = ((lineLength - 1) / diameter) + 1;
        int index = 0;
        for (int i = 0; i < numRows; i++) {
            for (int j = i; j < lineLength; j += numRows) {
                decryptedLine[j] = line[index++];
            }
        }
        outputFile << decryptedLine << std::endl;
    }
    inputFile.close();
    outputFile.close();
}