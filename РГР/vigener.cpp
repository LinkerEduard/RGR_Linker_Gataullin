#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void vigener_encrypt(string inputFileFileName, string outputFileFileName)
{
    setlocale(LC_ALL, "Russian");
    ifstream inputFile(inputFileFileName);
    ofstream outputFile(outputFileFileName);
    string line;
    string key1;
    string key2;
    string temp_key;
    jump:
    cout << "Enter the key in English (for English text) and in Russian (for Russian text)" << endl;
    getline(cin, temp_key);

    for (size_t i = 0; i < temp_key.length(); ++i) {
        if (temp_key[i] >= 'a' && temp_key[i] <= 'z') {
            key1 += temp_key[i];
        }
        else if (temp_key[i] >= 'A' && temp_key[i] <= 'Z') {
            key1 += temp_key[i];
        }
        else if (temp_key[i] >= '�' && temp_key[i] <= '�') {
            key2 += temp_key[i];
        }
        else if (temp_key[i] >= '�' && temp_key[i] <= '�') {
            key2 += temp_key[i];
        }
    }
    if ((key1.length() == 0) && (key2.length() == 0)) { cout << "Error" << endl; goto jump; }

    int keyIndex = 0;
    unsigned char part_key_eng=' ', part_key_rus=' ';
    while (getline(inputFile, line)) {
        for (size_t i = 0; i < line.length(); ++i) {
            unsigned char letter = line[i];
            if ((letter >= 'A' && letter <= 'Z') || (letter >= 'a' && letter <= 'z') || (letter >= int(unsigned char('�')) && letter <= int(unsigned char('�'))) || (letter >= int(unsigned char('�')) && letter <= int(unsigned char('�')))) {
                if(key1.length() != 0){ part_key_eng = key1[keyIndex % key1.length()]; }
                if(key2.length() != 0){ part_key_rus = key2[keyIndex % key2.length()]; }
                
                if (key1.length() != 0) {
                    if (part_key_eng >= 'a' && part_key_eng <= 'z') {
                        part_key_eng -= 'a';
                    }
                    else if (part_key_eng >= 'A' && part_key_eng <= 'Z') {
                        part_key_eng -= 'A';
                    }
                }
                if (key2.length() != 0) {
                    if (part_key_rus >= int(unsigned char('�')) && part_key_rus <= int(unsigned char('�'))) {
                        part_key_rus -= int(unsigned char('�'));
                    }
                    else if (part_key_rus >= int(unsigned char('�')) && part_key_rus <= int(unsigned char('�'))) {
                        part_key_rus -= int(unsigned char('�'));
                    }
                }
                if (key1.length() != 0) {
                    if (letter >= 'a' && letter <= 'z') {
                        letter -= 'a';
                        letter = (letter + part_key_eng) % 26;
                        letter += 'a';
                    }
                    else if (letter >= 'A' && letter <= 'Z') {
                        letter -= 'A';
                        letter = (letter + part_key_eng) % 26;
                        letter += 'A';
                    }
                }
                if (key2.length() != 0) {
                    if (letter >= int(unsigned char('�')) && letter <= int(unsigned char('�'))) {
                        letter -= int(unsigned char('�'));
                        letter = (letter + part_key_rus) % 32;
                        letter += int(unsigned char('�'));
                    }
                    else if (letter >= int(unsigned char('�')) && letter <= int(unsigned char('�'))) {
                        letter -= int(unsigned char('�'));
                        letter = (letter + part_key_rus) % 32;
                        letter += int(unsigned char('�'));
                    }
                }
                outputFile << letter;
                keyIndex++;
            }
            else{ outputFile << letter; }
        }
        outputFile << endl;
    }
    inputFile.close();
    outputFile.close();
}

void vigener_decrypt(string inputFileFileName, string outputFileFileName)
{
    setlocale(LC_ALL, "Russian");
    ifstream inputFile(inputFileFileName);
    ofstream outputFile(outputFileFileName);
    string line;
    string key1;
    string key2;
    string temp_key;
    jump:
    cout << "Enter the key in English (for English text) and in Russian (for Russian text)" << endl;
    getline(cin, temp_key);

    for (size_t i = 0; i < temp_key.length(); ++i) {
        if (temp_key[i] >= 'a' && temp_key[i] <= 'z') {
            key1 += temp_key[i];
        }
        else if (temp_key[i] >= 'A' && temp_key[i] <= 'Z') {
            key1 += temp_key[i];
        }
        else if (temp_key[i] >= '�' && temp_key[i] <= '�') {
            key2 += temp_key[i];
        }
        else if (temp_key[i] >= '�' && temp_key[i] <= '�') {
            key2 += temp_key[i];
        }
    }
    if ((key1.length() == 0) && ((key2.length() == 0))) { cout << "Error" << endl; goto jump; }

    int keyIndex = 0;
    unsigned char part_key_eng=' ', part_key_rus=' ';
    while (getline(inputFile, line)) {
        for (size_t i = 0; i < line.length(); ++i) {
            unsigned char letter = line[i];
            if ((letter >= 'A' && letter <= 'Z') || (letter >= 'a' && letter <= 'z') || (letter >= int(unsigned char('�')) && letter <= int(unsigned char('�'))) || (letter >= int(unsigned char('�')) && letter <= int(unsigned char('�')))) {
                if (key1.length() != 0) { part_key_eng = key1[keyIndex % key1.length()]; }
                if (key2.length() != 0) { part_key_rus = key2[keyIndex % key2.length()]; }
                if (key1.length() != 0) {
                    if (part_key_eng >= 'a' && part_key_eng <= 'z') {
                        part_key_eng -= 'a';
                    }
                    else if (part_key_eng >= 'A' && part_key_eng <= 'Z') {
                        part_key_eng -= 'A';
                    }
                }
                if (key2.length() != 0) {
                    if (part_key_rus >= int(unsigned char('�')) && part_key_rus <= int(unsigned char('�'))) {
                        part_key_rus -= int(unsigned char('�'));
                    }
                    else if (part_key_rus >= int(unsigned char('�')) && part_key_rus <= int(unsigned char('�'))) {
                        part_key_rus -= int(unsigned char('�'));
                    }
                }
                if (key1.length() != 0) {
                    if (letter >= 'a' && letter <= 'z') {
                        letter -= 'a';
                        letter = (letter - part_key_eng + 26) % 26;
                        letter += 'a';
                    }
                    else if (letter >= 'A' && letter <= 'Z') {
                        letter -= 'A';
                        letter = (letter - part_key_eng + 26) % 26;
                        letter += 'A';
                    }
                }
                if (key2.length() != 0) {
                    if (letter >= int(unsigned char('�')) && letter <= int(unsigned char('�'))) {
                        letter -= int(unsigned char('�'));
                        letter = (letter - part_key_rus + 32) % 32;
                        letter += int(unsigned char('�'));
                    }
                    else if (letter >= int(unsigned char('�')) && letter <= int(unsigned char('�'))) {
                        letter -= int(unsigned char('�'));
                        letter = (letter - part_key_rus + 32) % 32;
                        letter += int(unsigned char('�'));
                    }
                }
                outputFile << letter;
                keyIndex++;
            }
            else { outputFile << letter; }
        }
        outputFile << endl;
    }
    inputFile.close();
    outputFile.close();
}