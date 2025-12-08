#include <stddef.h>
#include <stdlib.h>
#include <time.h> // 包含 time() 以便为 rand() 播种

// "one_time_pad.h" 假设已包含在主文件中
// #include "one_time_pad.h"

/**
 * @brief 生成一个指定长度的随机密钥。
 * @note 此实现使用 rand()，它不适用于密码学目的。
 * 应在 main() 中调用一次 srand(time(NULL))。
 * @param len 密钥所需的字节长度。
 * @return 成功时返回指向新分配密钥的指针，失败时返回 NULL。
 */
unsigned char* generate_key(int len) {
    if (len <= 0) {
        return NULL;
    }

    // 分配内存
    unsigned char* key = (unsigned char*)malloc(len * sizeof(unsigned char));
    if (key == NULL) {
        return NULL; // 内存分配失败
    }

    // 填充随机字节
    for (int i = 0; i < len; i++) {
        // rand() % 256 在 [0, 255] 范围内生成一个伪随机数
        key[i] = (unsigned char)(rand() % 256);
    }

    return key;
}

/**
 * @brief 使用一次性密码本加密消息。
 * @param plain_text 指向要加密的明文数据的指针。
 * @param len 数据的长度（字节）。
 * @param key 指向加密密钥的指针（长度必须 >= len）。
 * @return 成功时返回指向新分配密文的指针，失败时返回 NULL。
 */
unsigned char* encrypt(unsigned char* plain_text, int len, unsigned char* key) {
    if (plain_text == NULL || key == NULL || len <= 0) {
        return NULL;
    }

    // 为密文分配内存
    unsigned char* cipher_text = (unsigned char*)malloc(len * sizeof(unsigned char));
    if (cipher_text == NULL) {
        return NULL; // 内存分配失败
    }

    // 执行按位异或 (XOR)
    for (int i = 0; i < len; i++) {
        cipher_text[i] = plain_text[i] ^ key[i];
    }

    return cipher_text;
}

/**
 * @brief 使用一次性密码本解密消息。
 * @note 解密操作与加密操作完全相同。
 * @param cipher_text 指向要解密的密文数据的指针。
 * @param len 数据的长度（字节）。
 * @param key 指向解密密钥的指针（必须是用于加密的同一密钥）。
 * @return 成功时返回指向新分配明文的指针，失败时返回 NULL。
 */
unsigned char* decrypt(unsigned char* cipher_text, int len, unsigned char* key) {
    if (cipher_text == NULL || key == NULL || len <= 0) {
        return NULL;
    }

    // 为解密后的明文分配内存
    unsigned char* plain_text = (unsigned char*)malloc(len * sizeof(unsigned char));
    if (plain_text == NULL) {
        return NULL; // 内存分配失败
    }

    // 执行按位异或 (XOR)
    for (int i = 0; i < len; i++) {
        plain_text[i] = cipher_text[i] ^ key[i];
    }

    return plain_text;
}
