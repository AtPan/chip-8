#pragma once

unsigned char *memory_instantiate(unsigned long);
void memory_destroy(unsigned char *);
int memory_draw_sprite(unsigned char *, unsigned char, unsigned char, unsigned char, unsigned char *);

void load_rom(unsigned char *, const char *);

#define memory_get_byte(mem, addr) (mem)[(addr) & ~SIZE_MEMORY]
#define memory_get_word(mem, addr) (unsigned short)(((mem)[((addr) & ~SIZE_MEMORY) + 1]) + ((mem)[(addr) & ~SIZE_MEMORY] << 8))
#define memory_set_byte(mem, addr, val) ((mem)[(addr) & ~SIZE_MEMORY] = val)
#define memory_set_word(mem, addr, val) (mem)[(addr) & ~SIZE_MEMORY] = (val) >> 8; (mem)[((addr) & ~SIZE_MEMORY) + 1] = (val) & 0xff

/* Memory Constants */
#define SIZE_MEMORY 0x2000
/* ---------------- */

/* Graphics Constants */
#define SIZE_GRAPHICS 0x100
#define OFFSET_GRAPHICS 0x100
/* ------------------ */

/* Rom Constants */
#define SIZE_ROM 0x1e00
#define OFFSET_ROM 0x200
/* ------------- */

/* Font Constants */
#define OFFSET_FONT 0x20
/* -------------- */

/* Stack Constants */
#define OFFSET_STACK 0
#define MAX_STACK 0x20
#define MIN_STACK 0
/* --------------- */
