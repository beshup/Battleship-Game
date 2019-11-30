#include <stdio.h>
#include <stdlib.h>
#include "vehicle.h"
#include <assert.h>

struct Vehicle{
  int x, y, dir, size;
  int spacesHit[100];
};

void addToShipSpacesHit(struct Vehicle *vehicle, int spaceHit, int sizeOfVehicle){
  for (int i=0; i<sizeOfVehicle; i++){
    if (i == spaceHit){
      (*vehicle).spacesHit[spaceHit] = 1;
    }
  }
}

struct Vehicle *makeVehicle(int x, int y, int dir, int size){
  struct Vehicle *newVehicle = malloc(sizeof(struct Vehicle));
  (*newVehicle).dir = dir;
  (*newVehicle).size = size;
  (*newVehicle).x = x;
  (*newVehicle).y = y;
  return (newVehicle);
}

struct Vehicle **freeVehicles(struct Vehicle **v, int n){
  for (int i=0; i< n; i++){
    free(v[i]);
    v[i] = NULL;
  }
  free(v);
  v= NULL;
  return(v);
}



bool shipDead(struct Vehicle *v){
  int sizee = (*v).size;
  int sum=0;
  for (int i=0; i<sizee; i++){
    if ((*v).spacesHit[i] == 1){
      sum++;
    }
  }
  if (sum==sizee){
    return true;
  }
  return false;
}

bool battleshipShot(struct Vehicle **targets, int n, int x, int y){
  for (int i=0; i<n; i++){
    int sizee = (*targets[i]).size;
    int dirr = (*targets[i]).dir;
    int xx = (*targets[i]).x;
    int yy = (*targets[i]).y;
    for (int k=0; k<sizee; k++){
      if (dirr == NORTH){
        if (((yy - k)==y)&&(xx==x)){
          addToShipSpacesHit(targets[i], k, sizee);
          return true;
        }
      }
      if (dirr == SOUTH){
        if (((yy + k)==y)&&(xx==x)){
          addToShipSpacesHit(targets[i], k, sizee);
          return true;
        }
      }
      if (dirr == EAST){
        if (((xx + k)==x)&&(yy==y)){
          addToShipSpacesHit(targets[i], k, sizee);
          return true;
        }
      }
      if (dirr == WEST){
        if (((xx - k)==x)&&(yy==y)){
          addToShipSpacesHit(targets[i], k, sizee);
          return true;
        }
      }
    } 
  }
  return false;
}

bool checkForShip(struct Vehicle **targets, int n, int y, int x){
  for (int i=0; i<n; i++){
    int sizee = (*targets[i]).size;
    int dirr = (*targets[i]).dir;
    int xx = (*targets[i]).x;
    int yy = (*targets[i]).y;
    for (int k=0; k<sizee; k++){
      if (dirr == NORTH){
        if (((yy - k)==y)&&(xx==x)){

          return true;
        }
      }
      if (dirr == SOUTH){
        if (((yy + k)==y)&&(xx==x)){

          return true;
        }
      }
      if (dirr == EAST){
        if (((xx + k)==x)&&(yy==y)){

          return true;
        }
      }
      if (dirr == WEST){
        if (((xx - k)==x)&&(yy==y)){

          return true;
        }
      }
    } 
  }
  return false;
}

struct Vehicle *whichVehicle(struct Vehicle **v, int n, int y, int x){
  for (int i=0; i<n; i++){
    int sizee = (*v[i]).size;
    int dirr = (*v[i]).dir;
    int xx = (*v[i]).x;
    int yy = (*v[i]).y;
    for (int k=0; k<sizee; k++){
      if (dirr == NORTH){
        if (((yy - k)==y)&&(xx==x)){
          return v[i];
        }
      }
      if (dirr == SOUTH){
        if (((yy + k)==y)&&(xx==x)){
          return v[i];
        }
      }
      if (dirr == EAST){
        if (((xx + k)==x)&&(yy==y)){
          return v[i];
        }
      }
      if (dirr == WEST){
        if (((xx - k)==x)&&(yy==y)){
          return v[i];
        }
      }
    } 
  }
  return 0;
}

int howFarDownVehicle(struct Vehicle *v, int y, int x){
  int sizee = (*v).size;
  int dirr = (*v).dir;
  int xx = (*v).x;
  int yy = (*v).y;
  for (int k=0; k<sizee; k++){
      if (dirr == NORTH){
        if (((yy - k)==y)&&(xx==x)){
          return k;
        }
      }
      if (dirr == SOUTH){
        if (((yy + k)==y)&&(xx==x)){
          return k;
        }
      }
      if (dirr == EAST){
        if (((xx + k)==x)&&(yy==y)){
          return k;
        }
      }
      if (dirr == WEST){
        if (((xx - k)==x)&&(yy==y)){
          return k;
        }
      }
    }
    return 0;
}

void printBattleships(struct Vehicle **v, int n, int width, int height){
  int boardStored[height][width];
  for (int i=0; i<height; i++){
    for (int j=0; j<width; j++){
      if (checkForShip(v, n, i, j)==true){
        boardStored[i][j] = 1;
      }
      else{
        boardStored[i][j] = 0;
      }
    }
  }
  for (int i=0; i<height; i++){
    for (int j=0; j<width; j++){
      if(boardStored[i][j] == 1){
        int spaceDown = howFarDownVehicle(whichVehicle(v, n, i, j), i, j);
        if ((*whichVehicle(v, n, i, j)).spacesHit[spaceDown] == 1){
          boardStored[i][j] = 2;
        }
      }
    }
  }

  for (int i=0; i<height; i++){
    for (int j=0; j<width; j++){
      if (boardStored[i][j] == 0){
        printf("-");
      }
      else if (boardStored[i][j] == 1){
        printf("O");
      }
      else if (boardStored[i][j] == 2){
        printf("X");
      }
    }
    printf("\n");
  }
}