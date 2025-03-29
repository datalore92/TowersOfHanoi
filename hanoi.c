#include "hanoi.h"

Move moves[MAX_MOVES];
int moveCount = 0;

void solveHanoi(int n, int from, int aux, int to) {
    if(n == 0) return;
    
    // First move n-1 disks from source to auxiliary
    solveHanoi(n - 1, from, to, aux);
    
    // Move nth disk from source to destination
    moves[moveCount].from = from;
    moves[moveCount].to = to;
    moveCount++;
    
    // Finally move n-1 disks from auxiliary to destination
    solveHanoi(n - 1, aux, from, to);
}
