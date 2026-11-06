#include "../Header/player.h"
#include <stdio.h>

int addWeaponToBag(Player *p, int weaponId) {
  if (p->bagCount == MAX_BAG) {
    printf("You can't add items to inventory, the inventory is full.\n");
    return 0;
  }

  p->inverntory[p->bagCount] = weaponId;
  p->bagCount++;
  return 1;
};

const char *getWeaponName(int weaponId) { // why did we convert this function to
                                          // a pointer? by adding *
  switch (weaponId) {
  case 0:
    return "None";
    break;
  case 1:
    return "Dagger";
    break;
  case 2:
    return "Katana";
    break;

  default:
    printf("%d", weaponId);
    return "Unknown";
  }
} // why is this showing probility of error

void displayInventory(const Player *p) {
  printf("---------Inventory------------\n");
  for (int i = 0; i < p->bagCount; i++) {
    printf("\t%d:\t %s\n", i, getWeaponName(p->inverntory[i]));
  }
  printf("--------------------------------\n");
}

void equiqWeaponFromBag(Player *p) {
  int choice;
  printf("-----------------------------------\n");
  printf("Select weapon from inventory: \n");
  scanf("%d", &choice);
  printf("-----------------------------------\n");
  p->equippedWeapon = choice;
}

int calculatePlayerDamage(const Player *p) {
  switch (p->equippedWeapon) {
  case 0:
    return 10;
    break;
  case 1:
    return 20;
    break;
  case 2:
    return 30;
    break;
  default:
    return 0;
  }
}
