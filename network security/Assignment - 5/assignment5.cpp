#include <bits/stdc++.h>
using namespace std;

const int N = 3;
const int MOD = 26;
int KEYMATRIX[N][N];
int KEYMATRIXINVERSE[N][N];

void getCofactor(vector<vector<int>> &temp, int p, int q, int n)
{
    int i = 0, j = 0;
    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < n; col++)
        {
            if (row != p && col != q)
            {
                temp[i][j++] = KEYMATRIX[row][col];

                if (j == n - 1)
                {
                    j = 0;
                    i++;
                }
            }
        }
    }
}

int determinant(int n)
{
    int D = 0;
    if (n == 1)
        return KEYMATRIX[0][0];
    vector<vector<int>> temp(N, vector<int>(N));
    int sign = 1;
    for (int f = 0; f < n; f++)
    {
        getCofactor(temp, 0, f, n);
        D += sign * KEYMATRIX[0][f] * determinant(n - 1);
        sign = -sign;
    }
    return D;
}

void adjoint()
{
    if (N == 1)
    {
        KEYMATRIXINVERSE[0][0] = 1;
        return;
    }
    int sign = 1;
    vector<vector<int>> temp(N, vector<int>(N));
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            getCofactor(temp, i, j, N);

            sign = ((i + j) % 2 == 0) ? 1 : -1;

            KEYMATRIXINVERSE[j][i] = (sign) * (determinant(N - 1));
        }
    }
}

int modInverse(int A)
{
    if (__gcd(A, MOD) > 1) {
        return -1;
    }
    for (int X = 1; X < MOD; X++)
        if (((A % MOD) * (X % MOD)) % MOD == 1)
            return X;
}

int keyMatricGeneration()
{
    cout << "Enter the KEY of 3X3 :\n"
         << endl;

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cout << "\t enter " << i << ", " << j << " value of KEY : ";
            cin >> KEYMATRIX[i][j];
        }
    }

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cout << KEYMATRIX[i][j] << " ";
        }
        cout << endl;
    }

    int check = determinant(N);

    if (check == 0)
    {
        cout << "KEY cannot be used for encryption";
        return 1;
    }

    int detInverse = modInverse(check);

    adjoint();

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            KEYMATRIXINVERSE[i][j] = (KEYMATRIXINVERSE[i][j] * detInverse) % MOD;
        }
    }

    return 0;
}

void encrypt(int cipherMatrix[][1], int messageVector[][1])
{
    int x, i, j;
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 1; j++)
        {
            cipherMatrix[i][j] = 0;

            for (x = 0; x < 3; x++)
            {
                cipherMatrix[i][j] += KEYMATRIX[i][x] * messageVector[x][j];
            }

            cipherMatrix[i][j] = cipherMatrix[i][j] % 26;
        }
    }
}

void decrypt(int messageMatrix[][1], int cipherVector[][1])
{
    int x, i, j;
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 1; j++)
        {
            messageMatrix[i][j] = 0;

            for (x = 0; x < 3; x++)
            {
                messageMatrix[i][j] += KEYMATRIXINVERSE[i][x] * cipherVector[x][j];
            }

            messageMatrix[i][j] = messageMatrix[i][j] % 26;
        }
    }
}

string hillCipherEncryption(string plaintext)
{
    string cipherText;
    while (plaintext.length() % 3 != 0)
    {
        plaintext.append("Z");
    }

    for (int i = 0; i < plaintext.length() / 3; i++)
    {
        int messageVector[3][1];
        for (int j = 0; j < 3; j++)
        {
            messageVector[i][0] = (plaintext[i * 3 + j]) % 65;
        }

        int messageMatrix[3][1];
        encrypt(messageMatrix, messageVector);

        for (int i = 0; i < 3; i++)
        {
            cipherText += messageMatrix[i][0] + 65;
        }
    }

    return cipherText;
}

string hillCipherDecryption(const string cipherText)
{
    string plaintext;

    for (int i = 0; i < cipherText.length() / 3; i++)
    {
        int cipherVector[3][1];
        for (int j = 0; j < 3; j++)
        {
            cipherVector[i][0] = (cipherText[i * 3 + j]) % 65;
        }

        int cipherMatrix[3][1];
        decrypt(cipherMatrix, cipherVector);

        for (int i = 0; i < 3; i++)
        {
            plaintext += cipherMatrix[i][0] + 65;
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
        cout << "1. Encryption of Hill Cipher" << endl;
        cout << "2. Decryption of Hill Cipher." << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;
        cin.ignore();

        if (choice == 3)
            break;

        string plaintext, cipherText, decryptedText;
        switch (choice)
        {
        case 1:
        {
            int invalidkey = keyMatricGeneration();
            if (invalidkey)
                break;
            plaintext = readFile("file.txt");
            cipherText = hillCipherEncryption(plaintext);
            writeFile("Cipher.txt", cipherText);
            cout << "Encryption complete. Output written to Cipher.txt" << endl;
            break;
        }
        case 2:
            cipherText = readFile("Cipher.txt");
            decryptedText = hillCipherDecryption(cipherText);
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
