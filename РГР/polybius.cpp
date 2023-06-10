#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void polybius_encrypt(string& inputFileFileName, string& outputFileFileName)
{
    ifstream inputFile(inputFileFileName);
    ofstream outputFile(outputFileFileName);
    string line;
    while (getline(inputFile, line)) {
        for (size_t i = 0; i < line.length(); ++i) {
            int code_ascii = static_cast<unsigned char>(line[i]);
            if (code_ascii < 100) { outputFile << '0' << code_ascii / 10 << '0' << code_ascii % 10; }
            else { outputFile << code_ascii / 100 << '0' << (code_ascii / 10) % 10 << code_ascii % 10; }
        }
        outputFile << endl;
    }
    inputFile.close();
    outputFile.close();
}

void polybius_decrypt(string& inputFileFileName, string& outputFileFileName)
{
    ifstream inputFile(inputFileFileName);
    ofstream outputFile(outputFileFileName);
    string line;
    int code_ascii;
    while (getline(inputFile, line)) {
        for (size_t i = 0; i < line.length(); ++i) {
            if ((line[i] - '0' >= 0) && (line[i] - '0' <= 9) && (line[i + 1] - '0' >= 0) && (line[i + 1] - '0' <= 9) && (line[i + 2] - '0' >= 0) && (line[i + 2] - '0' <= 9) && (line[i + 3] - '0' >= 0) && (line[i + 3] - '0' <= 9)) {
                if (line[i] == '0') {
                    code_ascii = int(line[i + 1] - '0') * 10 + int(line[i + 3] - '0');
                    outputFile << unsigned char(code_ascii);
                }
                else {
                    code_ascii = int(line[i] - '0') * 100 + int(line[i + 2] - '0') * 10 + int(line[i + 3] - '0');
                    outputFile << unsigned char(code_ascii);
                }
                i += 3;
            }
            else { outputFile << line[i]; }
        }
        outputFile << endl;
    }
    inputFile.close();
    outputFile.close();
}