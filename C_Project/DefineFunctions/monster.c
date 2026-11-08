#include "../Header/monster.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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

Monster createViper() {
  Monster viper;
  strcpy(viper.name, "Rich Viper");
  viper.hp = 120;
  viper.maxHp = 120;
  viper.attack = 20;
  viper.expReward = 60;
  viper.goldReward = 100;
  viper.ability = ABILITY_POISON;
  return viper;
}

Monster createChronoTheTime() {
  Monster chrono;
  strcpy(chrono.name, "Chrono The Time");
  chrono.hp = 200;
  chrono.maxHp = 200;
  chrono.attack = 35;
  chrono.expReward = 100;
  chrono.goldReward = 40;
  chrono.ability = ABILITY_TIME_CONTROL;
  return chrono;
}

Monster createTheSunKing() {
  Monster sunKing;
  strcpy(sunKing.name, "Sun King, Sukuna");
  sunKing.hp = 500;
  sunKing.maxHp = 500;
  sunKing.attack = 50;
  sunKing.expReward = 1000;
  sunKing.goldReward = 1000;
  sunKing.ability = ABILITY_SECOND_PHASE;
  return sunKing;
}

const char *getMonsterAbilityName(MonsterAbility a) {
  switch (a) {
  case 0:
    return "None";
    break;
  case 1:
    return "Poison Spit";
    break;
  case 2:
    return "Regeneration";
    break;
  case 3:
    return "Time Wrap";
    break;
  case 4:
    return "Second Phase (Enrage)";
    break;
  default:
    return "Error in ability";
    break;
  }
}

MonsterAbility getRandomAbility() {
  int roll = (rand() % 3) + 1;
  return (MonsterAbility)roll;
}
void triggerMonsterAbility(Monster *m, Player *p) {
  switch (m->ability) {
  case ABILITY_REGENERATION:
    if (m->hp < m->maxHp && m->hp > 0) {
      int healAmount = 5;
      m->hp += healAmount;
      if (m->hp > m->maxHp) {
        m->hp = m->maxHp;
      }
      printf("%s is Regenerating and restoring %d HP! (Current HP: %d / %d \n)",
             m->name, healAmount, m->hp, m->maxHp);
    }
    break;
  case ABILITY_POISON:
    if (m->hp > 0 && p->hp > 0) {
      int posionDamage = 5;
      p->hp -= posionDamage;
      printf("%s posined you. Dealing %d poison damage! (Your HP: %d)\n",
             m->name, posionDamage, p->hp);
    }
    if (p->hp <= 0) {
      printf("You died due to %s posion!\n", m->name);
      p->hp = 0;
    }
    break;
  case ABILITY_SECOND_PHASE:
    if (m->hp <= 10) {
      printf("%s: OH Death become my blade once more.\n", m->name);
      printf("%s is in Second Phase\n", m->name);
      m->maxHp = 300;
      m->hp = 300;
      m->attack = 50;
      m->expReward = 500;
      m->goldReward = 500;
      m->ability = getRandomAbility();
    }
    break;
  case ABILITY_TIME_CONTROL: {
    int roll = rand() % 100;
    if (roll < 25 && m->hp > 0 && p->hp > 0) {
      printf("\n%s whisper: You dare challenge the time.....", m->name);
      printf("TIME HAS FROZEN! You can't move");

      int accumateDamage = 0;
      int hitCount = 0;

      while (accumateDamage < 30 && p->hp > 0) {
        int strike = 10;
        p->hp -= strike;
        accumateDamage += strike;
        if (p->hp <= 0) {
          printf("%s whisper: Let yourself be consumed by the time....",
                 m->name);
          printf("You died");
          break;
        }
        hitCount++;
      }
      printf("\nTime Flows again\n");
    }
  } break;

  default:
    break;
  }
}

Monster getRandomMonster() {
  int diceValue = rand() % 4;
  switch (diceValue) {
  case 0:
    createTroll();
    break;
  case 1:
    createViper();
    break;
  case 2:
    createChronoTheTime();
    break;
  case 3:
    createTheSunKing();
    break;
  default:
    createTroll();
    break;
  }
}