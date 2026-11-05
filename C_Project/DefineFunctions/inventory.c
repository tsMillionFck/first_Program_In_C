#include "../Header/player.h"
#include <stdio.h>

int addWeaponToBag(Player *p, int weaponId) {
  if (p->bagCount == MAX_BAG) {
    printf("You can't add items to inventory, the inventory is full.");
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
  case 3:
    return "Katana";
    break;
  }
} // why is this showing probility of error

void displayInventory(const Player *p) {
  for (int i = 0; i < p->bagCount - 1; i++) {
    printf("%s", getWeaponName(p->inverntory[i]));
  }
}

void equiqWeaponFromBag(Player *p) {
  short int choice;
  printf("-----------------------------------");
  printf("Select weapon from inventory: ");
  scanf("%d", &choice);
  printf("-----------------------------------");
  p->equippedWeapon = choice;
}
