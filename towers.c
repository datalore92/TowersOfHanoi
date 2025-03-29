#include "towers.h"
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

TTF_Font* gFont = NULL;

// Initialize the TTF library and load the font
int initTTF(void) {
    if (TTF_Init() < 0) {
        printf("TTF_Init failed: %s\n", TTF_GetError());
        return 0;
    }
    gFont = TTF_OpenFont("C:\\Windows\\Fonts\\arial.ttf", 20);  // Smaller font size
    if (!gFont) {
        printf("Failed to load font: %s\n", TTF_GetError());
        return 0;
    }
    return 1;
}

// Close the TTF library and free the font
void closeTTF(void) {
    if (gFont) TTF_CloseFont(gFont);
    TTF_Quit();
}

// Render text on the screen using SDL_ttf
void drawText(SDL_Renderer* renderer, const char* text, SDL_Rect* rect, SDL_Color color) {
    if (!gFont) return;
    SDL_Surface* surface = TTF_RenderText_Solid(gFont, text, color);
    if (surface) {
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_RenderCopy(renderer, texture, NULL, rect);
        SDL_DestroyTexture(texture);
        SDL_FreeSurface(surface);
    }
}

// Stack operations for tower manipulation
void push(Tower *tower, int disk) {
    tower->disks[tower->count++] = disk;    // Add disk and increment count
}

int pop(Tower *tower) {
    if (tower->count <= 0) return -1;       // Return -1 if tower is empty
    return tower->disks[--tower->count];     // Remove and return top disk
}

// Draw the towers and disks on the screen
void drawTowers(SDL_Renderer *renderer, Tower towers[]) {
    // Set background color
    SDL_SetRenderDrawColor(renderer, 230, 230, 230, 255);
    SDL_RenderClear(renderer);
    
    // Calculate spacing between towers
    int towerSpacing = WINDOW_WIDTH / (TOWER_COUNT + 1);
    
    // Draw the vertical poles for each tower
    for (int i = 0; i < TOWER_COUNT; i++) {
        int x = towerSpacing * (i + 1) - TOWER_WIDTH / 2;
        SDL_Rect towerRect = { x, WINDOW_HEIGHT / 4, TOWER_WIDTH, WINDOW_HEIGHT / 2 };
        SDL_SetRenderDrawColor(renderer, 80, 80, 80, 255);
        SDL_RenderFillRect(renderer, &towerRect);
    }
    
    // Draw the disks on each tower
    for (int i = 0; i < TOWER_COUNT; i++) {
        int towerX = towerSpacing * (i + 1);
        int baseY = WINDOW_HEIGHT * 3 / 4;   // Bottom position for disks
        
        // Draw each disk from bottom to top
        for (int j = 0; j < towers[i].count; j++) {
            int disk = towers[i].disks[j];
            int diskWidth = 40 + disk * 20;  // Disk width based on size
            int diskX = towerX - diskWidth / 2;
            int diskY = baseY - (j + 1) * DISK_HEIGHT;
            
            // Create and draw the disk rectangle
            SDL_Rect diskRect = { diskX, diskY, diskWidth, DISK_HEIGHT - 2 };
            SDL_SetRenderDrawColor(renderer, 0, 0, 255 - disk * 20, 255);  // Color varies by size
            SDL_RenderFillRect(renderer, &diskRect);
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderDrawRect(renderer, &diskRect);
        }
    }
    
    SDL_RenderPresent(renderer);
}

// Draw a button on the screen
void drawButton(SDL_Renderer *renderer, Button *button) {
    SDL_SetRenderDrawColor(renderer, 100, 100, 200, 255);
    SDL_RenderFillRect(renderer, &button->rect);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &button->rect);
}

// Check if a button is clicked based on mouse coordinates
int isButtonClicked(Button *button, int mouseX, int mouseY) {
    return mouseX >= button->rect.x && mouseX <= button->rect.x + button->rect.w &&
           mouseY >= button->rect.y && mouseY <= button->rect.y + button->rect.h;
}

// Draw the difficulty selection screen and handle user input
int drawDifficultySelection(SDL_Renderer *renderer) {
    Button buttons[3] = {
        {{WINDOW_WIDTH/4 - 60, WINDOW_HEIGHT/2 - 25, 120, 50}, "Easy"},
        {{WINDOW_WIDTH/2 - 60, WINDOW_HEIGHT/2 - 25, 120, 50}, "Medium"},
        {{3*WINDOW_WIDTH/4 - 60, WINDOW_HEIGHT/2 - 25, 120, 50}, "Hard"}
    };
    
    SDL_SetRenderDrawColor(renderer, 230, 230, 230, 255);
    SDL_RenderClear(renderer);
    
    // Draw title text
    SDL_Rect titleRect = {WINDOW_WIDTH/2 - 100, WINDOW_HEIGHT/4, 200, 40};
    SDL_Color textColor = {50, 50, 50, 255};
    drawText(renderer, "Select Difficulty", &titleRect, textColor);
    
    for(int i = 0; i < 3; i++) {
        drawButton(renderer, &buttons[i]);
        SDL_Rect textRect = buttons[i].rect;
        // Center text both vertically and horizontally
        int textWidth, textHeight;
        TTF_SizeText(gFont, buttons[i].text, &textWidth, &textHeight);
        textRect.x += (textRect.w - textWidth) / 2;
        textRect.y += (textRect.h - textHeight) / 2;
        drawText(renderer, buttons[i].text, &textRect, (SDL_Color){0, 0, 0, 255});
    }
    
    SDL_RenderPresent(renderer);
    
    SDL_Event event;
    while(1) {
        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT) return 0;
            if(event.type == SDL_MOUSEBUTTONDOWN) {
                int mouseX = event.button.x;
                int mouseY = event.button.y;
                for(int i = 0; i < 3; i++) {
                    if(isButtonClicked(&buttons[i], mouseX, mouseY)) {
                        return (i == 0) ? 3 : (i == 1) ? 5 : 8;
                    }
                }
            }
        }
        SDL_Delay(16);
    }
    return 3;  // default to easy if something goes wrong
}