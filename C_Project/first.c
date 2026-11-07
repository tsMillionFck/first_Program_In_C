#include "./Header/monster.h"
#include "./Header/player.h"
#include <stdio.h>
FILE *file;

void checkLevelUp(Player *p) {
  int baseCount = 100;
  if (p->experience > baseCount) {
    p->experience = 0;
    p->level = p->level + 1;
    baseCount = baseCount + 100;
    printf("-------------------------------\n");
    printf("Level Increase by 1. (Level: %d)\n", p->level);
    p->maxHp = p->maxHp + 20;
    p->hp = p->maxHp;
    printf("Max health increased to %d, Fully healed %d / %d\n", p->maxHp,
           p->hp, p->maxHp);
    printf("-------------------------------\n");
  }
}

void restRestore(Player *p) {
  if (p->hp != p->maxHp && p->gold >= 20) {
    printf("Using 20 Gold to restore Health. Current HP %d / %d", p->hp,
           p->maxHp);
    p->gold = p->gold - 20;
    p->hp = p->maxHp;
    printf("Restore Health to Fullest. %d / %d", p->hp, p->maxHp);
  } else {
    printf("Either you are short on Gold %d (Required 20), or have full Health "
           "%d / %d",
           p->gold, p->hp, p->maxHp);
  }
}

void showPlayerState(Player *p) {
  printf("-----------------------------\n");
  printf("Health: %d / %d\n", p->hp,
         p->maxHp); // I want to write every printf myself;
  printf("Gold: %d\n", p->gold);
  printf("Health Portions: %d\n", p->portions);
  printf("-----Weapons-----");
  displayInventory(p);
  printf("-----------------");
  printf("Pet: %d\n", p->hasPet);
  printf("Experience: %d\n", p->experience);
  printf("Level: %d\n", p->level);
  printf("-----------------------------\n");
};

void printShowMenu(int gold, int portionPrice, int daggerPrice, int katanaPrice,
                   int petPrice) {
  printf("Current Balance: %d\n", gold);
  printf("1. Katana (Cost: %d)\n", katanaPrice);
  printf("2. Dagger (Cost: %d)\n", daggerPrice);
  printf("3. Health Potion (Cost: %d)\n", portionPrice);
  printf("4. Pet (Cost: %d)\n", petPrice);
  printf("5. To Exit\n");
};

void saveGame(const Player *p) {
  file = fopen("save.txt", "w");
  if (file != NULL) {
    fprintf(file, "%d %d %d %d %d %d %d %d %d\n", p->gold, p->hp, p->maxHp,
            p->portions, p->equippedWeapon, p->hasPet, p->experience, p->level,
            p->bagCount);

    for (int i = 0; i < MAX_BAG; i++) {
      fprintf(file, "%d ", p->inverntory[i]);
    }

    fprintf(file, "\n");
    fclose(file);
    printf("Progress Saved");
  } else {
    printf("File Can't be Saved!");
  }
}

void enterDungeon(Player *p) {
  int choice;
  printf("Entered The Dungeon.\n");
  printf("-------------------------------\n");
  printf("1. To Fight with Monster\n");
  printf("2. Exit the Dungeon.\n");
  printf("3. To see upcoming Monster.\n");
  printf("-------------------------------\n");
  scanf("%d", &choice);
  Monster troll = createTroll();
  printf("Monster Name: %s\n", troll.name);

  switch (choice) {
  case 1:
    while (choice != 4 && troll.hp >= 0 && p->hp >= 0) {
      int damage = calculatePlayerDamage(p);
      int monsterDamage = troll.attack;

      printf("-----------Stats-------------\n");
      printf("Player Health: %d / %d\n", p->hp, p->maxHp);
      printf("Monster Health: %d / %d\n", troll.hp, troll.maxHp);
      printf("-----------Actions-----------\n");
      printf("1. To Attack Monster with %s\n",
             getWeaponName(p->equippedWeapon));
      printf("2. Open Weapon Inventory\n");
      printf("3. To Drink Portion\n");
      printf("4. To Exit\n");
      scanf("%d", &choice);

      switch (choice) {
      case 1:
        printf("You did %d Damage to Monster\n", damage);
        troll.hp = troll.hp - damage;
        if (troll.hp <= 0) {
          printf("Monster Health: 0\n");
          p->gold = p->gold + troll.goldReward;
          printf("You killed the Monster and Earned %d Gold Coins(Total "
                 "Gold: %d)\n",
                 troll.goldReward, p->gold);
          p->experience = p->experience + troll.expReward;
          printf("Experienced Increased to %d \n ", p->experience);
          checkLevelUp(p);
        } else {
          printf("Monster Health: %d\n", troll.hp);
          printf("Monster Did %d Damage to You\n", monsterDamage);
          p->hp = p->hp - monsterDamage;
          printf("Your Health: %d\n", p->hp);
        }

        break;

      case 2: {
        int choice = 0;
        displayInventory(p);
        while (choice != 2) {
          printf("1. Change Weapon. (Option 1)\n");
          printf("2. Return to Battle (Option 2)\n");
          printf("Select Option: ");
          scanf("%d", &choice);

          if (choice == 1) {
            equiqWeaponFromBag(p);
          }
        }
      } break;

      case 3:
        if (p->portions > 0 && p->hp < 100) {
          printf("Drinking Portion");

          p->portions = p->portions - 1;
          printf("Health Increased by 30\n");

          break;
        } else if (p->hp == 100) {
          printf("Your Health is Full");
          break;
        } else {
          printf("You have no Portion\n");
          break;
        }

      case 4:
        printf("Exiting the Fight (cause 20 golds)");
        p->gold = p->gold - 20;
        break;

      default:
        printf("Invalid Choice try Again\n");
        continue;
      }

      if (p->hp <= 0) {
        if (p->experience > 30) {
          p->experience = p->experience - 30;
          p->level = p->level - 1;
        } else {
          p->experience = 0;
          p->level = 0;
          p->gold = p->gold - 10;
        }
        printf("Game Over\n");
        break;
      }
    }
    break;
  case 2:
    printf("--UPCOMING MONSTER--\n");
    Monster troll2 = createTroll();
    printf("Name\t:\t %s\n", troll2.name);
    printf("Hp\t:\t %d\n", troll2.hp);
    printf("maxHp\t:\t %d\n", troll2.maxHp);
    printf("Attack\t:\t %d\n", troll2.attack);
    printf("ExpReward\t:\t %d\n", troll2.expReward);
    printf("GoldReward\t:\t %d\n", troll2.goldReward);
    printf("Ability\t:\t %d\n", troll2.ability);
    printf("-----------------------");
    break;
  case 3:
    printf("Exiting Dungeon.\n");
    break;
  }
}

