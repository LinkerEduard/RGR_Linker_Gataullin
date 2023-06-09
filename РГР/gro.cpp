#include <iostream>
#include <fstream>
#include <string>
using namespace std;
bool checkIfNumeric(string str)
{
    return !str.empty() && str.find_first_not_of("0123456789") == string::npos;
}
void changegro(int& asciiCode, wchar_t symbol) {
    int temp = 0;
    if ((symbol >= 65 && symbol <= 90) || (symbol >= 97 && symbol <= 122)) {
        if (symbol < 97) temp = 32;
        asciiCode += temp;
        if (asciiCode > 122) asciiCode -= 26;
        if (asciiCode < 97) asciiCode += 26;
        asciiCode -= temp;
    }
    else if (symbol >= 192 && symbol <= 255) {
        if (symbol < 224) temp = 32;
        asciiCode += temp;
        if (asciiCode > 255) asciiCode -= 32;
        if (asciiCode < 224) asciiCode += 32;
        asciiCode -= temp;
    }
    else asciiCode = int(symbol);
}
void gro_universal(string inputFileName, string outputFileName, int temp) {
    wifstream inputFile(inputFileName);
    wofstream outputFile(outputFileName);
    string key;
    do {
        cout << "Enter key: ";
        getline(cin, key);
        if (!(checkIfNumeric(key)))
            cout << "Invalid Key (The number must be a natural number). Please try again." << endl;
        else {
            int keyLength = key.length();
            int* keyArray = new int[keyLength];
            for (int i = 0; i < keyLength; i++)
            {
                keyArray[i] = key[i] - '0';
            }
            wstring line;
            while (getline(inputFile, line))
            {
                for (int i = 0; i < line.length(); i++)
                {
                    wchar_t symbol = line[i];
                    if (symbol == ' ')
                    {
                        outputFile << " ";
                        continue;
                    }
                    int asciiCode = (int)symbol + temp * keyArray[i % keyLength];
                    changegro(asciiCode, symbol);
                    outputFile << (wchar_t)asciiCode;
                }
                outputFile << endl;
            }
            inputFile.close();
            outputFile.close();
            delete[] keyArray;
        }
    } while (!(checkIfNumeric(key)));
}
void gro_encrypt(string inputFileName, string outputFileName) {
    gro_universal(inputFileName, outputFileName, 1);
}
void gro_decrypt(string inputFileName, string outputFileName) {
    gro_universal(inputFileName, outputFileName, -1);
}