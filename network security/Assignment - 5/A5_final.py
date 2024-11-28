def char_to_num(c):
    return ord(c) - ord('A')

def num_to_char(n):
    return chr(n + ord('A'))

def create_key_matrix(key, size):
    key = key.upper().replace(" ", "")
    
    required_length = size * size
    padding = required_length - len(key)
    key += 'X' * padding 
    
    key_matrix = []
    for i in range(size):
        row = [char_to_num(key[i * size + j]) for j in range(size)]
        key_matrix.append(row)
    return key_matrix

def pad_plaintext(plain_text, size):
    plain_text = plain_text.upper().replace(" ", "")
    padding = (size - len(plain_text) % size) % size
    return plain_text + 'X' * padding

def create_message_matrix(message, size):
    message = pad_plaintext(message, size)
    message_matrix = []
    for i in range(0, len(message), size):
        row = [char_to_num(c) for c in message[i:i + size]]
        message_matrix.append(row)
    return [list(i) for i in zip(*message_matrix)]

def matrix_multiply_mod(A, B, size, mod=26):
    result = [[0] * len(B[0]) for _ in range(size)]
    for i in range(size):
        for j in range(len(B[0])):
            result[i][j] = sum(A[i][k] * B[k][j] for k in range(size)) % mod
    return result

def find_determinant(matrix, size):
    if size == 2:
        return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0]
    determinant = 0
    for c in range(size):
        sub_matrix = [row[:c] + row[c + 1:] for row in matrix[1:]]
        determinant += ((-1) ** c) * matrix[0][c] * find_determinant(sub_matrix, size - 1)
    return determinant

def find_matrix_inverse(matrix, size, mod):
    det = find_determinant(matrix, size) % mod
    try:
        det_inv = pow(det, -1, mod) 
    except ValueError:
        raise ValueError(f"Determinant {det} is not invertible under mod {mod}. "
                         "Ensure the key matrix is valid and invertible.")
    
    if size == 2:
        return [[matrix[1][1] * det_inv % mod, -matrix[0][1] * det_inv % mod],
                [-matrix[1][0] * det_inv % mod, matrix[0][0] * det_inv % mod]]
    
    cofactors = []
    for r in range(size):
        cofactor_row = []
        for c in range(size):
            minor = [row[:c] + row[c + 1:] for row in matrix[:r] + matrix[r + 1:]]
            cofactor_row.append(((-1) ** (r + c)) * find_determinant(minor, size - 1))
        cofactor_row = [x % mod for x in cofactor_row]
        cofactors.append(cofactor_row)
    
    cofactors = [list(i) for i in zip(*cofactors)]  
    
    for r in range(size):
        for c in range(size):
            cofactors[r][c] = (cofactors[r][c] * det_inv) % mod
    
    return cofactors

def hill_cipher_encrypt(plain_text, key_matrix, size):
    plain_matrix = create_message_matrix(plain_text, size)
    cipher_matrix = matrix_multiply_mod(key_matrix, plain_matrix, size)
    cipher_text = ''.join([num_to_char(cipher_matrix[i][j]) for j in range(len(cipher_matrix[0])) for i in range(size)])
    return cipher_text

def hill_cipher_decrypt(cipher_text, key_matrix, size):
    try:
        key_matrix_inv = find_matrix_inverse(key_matrix, size, 26)
    except ValueError as e:
        print(f"Error: {e}")
        return ""
    
    cipher_matrix = create_message_matrix(cipher_text, size)
    plain_matrix = matrix_multiply_mod(key_matrix_inv, cipher_matrix, size)
    plain_text = ''.join([num_to_char(plain_matrix[i][j]) for j in range(len(plain_matrix[0])) for i in range(size)])
    return plain_text

def hill_cipher_menu():
    while True:
        print("\nMenu:")
        print("1. Encryption")
        print("2. Decryption")
        print("3. Exit")
        choice = int(input("Enter your choice: "))
        
        if choice == 1:
            plain_text = input("Enter the plaintext: ")
            key = input("Enter the key: ")
            size = int(len(key) ** 0.5)
            if size * size != len(key):
                print(f"Key length is not a perfect square. Padding the key with 'X'.")
            key_matrix = create_key_matrix(key, size)
            cipher_text = hill_cipher_encrypt(plain_text, key_matrix, size)
            print(f"Encrypted Text: {cipher_text}")
        
        elif choice == 2:
            cipher_text = input("Enter the ciphertext: ")
            key = input("Enter the key: ")
            size = int(len(key) ** 0.5)
            if size * size != len(key):
                print(f"Key length is not a perfect square. Padding the key with 'X'.")
            key_matrix = create_key_matrix(key, size)
            plain_text = hill_cipher_decrypt(cipher_text, key_matrix, size)
            if plain_text:
                print(f"Decrypted Text: {plain_text}")
        
        elif choice == 3:
            print("Exiting...")
            break
        
        else:
            print("Invalid choice. Please try again.")

if __name__ == "__main__":
    hill_cipher_menu()
