#ifndef MONSTER_H
#define MONSTER_H
#include "./player.h"

typedef enum {
  ABILITY_NONE = 0,
  ABILITY_POISON = 1,
  ABILITY_REGENERATION = 2,
  ABILITY_TIME_CONTROL = 3,
  ABILITY_SECOND_PHASE = 4,
  ABILITY_COUNT
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

Monster createTroll();
Monster createViper();
Monster createChronoTheTime();
Monster createTheSunKing();
MonsterAbility getRandomAbility();
Monster getRandomMonster();
const char *getMonsterAbilityName(MonsterAbility a);
void triggerMonsterAbility(Monster *m, Player *p);

#endif