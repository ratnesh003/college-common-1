#include <bits/stdc++.h>
using namespace std;

const int SIZE = 6;
char KEYTABLE[SIZE][SIZE];
const string ALPHANUM = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

void keyTableGeneration(string key) {
    unordered_set<char> used;
    int x = 0, y = 0;
    for (char &c : key)
    {
        c = toupper(c);
        if (isalnum(c) && used.find(c) == used.end())
        {
            KEYTABLE[x][y++] = c;
            used.insert(c);
            if (y == SIZE)
            {
                y = 0;
                x++;
            }
        }
    }
    for (char c : ALPHANUM)
    {
        if (used.find(c) == used.end())
        {
            KEYTABLE[x][y++] = c;
            used.insert(c);
            if (y == SIZE)
            {
                y = 0;
                x++;
            }
        }
    }
    return ;
}

void findPosition(char c, int &row, int &col)
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (KEYTABLE[i][j] == c)
            {
                row = i;
                col = j;
                return;
            }
        }
    }
}

string playFairCipherEncryption(string plaintext) {
    string cipherText;

    string result;
    for (char c : plaintext)
    {
        if (isalnum(c))
        {
            result += toupper(c);
        }
    }

    plaintext = result;

    for (size_t i = 0; i < plaintext.length(); i += 2)
    {
        if (i + 1 == plaintext.length() || plaintext[i] == plaintext[i + 1])
        {
            plaintext.insert(i + 1, "X");
        }
    }

    for (size_t i = 0; i < plaintext.length(); i += 2)
    {
        int row1, col1, row2, col2;
        findPosition(plaintext[i], row1, col1);
        findPosition(plaintext[i + 1], row2, col2);
        if (row1 == row2)
        {
            cipherText += KEYTABLE[row1][(col1 + 1) % SIZE];
            cipherText += KEYTABLE[row2][(col2 + 1) % SIZE];
        }
        else if (col1 == col2)
        {
            cipherText += KEYTABLE[(row1 + 1) % SIZE][col1];
            cipherText += KEYTABLE[(row2 + 1) % SIZE][col2];
        }
        else
        {
            cipherText += KEYTABLE[row1][col2];
            cipherText += KEYTABLE[row2][col1];
        }
    }
    return cipherText;
}

string playFairCipherDecryption(const string cipherText) {
    string plaintext;
    for (size_t i = 0; i < cipherText.length(); i += 2)
    {
        int row1, col1, row2, col2;
        findPosition(cipherText[i], row1, col1);
        findPosition(cipherText[i + 1], row2, col2);
        if (row1 == row2)
        {
            plaintext += KEYTABLE[row1][(col1 + SIZE - 1) % SIZE];
            plaintext += KEYTABLE[row2][(col2 + SIZE - 1) % SIZE];
        }
        else if (col1 == col2)
        {
            plaintext += KEYTABLE[(row1 + SIZE - 1) % SIZE][col1];
            plaintext += KEYTABLE[(row2 + SIZE - 1) % SIZE][col2];
        }
        else
        {
            plaintext += KEYTABLE[row1][col2];
            plaintext += KEYTABLE[row2][col1];
        }
    }
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
        cout << "1. Encryption of Playfair Cipher" << endl;
        cout << "2. Decryption of Playfair Cipher." << endl;
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
            keyTableGeneration(key);
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
