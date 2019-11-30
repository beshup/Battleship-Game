#ifndef VEHICLE_H_
#define VEHICLE_H_
#include <stdbool.h>

#define NORTH 1
#define EAST 2
#define SOUTH 4
#define WEST 8

struct Vehicle;

void addToShipSpacesHit(struct Vehicle *vehicle, int spaceHit, int sizeOfVehicle);

struct Vehicle *makeVehicle(int x, int y, int dir, int size);

struct Vehicle **freeVehicles(struct Vehicle **v, int n);

bool shipDead(struct Vehicle *v);

bool battleshipShot(struct Vehicle** targets, int n, int x, int y);

bool checkForShip(struct Vehicle **targets, int n, int x, int y);

struct Vehicle *whichVehicle(struct Vehicle **v, int n, int x, int y);

int howFarDownVehicle(struct Vehicle *v, int x, int y);

void printBattleships(struct Vehicle** v, int n, int width, int height);

#endif