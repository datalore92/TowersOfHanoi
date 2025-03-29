#ifndef HANOI_H
#define HANOI_H

#define MAX_MOVES 1024

typedef struct {
    int from;
    int to;
} Move;

// Global array to hold moves and a counter.
extern Move moves[MAX_MOVES];
extern int moveCount;

// Recursively compute moves for Towers of Hanoi.
void solveHanoi(int n, int from, int aux, int to);

#endif // HANOI_H
