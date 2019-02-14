
#include <stdio.h>
#include <stdint.h>

#include "scarv/prince/prince.h"

const uint32_t num_prince_vectors = 4;

//! Known I/O vectors for prince.
uint64_t prince_test_vectors[][4] = {
// plaintext       ,  k0              ,  k1              ,  cipher
{0x0000000000000000,0x0000000000000000,0x0000000000000000,0x818665aa0d02dfda},
{0xffffffffffffffff,0x0000000000000000,0x0000000000000000,0x604ae6ca03c20ada},
{0x0000000000000000,0xffffffffffffffff,0x0000000000000000,0x9fb51935fc3df524},
{0x0000000000000000,0x0000000000000000,0xffffffffffffffff,0x78a54cbe737bb7ef},
{0x0123456789abcdef,0x0000000000000000,0xfedcba9876543210,0xae25ad3ca8fa9ccf},
};


int main(int argc, char ** argv) {

    for(int i = 0; i < num_prince_vectors; i++) {

        uint64_t plaintext = prince_test_vectors[i][0];
        uint64_t k0        = prince_test_vectors[i][1];
        uint64_t k1        = prince_test_vectors[i][2];
        uint64_t ciphertext= prince_test_vectors[i][3];

        printf("# ----- Prince %d / %d --------\n", i,num_prince_vectors);

        printf("plaintext = 0x%016lX\n", plaintext );
        printf("k0        = 0x%016lX\n", k0        );
        printf("k1        = 0x%016lX\n", k1        );
        printf("ciphertext= 0x%016lX\n", ciphertext);
        
        uint64_t enc_result = prince_enc(plaintext, k0, k1);

        printf("enc_result= 0x%016lX\n", enc_result);
        if(enc_result != ciphertext) {
            printf("print('Encryption fail. Expect 0x%016lX, got 0x%016lX\n",
                ciphertext, enc_result);
        }
        
        uint64_t dec_result = prince_dec(ciphertext, k0, k1);

        printf("dec_result= 0x%016lX\n", dec_result);
        if(dec_result != plaintext) {
            printf("print('Decryption fail. Expect 0x%016lX, got 0x%016lX\n",
                plaintext, dec_result);
        }
    }

}
