#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void atb_encrypt(string inputFileFileName, string outputFileFileName)
{
    ifstream inputFile(inputFileFileName);
    ofstream outputFile(outputFileFileName);
    string line;
    while (getline(inputFile, line)) {
        for (size_t i = 0; i < line.length(); ++i) {
            if (line[i] >= 'A' && line[i] <= 'Z') {
                outputFile << char('Z' - (line[i] - 'A'));
            }
            else if (line[i] >= 'a' && line[i] <= 'z') {
                outputFile << char('z' - (line[i] - 'a'));
            }
            else if (line[i] >= 'à' && line[i] <= 'ÿ') {
                outputFile << char('ÿ' - (line[i] - 'à'));
            }
            else if (line[i] >= 'À' && line[i] <= 'ß') {
                outputFile << char('ß' - (line[i] - 'À'));
            }
            else if (line[i] >= '0' && line[i] <= '9') {
                outputFile << char('9' - (line[i] - '0'));
            }
            else {
                outputFile << line[i];
            }
        }
        outputFile << endl;
    }
    inputFile.close();
    outputFile.close();
}


void atb_decrypt(string inputFileFileName, string outputFileFileName)
{
    ifstream inputFile(inputFileFileName);
    ofstream outputFile(outputFileFileName);
    string line;
    while (getline(inputFile, line)) {
        for (size_t i = 0; i < line.length(); ++i) {
            if (line[i] >= 'A' && line[i] <= 'Z') {
                outputFile << char('Z' - (line[i] - 'A'));
            }
            else if (line[i] >= 'a' && line[i] <= 'z') {
                outputFile << char('z' - (line[i] - 'a'));
            }
            else if (line[i] >= 'à' && line[i] <= 'ÿ') {
                outputFile << char('ÿ' - (line[i] - 'à'));
            }
            else if (line[i] >= 'À' && line[i] <= 'ß') {
                outputFile << char('ß' - (line[i] - 'À'));
            }
            else if (line[i] >= '0' && line[i] <= '9') {
                outputFile << char('9' - (line[i] - '0'));
            }
            else {
                outputFile << line[i];
            }
        }
        outputFile << endl;
    }
    inputFile.close();
    outputFile.close();
}