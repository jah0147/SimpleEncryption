//
// Created by jacob_howard on 10/24/2023.
//

#include "EncryptDecrypt.h"
#include <numeric>

EncryptDecrypt::EncryptDecrypt()
{
}

int EncryptDecrypt::deriveKey(const string& password) {
    int key = 0;
    // Sum the ASCII values of the password characters
    for (char c : password) {
        key += static_cast<int>(c);
    }
    // Modulo to keep the key in a reasonable range, +1 to avoid a key of 0.
    return (key % 50) + 1;
}

// The core encryption algorithm for a string
string EncryptDecrypt::encrypt(string text, int key) {
    for (int i = 0; i < key; i++) {
        string odds = "";
        string evens = "";
        for (size_t j = 0; j < text.length(); j++) {
            if (j % 2 == 0) {
                evens += text[j];
            } else {
                odds += text[j];
            }
        }
        text = odds + evens;
    }
    return text;
}

// The core decryption algorithm for a string
string EncryptDecrypt::decrypt(string encryptedText, int key) {
    for (int x = 0; x < key; x++) {
        string decryptedText = "";

        size_t odds_len = encryptedText.length() / 2;
        string odds = encryptedText.substr(0, odds_len);
        string evens = encryptedText.substr(odds_len);

        size_t j = 0, k = 0;
        for (size_t i = 0; i < encryptedText.length(); i++) {
            if (i % 2 == 0) {
                if (j < evens.length()) {
                    decryptedText += evens[j++];
                }
            } else {
                if (k < odds.length()) {
                    decryptedText += odds[k++];
                }
            }
        }
        encryptedText = decryptedText;
    }
    return encryptedText;
}

// Encrypt a file by reading, encrypting content, and overwriting
void EncryptDecrypt::encryptFile(const string& filename, const string& password) {
    // Open the input file in binary mode. This is crucial for handling all file types,
    // not just text files. In binary mode, the data is read as-is, without any
    // character translation (e.g., for line endings), which prevents corruption.
    ifstream input_file(filename, std::ios::binary);
    if (!input_file.is_open()) {
        cerr << "Error: Could not open file for reading: " << filename << endl;
        return;
    }
    stringstream buffer;
    buffer << input_file.rdbuf();
    string text = buffer.str();
    input_file.close();

    int key = deriveKey(password);
    string encrypted_text = encrypt(text, key);

    // Open the output file in binary mode to write the data without translation.
    // ios::trunc clears the file before writing.
    ofstream output_file(filename, std::ios::binary | std::ios::trunc);
    if (!output_file.is_open()) {
        cerr << "Error: Could not open file for writing: " << filename << endl;
        return;
    }
    output_file << encrypted_text;
    output_file.close();
}

// Decrypt a file by reading, decrypting content, and overwriting
void EncryptDecrypt::decryptFile(const string &filename, const string& password) {
    // Open the input file in binary mode to ensure the encrypted data is read
    // correctly without any character translation, which would corrupt the file.
    ifstream input_file(filename, std::ios::binary);
    if (!input_file.is_open()) {
        cerr << "Error: Could not open file for reading: " << filename << endl;
        return;
    }
    stringstream buffer;
    buffer << input_file.rdbuf();
    string encryptedText = buffer.str();
    input_file.close();

    int key = deriveKey(password);
    string decryptedText = decrypt(encryptedText, key);

    // Open the output file in binary mode to write the decrypted data faithfully.
    // ios::trunc clears the file before writing.
    ofstream output_file(filename, std::ios::binary | std::ios::trunc);
    if (!output_file.is_open()) {
        cerr << "Error: Could not open file for writing: " << filename << endl;
        return;
    }
    output_file << decryptedText;
    output_file.close();
}
