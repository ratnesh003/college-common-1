#include <bits\stdc++.h>
using namespace std;

string freqorder = "etainoshrdlucmfwygpbvkqjxz";

priority_queue<pair<char, int>> freqmap;

int cnt = 26;


string caesarEncrypt(const string &text, int shift)
{
    string encrypted;
    for (char c : text)
    {
        if (isalpha(c))
        {
            char base = isupper(c) ? 'A' : 'a';
            encrypted += (c - base + shift) % 26 + base;
        }
        else
        {
            encrypted += c;
        }
    }
    return encrypted;
}


string caesarDecrypt(const string &text, int shift)
{
    return caesarEncrypt(text, 26 - (shift % 26));
}


void bruteForceCaesar(const string &text)
{
    for (int shift = 0; shift < 26; ++shift)
    {
        string decrypted = caesarDecrypt(text, shift);
        cout << "Shift " << shift << ": " << decrypted << endl;
    }
}


int frequencyAnalysis(const string &text)
{
    map<char, int> freq;
    for (char c : text)
    {
        if (isalpha(c))
        {
            c = tolower(c);
            freq[c]++;
        }
    }
    char mostFreqChar = max_element(freq.begin(), freq.end(),
                                    [](const pair<char, int> &a, const pair<char, int> &b)
                                    {
                                        return a.second < b.second;
                                    })
                            ->first;
    char c = freqmap.top().second;
    freqmap.pop();
    return (mostFreqChar - c + 26) % 26;
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
    for (char it : freqorder)
        freqmap.push({cnt--, it});
    while (true)
    {
        cout << "Menu:" << endl;
        cout << "1. Encryption of Caesar Cipher" << endl;
        cout << "2. Decryption of Caesar Cipher" << endl;
        cout << "3. Cryptanalysis of Caesar Cipher" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;
        cin.ignore();
        if (choice == 4)
        {
            break;
        }
        string plaintext, cipherText, decryptedText;
        int shift;
        string filename, outputFilename;
        switch (choice)
        {
        case 1:
            cout << "Enter shift value: ";
            cin >> shift;
            cin.ignore();
            plaintext = readFile("file.txt");
            cipherText = caesarEncrypt(plaintext, shift);
            writeFile("Cipher.txt", cipherText);
            cout << "Encryption complete. Output written to Cipher.txt" << endl;
            break;
        case 2:
            cout << "Enter shift value: ";
            cin >> shift;
            cin.ignore();
            cipherText = readFile("Cipher.txt");
            decryptedText = caesarDecrypt(cipherText, shift);
            writeFile("Recover.txt", decryptedText);
            cout << "Decryption complete. Output written to Recover.txt" << endl;
            break;
        case 3:
            cout << "1. Brute Force Attack" << endl;
            cout << "2. Frequency Analysis" << endl;
            cout << "Enter your choice: ";
            int subChoice;
            cin >> subChoice;
            cin.ignore();
            cipherText = readFile("Cipher.txt");
            if (subChoice == 1)
            {
                bruteForceCaesar(cipherText);
            }
            else if (subChoice == 2)
            {
                bool check = true;
                while (check)
                {
                    int estimatedShift = frequencyAnalysis(cipherText);
                    cout << "Estimated shift based on frequency analysis: " << estimatedShift << endl;
                    cipherText = readFile("Cipher.txt");
                    decryptedText = caesarDecrypt(cipherText, shift);
                    writeFile("Recover.txt", decryptedText);
                    cout << "For again frequency analysis choose Y else N" << endl;
                    string flag;
                    cin >> flag;
                    if (flag == "Y")
                    {
                        cnt = 26;
                        for (char it : freqorder)
                            freqmap.push({cnt--, it});
                    }
                    else {
                        break;
                    }
                }
            }
            else
            {
                cout << "Invalid choice!" << endl;
            }
            break;
        default:
            cout << "Invalid choice!" << endl;
            break;
        }
    }
    return 0;
}