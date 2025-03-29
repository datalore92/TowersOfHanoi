#ifndef TOWERS_H
#define TOWERS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

// Game configuration constants
#define MAX_DISKS 10        // Maximum number of disks allowed in the game
#define WINDOW_WIDTH 800    // Window width in pixels
#define WINDOW_HEIGHT 600   // Window height in pixels
#define TOWER_COUNT 3       // Number of towers (standard game uses 3)
#define TOWER_WIDTH 10      // Width of tower poles in pixels
#define DISK_HEIGHT 20      // Height of each disk in pixels

// Structure representing a tower that can hold disks
typedef struct {
    int disks[MAX_DISKS];   // Array storing disk sizes (larger number = bigger disk)
    int count;              // Number of disks currently on this tower
} Tower;

// Structure for clickable buttons with text
typedef struct {
    SDL_Rect rect;          // Rectangle defining button position and size
    const char* text;       // Text to display on the button
} Button;

// Font handle for text rendering
extern TTF_Font* gFont;

// Text rendering functions
void drawText(SDL_Renderer* renderer, const char* text, SDL_Rect* rect, SDL_Color color); // Render text on the screen
int initTTF(void);         // Initialize TTF system
void closeTTF(void);       // Cleanup TTF system

// Tower manipulation functions
void push(Tower *tower, int disk);     // Add disk to tower
int pop(Tower *tower);                 // Remove and return top disk from tower

// Rendering functions
void drawTowers(SDL_Renderer *renderer, Tower towers[]);    // Draw all towers and disks
void drawButton(SDL_Renderer *renderer, Button *button);    // Draw a button
int isButtonClicked(Button *button, int mouseX, int mouseY);// Check if button was clicked
int drawDifficultySelection(SDL_Renderer *renderer);        // Show difficulty selection screen

#endif // TOWERS_H
