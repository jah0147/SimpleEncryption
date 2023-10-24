//
// Created by jacob_howard on 10/24/2023.
//
#include "string"
#include <algorithm>
#include "iostream"
#include <fstream>
#include "sstream"
using namespace std;

#ifndef TEST_ENCRYPTDECRYPT_H
#define TEST_ENCRYPTDECRYPT_H


class EncryptDecrypt
{
public:
    EncryptDecrypt();

    //Get user input (return true for encrpytion or false for decryption
    bool getUsrInput();
    //Encrypt or decrypt based on user
    void encryption_decryption(bool bEncrypt);
    //encrpyt a string
    string encrypt(string &text, int key);
    //decrypt a string
    string decrypt(std::string &encryptedText, int key);
    //encrypt a file
    void encryptFile(const string& filename, int key);
    //decrypt a file
    void decryptFile(const string &filename, int key);

private:

};


#endif //TEST_ENCRYPTDECRYPT_H
