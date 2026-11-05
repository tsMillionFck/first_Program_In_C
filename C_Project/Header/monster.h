#ifndef MONSTER_H
#define MONSTER_H

typedef struct {
  char name[30];
  int hp;
  int maxHp;
  int attack;
  int expReward;
  int goldReward;
} Monster;

#endif