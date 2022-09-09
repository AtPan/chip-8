#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "fonts.h"
#include "screen.h"
#include "memory.h"
#include "opcode.h"
#include "processor.h"

int main(void);

int main() {
    struct system_t sys;

    printf("Test 1: ");
    opcode_instantiate();
    sys.cpu = processor_instantiate();
    sys.mem = memory_instantiate(SIZE_MEMORY);
    screen_instantiate();
    printf("Passed\n");

    printf("Test 2: ");
    processor_display(sys.cpu);
    printf("Passed\n");

    printf("Test 3: ");
    sys.opcode = 0x2abc;
    opcode_execute(&sys);
    assert(sys.cpu->pc == 0xabc);
    assert(sys.cpu->sp == MAX_STACK - 2);
    printf("Passed\n");

    printf("Test 4: ");
    sys.opcode = 0x00ee;
    opcode_execute(&sys);
    assert(sys.cpu->pc == OFFSET_ROM + 2);
    assert(sys.cpu->sp == MAX_STACK);
    printf("Passed\n");

    printf("Test 5: ");
    unsigned short pc = sys.cpu->pc;
    processor_set_register(sys.cpu, 0, 0x42);
    sys.opcode = 0x3042;
    opcode_execute(&sys);
    assert(processor_get_register(sys.cpu, 0) == 0x42);
    assert(sys.cpu->pc == pc + 2);
    printf("Passed\n");

    printf("Test 6: ");
    processor_set_register(sys.cpu, 0, 1);
    processor_set_register(sys.cpu, 1, 0xff);
    sys.opcode = 0x8015;
    opcode_execute(&sys);
    assert(sys.cpu->vf == 0);
    printf("Passed\n");

    printf("Test 7: ");
    sys.cpu->v0 = 0xaa;
    sys.cpu->v1 = 0xbb;
    sys.cpu->v2 = 0xcc;
    sys.cpu->v3 = 0xdd;
    sys.cpu->I = 0;
    sys.opcode = 0xf355;
    opcode_execute(&sys);
    assert(sys.cpu->I == 4);
    assert(sys.mem[0] == 0xaa);
    assert(sys.mem[1] == 0xbb);
    assert(sys.mem[2] == 0xcc);
    assert(sys.mem[3] == 0xdd);
    printf("Passed\n");

    printf("Test 8: ");
    sys.cpu->v0 = 0;
    sys.cpu->v1 = 0;
    sys.cpu->v2 = 0;
    sys.cpu->v3 = 0;
    sys.cpu->I = 0;
    sys.opcode = 0xf365;
    opcode_execute(&sys);
    assert(sys.cpu->I == 4);
    assert(sys.cpu->v0 == 0xaa);
    assert(sys.cpu->v1 == 0xbb);
    assert(sys.cpu->v2 == 0xcc);
    assert(sys.cpu->v3 == 0xdd);
    printf("Passed\n");

    printf("Test 9: ");
    sys.cpu->v0 = 231;
    sys.opcode = 0xf033;
    opcode_execute(&sys);
    assert(sys.mem[sys.cpu->I] == 2);
    assert(sys.mem[sys.cpu->I + 1] == 3);
    assert(sys.mem[sys.cpu->I + 2] == 1);
    printf("Passed\n");

    for(int i = 0; i < LEN_FONT; i++) {
        printf("\rTest 10: mem[%d] =?= font[%d]", OFFSET_FONT + i, i);
        fflush(stdout);
        assert(sys.mem[OFFSET_FONT + i] == font[i]);
    }
    printf("\rTest 10: Passed               \n");


    screen_clear();

    printf("Test 11: ");
    sys.cpu->v0 = 7;
    sys.opcode = 0xf029;
    opcode_execute(&sys);
    assert(sys.cpu->I == OFFSET_FONT + 35);
    printf("Passed\n");

    printf("Test 12...\n");
    sys.opcode = 0xd005;
    opcode_execute(&sys);

    printf("Test 13: ");
    sys.cpu->v1 = 0x0f;
    sys.opcode = 0x8116;
    opcode_execute(&sys);
    assert(sys.cpu->v1 == (0x0f >> 1));
    assert(sys.cpu->vf == 1);
    printf("Passed\n");

    printf("Test 14: ");
    sys.cpu->v1 = 0xe0;
    sys.opcode = 0x811e;
    opcode_execute(&sys);
    printf("%02x\n", sys.cpu->v1);
    assert(sys.cpu->v1 == (unsigned char)(0xe0 << 1));
    assert(sys.cpu->vf == 1);
    printf("Passed\n");

    int run = 1;
    SDL_Event e;
    while(run) {
        while(SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                run = 0;
                break;
            }
        }
    }

    processor_destroy(sys.cpu);
    memory_destroy(sys.mem);
    screen_destroy();
    return 0;
}
