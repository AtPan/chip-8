#pragma once

#include "memory.h"

struct cpu_t {
    unsigned char v0; unsigned char v1;
    unsigned char v2; unsigned char v3;
    unsigned char v4; unsigned char v5;
    unsigned char v6; unsigned char v7;
    unsigned char v8; unsigned char v9;
    unsigned char va; unsigned char vb;
    unsigned char vc; unsigned char vd;
    unsigned char ve; unsigned char vf;

    unsigned char delay;
    unsigned char sound;
    unsigned short I;
    unsigned short sp;
    unsigned short pc;
};

//#define processor_set_register(cpu, reg, val) *((unsigned char *)(cpu) + (reg)) = (unsigned char)(0xff & (val))
#define processor_get_register(cpu, reg) *((unsigned char *)(cpu) + (reg))
void processor_set_register(struct cpu_t *, unsigned char, unsigned char);

#define V0 0
#define V1 1
#define V2 2
#define V3 3
#define V4 4
#define V5 5
#define V6 6
#define V7 7
#define V8 8
#define V9 9
#define VA 10
#define VB 11
#define VC 12
#define VD 13
#define VE 14
#define VF 15
#define VDELAY 16
#define VSOUND 17

struct cpu_t *processor_instantiate(void);
void processor_destroy(struct cpu_t *);

void processor_display(struct cpu_t *);
