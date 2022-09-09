#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fonts.h"
#include "error.h"
#include "memory.h"
#include "resources.h"

void load_rom(unsigned char * restrict mem, const char *rom_path) {
    FILE *rom = fopen(rom_path, "rb");
    if(rom == NULL) {
        fatal_error(ERROR_ROM_NOT_AVAILABLE, CODE_ROM_NOT_AVAILABLE);
    }

    fseek(rom, 0, SEEK_END);
    unsigned long romlen = ftell(rom);
    fseek(rom, 0, SEEK_SET);

    if(romlen >= SIZE_ROM) {
        fclose(rom);
        fatal_error(ERROR_ROM_NOT_VALID, CODE_ROM_NOT_VALID);
    }

    if(fread(&mem[OFFSET_ROM], romlen, 1, rom) != 1) {
        if(ferror(rom)) {
            perror(rom_path);
            exit(CODE_RESOURCE_NOT_AVAILABLE);
        }
        fatal_error(ERROR_RESOURCE_NOT_AVAILABLE, CODE_RESOURCE_NOT_AVAILABLE);
    }

    fclose(rom);
}

int memory_draw_sprite(unsigned char * restrict gfx, unsigned char x, unsigned char y, unsigned char n, unsigned char * restrict sprite) {
    int hit = 0;

    x &= 0x3f;
    y &= 0x1f;
    if(y + n > 31) {
        n = 32 - y;
    }

    if(x & 7) {
        for(unsigned char i = 0; i < n; i++) {
            if(gfx[((y + i) * 8) + (x >> 3)] & (sprite[i] >> (x & 7)) ||
                    gfx[((y + i) * 8) + (x >> 3) + 1] & (sprite[i] << (8 - (x & 7)))) hit = 1;
            gfx[((y + i) * 8) + (x >> 3)] ^= (sprite[i] >> (x & 7));

            if(x + 8 < 64) {
                gfx[((y + i) * 8) + (x >> 3) + 1] ^= (sprite[i] << (8 - (x & 7)));
            }
        }
    }
    else {
        for(unsigned char i = 0; i < n; i++) {
            if(gfx[((y + i) * 8) + (x >> 3)] & sprite[i]) hit = 1;
            gfx[((y + i) * 8) + (x >> 3)] ^= sprite[i];
        }
    }

    return hit;
}

unsigned char *memory_instantiate(unsigned long n) {
    unsigned char *mem;
    if((mem = malloc(n)) == NULL) {
        fprintf(stderr, ERROR_RESOURCE_NOT_AVAILABLE);
        exit(CODE_RESOURCE_NOT_AVAILABLE);
    }

    memcpy(mem + OFFSET_FONT, font, LEN_FONT);
    save_resource(RESOURCE_MEMORY, mem);
    return mem;
}

void memory_destroy(unsigned char *mem) {
    free(mem);
    save_resource(RESOURCE_MEMORY, NULL);
}
