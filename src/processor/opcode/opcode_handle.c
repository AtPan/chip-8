#include "opcode.h"
#include "local_opcode.h"

int opcode_handle(unsigned short op) {
    int handle = HANDLE_INVALID;

    switch (op >> 12) {
        case 0:
            switch (op & 0xff) {
                case 0xee:
                    handle = HANDLE_RETURN;
                    break;
                case 0xe0:
                    handle = HANDLE_CLEAR_SCREEN;
                    break;
                default:
                    handle = HANDLE_CALL;
                    break;
            }
            break;
        case 1:
            handle = HANDLE_JUMP;
            break;
        case 2:
            handle = HANDLE_CALL;
            break;
        case 3:
            handle = HANDLE_SKIP_REI;
            break;
        case 4:
            handle = HANDLE_SKIP_RNEI;
            break;
        case 5:
            if((op & 0xf) == 0) {
                handle = HANDLE_SKIP_RER;
            }
            break;
        case 6:
            handle = HANDLE_MOVE_IMM;
            break;
        case 7:
            handle = HANDLE_ADD_IMM;
            break;
        case 8:
            switch (op & 0xf) {
                case 0:
                    handle = HANDLE_MOVE_REG;
                    break;
                case 1:
                    handle = HANDLE_OR_REG;
                    break;
                case 2:
                    handle = HANDLE_AND_REG;
                    break;
                case 3:
                    handle = HANDLE_XOR_REG;
                    break;
                case 4:
                    handle = HANDLE_ADD_REG;
                    break;
                case 5:
                    handle = HANDLE_SUB_XYREG;
                    break;
                case 6:
                    handle = HANDLE_SHIFT_RIGHT;
                    break;
                case 7:
                    handle = HANDLE_SUB_YXREG;
                    break;
                case 0xe:
                    handle = HANDLE_SHIFT_LEFT;
                    break;
            }
            break;
        case 9:
            if((op & 0xf) == 0) {
                handle = HANDLE_SKIP_RNER;
            }
            break;
        case 10:
            handle = HANDLE_SAVE_IREGIMM;
            break;
        case 11:
            handle = HANDLE_JUMP_IMMOFF;
            break;
        case 12:
            handle = HANDLE_GENERATE_RAND;
            break;
        case 13:
            handle = HANDLE_DRAW_SPRITE;
            break;
        case 14:
        case 15:
            switch (op & 0xff) {
                case 0x9e:
                    handle = HANDLE_SKIP_KEYP;
                    break;
                case 0xa1:
                    handle = HANDLE_SKIP_KEYU;
                    break;
                case 7:
                    handle = HANDLE_READ_DELAY;
                    break;
                case 10:
                    handle = HANDLE_KEYPRESS_HALT;
                    break;
                case 0x15:
                    handle = HANDLE_WRITE_DELAY;
                    break;
                case 0x18:
                    handle = HANDLE_WRITE_SOUND;
                    break;
                case 0x1e:
                    handle = HANDLE_ADD_IREG;
                    break;
                case 0x29:
                    handle = HANDLE_SETFONT_HEX;
                    break;
                case 0x33:
                    handle = HANDLE_HTOD;
                    break;
                case 0x55:
                    handle = HANDLE_PUSH;
                    break;
                case 0x65:
                    handle = HANDLE_POP;
                    break;
            }
            break;
    }

    return handle;
}
