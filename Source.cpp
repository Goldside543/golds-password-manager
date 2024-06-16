#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib> // For system("pause")

// Function to encrypt a string (you can use a better encryption algorithm)
std::string encrypt(const std::string& input) {
    std::string encrypted;
    for (char c : input) {
        encrypted += c + 1; // Simple shift
    }
    return encrypted;
}

// Function to decrypt an encrypted string
std::string decrypt(const std::string& encrypted) {
    std::string decrypted;
    for (char c : encrypted) {
        decrypted += c - 1; // Reverse the shift
    }
    return decrypted;
}

// Function to add a new password
void addPassword(std::ofstream& file) {
    std::string username, password;
    std::cout << "Enter username: ";
    std::cin >> username;
    std::cout << "Enter password: ";
    std::cin >> password;

    // Encrypt the password before storing
    password = encrypt(password);

    file << username << " " << password << std::endl;
    std::cout << "Password added successfully!\n";
}

// Function to retrieve a password
void retrievePassword(std::ifstream& file) {
    std::string username;
    std::cout << "Enter username: ";
    std::cin >> username;

    std::string storedUsername, storedPassword;
    while (file >> storedUsername >> storedPassword) {
        if (storedUsername == username) {
            // Decrypt the stored password
            std::string decryptedPassword = decrypt(storedPassword);
            std::cout << "Password for user '" << username << "': " << decryptedPassword << "\n";
            return;
        }
    }
    std::cout << "User not found.\n";
}

int main() {
    std::ofstream outFile("passwords.txt", std::ios::app); // Append mode
    std::ifstream inFile("passwords.txt");

    if (!outFile || !inFile) {
        std::cerr << "Error opening file.\n";
        return 1;
    }

    int choice;
    do {
        std::cout << "\nPassword Manager Menu:\n";
        std::cout << "1. Add a password\n";
        std::cout << "2. Retrieve a password\n";
        std::cout << "3. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            addPassword(outFile);
            break;
        case 2:
            retrievePassword(inFile);
            break;
        case 3:
            std::cout << "Exiting...\n";
            break;
        default:
            std::cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 3);

    outFile.close();
    inFile.close();
    system("pause"); // Pause execution (Windows-specific)
    return 0;
}
