#include <SDL2/SDL.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_scancode.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "chip8.h"
#include "local_opcode.h"
#include "processor.h"
#include "screen.h"
#include "error.h"

static const unsigned char key_layout[] = {
    SDL_SCANCODE_X, SDL_SCANCODE_1, SDL_SCANCODE_2,
    SDL_SCANCODE_3, SDL_SCANCODE_Q, SDL_SCANCODE_W,
    SDL_SCANCODE_E, SDL_SCANCODE_A, SDL_SCANCODE_S,
    SDL_SCANCODE_D, SDL_SCANCODE_Z, SDL_SCANCODE_C,
    SDL_SCANCODE_4, SDL_SCANCODE_R, SDL_SCANCODE_F,
    SDL_SCANCODE_V
};

void handle_invalid(struct system_t * restrict sys) {
    fprintf(stderr, "0x%04x\n", sys->opcode);
    fatal_error(ERROR_INVALID_OPCODE, CODE_INVALID_OPCODE);
}

void handle_call(struct system_t * restrict sys) {
    sys->cpu->sp -= 2;
    memory_set_word(sys->mem, sys->cpu->sp, sys->cpu->pc);
    sys->cpu->pc = sys->opcode & 0xfff;
}

void handle_clear_screen(struct system_t * restrict sys) {
    memset(sys->mem + OFFSET_GRAPHICS, 0, SIZE_GRAPHICS);
    screen_clear();
}

void handle_return(struct system_t * restrict sys) {
    sys->cpu->pc = memory_get_word(sys->mem, sys->cpu->sp);
    sys->cpu->sp += 2;
}

void handle_jump(struct system_t * restrict sys) {
    sys->cpu->pc = sys->opcode & 0xfff;
}

void handle_skip_rei(struct system_t *sys) {
    if(processor_get_register(sys->cpu, (sys->opcode & 0x0f00) >> 8) == (sys->opcode & 0xff)) {
        sys->cpu->pc += 2;
    }
}

void handle_skip_rnei(struct system_t *sys) {
    if(processor_get_register(sys->cpu, (sys->opcode & 0x0f00) >> 8) != (sys->opcode & 0xff)) {
        sys->cpu->pc += 2;
    }
}

void handle_skip_rer(struct system_t *sys) {
    if(processor_get_register(sys->cpu, (sys->opcode & 0x0f00) >> 8) == processor_get_register(sys->cpu, (sys->opcode & 0x00f0) >> 4)) {
        sys->cpu->pc += 2;
    }
}

void handle_move_imm(struct system_t *sys) {
    processor_set_register(sys->cpu, (sys->opcode & 0x0f00) >> 8, sys->opcode & 0xff);
}

void handle_add_imm(struct system_t *sys) {
    processor_set_register(sys->cpu, (sys->opcode & 0x0f00) >> 8,
            processor_get_register(sys->cpu, (sys->opcode & 0x0f00) >> 8) + (sys->opcode & 0xff));
}

void handle_move_reg(struct system_t *sys) {
    processor_set_register(sys->cpu, (sys->opcode & 0x0f00) >> 8,
            processor_get_register(sys->cpu, (sys->opcode & 0x00f0) >> 4));
}

void handle_or_reg(struct system_t *sys) {
    processor_set_register(sys->cpu, (sys->opcode & 0x0f00) >> 8,
            processor_get_register(sys->cpu, (sys->opcode & 0x0f00) >> 8) | processor_get_register(sys->cpu, (sys->opcode & 0x00f0) >> 4));
    sys->cpu->vf = 0;
}

void handle_and_reg(struct system_t *sys) {
    processor_set_register(sys->cpu, (sys->opcode & 0x0f00) >> 8,
            processor_get_register(sys->cpu, (sys->opcode & 0x0f00) >> 8) & processor_get_register(sys->cpu, (sys->opcode & 0x00f0) >> 4));
    sys->cpu->vf = 0;
}

void handle_xor_reg(struct system_t *sys) {
    processor_set_register(sys->cpu, (sys->opcode & 0x0f00) >> 8,
            processor_get_register(sys->cpu, (sys->opcode & 0x0f00) >> 8) ^ processor_get_register(sys->cpu, (sys->opcode & 0x00f0) >> 4));
    sys->cpu->vf = 0;
}

void handle_add_reg(struct system_t *sys) {
    unsigned short sum = (processor_get_register(sys->cpu, (sys->opcode & 0x0f00) >> 8) + processor_get_register(sys-> cpu, (sys->opcode & 0x00f0) >> 4));
    processor_set_register(sys->cpu, (sys->opcode & 0x0f00) >> 8, (unsigned char)sum);
    processor_set_register(sys->cpu, VF, sum >> 8 ? 1 : 0);
}

void handle_sub_xyreg(struct system_t *sys) {
    unsigned char x = processor_get_register(sys->cpu, (sys->opcode & 0x0f00) >> 8);
    unsigned char y = processor_get_register(sys->cpu, (sys->opcode & 0x00f0) >> 4);
    unsigned short dif = x - y;
    processor_set_register(sys->cpu, (sys->opcode & 0x0f00) >> 8, (unsigned char)dif);
    processor_set_register(sys->cpu, VF, y > x ? 0 : 1);
}

