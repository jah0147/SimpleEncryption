//
// Created by jacob_howard on 10/24/2023.
//

#include <limits>
#include "EncryptDecrypt.h"

EncryptDecrypt::EncryptDecrypt()
{
}

//Get user input
bool EncryptDecrypt::getUsrInput()
{
    bool bCommand = false;
    bool bEncrypt;

    while (!bCommand) {
        cout << "Would you like to Encrypt or Decrypt (E/D): ";
        char usr_input;
        cin >> usr_input;
        if (isalpha(usr_input))
        {
            usr_input = toupper(usr_input);
            switch (usr_input)
            {
                //Encrypt case
                case 'E':
                    bEncrypt = true;
                    bCommand = true;
                    break;
                    //Decrypt case
                case 'D':
                    bEncrypt = false;
                    bCommand = true;
                    break;
                default:
                    system("cls");
                    cout << "The input must be E or D..." << endl;
                    break;
            }
        }
        else
        {
            system("cls");
            cout << "The input must be E or D..." << endl;
        }
    }
    return bEncrypt;
}
//based in usr input, decide to En,De a string or file
void EncryptDecrypt::encryption_decryption(bool bEncrypt)
{
    bool bCommand = false;
    if (bEncrypt)
    {
        while (!bCommand) {
            cout << "Would you like to Encrypt a file or a message (F/M): ";
            char usr_input;
            cin >> usr_input;
            if (isalpha(usr_input))
            {
                usr_input = toupper(usr_input);
                string filename; //user input filename
                int key; //user input key
                string message; //user input message
                string coded_message; //output coded message
                stringstream ss;
                switch (usr_input)
                {
                    //Encrypt case
                    case 'F':
                        bCommand = true;

                        // COme back later to add checks for correct file name input and key
                        system("cls");
                        cout << "Please input the filename (Ex: file.txt): ";
                        cin >> filename;
                        system("cls");
                        cout << "Please input your key (Ex: 21): ";
                        cin >> key;
                        encryptFile(filename, key);
                        break;
                        //Decrypt case
                    case 'M':
                        // Come back to check for bad user inputs
                        bCommand = true;
                        system("cls");
                        cout << "What is your message: ";
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Wait for the user to press enter.
                        if (cin.peek() == '\n') {
                            cin.ignore(); // Skip the newline character.
                        }
                        getline(ss, message); // Read the message from the input stream.
                        system("cls");
                        cout << "What is your key (Ex: 21): ";
                        if (cin.peek() == '\n') {
                            cin.ignore(); // Skip the newline character.
                        }
                        cin >> key; // Read the key from the input stream.

                        coded_message = encrypt(message, key);
                        system("cls");
                        cout << "message: " << message << " key: " << key << endl;
                        cout << "Coded Message: " << coded_message << endl;

                        string wait;
                        cin >> wait;
                        system("cls");
                        break;
                }
            } else
            {
                system("cls");
                cout << "The input must be F or M..." << endl;
            }
        }
    }
    else
    {
        while (!bCommand) {
            cout << "Would you like to Decrypt a file or a message (F/M): ";
            char usr_input;
            cin >> usr_input;
            if (isalpha(usr_input)) {
                toupper(usr_input);
                string filename; //user input filename
                int key; //user input key
                string coded_message; //user input message
                string decoded_message; //output message
                switch (usr_input) {
                    //Encrypt case
                    case 'F':
                        bCommand = true;
                        // COme back later to add checks for correct file name input and key
                        system("cls");
                        cout << "Please input the filename (Ex: file.txt): ";
                        cin >> filename;
                        system("cls");
                        cout << "Please input your key (Ex: 21): ";
                        cin >> key;
                        decryptFile(filename, key);
                        break;
                        //Decrypt case
                    case 'M':
                        // Come back to check for bad user inputs
                        bCommand = true;

                        system("cls");
                        cout << "What is your message: ";
                        getline(cin, coded_message);
                        // Wait until the user hits enter.
                        cin.ignore();
                        system("cls");
                        cout << "What is your key (Ex: 21): ";
                        cin >> key;
                        decoded_message = decrypt(coded_message, key);
                        system("cls");
                        cout << "Decoded Message: " << decoded_message;
                        break;
                    default:
                        system("cls");
                        cout << "The input must be F or M..." << endl;
                        break;
                }
            } else {
                system("cls");
                cout << "The input must be F or M..." << endl;
            }
        }
    }
}
//Encrypt a string
string EncryptDecrypt::encrypt(string &text, int key) {
    string odds = "";
    string evens = "";
    //loop based on encryption number
    for (int i = 0; i < key; i++)
    {
        //switch indeceese
        for (int j = 0; j < text.length(); j++)
        {
            //add to odds or evens string
            if (j%2 == 0)
            {
                evens += text[j];
            }
            else
            {
                odds += text[j];
            }
        }
        text = odds + evens; //set text string
        //reset odds and evens
        odds = "";
        evens = "";
    }
    return text;
}
//Decrypt a string
string EncryptDecrypt::decrypt(std::string &encryptedText, int key)
{
    string odds = "";
    string evens = "";
    string decryptedText = "";

    if (key <= 0) //if we do not decrypt
    {
        decryptedText = encryptedText;
    }
    // Loop number of encryptions
    for (int x = 0; x < key; x++)
    {
        decryptedText = ""; //reset decripted
        // Split string into evens and odds
        odds = encryptedText.substr(0, encryptedText.length() / 2);
        evens = encryptedText.substr(encryptedText.length() / 2, encryptedText.length());

        // Add up strings
        int j = 0;
        for (int i = 0; i < encryptedText.length(); i++)
        {

            if ((i % 2) == 0) //if we on even i
            {
                decryptedText += evens[j];
            } else { // odd i
                decryptedText += odds[j];
                j++;
            }
        }
        encryptedText = decryptedText; //set encrypted to decrypted text for next loop
    }

    return decryptedText;
}
// Encrypt a file
void EncryptDecrypt::encryptFile(const string& filename, int key) {
    ifstream input_file(filename);
    string text;

    //set string to file contents
    while (std::getline(input_file, text)) {}
    input_file.close();

    string odds = "";
    string evens = "";
    //loop based on encryption number
    for (int i = 0; i < key; i++)
    {
        //switch indeceese
        for (int j = 0; j < text.length(); j++)
        {
            //add to odds or evens string
            if (j%2 == 0)
            {
                evens += text[j];
            }
            else
            {
                odds += text[j];
            }
        }
        text = odds + evens; //set text string
        //reset odds and evens
        odds = "";
        evens = "";
    }
    // Open the new file.
    ofstream output_file("encrypted_file.txt");

    // Write the string to the new file.
    output_file << text;
    // Close the new file.
    output_file.close();
}
//Decrypt a file
void EncryptDecrypt::decryptFile(const string &filename, int key) {
    // Open the input file.
    ifstream input_file(filename);

    // Read the contents of the input file into a string.
    string encryptedText;
    while (getline(input_file, encryptedText)) {}

    input_file.close();

    string odds = "";
    string evens = "";
    string decryptedText = "";

    if (key <= 0) //if we do not decrypt
    {
        decryptedText = encryptedText;
    }
    // Loop number of encryptions
    for (int x = 0; x < key; x++)
    {
        decryptedText = ""; //reset decripted
        // Split string into evens and odds
        odds = encryptedText.substr(0, encryptedText.length() / 2);
        evens = encryptedText.substr(encryptedText.length() / 2, encryptedText.length());

        // Add up strings
        int j = 0;
        for (int i = 0; i < encryptedText.length(); i++)
        {

            if ((i % 2) == 0) //if we on even i
            {
                decryptedText += evens[j];
            } else { // odd i
                decryptedText += odds[j];
                j++;
            }
        }
        encryptedText = decryptedText; //set encrypted to decrypted text for next loop
    }

    // Open the new file.
    ofstream output_file("decrypted_file.txt");

    // Write the string to the new file.
    output_file << decryptedText;

    // Close the new file.
    output_file.close();
}