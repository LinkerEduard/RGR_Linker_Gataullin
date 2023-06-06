#include "polybius.h"

const char TABLE[99][99] = { {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K'},
                           {'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V'},
                           {'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g'},
                           {'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r'},
                           {'s', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'À', 'Á', 'Â'},
                           {'Ã', 'Ä', 'Å', '¨', 'Æ', 'Ç', 'È', 'É', 'Ê', 'Ë', 'Ì'},
                           {'Í', 'Î', 'Ï', 'Ð', 'Ñ', 'Ò', 'Ó', 'Ô', 'Õ', 'Ö', '×'},
                           {'Ø', 'Ù', 'Ú', 'Û', 'Ü', 'Ý', 'Þ', 'ß', 'à', 'á', 'â'},
                           {'ã', 'ä', 'å', '¸', 'æ', 'ç', 'è', 'é', 'ê', 'ë', 'ì'},
                           {'í', 'î', 'ï', 'ð', 'ñ', 'ò', 'ó', 'ô', 'õ', 'ö', '÷'},
                           {'ø', 'ù', 'ú', 'û', 'ü', 'ý', 'þ', 'ÿ', '0', '1', '2'},
                           {'3', '4', '5', '6', '7', '8', '9', ' '}};

void findPosition(char letter, int& row, int& col)
{
    for (int i = 0; i < 99; ++i) {
        for (int j = 0; j < 99; ++j) {
            if (TABLE[i][j] == letter) {
                row = i;
                col = j;
            }
        }
    }
}

void polybius_encrypt(string inputFileFileName, string outputFileFileName)
{
    ifstream inputFile(inputFileFileName);
    ofstream outputFile(outputFileFileName);
    string line;
    while (getline(inputFile, line)) {
        for (size_t i = 0; i < line.length(); ++i) {
            char letter = line[i];
            if ((letter >= 'A' && letter <= 'Z') || (letter >= 'a' && letter <= 'z') || (letter >= 'À' && letter <= 'ß') || (letter >= 'à' && letter <= 'ÿ') || (letter >= '0' && letter <= '9') || (letter == ' ')) {
                int row, col;
                findPosition(letter, row, col);
                if ((row >= 10) && (col >= 10)) {
                    outputFile << row << col;
                }
                else if ((row >= 10) && (col < 10)){
                    outputFile << row << "0" << col;
                }
                else if ((row < 10) && (col >= 10)) {
                    outputFile << "0" << row << col;
                }
                else{
                    outputFile << "0" << row << "0" << col;
                }
            }
            else {
                outputFile << line[i];
            }
        }
        outputFile << endl;
    }
}

void polybius_decrypt(string inputFileFileName, string outputFileFileName)
{
    ifstream inputFile(inputFileFileName);
    ofstream outputFile(outputFileFileName);
    string line;
    while (getline(inputFile, line)) {
        for (size_t i = 0; i < line.length(); ++i) {
            if ((line[i]-'0'>=0) && (line[i] - '0' <= 9) && (line[i+1]!=0) && (line[i + 2] != 0) && (line[i + 3] != 0) && (line[i+1] - '0' >= 0) && (line[i+1] - '0' <= 9) &&(line[i + 2] - '0' >= 0) && (line[i + 2] - '0' <= 9) && (line[i + 3] - '0' >= 0) && (line[i + 3] - '0' <= 9)) {
                int row = (line[i]-'0') * 10 + (line[i + 1]-'0');
                int col = (line[i + 2] - '0') * 10 + (line[i + 3] - '0');
                outputFile << TABLE[row][col];
                i += 3;
            }
            else {
                outputFile << line[i];
            }
        }
        outputFile << endl;
    }
}