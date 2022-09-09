#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_audio.h>
#include <stdlib.h>
#include "resources.h"
#include "error.h"
#include "memory.h"
#include "screen.h"

#define PIXEL_SCALE 8
#define MIN_X 0
#define MIN_Y 0
#define MIN_EMU_SCREEN_X 0
#define MIN_EMU_SCREEN_Y 0
#define MAX_X 64
#define MAX_Y 32
#define MAX_EMU_SCREEN_X 0
#define MAX_EMU_SCREEN_Y 0
#define SDL_VIDEO_FLAGS SDL_INIT_VIDEO | SDL_INIT_AUDIO

static SDL_Window *screen;
static SDL_Renderer *render;
static SDL_Rect rect;

void screen_instantiate() {
    if(SDL_Init(SDL_VIDEO_FLAGS) < 0) {
        printf("SDL Error: %s\n", SDL_GetError());
        exit(CODE_SCREEN_NOT_AVAILABLE);
    }

    uint32_t flags = SDL_WINDOW_SHOWN;
    screen = SDL_CreateWindow("Chip8 Emulator",
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, MAX_X * PIXEL_SCALE, MAX_Y * PIXEL_SCALE, flags);

    if(screen == NULL) {
        printf("SDL Error: %s\n", SDL_GetError());
        fatal_error(ERROR_SCREEN_NOT_AVAILABLE, CODE_SCREEN_NOT_AVAILABLE);
    }

    render = SDL_CreateRenderer(screen, -1, SDL_RENDERER_ACCELERATED);

    rect.w = PIXEL_SCALE;
    rect.h = PIXEL_SCALE;

    save_resource(RESOURCE_SCREEN, screen);

    SDL_ShowWindow(screen);
}

void screen_update(unsigned char * restrict gfx) {
    for(unsigned char y = 0; y < 32; y++) {
        rect.y = y * PIXEL_SCALE;
        rect.x = 0;
        for(unsigned char x = 0; x < 8; x++) {
            unsigned char byte = *(gfx + x + (y * 8));

            for(char bit = 7; bit >= 0; bit--) {
                if(((byte >> bit) & 1) == 1) {
                    // Turn on square
                    SDL_SetRenderDrawColor(render, 255, 255, 255, 0);
                }
                else {
                    // Turn off square
                    SDL_SetRenderDrawColor(render, 0, 0, 0, 0);
                }
                SDL_RenderFillRect(render, &rect);
                rect.x += PIXEL_SCALE;
            }
        }
    }

    SDL_RenderPresent(render);
}

void screen_clear() {
    SDL_SetRenderDrawColor(render, 0, 0, 0, 0);
    SDL_RenderClear(render);
    SDL_RenderPresent(render);
}

void screen_destroy() {
    SDL_QuitSubSystem(SDL_VIDEO_FLAGS);
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(screen);
    SDL_Quit();
    save_resource(RESOURCE_SCREEN, NULL);
}