void enterMerchantShop(Player *p) {
  int portionPrice = 80;
  int daggerPrice = 50;
  int katanaPrice = 100;
  int petPrice = 1000;
  int choice = 0;

  printf("You arrive at the Outpost Merchant.\n");
  printf("You have: %d Gold Coin.\n", p->gold);

  while (choice != 5) {
    printf("You can Buy: \n");
    printShowMenu(p->gold, portionPrice, daggerPrice, katanaPrice, petPrice);

    printf("Enter Option (1,2,3,4,5): ");
    scanf("%d", &choice);
    if (choice == 1) {
      if (p->gold >= katanaPrice) {
        p->gold = p->gold - katanaPrice;
        printf("You Bought a Katana (-%d) (Avl. Balance: %d)\n", katanaPrice,
               p->gold);
        addWeaponToBag(p, WEAPON_KATANA);
        if (p->equippedWeapon == 0) {
          p->equippedWeapon = WEAPON_KATANA;
        }
      } else {
        printf("You don't have enough Gold Coins to buy a Katana\n");
      }
    } else if (choice == 2) {
      if (p->gold >= daggerPrice) {
        p->gold = p->gold - daggerPrice;
        printf("You Bought a Dagger (-%d) (Avl. Balance: %d)\n", daggerPrice,
               p->gold);
        addWeaponToBag(p, WEAPON_DAGGER);
        if (p->equippedWeapon == 0) {
          p->equippedWeapon = WEAPON_DAGGER;
        }
      } else {
        printf("You don't have enough Gold Coins to buy a Dagger\n");
      }
    } else if (choice == 3) {
      if (p->gold >= portionPrice) {
        p->gold = p->gold - portionPrice;
        printf("You Bought a Health Potion (-%d) (Avl. Balance: %d)\n",
               portionPrice, p->gold);
        (p->portions)++;
      } else {
        printf("You don't have enough Gold Coins to buy a Health Potion\n");
      }
    } else if (choice == 4) {
      if (p->gold >= petPrice) {
        p->gold = p->gold - petPrice;
        printf("You Bought a Pet (-%d) (Avl. Balance: %d)\n", petPrice,
               p->gold);
      } else {
        printf("You don't have enough Gold Coins to buy a Pet\n");
      }
    } else if (choice == 5) {
      printf("Have a Good Day! You exit the Shop\n");
      printf("Avaliable Gold Coin: %d\n", p->gold);
      saveGame(p);
      break;
    } else {
      printf("Invalid Choice.\n");
    }
  }
}

void home(Player *p) {
  int choice = 0;

  while (choice != 5) {
    printf("You arrive at a safe house\n");
    printf("You have %d Health, %d Gold, %d Healing Portions, %s Weapon\n",
           p->hp, p->gold, p->portions, getWeaponName(p->equippedWeapon));
    printf("-----------------------------\n");
    printf("Enter Merchant Shop (Option 1)\n");
    printf("Enter Dungeon (Option 2)\n");
    printf("Check Stats (Option 3)\n");
    printf("Rest to Restore Health (Option 4)\n");
    printf("Exit Game (Option 5)\n");
    printf("-----------------------------\n");
    printf("Enter Option: ");

    scanf("%d", &choice);

    switch (choice) {
    case 1:
      enterMerchantShop(p);
      break;
    case 2:
      enterDungeon(p);
      break;
    case 3:
      showPlayerState(p);
      break;
    case 4:
      restRestore(p);
      break;
    case 5:
      printf("Saving and leaving the game. Goodbye.\n");
      saveGame(p);
      break;
    default:
      printf("Invalid Choice");
      break;
    }
  }
}

void loadGame(Player *p) {
  file = fopen("save.txt", "r");
  if (file != NULL) {
    fscanf(file, "%d %d %d %d %d %d %d %d %d\n", &p->gold, &p->hp, &p->maxHp,
           &p->portions, &p->equippedWeapon, &p->hasPet, &p->experience,
           &p->level, &p->bagCount);

    for (int i = 0; i < MAX_BAG; i++) {
      fscanf(file, "%d", &p->inverntory[i]);
    }
    printf("Game Loaded Successful\n");
    fclose(file);
  } else {
    p->gold = 10;
    p->hp = 100;
    p->maxHp = 100;
    p->portions = 0;
    p->hasPet = 0;
    p->experience = 0;
    p->level = 0;
    p->bagCount = 0;
    p->equippedWeapon = 0;

    for (int i = 0; i < MAX_BAG; i++) {
      p->inverntory[i] = 0;
    }
    printf("New game has started\n");
  }
}

int main() {
  Player player = {0};

  loadGame(&player);

  home(&player);

  return 0;
}