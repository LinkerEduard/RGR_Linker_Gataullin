#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void changeatb(int& asciiCode)
{
    int temp = 0;
    if ((asciiCode >= 65 && asciiCode <= 90) || (asciiCode >= 97 && asciiCode <= 122)) {
        if (asciiCode < 97) temp = 32;
        asciiCode = 122 - (asciiCode + temp - 97);
        asciiCode -= temp;
    }
    if (asciiCode >= 192 && asciiCode <= 255) {
        if (asciiCode < 224) temp = 32;
        asciiCode = 255 - (asciiCode + temp - 224);
        asciiCode -= temp;
    }
    if (asciiCode >= 48 && asciiCode <= 57) {
        asciiCode = 57 - (asciiCode - 48);
    }
}
void atb_encrypt(string& inputFileFileName, string& outputFileFileName)
{
    wifstream inputFile(inputFileFileName);
    wofstream outputFile(outputFileFileName);
    wstring line;
    while (getline(inputFile, line)) {
        for (int i = 0; i < line.length(); i++) {
            wchar_t symbol = line[i]; 
            if (symbol == ' ') {
                outputFile << " ";
                continue;
            }
            int asciiCode = (int)symbol;
            changeatb(asciiCode);
            outputFile << (wchar_t)asciiCode;
        }
        outputFile << endl;
    }
    inputFile.close();
    outputFile.close();
}


void atb_decrypt(string& inputFileFileName, string& outputFileFileName)
{
    atb_encrypt(inputFileFileName, outputFileFileName);
}