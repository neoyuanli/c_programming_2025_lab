#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "one_time_pad.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h> // 用于 strcmp
#include <time.h>

// 假设 "one_time_pad.h" 包含函数声明
// #include "one_time_pad.h"

// --- 粘贴您之前的函数实现 ---

/**
 * @brief 生成一个指定长度的随机密钥。
 * @note 此实现使用 rand()，它不适用于密码学目的。
 * 应在 main() 中调用一次 srand(time(NULL))。
 */
unsigned char* generate_key(int len) {
    if (len <= 0) return NULL;
    unsigned char* key = (unsigned char*)malloc(len * sizeof(unsigned char));
    if (key == NULL) return NULL;
    for (int i = 0; i < len; i++) {
        key[i] = (unsigned char)(rand() % 256);
    }
    return key;
}

/**
 * @brief 使用一次性密码本加密消息。
 */
unsigned char* encrypt(unsigned char* plain_text, int len, unsigned char* key) {
    if (plain_text == NULL || key == NULL || len <= 0) return NULL;
    unsigned char* cipher_text = (unsigned char*)malloc(len * sizeof(unsigned char));
    if (cipher_text == NULL) return NULL;
    for (int i = 0; i < len; i++) {
        cipher_text[i] = plain_text[i] ^ key[i];
    }
    return cipher_text;
}

/**
 * @brief 使用一次性密码本解密消息。
 */
unsigned char* decrypt(unsigned char* cipher_text, int len, unsigned char* key) {
    // 解密与加密操作相同
    return encrypt(cipher_text, len, key);
}

// --- 文件 I/O 帮助函数 ---

/**
 * @brief 将数据缓冲区写入文件。
 * @return 0 表示成功, -1 表示失败。
 */
int write_file(const char* filename, unsigned char* data, int len) {
    FILE* fp = fopen(filename, "wb"); // 'wb' = Write Binary
    if (fp == NULL) {
        perror("Error opening file for writing");
        return -1;
    }
    size_t written = fwrite(data, sizeof(unsigned char), len, fp);
    fclose(fp);
    if (written != (size_t)len) {
        fprintf(stderr, "Error: Failed to write all bytes to %s\n", filename);
        return -1;
    }
    return 0;
}

/**
 * @brief 从文件读取所有数据到新分配的缓冲区。
 * @param out_len 指向一个整数，用于存储读取的字节数。
 * @return 指向数据缓冲区的指针，失败时返回 NULL。
 */
unsigned char* read_file(const char* filename, int* out_len) {
    FILE* fp = fopen(filename, "rb"); // 'rb' = Read Binary
    if (fp == NULL) {
        perror("Error opening file for reading");
        return NULL;
    }

    // 确定文件大小
    fseek(fp, 0, SEEK_END);
    long file_size = ftell(fp);
    fseek(fp, 0, SEEK_SET); // 重置到文件开头

    if (file_size <= 0) {
        fclose(fp);
        if (file_size == 0) {
             fprintf(stderr, "Warning: File %s is empty.\n", filename);
             *out_len = 0;
             // 返回一个大小为 0 的有效（但无用）指针或 NULL
             // 为简单起见，我们返回 NULL
             return NULL;
        }
        fprintf(stderr, "Error determining file size for %s\n", filename);
        return NULL;
    }

    // 分配内存
    unsigned char* buffer = (unsigned char*)malloc(file_size);
    if (buffer == NULL) {
        fprintf(stderr, "Error: Failed to allocate memory for file content.\n");
        fclose(fp);
        return NULL;
    }

    // 读取文件内容
    size_t read_bytes = fread(buffer, 1, file_size, fp);
    fclose(fp);

    if (read_bytes != (size_t)file_size) {
        fprintf(stderr, "Error: Failed to read all bytes from %s\n", filename);
        free(buffer);
        return NULL;
    }

    *out_len = (int)file_size;
    return buffer;
}

// --- 工具函数 ---

void print_usage(const char* prog_name) {
    fprintf(stderr, "Usage:\n");
    fprintf(stderr, "  1. Generate key: %s -generate_key <key_file> <length>\n", prog_name);
    fprintf(stderr, "  2. Encrypt file: %s -encrypt <key_file> <input_file> <output_file>\n", prog_name);
    fprintf(stderr, "  3. Decrypt file: %s -decrypt <key_file> <input_file> <output_file>\n", prog_name);
}

// --- 主函数 ---

