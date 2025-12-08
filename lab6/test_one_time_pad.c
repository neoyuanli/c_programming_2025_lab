#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "one_time_pad.h"

void test_key_generation() {
  printf("Running test: Key Generation...\n");

  // Test 1.1: Valid length
  unsigned char* key1 = generate_key(16);
  assert(key1 != NULL);
  free(key1);

  // Test 1.2: Edge case length 0
  unsigned char* key2 = generate_key(0);
  assert(key2 == NULL);

  // Test 1.3: Invalid length -1
  unsigned char* key3 = generate_key(-1);
  assert(key3 == NULL);

  printf("  ...passed.\n");
}

// Test Case 2 & 3: NULL Inputs
void test_null_inputs() {
  printf("Running test: NULL Inputs...\n");
  unsigned char dummy_key[1] = {0x01};
  unsigned char dummy_data[1] = {0x01};

  // Test 2.2: encrypt(NULL, ...)
  unsigned char* res1 = encrypt(NULL, 1, dummy_key);
  assert(res1 == NULL);

  // Test 2.3: encrypt(..., NULL)
  unsigned char* res2 = encrypt(dummy_data, 1, NULL);
  assert(res2 == NULL);

  // Test 3.2: decrypt(NULL, ...)
  unsigned char* res3 = decrypt(NULL, 1, dummy_key);
  assert(res3 == NULL);

  // Test 3.3: decrypt(..., NULL)
  unsigned char* res4 = decrypt(dummy_data, 1, NULL);
  assert(res4 == NULL);

  // Test 2.4: Invalid length (zero)
  unsigned char* res5 = encrypt(dummy_data, 0, dummy_key);
  assert(res5 == NULL);

  printf("  ...passed.\n");
}

void test_known_values() {
  printf("Running test: Known Values...\n");
  unsigned char plain[] = {0xAA, 0xBB, 0xCC};
  unsigned char key[] = {0x11, 0x22, 0x33};
  unsigned char expected_cipher[] = {0xBB, 0x99, 0xFF};
  int len = 3;

  // Test 2.1: Encryption
  unsigned char* cipher = encrypt(plain, len, key);
  assert(cipher != NULL);  // 必须成功分配
  // 验证加密逻辑
  assert(memcmp(cipher, expected_cipher, len) == 0);

  // Test 3.1: Decryption
  unsigned char* decrypted = decrypt(cipher, len, key);
  assert(decrypted != NULL);  // 必须成功分配
  // 验证解密逻辑
  assert(memcmp(decrypted, plain, len) == 0);

  free(cipher);
  free(decrypted);
  printf("  ...passed.\n");
}

void test_roundtrip() {
  printf("Running test: Full Roundtrip...\n");

  unsigned char message[] = "Hello World!";
  int len = sizeof(message);  // 包括 '\0'

  // 1. Generate key
  unsigned char* key = generate_key(len);
  assert(key != NULL);

  // 2. Encrypt
  unsigned char* cipher_text = encrypt(message, len, key);
  assert(cipher_text != NULL);

  // 3. Sanity check: ciphertext should be different from plaintext
  assert(memcmp(message, cipher_text, len) != 0);

  // 4. Decrypt
  unsigned char* decrypted_text = decrypt(cipher_text, len, key);
  assert(decrypted_text != NULL);

  // 5. Verify
  assert(memcmp(message, decrypted_text, len) == 0);

  // 6. Clean up
  free(key);
  free(cipher_text);
  free(decrypted_text);

  printf("  ...passed.\n");
}

int main() {
  // Seed the random number generator ONCE.
  srand((unsigned int)time(NULL));

  printf("--- Starting One-Time Pad (OTP) Test Suite ---\n");

  test_key_generation();
  test_null_inputs();
  test_known_values();
  test_roundtrip();

  printf("--- All tests passed! ---\n");
  return 0;
}
