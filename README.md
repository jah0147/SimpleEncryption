# Simple C++ File Encryption

## Overview

This is a simple command-line application written in C++ that allows you to encrypt and decrypt files using a password. The application uses a basic transposition cipher for its encryption algorithm.

## How it Works

The encryption algorithm is a simple transposition cipher. It works by repeatedly rearranging the characters of the input text.

1.  **Key Derivation:** The password you provide is converted into a numeric "key". This is done by summing the ASCII values of all characters in the password. The result is then taken modulo 50 (to keep the number of iterations reasonable) and 1 is added (to ensure the key is never zero).

2.  **Transposition:** The application then iterates a number of times equal to the derived key. In each iteration, it splits the text into two strings: one containing all the characters at even positions, and one containing all the characters at odd positions. It then concatenates these two strings (`odds` + `evens`) to form the new text for the next iteration.

Decryption is the reverse of this process. It intelligently splits the encrypted text back into the "odds" and "evens" parts and reconstructs the original text, repeating the process for the same number of key iterations.

## How to Build

The project uses CMake for building. You will need a C++ compiler (like g++) and CMake installed on your system.

1.  **Clone the repository:**
    ```bash
    git clone <repository-url>
    cd <repository-directory>
    ```

2.  **Create a build directory:**
    ```bash
    mkdir build
    cd build
    ```

3.  **Run CMake to configure the project:**
    ```bash
    cmake ..
    ```

4.  **Compile the source code:**
    ```bash
    make
    ```
    This will create an executable named `encryption` in the `build` directory.

## How to Use

The application is run from the command line and takes three arguments.

**Syntax:**
```bash
./build/encryption <operation> <filepath> <password>
```

**Arguments:**

*   `<operation>`:
    *   `e`: Encrypt the file.
    *   `d`: Decrypt the file.
*   `<filepath>`: The path to the file you want to process.
*   `<password>`: The password to use for encryption or decryption.

**Example: Encrypting a file**
```bash
./build/encryption e my_secret_document.txt "p@ssw0rd123"
```

**Example: Decrypting a file**
```bash
./build/encryption d my_secret_document.txt "p@ssw0rd123"
```

**Note:** The application modifies the file in-place. Make sure you have a backup if the data is critical.

---

## Recreating the Project: A Tutorial

This section provides a conceptual walkthrough for a C++ developer to recreate this project from scratch.

### 1. Project Structure

First, organize your project into four main files:
- `CMakeLists.txt`: The build instructions for the CMake tool.
- `EncryptDecrypt.h`: The header file for our encryption/decryption class. It defines the class interface.
- `EncryptDecrypt.cpp`: The implementation file for the class, containing the core logic.
- `main.cpp`: The entry point of our application, responsible for handling command-line arguments.

### 2. The Class Header (`EncryptDecrypt.h`)

This file defines the `EncryptDecrypt` class. We seprarate the interface from the implementation to keep the code organized.

```cpp
#include <string>
// ... other necessary includes like fstream, iostream, etc.

class EncryptDecrypt {
public:
    EncryptDecrypt(); // Constructor
    void encryptFile(const std::string& filename, const std::string& password);
    void decryptFile(const std::string& filename, const std::string& password);

private:
    int deriveKey(const std::string& password);
    std::string encrypt(std::string text, int key);
    std::string decrypt(std::string encryptedText, int key);
};
```
- **Why public methods?** `encryptFile` and `decryptFile` are the main public-facing functions that `main.cpp` will call.
- **Why private methods?** `deriveKey`, `encrypt`, and `decrypt` are internal helper functions. They contain the core logic but don't need to be called from outside the class, so we hide them by making them private. This is a key principle of encapsulation.

### 3. The Implementation (`EncryptDecrypt.cpp`)

Here we implement the logic defined in the header.

- **`deriveKey`**: This function converts the password string into a number. A simple algorithm is to sum the ASCII values of the characters. We use the modulo operator (`%`) to keep the resulting key within a reasonable range, preventing excessively long encryption times.

- **`encrypt` and `decrypt`**: These are the core of the cipher. The `encrypt` function rearranges the string by separating odd and even-indexed characters. The `decrypt` function must perform the exact reverse of this process to restore the original text. It's crucial that the splitting logic in `decrypt` correctly mirrors how `encrypt` combines the strings.

- **`encryptFile` and `decryptFile`**: These methods handle file I/O.
    1. They open and read the entire contents of the file at the given `filepath` into a string. A `stringstream` is a good way to do this.
    2. They call `deriveKey` to get the encryption key from the password.
    3. They call the private `encrypt` or `decrypt` method on the file's content.
    4. They open the *same file* again for writing (using `std::ios::trunc` to clear it) and write the modified content back, overwriting the original.

### 4. The Main Entry Point (`main.cpp`)

This file is the C++ program's entry point and handles the user-facing logic.

```cpp
#include "EncryptDecrypt.h"
#include <iostream>

int main(int argc, char* argv[]) {
    // ...
}
```
- **`argc` and `argv`**: These are how C++ programs receive command-line arguments. `argc` is the argument count, and `argv` is an array of C-style strings.
- **Argument Parsing**: The first part of `main` should check if `argc` is correct (it should be 4: program name, operation, filepath, password). If not, print a usage message and exit.
- **Calling the Logic**: Based on the operation (`argv[1]`), create an instance of the `EncryptDecrypt` class and call either `ed.encryptFile(...)` or `ed.decryptFile(...)`, passing the filepath and password from `argv`.

### 5. The Build System (`CMakeLists.txt`)

CMake is a tool that automates the build process.

```cmake
cmake_minimum_required(VERSION 3.10) # Sets the minimum required CMake version
project(encryption) # Defines the project name

set(CMAKE_CXX_STANDARD 14) # Sets the C++ standard to C++14

# Creates the executable 'encryption' from the specified source files
add_executable(encryption main.cpp EncryptDecrypt.cpp)
```
- This file tells CMake how to build your project. The `add_executable` command is the most important part: it links all your source files together to create the final application.

By following these steps, you can build a clean, organized, and functional command-line utility in C++.
