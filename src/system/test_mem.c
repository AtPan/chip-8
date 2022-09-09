#include <assert.h>
#include <stdio.h>
#include "memory.h"
#include "processor.h"

int main(int, char**);

int main(int argc, char *argv[]) {
    if(argc != 2) {
        return 1;
    }

    processor_instantiate();
    memory_instantiate();

    unsigned short short1 = 1234;
    unsigned short short2 = 1893;
    unsigned short short3 = 14863;

    unsigned char byte1 = 18;
    unsigned char byte2 = 146;
    unsigned char byte3 = 215;


    unsigned short even_addr = 0x100;
    unsigned short odd_addr = 0x241;


    printf("Byte Tests ----------\n");
    memory_set_byte(even_addr, byte1);
    memory_set_byte(even_addr + 1, byte2);
    memory_set_byte(even_addr + 2, byte3);

    printf("Test 1: ");
    assert(memory_get_byte(even_addr) == byte1);
    printf("Passed\n");

    printf("Test 2: ");
    assert(memory_get_byte(even_addr + 1) == byte2);
    printf("Passed\n");

    printf("Test 3: ");
    assert(memory_get_byte(even_addr + 2) == byte3);
    printf("Passed\n\n\n");



    printf("Word Tests ----------\n");
    memory_set_word(odd_addr, short1);
    memory_set_word(odd_addr + 2, short2);
    memory_set_word(odd_addr + 4, short3);

    printf("Test 1: ");
    assert(memory_get_word(odd_addr) == short1);
    printf("Passed\n");

    printf("Test 2: ");
    assert(memory_get_word(odd_addr + 2) == short2);
    printf("Passed\n");

    printf("Test 3: ");
    assert(memory_get_word(odd_addr + 4) == short3);
    printf("Passed\n\n\n");



    printf("Stack Tests ----------\n");
    push_word(short1);
    push_byte(byte1);
    push_word(short2);
    push_byte(byte2);
    push_word(short3);
    push_byte(byte3);

    printf("Test 1: ");
    assert(pop_byte() == byte3);
    printf("Passed\n");

    printf("Test 2: ");
    assert(pop_word() == short3);
    printf("Passed\n");

    printf("Test 3: ");
    assert(pop_byte() == byte2);
    printf("Passed\n");

    printf("Test 4: ");
    assert(pop_word() == short2);
    printf("Passed\n");

    printf("Test 5: ");
    assert(pop_byte() == byte1);
    printf("Passed\n");

    printf("Test 6: ");
    assert(pop_word() == short1);
    printf("Passed\n\n\n");

    memory_destroy();

    return 0;
}
