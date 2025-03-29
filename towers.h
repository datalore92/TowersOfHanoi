#ifndef TOWERS_H
#define TOWERS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#define MAX_DISKS 10
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define TOWER_COUNT 3
#define TOWER_WIDTH 10
#define DISK_HEIGHT 20

typedef struct {
    int disks[MAX_DISKS];
    int count;
} Tower;

typedef struct {
    SDL_Rect rect;
    const char* text;
} Button;

extern TTF_Font* gFont;
void drawText(SDL_Renderer* renderer, const char* text, SDL_Rect* rect, SDL_Color color);
int initTTF(void);
void closeTTF(void);

void push(Tower *tower, int disk);
int pop(Tower *tower);
void drawTowers(SDL_Renderer *renderer, Tower towers[]);
void drawButton(SDL_Renderer *renderer, Button *button);
int isButtonClicked(Button *button, int mouseX, int mouseY);
int drawDifficultySelection(SDL_Renderer *renderer);

#endif // TOWERS_H
