#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include "towers.h"

int main(int argc, char* argv[]) {
    // Initialize SDL and create window/renderer
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL_Init error: %s\n", SDL_GetError());
        return 1;
    }
    if (!initTTF()) {
        SDL_Quit();
        return 1;
    }
    SDL_Window *win = SDL_CreateWindow("Towers of Hanoi", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (!win) {
        printf("SDL_CreateWindow error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    SDL_Renderer *renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        SDL_DestroyWindow(win);
        printf("SDL_CreateRenderer error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Game state variables
    enum { STATE_PLAYING, STATE_WIN } gameState = STATE_PLAYING;
    int quit = 0;                  // Main game loop control
    SDL_Event event;              // SDL event handling
    int selectedTower = -1;       // Currently selected tower (-1 = none)
    int diskCount;                // Number of disks in current game
    Tower towers[TOWER_COUNT];    // Array of towers

restart_game:
    // Initialize new game with selected difficulty
    diskCount = drawDifficultySelection(renderer);
    if(diskCount == 0) {  // Handle window close during difficulty selection
        quit = 1;
        goto end_game;
    }

    // Initialize towers and place all disks on first tower
    for (int i = 0; i < TOWER_COUNT; i++) { towers[i].count = 0; }
    for (int disk = diskCount; disk >= 1; disk--) { push(&towers[0], disk); }
    selectedTower = -1;
    gameState = STATE_PLAYING;

    // Clear pending events
    while(SDL_PollEvent(&event));

    while (!quit) {
        if(gameState == STATE_PLAYING) {
            // Handle user input and game logic
            while(SDL_PollEvent(&event)) {
                // Handle quit event
                if(event.type == SDL_QUIT) { quit = 1; }
                
                // Handle mouse clicks for disk movement
                if(event.type == SDL_MOUSEBUTTONDOWN) {
                    int mouseX = event.button.x;
                    int towerSpacing = WINDOW_WIDTH / (TOWER_COUNT + 1);
                    for (int i = 0; i < TOWER_COUNT; i++) {
                        int center = towerSpacing * (i + 1);
                        if(abs(mouseX - center) < towerSpacing / 2) {
                            if(selectedTower == -1) {
                                if(towers[i].count > 0)
                                    selectedTower = i;
                            } else {
                                if(selectedTower == i)
                                    selectedTower = -1;
                                else {
                                    int movingDisk = towers[selectedTower].disks[towers[selectedTower].count - 1];
                                    if(towers[i].count == 0 || towers[i].disks[towers[i].count - 1] > movingDisk) {
                                        int disk = pop(&towers[selectedTower]);
                                        push(&towers[i], disk);
                                        selectedTower = -1;
                                        if(towers[i].count == diskCount && i != 0)
                                            gameState = STATE_WIN;
                                    } else { selectedTower = -1; }
                                }
                            }
                            break;
                        }
                    }
                }
            }

            // Render game state
            drawTowers(renderer, towers);
            
            // Highlight selected tower
            if(selectedTower != -1) {
                int towerSpacing = WINDOW_WIDTH / (TOWER_COUNT + 1);
                int center = towerSpacing * (selectedTower + 1);
                SDL_Rect highlight = {center - 60, WINDOW_HEIGHT / 4, 120, WINDOW_HEIGHT / 2};
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 128);
                SDL_RenderDrawRect(renderer, &highlight);
                SDL_RenderPresent(renderer);
            }
        }
        else if(gameState == STATE_WIN) {
            // Handle win screen and button interactions
            // Render win screen with "You win!" text and two buttons.
            SDL_SetRenderDrawColor(renderer, 230, 230, 230, 255);
            SDL_RenderClear(renderer);
            SDL_Rect winTextRect = {WINDOW_WIDTH/2 - 100, WINDOW_HEIGHT/4 - 30, 200, 50};
            drawText(renderer, "You win!", &winTextRect, (SDL_Color){0,0,0,255});
            Button winButtons[2] = {
                {{WINDOW_WIDTH/2 - 150, WINDOW_HEIGHT/2, 120, 50}, "Play Again"},
                {{WINDOW_WIDTH/2 + 30,  WINDOW_HEIGHT/2, 120, 50}, "Quit"}
            };
            for (int i = 0; i < 2; i++) {
                drawButton(renderer, &winButtons[i]);
                SDL_Rect btnTextRect = winButtons[i].rect;
                int textW, textH;
                TTF_SizeText(gFont, winButtons[i].text, &textW, &textH);
                btnTextRect.x += (winButtons[i].rect.w - textW) / 2;
                btnTextRect.y += (winButtons[i].rect.h - textH) / 2;
                drawText(renderer, winButtons[i].text, &btnTextRect, (SDL_Color){0,0,0,255});
            }
            SDL_RenderPresent(renderer);

            while(SDL_PollEvent(&event)) {
                if(event.type == SDL_QUIT) { quit = 1; }
                if(event.type == SDL_MOUSEBUTTONDOWN) {
                    int mx = event.button.x, my = event.button.y;
                    for (int i = 0; i < 2; i++) {
                        if(isButtonClicked(&winButtons[i], mx, my)) {
                            if(i == 0) { // Play Again
                                selectedTower = -1;
                                goto restart_game;
                            } else { // Quit
                                quit = 1;
                            }
                        }
                    }
                }
            }
        }
        SDL_Delay(16);  // Cap frame rate
    }

end_game:
    // Cleanup and exit
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
    closeTTF();
    SDL_Quit();
    return 0;
}
