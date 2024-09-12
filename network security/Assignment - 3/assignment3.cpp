#include <bits/stdc++.h>
using namespace std;

string railFenceEncryption(string text, int key)
{
	char zigZagMap[key][(text.length())];

	for (int i=0; i < key; i++)
		for (int j = 0; j < text.length(); j++)
			zigZagMap[i][j] = '\n';

	bool direction = false;
	int row = 0, col = 0;

	for (int i=0; i < text.length(); i++)
	{
		if (row == 0 || row == key-1)
			direction = !direction;

		zigZagMap[row][col++] = text[i];

		direction?row++ : row--;
	}

	string result;
	for (int i=0; i < key; i++)
		for (int j=0; j < text.length(); j++)
			if (zigZagMap[i][j]!='\n')
				result.push_back(zigZagMap[i][j]);

	return result;
}

string railFenceDecryption(string cipher, int key)
{
	char zigZagMap[key][cipher.length()];

	for (int i=0; i < key; i++)
		for (int j=0; j < cipher.length(); j++)
			zigZagMap[i][j] = '\n';

	bool direction = false;

	int row = 0, col = 0;

	for (int i=0; i < cipher.length(); i++)
	{
		if (row == 0 || row == key-1)
			direction = !direction;

		zigZagMap[row][col++] = '*';

		direction?row++ : row--;
	}

	int index = 0;
	for (int i=0; i<key; i++)
		for (int j=0; j<cipher.length(); j++)
			if (zigZagMap[i][j] == '*' && index<cipher.length())
				zigZagMap[i][j] = cipher[index++];


	string result;
    direction = false;

	row = 0, col = 0;
	for (int i=0; i< cipher.length(); i++)
	{
		if (row == 0 || row == key-1)
			direction = !direction;

		if (zigZagMap[row][col] != '*')
			result.push_back(zigZagMap[row][col++]);

		direction?row++: row--;
	}
	return result;
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
        cout << "1. Encryption of Rail Fence Cipher" << endl;
        cout << "2. Decryption of Rail Fence Cipher" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;
        cin.ignore();
        if (choice == 3)
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
            cipherText = railFenceEncryption(plaintext, shift);
            writeFile("Cipher.txt", cipherText);
            cout << "Encryption complete. Output written to Cipher.txt" << endl;
            break;
        case 2:
            cout << "Enter shift value: ";
            cin >> shift;
            cin.ignore();
            cipherText = readFile("Cipher.txt");
            decryptedText = railFenceDecryption(cipherText, shift);
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