int main(int argc, char* argv[]) {
    // 关键：为 rand() 播种。
    // 注意：rand() 不是密码学安全的！
    srand(time(NULL));

    if (argc < 2) {
        fprintf(stderr, "Error: No mode specified.\n");
        print_usage(argv[0]);
        return 1;
    }

    const char* mode = argv[1];

    // 模式 1: 生成密钥
    // otp_tool.exe -generate_key key.txt 20
    if (strcmp(mode, "-generate_key") == 0) {
        if (argc != 4) {
            fprintf(stderr, "Error: Invalid arguments for -generate_key\n");
            print_usage(argv[0]);
            return 1;
        }
        const char* key_file = argv[2];
        int len = atoi(argv[3]); // 将字符串转换为整数

        if (len <= 0) {
            fprintf(stderr, "Error: Invalid key length '%s'. Must be > 0.\n", argv[3]);
            return 1;
        }

        unsigned char* key = generate_key(len);
        if (key == NULL) {
            fprintf(stderr, "Error: Key generation failed (length %d).\n", len);
            return 1;
        }

        if (write_file(key_file, key, len) != 0) {
            fprintf(stderr, "Error: Failed to write key to %s\n", key_file);
            free(key);
            return 1;
        }

        printf("Successfully generated key of length %d to %s\n", len, key_file);
        free(key);
    }
    // 模式 2: 加密
    // otp_tool.exe -encrypt key.txt plaintext.txt ciphertext.txt
    else if (strcmp(mode, "-encrypt") == 0) {
        if (argc != 5) {
            fprintf(stderr, "Error: Invalid arguments for -encrypt\n");
            print_usage(argv[0]);
            return 1;
        }
        const char* key_file = argv[2];
        const char* input_file = argv[3];
        const char* output_file = argv[4];

        int key_len = 0;
        int text_len = 0;
        unsigned char* key_data = read_file(key_file, &key_len);
        unsigned char* plain_data = read_file(input_file, &text_len);

        if (key_data == NULL || plain_data == NULL) {
            fprintf(stderr, "Error: Failed to read key or input file.\n");
            free(key_data); // free(NULL) 是安全的
            free(plain_data);
            return 1;
        }

        // OTP 的关键安全要求
        if (key_len < text_len) {
            fprintf(stderr, "Error: Key length (%d) is shorter than plaintext length (%d).\n", key_len, text_len);
            fprintf(stderr, "One-time pad requires key_len >= text_len.\n");
            free(key_data);
            free(plain_data);
            return 1;
        }

        unsigned char* cipher_data = encrypt(plain_data, text_len, key_data);
        if (cipher_data == NULL) {
            fprintf(stderr, "Error: Encryption failed.\n");
            free(key_data);
            free(plain_data);
            return 1;
        }

        if (write_file(output_file, cipher_data, text_len) != 0) {
            fprintf(stderr, "Error: Failed to write ciphertext to %s\n", output_file);
        } else {
            printf("Successfully encrypted %s to %s (using %d bytes of key).\n", input_file, output_file, text_len);
        }

        free(key_data);
        free(plain_data);
        free(cipher_data);
    }
    // 模式 3: 解密
    // otp_tool.exe -decrypt key.txt ciphertext.txt decrypted.txt
    else if (strcmp(mode, "-decrypt") == 0) {
        if (argc != 5) {
            fprintf(stderr, "Error: Invalid arguments for -decrypt\n");
            print_usage(argv[0]);
            return 1;
        }
        const char* key_file = argv[2];
        const char* input_file = argv[3]; // 密文
        const char* output_file = argv[4]; // 解密后的明文

        int key_len = 0;
        int cipher_len = 0;
        unsigned char* key_data = read_file(key_file, &key_len);
        unsigned char* cipher_data = read_file(input_file, &cipher_len);

        if (key_data == NULL || cipher_data == NULL) {
            fprintf(stderr, "Error: Failed to read key or input file.\n");
            free(key_data);
            free(cipher_data);
            return 1;
        }

        if (key_len < cipher_len) {
            fprintf(stderr, "Error: Key length (%d) is shorter than ciphertext length (%d).\n", key_len, cipher_len);
            free(key_data);
            free(cipher_data);
            return 1;
        }

        unsigned char* plain_data = decrypt(cipher_data, cipher_len, key_data);
        if (plain_data == NULL) {
            fprintf(stderr, "Error: Decryption failed.\n");
            free(key_data);
            free(cipher_data);
            return 1;
        }

        if (write_file(output_file, plain_data, cipher_len) != 0) {
            fprintf(stderr, "Error: Failed to write decrypted text to %s\n", output_file);
        } else {
            printf("Successfully decrypted %s to %s (using %d bytes of key).\n", input_file, output_file, cipher_len);
        }

        free(key_data);
        free(cipher_data);
        free(plain_data);
    }
    // 未知模式
    else {
        fprintf(stderr, "Error: Unknown mode '%s'\n", mode);
        print_usage(argv[0]);
        return 1;
    }

    return 0; // 成功
}
