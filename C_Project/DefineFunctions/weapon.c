#include "../Header/weapon.h"
#include <string.h>

Weapon createDagger() {
  Weapon w;
  w.id = 1;
  strcpy(w.name, "DAGGER");
  w.attackDamage = 10;
  w.price = 10;
  w.critChance = 25;
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
  w.ability = WEAPON_ABILITY_NONE;
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
// here we define those functions