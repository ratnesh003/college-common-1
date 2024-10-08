#include <bits/stdc++.h>
using namespace std;

const int SIZE = 3;
int KEYMATRIX[SIZE][SIZE];
 


void keyMatricGeneration(string key) {
    return ;
}

string playFairCipherEncryption(string plaintext) {
    string cipherText;
    return cipherText;
}

string playFairCipherDecryption(const string cipherText) {
    string plaintext;
    return plaintext;
}

string readFile(const string &filename)
{
    ifstream file(filename);
    if (!file)
    {
        cerr << "Error opening file: " << filename << endl;
        exit(1);
    }
    return string((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
}

void writeFile(const string &filename, const string &content)
{
    ofstream file(filename);
    if (!file)
    {
        cerr << "Error opening file: " << filename << endl;
        exit(1);
    }
    file << content;
}

int main()
{
    while (true)
    {
        cout << "Menu:" << endl;
        cout << "1. Encryption of Hill Cipher" << endl;
        cout << "2. Decryption of Hill Cipher." << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;
        cin.ignore();

        if (choice == 3)
            break;

        string plaintext, cipherText, decryptedText, key;
        switch (choice)
        {
        case 1:
            key = readFile("key.txt");
            keyMatricGeneration(key);
            plaintext = readFile("file.txt");
            cipherText = playFairCipherEncryption(plaintext);
            writeFile("Cipher.txt", cipherText);
            cout << "Encryption complete. Output written to Cipher.txt" << endl;
            break;
        case 2:
            cipherText = readFile("Cipher.txt");
            decryptedText = playFairCipherDecryption(cipherText);
            writeFile("Recover.txt", decryptedText);
            cout << "Decryption complete. Output written to Recover.txt" << endl;
            break;
        default:
            cout << "Invalid choice!" << endl;
            break;
        }
    }
    return 0;
}