void handle_shift_right(struct system_t *sys) {
    unsigned char yreg = processor_get_register(sys->cpu, (sys->opcode & 0x00f0) >> 4);
    processor_set_register(sys->cpu, (sys->opcode & 0x0f00) >> 8, yreg >> 1);
    processor_set_register(sys->cpu, VF, yreg & 1);
}

void handle_sub_yxreg(struct system_t *sys) {
    unsigned char x = processor_get_register(sys->cpu, (sys->opcode & 0x0f00) >> 8);
    unsigned char y = processor_get_register(sys->cpu, (sys->opcode & 0x00f0) >> 4);
    processor_set_register(sys->cpu, (sys->opcode & 0x0f00) >> 8, y - x);
    processor_set_register(sys->cpu, VF, x > y ? 0 : 1);
}

void handle_shift_left(struct system_t *sys) {
    unsigned char yreg = processor_get_register(sys->cpu, (sys->opcode & 0x00f0) >> 4);
    processor_set_register(sys->cpu, (sys->opcode & 0x0f00) >> 8, yreg << 1);
    processor_set_register(sys->cpu, VF, yreg >> 7);
}

void handle_skip_rner(struct system_t *sys) {
    if(processor_get_register(sys->cpu, (sys->opcode & 0x0f00) >> 8) != processor_get_register(sys->cpu, (sys->opcode & 0x00f0) >> 4)) {
        sys->cpu->pc += 2;
    }
}

void handle_save_iregimm(struct system_t *sys) {
    sys->cpu->I = sys->opcode & 0xfff;
}

void handle_jump_immoff(struct system_t *sys) {
    sys->cpu->pc = processor_get_register(sys->cpu, V0) + (sys->opcode & 0xfff);
}

void handle_generate_rand(struct system_t *sys) {
    processor_set_register(sys->cpu, (sys->opcode & 0x0f00) >> 8, (unsigned char)rand() & (sys->opcode & 0xfff));
}

void handle_draw_sprite(struct system_t *sys) {
    int hit = memory_draw_sprite(sys->mem + OFFSET_GRAPHICS,
            processor_get_register(sys->cpu, (sys->opcode & 0x0f00) >> 8),
            processor_get_register(sys->cpu, (sys->opcode & 0x00f0) >> 4),
            sys->opcode & 0x000f,
            sys->mem + sys->cpu->I);
    sys->cpu->vf = hit;
    screen_update(sys->mem + OFFSET_GRAPHICS);
}

void handle_skip_keyp(struct system_t *sys) {
    const uint8_t *state = SDL_GetKeyboardState(NULL);
    if(state[key_layout[processor_get_register(sys->cpu, (sys->opcode & 0x0f00) >> 8) & 0xf]]) {
        sys->cpu->pc += 2;
    }
}

void handle_skip_keyu(struct system_t *sys) {
    const uint8_t *state = SDL_GetKeyboardState(NULL);
    if(!state[key_layout[processor_get_register(sys->cpu, (sys->opcode & 0x0f00) >> 8) & 0xf]]) {
        sys->cpu->pc += 2;
    }
}

void handle_read_delay(struct system_t *sys) {
    processor_set_register(sys->cpu, (sys->opcode & 0x0f00) >> 8, processor_get_register(sys->cpu, VDELAY));
}

void handle_keypress_halt(struct system_t *sys) {
    unsigned char i;
    int hit = 1;

    SDL_Event event;
    while(hit) {
        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT) {
                exit_prog(0);
            }
            if(event.type == SDL_KEYDOWN) {
                for(i = 0; i < 16 && key_layout[i] != event.key.keysym.scancode; i++);
                if(i != 16) {
                    hit = 0;
                    break;
                }
            }
        }
    }

    processor_set_register(sys->cpu, (sys->opcode & 0x0f00) >> 8, i);
}

void handle_write_delay(struct system_t *sys) {
    processor_set_register(sys->cpu, VDELAY, processor_get_register(sys->cpu, (sys->opcode & 0x0f00) >> 8));
}

void handle_write_sound(struct system_t *sys) {
    processor_set_register(sys->cpu, VSOUND, processor_get_register(sys->cpu, (sys->opcode & 0x0f00) >> 8));
}

void handle_add_ireg(struct system_t *sys) {
    sys->cpu->I += processor_get_register(sys->cpu, (sys->opcode & 0x0f00) >> 8);
}

void handle_setfont_hex(struct system_t *sys) {
    sys->cpu->I = OFFSET_FONT + ((processor_get_register(sys->cpu, (sys->opcode & 0x0f00) >> 8) & 0xf) * 5);
}

void handle_htod(struct system_t *sys) {
    unsigned char val = processor_get_register(sys->cpu, (sys->opcode & 0x0f00) >> 8);
    sys->mem[sys->cpu->I] = val / 100;
    sys->mem[sys->cpu->I + 1] = (val / 10) % 10;
    sys->mem[sys->cpu->I + 2] = val % 10;
}

void handle_push(struct system_t *sys) {
    unsigned char nib = (sys->opcode & 0x0f00) >> 8;

    for(unsigned short i = 0; i <= nib; i++) {
        memory_set_byte(sys->mem, sys->cpu->I++, processor_get_register(sys->cpu, i));
    }
}

void handle_pop(struct system_t *sys) {
    unsigned char nib = (sys->opcode & 0x0f00) >> 8;

    for(unsigned short i = 0; i <= nib; i++) {
        processor_set_register(sys->cpu, i, memory_get_byte(sys->mem, sys->cpu->I++));
    }
}
