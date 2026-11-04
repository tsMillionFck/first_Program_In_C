#ifndef PLAYER_H
#define PLAYER_H

typedef struct {
  int hp;
  int maxHp;
  int gold;
  int portions;
  int weapon;
  int experience;
  int level;
  int hasPet;
} Player;

int percentageChance(); // why do we use const in parameters of
                        // new player struct pointer

#endif