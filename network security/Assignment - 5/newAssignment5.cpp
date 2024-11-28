#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include <stdexcept>

using namespace std;

int modular_inverse(int a, int mod) {
    int m0 = mod, t, q;
    int x0 = 0, x1 = 1;

    if (mod == 1)
        return 0;

    while (a > 1) {
        q = a / mod;  // Quotient
        t = mod;

        // Update mod and a
        mod = a % mod;
        a = t;

        // Update x0 and x1
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }

    if (x1 < 0)
        x1 += m0;

    return x1;
}

int char_to_num(char c) {
    return c - 'A';
}

char num_to_char(int n) {
    return 'A' + n;
}

vector<vector<int>> create_key_matrix(string key, int size) {
    key.erase(remove(key.begin(), key.end(), ' '), key.end());
    transform(key.begin(), key.end(), key.begin(), ::toupper);

    int required_length = size * size;
    key.append(required_length - key.length(), 'X'); // Pad with 'X'

    vector<vector<int>> key_matrix(size, vector<int>(size));
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            key_matrix[i][j] = char_to_num(key[i * size + j]);
        }
    }
    return key_matrix;
}

string pad_plaintext(string plain_text, int size) {
    plain_text.erase(remove(plain_text.begin(), plain_text.end(), ' '), plain_text.end());
    transform(plain_text.begin(), plain_text.end(), plain_text.begin(), ::toupper);

    int padding = (size - plain_text.length() % size) % size;
    plain_text.append(padding, 'X'); // Pad with 'X'
    return plain_text;
}

vector<vector<int>> create_message_matrix(string message, int size) {
    message = pad_plaintext(message, size);
    vector<vector<int>> message_matrix(size, vector<int>(message.length() / size));
    
    for (size_t i = 0; i < message.length(); i++) {
        message_matrix[i % size][i / size] = char_to_num(message[i]);
    }
    return message_matrix;
}

vector<vector<int>> matrix_multiply_mod(const vector<vector<int>>& A, const vector<vector<int>>& B, int size, int mod = 26) {
    vector<vector<int>> result(size, vector<int>(B[0].size(), 0));
    for (int i = 0; i < size; i++) {
        for (size_t j = 0; j < B[0].size(); j++) {
            for (int k = 0; k < size; k++) {
                result[i][j] += A[i][k] * B[k][j];
            }
            result[i][j] %= mod;
        }
    }
    return result;
}

int find_determinant(vector<vector<int>> matrix, int size) {
    if (size == 2) {
        return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
    }

    int determinant = 0;
    for (int c = 0; c < size; c++) {
        vector<vector<int>> sub_matrix;
        for (int i = 1; i < size; i++) {
            vector<int> row;
            for (int j = 0; j < size; j++) {
                if (j != c) row.push_back(matrix[i][j]);
            }
            sub_matrix.push_back(row);
        }
        determinant += ((c % 2 == 0) ? 1 : -1) * matrix[0][c] * find_determinant(sub_matrix, size - 1);
    }
    return determinant;
}

vector<vector<int>> find_matrix_inverse(vector<vector<int>> matrix, int size, int mod) {
    int det = find_determinant(matrix, size) % mod;
    if (det < 0) det += mod;

    int det_inv;
    try {
        det_inv = modular_inverse(det, mod);
    } catch (exception& e) {
        throw runtime_error("Determinant is not invertible under modulo 26. Key is invalid.");
    }

    vector<vector<int>> cofactors(size, vector<int>(size));
    for (int r = 0; r < size; r++) {
        for (int c = 0; c < size; c++) {
            vector<vector<int>> minor;
            for (int i = 0; i < size; i++) {
                if (i == r) continue;
                vector<int> row;
                for (int j = 0; j < size; j++) {
                    if (j == c) continue;
                    row.push_back(matrix[i][j]);
                }
                minor.push_back(row);
            }
            cofactors[r][c] = ((r + c) % 2 == 0 ? 1 : -1) * find_determinant(minor, size - 1) % mod;
            if (cofactors[r][c] < 0) cofactors[r][c] += mod;
        }
    }

    vector<vector<int>> adjugate(size, vector<int>(size));
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            adjugate[i][j] = cofactors[j][i];
        }
    }

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            adjugate[i][j] = (adjugate[i][j] * det_inv) % mod;
        }
    }
    return adjugate;
}

string hill_cipher_encrypt(string plain_text, vector<vector<int>> key_matrix, int size) {
    vector<vector<int>> plain_matrix = create_message_matrix(plain_text, size);
    vector<vector<int>> cipher_matrix = matrix_multiply_mod(key_matrix, plain_matrix, size);

    string cipher_text;
    for (size_t j = 0; j < cipher_matrix[0].size(); j++) {
        for (int i = 0; i < size; i++) {
            cipher_text += num_to_char(cipher_matrix[i][j]);
        }
    }
    return cipher_text;
}

string hill_cipher_decrypt(string cipher_text, vector<vector<int>> key_matrix, int size) {
    vector<vector<int>> key_matrix_inv;
    try {
        key_matrix_inv = find_matrix_inverse(key_matrix, size, 26);
    } catch (exception& e) {
        cout << "Error: " << e.what() << endl;
        return "";
    }

    vector<vector<int>> cipher_matrix = create_message_matrix(cipher_text, size);
    vector<vector<int>> plain_matrix = matrix_multiply_mod(key_matrix_inv, cipher_matrix, size);

    string plain_text;
    for (size_t j = 0; j < plain_matrix[0].size(); j++) {
        for (int i = 0; i < size; i++) {
            plain_text += num_to_char(plain_matrix[i][j]);
        }
    }
    return plain_text;
}

void hill_cipher_menu() {
    while (true) {
        cout << "\nMenu:\n1. Encryption\n2. Decryption\n3. Exit\nEnter your choice: ";
        int choice;
        cin >> choice;

        if (choice == 1) {
            cout << "Enter the plaintext: ";
            string plain_text;
            cin >> plain_text;
            cin.ignore();

            cout << "Enter the key: ";
            string key;
            cin >> key;

            int size = sqrt(key.length());
            if (size * size != key.length()) {
                cout << "Key length is not a perfect square. Padding the key with 'X'.\n";
            }
            vector<vector<int>> key_matrix = create_key_matrix(key, size);
            string cipher_text = hill_cipher_encrypt(plain_text, key_matrix, size);
            cout << "Encrypted Text: " << cipher_text << endl;

        } else if (choice == 2) {
            cout << "Enter the ciphertext: ";
            string cipher_text;
            cin >> cipher_text;
            cin.ignore();

            cout << "Enter the key: ";
            string key;
            cin >> key;

            int size = sqrt(key.length());
            if (size * size != key.length()) {
                cout << "Key length is not a perfect square. Padding the key with 'X'.\n";
            }
            vector<vector<int>> key_matrix = create_key_matrix(key, size);
            string plain_text = hill_cipher_decrypt(cipher_text, key_matrix, size);
            if (!plain_text.empty()) {
                cout << "Decrypted Text: " << plain_text << endl;
            }

        } else if (choice == 3) {
            cout << "Exiting...\n";
            break;

        } else {
            cout << "Invalid choice. Please try again.\n";
        }
    }
}

int main() {
    hill_cipher_menu();
    return 0;
}
