#ifndef MONSTER_H
#define MONSTER_H

typedef enum {
  ABILITY_NONE = 0,
  ABILITY_POISON,
  ABILITY_REGENERATION,
  ABILITY_TIME_CONTROL,
  ABILITY_SECOND_PHASE
} MonsterAbility;

typedef struct {
  char name[30];
  int hp;
  int maxHp;
  int attack;
  int expReward;
  int goldReward;
  MonsterAbility ability;
} Monster;

#endif