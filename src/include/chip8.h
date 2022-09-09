#ifndef __CHIP_H
#define __CHIP_H

#include "memory.h"

#define read_opcode(sys) do { \
    (sys)->opcode = memory_get_word((sys)->mem, (sys)->cpu->pc); \
    (sys)->cpu->pc += 2; \
} while(0)

struct system_t {
    struct cpu_t *cpu;
    unsigned char *mem;
    unsigned short opcode;
};

#include "error.h"
#include "fonts.h"
#include "opcode.h"
#include "processor.h"
#include "resources.h"
#include "screen.h"

#endif
