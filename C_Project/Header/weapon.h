#ifndef WEAPON_H
#define WEAPON_H
#include "monster.h"
#include "player.h"

typedef enum {
  WEAPON_ABILITY_NONE = 0,
  WEAPON_ABILITY_FIRE,        // gives extra damage to due to fire. +15
  WEAPON_ABILITY_TIME_SLAYER, // 20% chance of stricking twice
  WEAPON_ABILITY_LIFESTEAL,   // Heals the player on hit
  WEAPON_ABILITY_OMEGA_SLASH  // 5% chances of slaying to monster in one slash
                             // but will reduce to 100% durability
} WeaponAbility;

typedef struct {
  int id;
  char name[30];
  int attackDamage;
  int price;
  int critChance;
  int expBoost;
  int durability;
  int maxDurability;
  int weaponTier;
  WeaponAbility ability;
} Weapon;

// here we declear function we are going to use in the main functions.

Weapon createDagger();
Weapon createKatana();
Weapon createTimeSlayer();
Weapon createOmegaKatana();
Weapon getWeaponById(int id);
const char *getWeaponAbilityName(
    WeaponAbility a); // const will make the data real only, char will let us
                      // have returned data as character, * will give the memory
                      // location of first character.
int executeWeaponAttack(const Weapon *w, Player *p, Monster *m);
#endif