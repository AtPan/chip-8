#include <SDL2/SDL.h>
#include <SDL2/SDL_keyboard.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "chip8.h"

int main(int, char **);

int main(int argc, char *argv[]) {
    if(argc == 1) {
        fprintf(stderr, "Usage: %s <RomName> [delay]\n", argv[0]);
        exit(1);
    }

    unsigned int delay = 3;
    if(argc == 3) {
        delay = atoi(argv[2]);
    }

    register struct cpu_t *cpu = processor_instantiate();
    unsigned char *mem = memory_instantiate(SIZE_MEMORY);
    load_rom(mem, argv[1]);
    opcode_instantiate();
    screen_instantiate();

    struct system_t sys;
    sys.cpu = cpu;
    sys.mem = mem;
    sys.opcode = 0;

    SDL_Event event;
    int run = 1;
    const double trigger = (1.0 / 60) * CLOCKS_PER_SEC / delay;

    clock_t last_trigger = clock();
    unsigned long iter = 0;

    while(run) {
        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT) {
                run = 0;
                break;
            }
        }

        if(clock() - last_trigger >= trigger) {
            if(sys.cpu->sound) sys.cpu->sound--;
            if(sys.cpu->delay) sys.cpu->delay--;

#ifdef DEBUG
            system("clear");
            processor_display(sys.cpu);
            int keydelay = 1;
#endif

            read_opcode(&sys);
            opcode_execute(&sys);

#ifdef DEBUG
            printf("Opcode [%04x] -- Iteration %ld\n\n", sys.opcode, iter);

            processor_display(sys.cpu);
            iter++;
            while(keydelay) {
                while(SDL_PollEvent(&event)) {
                    if(event.type == SDL_KEYDOWN) {
                        if(event.key.keysym.scancode == SDL_SCANCODE_RETURN) {
                            keydelay = 0;
                            break;
                        }
                    }
                    if(event.type == SDL_QUIT) {
                        run = 0;
                        keydelay = 0;
                        break;
                    }
                }
            }
#endif
            last_trigger = clock();
        }
    }

    screen_destroy();
    processor_destroy(cpu);
    memory_destroy(mem);
}
