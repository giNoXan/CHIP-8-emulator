#include <SDL2/SDL_render.h>
#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#define WINDOW_TITLE "Test Window"
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600


typedef struct {
    SDL_Window *window;
    SDL_Renderer *renderer;
} Chip8;

bool sdl_initialize(Chip8 *chip8);
void sdl_cleanup(Chip8 *chip8);

int main() {
    
    Chip8 chip8 = {
        .window = NULL,
        .renderer = NULL,
    };

    if (sdl_initialize(&chip8)) {
        sdl_cleanup(&chip8);
        printf("Not Good\n");
        exit(1);
    }

    SDL_RenderClear(chip8.renderer);
    SDL_RenderPresent(chip8.renderer);
    SDL_Delay(5000);

    sdl_cleanup(&chip8);
    printf("All Good\n");
    return 0;
}

bool sdl_initialize(Chip8 *chip8) {
   if (SDL_Init(SDL_INIT_EVERYTHING)) {
       fprintf(stderr, "Error initializing: %s\n", SDL_GetError());
       return true;
   }

   chip8->window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
   if (!chip8->window) {
       fprintf(stderr, "Error creating window: %s\n", SDL_GetError());
       return true;
   }

   chip8->renderer = SDL_CreateRenderer(chip8->window, -1, 0);
   if (!chip8->renderer) {
       fprintf(stderr, "Error creating renderer: %s\n", SDL_GetError());
       return true;
   }

   return false;
    
}

void sdl_cleanup(Chip8 *chip8) {
    SDL_DestroyRenderer(chip8->renderer);
    SDL_DestroyWindow(chip8->window);
    SDL_Quit();
    exit(0);
}
