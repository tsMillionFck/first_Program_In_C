#include "../Header/weapon.h"
#include "stdio.h"
#include "stdlib.h"
#include <string.h>

Weapon createDagger() {
  Weapon w;
  w.id = 1;
  strcpy(w.name, "DAGGER");
  w.attackDamage = 10;
  w.price = 10;
  w.critChance = 30;
  w.expBoost = 0;
  w.durability = 20;
  w.maxDurability = 20;
  strcpy(w.weaponTier, "Common");
  w.ability = WEAPON_ABILITY_NONE;
  return w;
}

Weapon createKatana() {
  Weapon w;
  w.id = 2;
  strcpy(w.name, "KATANA");
  w.attackDamage = 30;
  w.price = 100;
  w.critChance = 20;
  w.expBoost = 10;
  w.durability = 50;
  w.maxDurability = 50;
  strcpy(w.weaponTier, "Common");
  w.ability = WEAPON_ABILITY_LIFESTEAL;
  return w;
}

Weapon createTimeSlayer() {
  Weapon w;
  w.id = 3;
  strcpy(w.name, "TIME SLAYER");
  w.attackDamage = 50;
  w.price = 300;
  w.critChance = 15;
  w.expBoost = 30;
  w.durability = 100;
  w.maxDurability = 100;
  strcpy(w.weaponTier, "RATE");
  w.ability = WEAPON_ABILITY_TIME_SLAYER;
  return w;
}

Weapon createOmegaKatana() {
  Weapon w;
  w.id = 4;
  strcpy(w.name, "OMEGA KATANA");
  w.attackDamage = 100;
  w.price = 1000;
  w.critChance = 5;
  w.expBoost = 50;
  w.durability = 100;
  w.maxDurability = 100;
  strcpy(w.weaponTier, "LEGENDARY");
  w.ability = WEAPON_ABILITY_OMEGA_SLASH;
  return w;
}

Weapon getWeaponById(int id) {
  switch (id) {
  case 1:
    return createDagger();
    break;
  case 2:
    return createKatana();
    break;
  case 3:
    return createTimeSlayer();
    break;
  case 4:
    return createOmegaKatana();
    break;
  default:
    printf("Error in getting weapon");
    break;
  }
}

const char *getWeaponAbilityName(WeaponAbility a) {
  switch (a) {
  case WEAPON_ABILITY_NONE:
    return "NONE";
    break;
  case WEAPON_ABILITY_FIRE:
    return "Fire";
    break;
  case WEAPON_ABILITY_TIME_SLAYER:
    return "Time Slayer";
    break;
  case WEAPON_ABILITY_LIFESTEAL:
    return "Lifesteal";
    break;
  case WEAPON_ABILITY_OMEGA_SLASH:
    return "Omega Slash";
    break;
  }
}

int executeWeaponAttack(const Weapon *w, Player *p, Monster *m) {
  int totalDamage = w->attackDamage;
  if (rand() % 100 < w->critChance) {
    m->hp -= w->attackDamage * 2;
    printf("Critical HIT was done to %s (using weapon: %s with 2x Damage: %d)",
           m->name, w->name, w->attackDamage * 2);
  }
  m->hp -= w->attackDamage;

  switch (w->ability) {
  case WEAPON_ABILITY_FIRE: {
    int burnDamage = 15;
    totalDamage += burnDamage;
    printf("Fire damage was done to %s (Using ability: Fire) of %d", m->name,
           totalDamage);
  } break;
  case WEAPON_ABILITY_LIFESTEAL: {
    int healAmount = totalDamage / 3;
    p->hp += healAmount;
    if (p->hp > p->maxHp) {
      p->hp = p->maxHp;
    }
  }
  }
}

void weaponSTAT(Weapon *w) {
  printf("Name: %s\n", w->name);
  printf("Attack Damage: %d\n", w->attackDamage);
  printf("Crit Chance: %d\n", w->critChance);
  printf("Exp Boost: %d\n", w->expBoost);
  printf("Durability: %d/%d\n", w->durability, w->maxDurability);
  printf("Weapon Tier: %s\n", w->weaponTier);
  printf("Ability: %s\n", getWeaponAbilityName(w->ability));
}
// here we define those functions;