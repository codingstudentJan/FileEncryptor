#include "Encryptor.h"
#include <fstream>
#include <cstdio>
#define KEY_LEN  crypto_secretstream_xchacha20poly1305_KEYBYTES
#define CHUNK_SIZE 4096

void Encryptor::encryptFile(std::string pathToFile, const char* password = "default") {
    if (sodium_init() < 0) throw std::runtime_error("sodium_init failed");
    unsigned char key[KEY_LEN];
    deriveKeyFromPassword(password, key);
    encrypt(pathToFile,key);
    char hex[KEY_LEN * 2 + 1];
    sodium_bin2hex(hex, sizeof hex, key, KEY_LEN);
    std::cout << "Derived key (hex): " << hex << "\n";
    std::cout << "Encrypted File";
}

void Encryptor::encrypt(std::string pathToFile, unsigned char* key) {
    unsigned char  buf_in[CHUNK_SIZE];
    unsigned char  buf_out[CHUNK_SIZE + crypto_secretstream_xchacha20poly1305_ABYTES];
    unsigned char  header[crypto_secretstream_xchacha20poly1305_HEADERBYTES];
    crypto_secretstream_xchacha20poly1305_state st;
    FILE* fp_t, * fp_s;
    unsigned long long out_len;
    size_t         rlen;
    int            eof;
    unsigned char  tag;
    std::string target_file = pathToFile + "Enc";
    fp_s = fopen(pathToFile.c_str(), "rb");
    if (!fp_s) { perror("fopen source"); return; }

    fp_t = fopen(target_file.c_str(), "wb");
    if (!fp_t) { perror("fopen target"); fclose(fp_s); return; }

    if (crypto_secretstream_xchacha20poly1305_init_push(&st, header, key) != 0) {
        fclose(fp_t); fclose(fp_s); return;
    }
    fwrite(header, 1, sizeof header, fp_t);
    do {
        rlen = fread(buf_in, 1, sizeof buf_in, fp_s);
        eof = feof(fp_s);
        tag = eof ? crypto_secretstream_xchacha20poly1305_TAG_FINAL : 0;
        crypto_secretstream_xchacha20poly1305_push(&st, buf_out, &out_len, buf_in, rlen,
            NULL, 0, tag);
        fwrite(buf_out, 1, (size_t)out_len, fp_t);
    } while (!eof);
    fclose(fp_t);
    fclose(fp_s);
}

void Encryptor::deriveKeyFromPassword(const char* password, unsigned char* key) {
    unsigned char salt[crypto_pwhash_SALTBYTES];
    
    randombytes_buf(salt, sizeof salt);
    if (crypto_pwhash
    (key, KEY_LEN, password, strlen(password), salt,
        crypto_pwhash_OPSLIMIT_MODERATE, crypto_pwhash_MEMLIMIT_MODERATE,
        crypto_pwhash_ALG_DEFAULT) != 0) {
        /* out of memory */
    }

}
