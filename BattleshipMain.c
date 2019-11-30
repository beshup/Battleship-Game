#include <stdio.h>
#include <stdlib.h>
#include "vehicle.h"
#include <assert.h>

int playerAlive(struct Vehicle**ships, int n) {
    int shipsAlive = n;
    for (int i = 0; i < n; ++i) {
        if (shipDead(ships[i])) --shipsAlive;
    }
    return shipsAlive;
}

int charToDir(char c) {
    switch(c) {
        case 'N': return NORTH;
        case 'E': return EAST;
        case 'S': return SOUTH;
        case 'W': return WEST;
    }
    // Default to north
    return NORTH;
}

// Reads int for X, int for Y, int for Size, and char for Dir.
struct Vehicle *inputShip() {
    int x = 0, y = 0, size = 1;
    char dir = 'N';
    scanf("%d", &x);
    scanf("%d", &y);
    scanf("%d", &size);
    scanf(" %c", &dir);
    assert(dir=='N' || dir=='E' || dir=='W' || dir=='S');
    return makeVehicle(x, y, charToDir(dir), size);
}


int main() {
    int WIDTH = 8, HEIGHT = 8;
    int NUMSHIPS = 2;
    struct Vehicle** p1Ships = malloc(sizeof(struct Vehicle*)*NUMSHIPS);
    struct Vehicle** p2Ships = malloc(sizeof(struct Vehicle*)*NUMSHIPS);
    struct Vehicle** players[2] = {p1Ships, p2Ships};
    // Input ships for P1 and P2, alternating.
    for (int i = 0; i < NUMSHIPS; ++i) {
        printf("Enter player 1 ship x, y, size, dir (N,E,S,W): ");
        p1Ships[i] = inputShip();
        printf("Enter player 2 ship x, y, size, dir (N,E,S,W): ");
        p2Ships[i] = inputShip();
    }
    int playersTurn = 0;
    while(!feof(stdin)) {
        int x = 0, y = 0;
        int i = (playersTurn+1)%2;
        printf("Player %d's turn, your board:\n", playersTurn +1);
        printBattleships(players[playersTurn], NUMSHIPS, WIDTH, HEIGHT);
        printf("Enter target x and y for player %d: ", playersTurn+1);
        scanf("%d", &x);
        scanf("%d", &y);
        int hit = battleshipShot(players[i], NUMSHIPS, x, y);
        printf(hit ? "HIT!\n" : "Miss! :(\n");
        if (!playerAlive(players[i], NUMSHIPS)) break;
        playersTurn = i;
    }
    if (!feof(stdin)) {
        printf("Player %d wins!\n", playersTurn + 1);
    } else {
        printf("Game ended early\n");
    }
   freeVehicles(p1Ships, NUMSHIPS);
   freeVehicles(p2Ships, NUMSHIPS);
}