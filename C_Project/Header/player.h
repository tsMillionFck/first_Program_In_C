#ifndef PLAYER_H
#define PLAYER_H
#define MAX_BAG 6

typedef enum {
  WEAPON_NONE = 0,
  WEAPON_DAGGER = 1,
  WEAPON_KATANA = 2,
} WeaponType;

typedef struct {
  int hp;
  int maxHp;
  int gold;
  int portions;
  int inverntory[MAX_BAG]; // used to set a limit to how much a player can
                           // carry. Kind of like a Slot system
  int bagCount;            // to track how many itmes a player is carrying.
  int equippedWeapon;      // which weapon the player has equipped.
  int experience;
  int level;
  int hasPet;
} Player;

int percentageChance(); // why do we use const in parameters of
                        // new player struct pointer

int addWeaponToBag(Player *p, int weaponId);
const char *getWeaponName(int weaponId);
void displayInventory(const Player *p);
void equiqWeaponFromBag(Player *p);
int calculatePlayerDamage(const Player *p);

#endif