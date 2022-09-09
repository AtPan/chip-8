#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "error.h"
#include "processor.h"
#include "resources.h"

void processor_set_register(struct cpu_t *cpu, unsigned char reg, unsigned char val) {
    *((unsigned char *)cpu + reg) = (val & 0xff);
}

struct cpu_t *processor_instantiate() {
    struct cpu_t *cpu = malloc(sizeof(struct cpu_t));

    if(cpu != NULL) {
        memset(cpu, 0, sizeof(struct cpu_t));
        cpu->sp = OFFSET_STACK + MAX_STACK;
        cpu->pc = OFFSET_ROM;
    }

    save_resource(RESOURCE_CPU, cpu);
    return cpu;
}

void processor_destroy(struct cpu_t *cpu) {
    if(cpu != NULL) {
        free(cpu);
        save_resource(RESOURCE_CPU, NULL);
    }
}

/*
void push_word(struct cpu_t *cpu, unsigned short val) {
    if(cpu->sp == MIN_STACK) {
        fatal_error(ERROR_MEMORY_OVERFLOW, CODE_MEMORY_OVERFLOW);
    }

    cpu->sp -= 2;
    memory_set_word(cpu->sp, val);
}

unsigned short pop_word(struct cpu_t *cpu) {
    if(cpu->sp == MAX_STACK) {
        fatal_error(ERROR_MEMORY_UNDERFLOW, CODE_MEMORY_UNDERFLOW);
    }

    unsigned short word = (unsigned short)memory_get_word(cpu->sp);
    cpu->sp += 2;
    return word;
}

void push_byte(struct cpu_t *cpu, unsigned char val) {
    if(cpu->sp == MIN_STACK) {
        fatal_error(ERROR_MEMORY_OVERFLOW, CODE_MEMORY_OVERFLOW);
    }

    cpu->sp--;
    memory_set_byte(cpu->sp, val);
}

unsigned char pop_byte(struct cpu_t *cpu) {
    if(cpu->sp == MAX_STACK) {
        fatal_error(ERROR_MEMORY_UNDERFLOW, CODE_MEMORY_UNDERFLOW);
    }

    unsigned char byte = (unsigned char)memory_get_byte(cpu->sp++);
    return byte;
}
*/

void processor_display(struct cpu_t *cpu) {
    printf("Processor:\n");
    for(int i = 0; i < 8; i += 1) {
        printf("V%c - 0x%02x\t", (i > 9) ? ('A' + i - 10) : ('0' + i), *((unsigned char *)cpu + i));
        printf("V%c - 0x%02x\n", (i + 8 > 9) ? ('A' + i - 2) : ('0' + i + 8), *((unsigned char *)cpu + i + 8));
    }
    printf("Delay - 0x%02x\tSound - 0x%02x\n", cpu->delay, cpu->sound);
    printf("I - 0x%02x\tSP - 0x%02x\tPC - 0x%02x\n\n", cpu->I, cpu->sp, cpu->pc);
}
