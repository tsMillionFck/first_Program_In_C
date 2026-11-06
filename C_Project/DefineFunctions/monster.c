#include "../Header/monster.h"
#include <stdio.h>
#include <string.h>

Monster createTroll() {
  Monster troll;
  strcpy(troll.name, "Cave Troll");
  troll.hp = 120;
  troll.maxHp = 120;
  troll.attack = 18;
  troll.expReward = 50;
  troll.goldReward = 30;
  troll.ability = ABILITY_REGENERATION;
  return troll; // Troll monster creator
}