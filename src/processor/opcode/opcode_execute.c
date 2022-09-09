#include "chip8.h"
#include "opcode.h"
#include "local_opcode.h"

static void (*handles[MAX_HANDLE])(struct system_t *);

void opcode_execute(struct system_t *sys) {
    int handle = opcode_handle(sys->opcode);
    (*handles[handle])(sys);
}

void opcode_instantiate(void) {
    // Fill handles array
    handles[HANDLE_INVALID] = handle_invalid;
    handles[HANDLE_RETURN] = handle_return;
    handles[HANDLE_CLEAR_SCREEN] = handle_clear_screen;
    handles[HANDLE_CALL] = handle_call;
    handles[HANDLE_JUMP] = handle_jump;
    handles[HANDLE_SKIP_REI] = handle_skip_rei;
    handles[HANDLE_SKIP_RNEI] = handle_skip_rnei;
    handles[HANDLE_SKIP_RER] = handle_skip_rer;
    handles[HANDLE_MOVE_IMM] = handle_move_imm;
    handles[HANDLE_ADD_IMM] = handle_add_imm;
    handles[HANDLE_MOVE_REG] = handle_move_reg;
    handles[HANDLE_OR_REG] = handle_or_reg;
    handles[HANDLE_AND_REG] = handle_and_reg;
    handles[HANDLE_XOR_REG] = handle_xor_reg;
    handles[HANDLE_ADD_REG] = handle_add_reg;
    handles[HANDLE_SUB_XYREG] = handle_sub_xyreg;
    handles[HANDLE_SHIFT_RIGHT] = handle_shift_right;
    handles[HANDLE_SUB_YXREG] = handle_sub_yxreg;
    handles[HANDLE_SHIFT_LEFT] = handle_shift_left;
    handles[HANDLE_SKIP_RNER] = handle_skip_rner;
    handles[HANDLE_SAVE_IREGIMM] = handle_save_iregimm;
    handles[HANDLE_JUMP_IMMOFF] = handle_jump_immoff;
    handles[HANDLE_GENERATE_RAND] = handle_generate_rand;
    handles[HANDLE_DRAW_SPRITE] = handle_draw_sprite;
    handles[HANDLE_SKIP_KEYP] = handle_skip_keyp;
    handles[HANDLE_SKIP_KEYU] = handle_skip_keyu;
    handles[HANDLE_READ_DELAY] = handle_read_delay;
    handles[HANDLE_KEYPRESS_HALT] = handle_keypress_halt;
    handles[HANDLE_WRITE_DELAY] = handle_write_delay;
    handles[HANDLE_WRITE_SOUND] = handle_write_sound;
    handles[HANDLE_ADD_IREG] = handle_add_ireg;
    handles[HANDLE_SETFONT_HEX] = handle_setfont_hex;
    handles[HANDLE_HTOD] = handle_htod;
    handles[HANDLE_PUSH] = handle_push;
    handles[HANDLE_POP] = handle_pop;
}
