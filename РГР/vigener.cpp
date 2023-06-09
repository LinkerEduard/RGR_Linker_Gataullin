#include <iostream>
#include <fstream>
#include <string>
using namespace std;
void key(string& temp_key, string& key1, string& key2){
    for (size_t i = 0; i < temp_key.length(); ++i) {
        if (temp_key[i] >= 'a' && temp_key[i] <= 'z') {
            key1 += temp_key[i];
        }
        else if (temp_key[i] >= 'A' && temp_key[i] <= 'Z') {
            key1 += temp_key[i];
        }
        else if (temp_key[i] >= 'а' && temp_key[i] <= 'я') {
            key2 += temp_key[i];
        }
        else if (temp_key[i] >= 'А' && temp_key[i] <= 'Я') {
            key2 += temp_key[i];
        }
    }
}

void func_enc_dec(ifstream& inputFile, ofstream& outputFile, string& key1, string& key2, int& enc_dec) {
    string line;
    int keyIndex = 0;
    unsigned char part_key_eng = ' ', part_key_rus = ' ';
    while (getline(inputFile, line)) {
        for (size_t i = 0; i < line.length(); ++i) {
            unsigned char letter = line[i];
            if ((letter >= 'A' && letter <= 'Z') || (letter >= 'a' && letter <= 'z') || (letter >= int(unsigned char('А')) && letter <= int(unsigned char('Я'))) || (letter >= int(unsigned char('а')) && letter <= int(unsigned char('я')))) {
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
                    if (part_key_rus >= int(unsigned char('а')) && part_key_rus <= int(unsigned char('я'))) {
                        part_key_rus -= int(unsigned char('а'));
                    }
                    else if (part_key_rus >= int(unsigned char('А')) && part_key_rus <= int(unsigned char('Я'))) {
                        part_key_rus -= int(unsigned char('А'));
                    }
                }
                if (key1.length() != 0) {
                    if (letter >= 'a' && letter <= 'z') {
                        letter -= 'a';
                        if (enc_dec == 1) {
                            letter = (letter + part_key_eng) % 26;
                        }
                        else { letter = (letter - part_key_eng + 26) % 26; }
                        letter += 'a';
                    }
                    else if (letter >= 'A' && letter <= 'Z') {
                        letter -= 'A';
                        if (enc_dec == 1) {
                            letter = (letter + part_key_eng) % 26;
                        }
                        else { letter = (letter - part_key_eng + 26) % 26; }
                        letter += 'A';
                    }
                }
                if (key2.length() != 0) {
                    if (letter >= int(unsigned char('А')) && letter <= int(unsigned char('Я'))) {
                        letter -= int(unsigned char('А'));
                        if (enc_dec == 1) {
                            letter = (letter + part_key_rus) % 32;
                        }
                        else { letter = (letter - part_key_rus + 32) % 32; }
                        letter += int(unsigned char('А'));
                    }
                    else if (letter >= int(unsigned char('а')) && letter <= int(unsigned char('я'))) {
                        letter -= int(unsigned char('а'));
                        if (enc_dec == 1) {
                            letter = (letter + part_key_rus) % 32;
                        }
                        else { letter = (letter - part_key_rus + 32) % 32; }
                        letter += int(unsigned char('а'));
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
void vigener_encrypt(string& inputFileFileName, string& outputFileFileName)
{
    setlocale(LC_ALL, "Russian");
    ifstream inputFile(inputFileFileName);
    ofstream outputFile(outputFileFileName);
    string key1, key2, temp_key;
    int enc_dec = 1;
    jump:
    cout << "enter the key in English (for English text) and in Russian (for Russian text)" << endl;
    getline(cin, temp_key);
    key(temp_key, key1, key2);
    if ((key1.length() == 0) && (key2.length() == 0)) { cout << "Error, please enter at least one English or Russian letter" << endl; goto jump; }
    func_enc_dec(inputFile, outputFile, key1, key2, enc_dec);
}

void vigener_decrypt(string& inputFileFileName, string& outputFileFileName)
{
    setlocale(LC_ALL, "Russian");
    ifstream inputFile(inputFileFileName);
    ofstream outputFile(outputFileFileName);
    string key1, key2, temp_key;
    int enc_dec = 0;
    jump:
    cout << "enter the key in English (for English text) and in Russian (for Russian text)" << endl;
    getline(cin, temp_key);
    key(temp_key, key1, key2);
    if ((key1.length() == 0) && ((key2.length() == 0))) { cout << "Error, please enter at least one English or Russian letter" << endl; goto jump; }
    func_enc_dec(inputFile, outputFile, key1, key2, enc_dec);
}