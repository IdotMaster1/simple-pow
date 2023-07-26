#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

void sha1_hash(const char *input, char output[SHA_DIGEST_LENGTH * 2 + 1]) {
    unsigned char hash[SHA_DIGEST_LENGTH];
    SHA1((unsigned char*)input, strlen(input), hash);

    // phrl42 improvment (phrl42.ydns.eu)
    int arr_size = SHA_DIGEST_LENGTH * 2 + 1;
    for (int i = 0; i < arr_size; i++) {
        output[i] = 0;
    }

    // Convert the binary hash to a human-readable hex string
    for (int i = 0; i < SHA_DIGEST_LENGTH; i++) {
        sprintf(&output[i * 2], "%02x", hash[i]);
    }
    output[SHA_DIGEST_LENGTH * 2] = '\0'; // Null-terminate the string
}

int main() {
    const char *beforehash = "HeyImASimplePOWAlgo";
    const char *suffix = "!";
    // It's not "const int" because it will change, it is not "constant"
    int nonce = 0;

    // Start the hashing
    char sha1_output[SHA_DIGEST_LENGTH * 2 + 1];
    printf("Hashing...\n");
    sha1_hash(beforehash, sha1_output);
    printf("The SHA1 of '%s' is '%s'\n", beforehash, sha1_output);

    // loop
    while(1){
        // Add 1 to the nonce
        nonce++;
        // buffers
        char nonce_str[20];
        char target[5];
        int nonce_len = snprintf(nonce_str, sizeof(nonce_str), "%d", nonce);

        size_t beforehash_len = strlen(beforehash);
        size_t suffix_len = strlen(suffix);
        size_t total_length = beforehash_len + suffix_len + nonce_len;

        char *pow = (char *)malloc(total_length + 1);

        snprintf(pow, total_length + 1, "%s%s%s", beforehash, suffix, nonce_str);
        sha1_hash(pow, sha1_output);
        printf("Full pow: '%s' SHA1: '%s'\n", pow, sha1_output);

        strncpy(target, sha1_output, 4);
        target[4] = '\0';

        printf("target: %s\n", target);

        if (strcmp(target, "0000") == 0) {
            printf("Found nonce!\n");
            free(pow);
            break;
        }
        free(pow);
    }
    return 0;
}