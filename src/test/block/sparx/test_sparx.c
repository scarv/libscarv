
#include <stdio.h>
#include <stdint.h>

#include "scarv/block/sparx/sparx.h"

#include "util.h"

void test_sparx_dump( char* id, uint8_t* x, int l_x ) {
  printf( "%s = binascii.a2b_hex( '", id ); test_dump_seq( x, l_x, DUMP_LSB ); printf( "' )\n" );
}


void test_sparx_64_128( int trials, int l_min, int l_max ) {
    
    test_id( "test_sparx", "sparx_64_128", 1, trials );

    uint16_t key[]          = {0x0011, 0x2233, 0x4455, 0x6677,
                               0x8899, 0xaabb, 0xccdd, 0xeeff};
    uint16_t plaintext[]    = {0x0123, 0x4567, 0x89ab, 0xcdef};
    uint16_t ciphertext[]   = {0x2bbe, 0xf152, 0x01f5, 0x5f98};

    uint16_t ks [17][6]     = {{0}};

    test_sparx_dump("m0", (uint8_t*)plaintext, 8);
    test_sparx_dump("c0", (uint8_t*)ciphertext, 8);

    printf("# Key Schedule:\n");
    MEASURE(
        sparx_64_128_key_schedule(ks, key);
    );

    printf("# Key Encrypt:\n");
    MEASURE (
        sparx_64_128_encrypt(plaintext, ks);
    );
    
    test_sparx_dump("c1", (uint8_t*)plaintext, 8);
    
    printf("# Key Decrypt:\n");
    MEASURE (
        sparx_64_128_decrypt(ciphertext, ks);
    );
    
    test_sparx_dump("m1", (uint8_t*)ciphertext, 8);

    printf("if c0 != c1:\n");
    printf("    print('64_128 Encryption Error:')\n");
    printf("    print('c   = %%s' %% (binascii.b2a_hex(c0)))\n");
    printf("    print('   != %%s' %% (binascii.b2a_hex(c1)))\n");
    printf("    sys.exit(1)\n");
    printf("if m0 != m1:\n");
    printf("    print('64_128 Decryption Error:')\n");
    printf("    print('m   = %%s' %% (binascii.b2a_hex(m0)))\n");
    printf("    print('   != %%s' %% (binascii.b2a_hex(m1)))\n");
    printf("    sys.exit(1)\n");
}


void test_sparx_128_128( int trials, int l_min, int l_max ) {
    
    test_id( "test_sparx", "sparx_128_128", 1, trials );

    uint16_t key[]       = {0x0011, 0x2233, 0x4455, 0x6677,
                            0x8899, 0xaabb, 0xccdd, 0xeeff};

    uint16_t plaintext[] = {0x0123, 0x4567, 0x89ab, 0xcdef,
                            0xfedc, 0xba98, 0x7654, 0x3210};
    
    uint16_t ciphertext[]= {0x1cee, 0x7540, 0x7dbf, 0x23d8,
                            0xe0ee, 0x1597, 0xf428, 0x52d8};

    uint16_t ks [33][8]     = {{0}};

    test_sparx_dump("m0", (uint8_t*)plaintext, 8);
    test_sparx_dump("c0", (uint8_t*)ciphertext, 8);

    MEASURE(
        sparx_128_128_key_schedule(ks, key);
    );

    MEASURE (
        sparx_128_128_encrypt(plaintext, ks);
    );
    
    test_sparx_dump("c1", (uint8_t*)plaintext, 8);
    
    MEASURE (
        sparx_128_128_decrypt(ciphertext, ks);
    );
    
    test_sparx_dump("m1", (uint8_t*)ciphertext, 8);
    
    printf("if c0 != c1:\n");
    printf("    print('128_128 Encryption Error:')\n");
    printf("    print('c   = %%s' %% (binascii.b2a_hex(c0)))\n");
    printf("    print('   != %%s' %% (binascii.b2a_hex(c1)))\n");
    printf("    sys.exit(1)\n");
    printf("if m0 != m1:\n");
    printf("    print('128_128 Decryption Error:')\n");
    printf("    print('m   = %%s' %% (binascii.b2a_hex(m0)))\n");
    printf("    print('   != %%s' %% (binascii.b2a_hex(m1)))\n");
    printf("    sys.exit(1)\n");
}


void test_sparx_128_256( int trials, int l_min, int l_max ) {
    
    test_id( "test_sparx", "sparx_128_256", 1, trials );

    uint16_t key[]        = {0x0011, 0x2233, 0x4455, 0x6677,
                             0x8899, 0xaabb, 0xccdd, 0xeeff,
                             0xffee, 0xddcc, 0xbbaa, 0x9988,
                             0x7766, 0x5544, 0x3322, 0x1100};
    
    uint16_t plaintext[]  = {0x0123, 0x4567, 0x89ab, 0xcdef,
                             0xfedc, 0xba98, 0x7654, 0x3210};

    uint16_t ciphertext[] = {0x3328, 0xe637, 0x14c7, 0x6ce6,
                             0x32d1, 0x5a54, 0xe4b0, 0xc820};

    uint16_t ks [41][8]     = {{0}};

    test_sparx_dump("m0", (uint8_t*)plaintext, 8);
    test_sparx_dump("c0", (uint8_t*)ciphertext, 8);

    MEASURE(
        sparx_128_256_key_schedule(ks, key);
    );

    MEASURE (
        sparx_128_256_encrypt(plaintext, ks);
    );
    
    test_sparx_dump("c1", (uint8_t*)plaintext, 8);
    
    MEASURE (
        sparx_128_256_decrypt(ciphertext, ks);
    );
    
    test_sparx_dump("m1", (uint8_t*)ciphertext, 8);
   
    printf("if c0 != c1:\n");
    printf("    print('128_256 Encryption Error:')\n");
    printf("    print('c   = %%s' %% (binascii.b2a_hex(c0)))\n");
    printf("    print('   != %%s' %% (binascii.b2a_hex(c1)))\n");
    printf("    sys.exit(1)\n");
    printf("if m0 != m1:\n");
    printf("    print('128_256 Decryption Error:')\n");
    printf("    print('m   = %%s' %% (binascii.b2a_hex(m0)))\n");
    printf("    print('   != %%s' %% (binascii.b2a_hex(m1)))\n");
    printf("    sys.exit(1)\n");
}


int main( int argc, char* argv[] ) {
  test_init( argc, argv, "sys, binascii" );

  test_sparx_64_128( opt_trials, opt_data_min, opt_data_max );
  test_sparx_128_128( opt_trials, opt_data_min, opt_data_max );
  test_sparx_128_256( opt_trials, opt_data_min, opt_data_max );

  test_fini();

  return 0;
}
