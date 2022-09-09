#pragma once

typedef const char * ERROR;

#define ERROR_MEMORY_UNDERFLOW ((ERROR)"Stack underflow detected (ERROR_MEMORY_UNDERFLOW)")
#define CODE_MEMORY_UNDERFLOW 4

#define ERROR_MEMORY_OVERFLOW ((ERROR)"Stack overflow detected (ERROR_MEMORY_OVERFLOW)")
#define CODE_MEMORY_OVERFLOW 3

#define ERROR_MEMORY_ADDRESS_INVALID ((ERROR)"Invalid memory access detected (ERROR_MEMORY_ADDRESS_INVALID)")
#define CODE_MEMORY_ADDRESS_INVALID 5

#define ERROR_OPCODE_INVALID ((ERROR)"Invalid opcode detected (ERROR_OPCODE_INVALID)")
#define CODE_OPCODE_INVALID 2

#define ERROR_RESOURCE_NOT_AVAILABLE ((ERROR)"Unable to secure resource (ERROR_RESOURCE_NOT_AVAILABLE)")
#define CODE_RESOURCE_NOT_AVAILABLE 1

#define ERROR_ROM_NOT_AVAILABLE ((ERROR)"Unable to open ROM (ERROR_ROM_NOT_AVAILABLE)")
#define CODE_ROM_NOT_AVAILABLE 6

#define ERROR_ROM_NOT_VALID ((ERROR)"ROM not a valid CHIP8 rom (ERROR_ROM_NOT_VALD)")
#define CODE_ROM_NOT_VALID 7

#define ERROR_SCREEN_NOT_AVAILABLE ((ERROR)"Unable to secure screen (ERROR_SCREEN_NOT_AVAILABLE)")
#define CODE_SCREEN_NOT_AVAILABLE 8

#define ERROR_INVALID_OPCODE ((ERROR)"Corrupted memory encountered (ERROR_INVALID_OPCODE)")
#define CODE_INVALID_OPCODE 9

void fatal_error(ERROR, unsigned int);
void exit_prog(int);
