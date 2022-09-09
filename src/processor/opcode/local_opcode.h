#pragma once

#include "chip8.h"

#define MAX_HANDLE 35

#define HANDLE_INVALID 0
#define HANDLE_RETURN 1
#define HANDLE_CLEAR_SCREEN 2
#define HANDLE_CALL 3
#define HANDLE_JUMP 4
#define HANDLE_SKIP_REI 5
#define HANDLE_SKIP_RNEI 6
#define HANDLE_SKIP_RER 7
#define HANDLE_MOVE_IMM 8
#define HANDLE_ADD_IMM 9
#define HANDLE_MOVE_REG 10
#define HANDLE_OR_REG 11
#define HANDLE_AND_REG 12
#define HANDLE_XOR_REG 13
#define HANDLE_ADD_REG 14
#define HANDLE_SUB_XYREG 15
#define HANDLE_SHIFT_RIGHT 16
#define HANDLE_SUB_YXREG 17
#define HANDLE_SHIFT_LEFT 18
#define HANDLE_SKIP_RNER 19
#define HANDLE_SAVE_IREGIMM 20
#define HANDLE_JUMP_IMMOFF 21
#define HANDLE_GENERATE_RAND 22
#define HANDLE_DRAW_SPRITE 23
#define HANDLE_SKIP_KEYP 24
#define HANDLE_SKIP_KEYU 25
#define HANDLE_READ_DELAY 26
#define HANDLE_KEYPRESS_HALT 27
#define HANDLE_WRITE_DELAY 28
#define HANDLE_WRITE_SOUND 29
#define HANDLE_ADD_IREG 30
#define HANDLE_SETFONT_HEX 31
#define HANDLE_HTOD 32
#define HANDLE_PUSH 33
#define HANDLE_POP 34

int opcode_handle(unsigned short);
void handle_invalid(struct system_t *); void handle_return(struct system_t *);
void handle_clear_screen(struct system_t *); void handle_call(struct system_t *);
void handle_jump(struct system_t *); void handle_skip_rei(struct system_t *);
void handle_skip_rnei(struct system_t *); void handle_skip_rer(struct system_t *);
void handle_move_imm(struct system_t *); void handle_add_imm(struct system_t *);
void handle_move_reg(struct system_t *); void handle_or_reg(struct system_t *);
void handle_and_reg(struct system_t *); void handle_sub_xyreg(struct system_t *);
void handle_shift_right(struct system_t *); void handle_sub_yxreg(struct system_t *);
void handle_shift_left(struct system_t *); void handle_skip_rner(struct system_t *);
void handle_save_iregimm(struct system_t *); void handle_jump_immoff(struct system_t *);
void handle_generate_rand(struct system_t *); void handle_draw_sprite(struct system_t *);
void handle_skip_keyp(struct system_t *); void handle_skip_keyu(struct system_t *);
void handle_read_delay(struct system_t *); void handle_keypress_halt(struct system_t *);
void handle_write_delay(struct system_t *); void handle_write_sound(struct system_t *);
void handle_add_ireg(struct system_t *); void handle_setfont_hex(struct system_t *);
void handle_htod(struct system_t *); void handle_push(struct system_t *);
void handle_pop(struct system_t *); void handle_xor_reg(struct system_t *);
void handle_add_reg(struct system_t *);
