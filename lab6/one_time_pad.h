// Generate a random key of 'len' bytes.
// Each byte is uniformly chosen from [0, 255].
// The function allocates memory for the key.
// The caller will free the returned memory.
unsigned char* generate_key(int len);

// Encrypt a message of 'len' bytes using a one-time pad.
// For each i in [0, len-1], cipher_text[i] = plain_text[i] ^ key[i].
// Assume the key has length at least 'len'.
// Return the pointer to ciphertext.
// The function allocates memory for the ciphertext;
// the caller is responsible for freeing it.
unsigned char* encrypt(unsigned char* plain_text, int len, unsigned char* key);

// Decrypt a ciphertext of 'len' bytes using a one-time pad.
// For each i in [0, len-1], plain_text[i] = cipher_text[i] ^ key[i].
// Assume the key has length at least 'len'.
// Return the pointer to plaintext.
// The function allocates memory for the plaintext;
// the caller is responsible for freeing it.
unsigned char* decrypt(unsigned char* cipher_text, int len, unsigned char* key);
