
#include <stdio.h>
#include <stdint.h>

#include "scarv/sparx/sparx.h"

#include "test_util.h"


/* Test vectors */
/* ============ */
uint16_t sparx_64_128_key[] = {
    0x0011, 0x2233, 0x4455, 0x6677, 0x8899, 0xaabb, 0xccdd, 0xeeff};

uint16_t sparx_64_128_plaintext[] = {0x0123, 0x4567, 0x89ab, 0xcdef};
uint16_t sparx_64_128_ciphertext[] = {0x2bbe, 0xf152, 0x01f5, 0x5f98};


uint16_t sparx_128_128_key[] = {
    0x0011, 0x2233, 0x4455, 0x6677, 0x8899, 0xaabb, 0xccdd, 0xeeff};

uint16_t sparx_128_128_plaintext[] = {
    0x0123, 0x4567, 0x89ab, 0xcdef, 0xfedc, 0xba98, 0x7654, 0x3210};
uint16_t sparx_128_128_ciphertext[] = {
    0x1cee, 0x7540, 0x7dbf, 0x23d8, 0xe0ee, 0x1597, 0xf428, 0x52d8};


uint16_t sparx_128_256_key[] = {
    0x0011, 0x2233, 0x4455, 0x6677, 0x8899, 0xaabb, 0xccdd, 0xeeff,
    0xffee, 0xddcc, 0xbbaa, 0x9988, 0x7766, 0x5544, 0x3322, 0x1100};

uint16_t sparx_128_256_plaintext[] = {
    0x0123, 0x4567, 0x89ab, 0xcdef, 0xfedc, 0xba98, 0x7654, 0x3210};
uint16_t sparx_128_256_ciphertext[] = {
    0x3328, 0xe637, 0x14c7, 0x6ce6, 0x32d1, 0x5a54, 0xe4b0, 0xc820};


/* Helper functions */
/* ================ */

void initialize_test_vectors(uint16_t * x, uint16_t * master_key)
{
    uint8_t i;

    uint16_t *p_key;
    uint16_t *p_plaintext;


    if (SPARX_INSTANCE == SPARX_64_128)
    {
        printf("\n# === SPARX-64/128 ===\n");
        p_key = sparx_64_128_key;
        p_plaintext = sparx_64_128_plaintext;
    }

    if (SPARX_INSTANCE == SPARX_128_128)
    {
        printf("\n# === SPARX-128/128 ===\n");
        p_key = sparx_128_128_key;
        p_plaintext = sparx_128_128_plaintext;
    }

    if (SPARX_INSTANCE == SPARX_128_256)
    {
        printf("\n# === SPARX-128/256 ===\n");
        p_key = sparx_128_256_key;
        p_plaintext = sparx_128_256_plaintext;
    }


    /* Set test vectors */
    for (i=0 ; i<2*K_SIZE ; i++)
    {
        master_key[i] = p_key[i];
    }
    for (i=0 ; i<2*N_BRANCHES ; i++)
    {
        x[i] = p_plaintext[i];
    }


    printf("# steps=%d, rounds/steps=%d, block=32*%d\n\n",
           N_STEPS,
           ROUNDS_PER_STEPS,
           N_BRANCHES);
}


uint8_t check_test_vectors(uint16_t * x, uint8_t op)
{
    uint8_t i;
    uint8_t correct = 1;

    uint16_t *p_tv;
    uint16_t *p_plaintext;
    uint16_t *p_ciphertext;


    if (SPARX_INSTANCE == SPARX_64_128)
    {
        p_plaintext = sparx_64_128_plaintext;
        p_ciphertext = sparx_64_128_ciphertext;
    }

    if (SPARX_INSTANCE == SPARX_128_128)
    {
        p_plaintext = sparx_128_128_plaintext;
        p_ciphertext = sparx_128_128_ciphertext;
    }

    if (SPARX_INSTANCE == SPARX_128_256)
    {
        p_plaintext = sparx_128_256_plaintext;
        p_ciphertext = sparx_128_256_ciphertext;
    }

    if(0 == op)
    {
        p_tv = p_ciphertext;
    }
    else
    {
        p_tv = p_plaintext;
    }

    for (i=0 ; i<2*N_BRANCHES ; i++)
    {
        if (x[i] != p_tv[i])
        {
            correct = 0;
        }
    }

    correct ? printf("# \t OK!") : printf("# \t WRONG!");
    return !correct;
}



/* Main function */
/* ============= */

int main()
{
    uint16_t
        x[2*N_BRANCHES],
        master_key[2*K_SIZE],
        k[N_BRANCHES*N_STEPS+1][2*ROUNDS_PER_STEPS] = {{0}};
    uint8_t i, j, status = 0;


    initialize_test_vectors(x, master_key);


    printf("# master = ");
    for (i=0 ; i<2*K_SIZE ; i++)
    {
        printf("%04x ", master_key[i]);
    }

    uint32_t count_c = test_util_rdcycle();
    uint32_t count_i = test_util_rdinstret();

    sparx_key_schedule(k, master_key);
    
    count_c = test_util_rdcycle()  - count_c;
    count_i = test_util_rdinstret()- count_i;

    for (i=0 ; i<N_BRANCHES*N_STEPS+1 ; i++)
    {
        printf("\n# k^{%2d} = ", i);
        for (j=0 ; j<2*ROUNDS_PER_STEPS ; j++)
            printf("%04x ", k[i][j]);
    }

    printf("\n# Cycles: %d", count_c);
    printf("\n# Instrs: %d", count_i);


    printf("\n\n# plaintext  = ");
    for (i=0 ; i<2*N_BRANCHES ; i++)
    {
        printf("%04x ", x[i]);
    }

    count_c = test_util_rdcycle();
    count_i = test_util_rdinstret();

    sparx_encrypt(x, k);
    
    count_c = test_util_rdcycle()  - count_c;
    count_i = test_util_rdinstret()- count_i;

    printf("\n# ciphertext = ");
    for (i=0 ; i<2*N_BRANCHES ; i++)
    {
        printf("%04x ", x[i]);
    }
    status += check_test_vectors(x, 0);
    
    printf("\n# Cycles: %d", count_c);
    printf("\n# Instrs: %d", count_i);

    count_c = test_util_rdcycle();
    count_i = test_util_rdinstret();

    sparx_decrypt(x, k);
    
    count_c = test_util_rdcycle()  - count_c;
    count_i = test_util_rdinstret()- count_i;

    printf("\n# decryption = ");
    for (i=0 ; i<2*N_BRANCHES ; i++)
    {
        printf("%04x ", x[i]);
    }
    status += check_test_vectors(x, 1);
    
    printf("\n# Cycles: %d", count_c);
    printf("\n# Instrs: %d", count_i);


    printf("\n");
    
    return status;
}
