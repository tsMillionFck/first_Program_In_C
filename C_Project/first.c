#include <stdio.h>
FILE *file;

typedef struct {
  int hp;
  int maxHp;
  int gold;
  int portions;
  int weapon;
  int hasPet;
  int experience;
  int level;
} Player;

void showPlayerState(Player *p) {
  printf("-----------------------------\n");
  printf("Health: %d / %d\n", p->hp,
         p->maxHp); // I want to write every printf myself;
  printf("Gold: %d\n", p->gold);
  printf("Portions: %d\n", p->portions);
  printf("Weapons: %d\n", p->weapon);
  printf("Pet: %d\n", p->hasPet);
  printf("Experience: %d\n", p->experience);
  printf("Lever: %d\n", p->level);
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
    fprintf(file, "%d %d %d %d %d %d %d %d\n", p->gold, p->hp, p->maxHp,
            p->portions, p->weapon, p->hasPet, p->experience, p->level);
    fclose(file);
    printf("Progress Saved");
  } else {
    printf("File Can't be Saved!");
  }
}

void enterDungeon(Player *p) {
  int choice;
  printf("Entered The Dungeon.\n");
  printf("You have %d Health, %d Gold, %d Healing Portions, %d Katana\n", p->hp,
         p->gold, p->portions, p->weapon);
  printf("1. To Fight with Monster\n");
  printf("2. Exit the Dungeon.\n");
  scanf("%d", &choice);

  switch (choice) {
  case 1:
    if (p->weapon > 0) {
      int monsterHealth = 100;
      while (monsterHealth > 0) {
        printf("Monster Health: %d\n", monsterHealth);
        int damage = 30;
        int monsterDamage = 10;
        int choice;

        printf("1. To Attack Monster with Katana\n");
        printf("2. To Drink Portion\n");
        printf("3. To Exit\n");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
          printf("You did %d Damage to Monster\n", damage);
          monsterHealth = monsterHealth - damage;
          if (monsterHealth < 0) {
            printf("Monster Health: 0\n");
            p->gold = p->gold + 50;
            printf("You killed the Monster and Earned 50 Gold Coins(Total "
                   "Gold: %d)\n",
                   p->gold);
          } else {
            printf("Monster Health: %d\n", monsterHealth);
            printf("Monster Did %d Damage to You\n", monsterDamage);
            p->hp = p->hp - monsterDamage;
            printf("Your Health: %d\n", p->hp);
          }

          break;

        case 2:
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

        case 3:
          printf("Exiting the Fight (cause 20 golds)");
          p->gold = p->gold - 20;
          break;
        }

        if (p->hp == 0) {
          printf("Game Over\n");
          break;
        }
      }
    } else {
      printf("You don't have any weapon to Attack.");
    }

    break;
  case 2:
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
        p->weapon = 1;
      } else {
        printf("You don't have enough Gold Coins to buy a Katana\n");
      }
    } else if (choice == 2) {
      if (p->gold >= daggerPrice) {
        p->gold = p->gold - daggerPrice;
        printf("You Bought a Dagger (-%d) (Avl. Balance: %d)\n", daggerPrice,
               p->gold);
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

  while (choice != 4) {
    printf("You arrive at a safe house\n");
    printf("You have %d Health, %d Gold, %d Healing Portions, %d Katana\n",
           p->hp, p->gold, p->portions, p->weapon);
    printf("-----------------------------\n");
    printf("Enter Merchant Shop (Option 1)\n");
    printf("Enter Dungeon (Option 2)\n");
    printf("Check Stats (Option 3)\n");
    printf("Exit Game (Option 4)\n");
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
    fscanf(file, "%d %d %d %d %d %d %d %d\n", &p->gold, &p->hp, &p->maxHp,
           &p->portions, &p->weapon, &p->hasPet, &p->experience, &p->level);
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
    printf("New game has started\n");
  }
}

int main() {
  Player player;

  loadGame(&player);

  home(&player);

  return 0;
}