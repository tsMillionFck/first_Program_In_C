#include <stdio.h>
FILE *file;
void printShowMenu(int gold, int portionPrice, int daggerPrice, int katanaPrice,
                   int petPrice) {
  printf("Current Balance: %d\n", gold);
  printf("1. Katana (Cost: %d)\n", katanaPrice);
  printf("2. Dagger (Cost: %d)\n", daggerPrice);
  printf("3. Health Potion (Cost: %d)\n", portionPrice);
  printf("4. Pet (Cost: %d)\n", petPrice);
  printf("5. To Exit\n");
};

void saveGame(int gold, int hp, int portion, int hasKatana) {
  file = fopen("save.txt", "w");
  if (file != NULL) {
    fprintf(file, "%d %d %d %d\n", gold, hp, portion, hasKatana);
    fclose(file);
    printf("Progress Saved");
  } else {
    printf("File Can't be Saved!");
  }
}

void enterDungeon(int *hp, int *gold, int *portions, int hasKatana) {
  int choice;
  printf("Entered The Dungeon.\n");
  printf("You have %d Health, %d Gold, %d Healing Portions, %d Katana\n", *hp,
         *gold, *portions, hasKatana);
  printf("1. To Fight with Monster\n");
  printf("2. Exit the Dungeon.\n");
  scanf("%d", &choice);

  switch (choice) {
  case 1:
    if (hasKatana > 0) {
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
            *gold = *gold + 50;
            printf("You killed the Monster and Earned 50 Gold Coins(Total "
                   "Gold: %d)\n",
                   *gold);
          } else {
            printf("Monster Health: %d\n", monsterHealth);
            printf("Monster Did %d Damage to You\n", monsterDamage);
            *hp = *hp - monsterDamage;
            printf("Your Health: %d\n", *hp);
          }

          break;

        case 2:
          if (*portions > 0 && *hp < 100) {
            printf("Drinking Portion");

            *portions = *portions - 1;
            printf("Health Increased by 30\n");

            break;
          } else if (*hp == 100) {
            printf("Your Health is Full");
            break;
          } else {
            printf("You have no Portion\n");
            break;
          }

        case 3:
          printf("Exiting the Fight (cause 20 golds)");
          *gold = *gold - 20;
          break;
        }

        if (*hp == 0) {
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

void enterMerchantShop(int *hp, int *gold, int *portions, int *hasKatana,
                       int *experience) {
  int portionPrice = 80;
  int daggerPrice = 50;
  int katanaPrice = 100;
  int petPrice = 1000;
  int choice = 0;

  printf("You arrive at the Outpost Merchant.\n");
  printf("You have: %d Gold Coin.\n", *gold);

  while (choice != 5) {
    printf("You can Buy: \n");
    printShowMenu(*gold, portionPrice, daggerPrice, katanaPrice, petPrice);

    printf("Enter Option (1,2,3,4,5): ");
    scanf("%d", &choice);
    if (choice == 1) {
      if (*gold >= katanaPrice) {
        *gold = *gold - katanaPrice;
        printf("You Bought a Katana (-%d) (Avl. Balance: %d)\n", katanaPrice,
               *gold);
        *hasKatana = 1;
      } else {
        printf("You don't have enough Gold Coins to buy a Katana\n");
      }
    } else if (choice == 2) {
      if (*gold >= daggerPrice) {
        *gold = *gold - daggerPrice;
        printf("You Bought a Dagger (-%d) (Avl. Balance: %d)\n", daggerPrice,
               *gold);
      } else {
        printf("You don't have enough Gold Coins to buy a Dagger\n");
      }
    } else if (choice == 3) {
      if (*gold >= portionPrice) {
        *gold = *gold - portionPrice;
        printf("You Bought a Health Potion (-%d) (Avl. Balance: %d)\n",
               portionPrice, *gold);
        (*portions)++;
      } else {
        printf("You don't have enough Gold Coins to buy a Health Potion\n");
      }
    } else if (choice == 4) {
      if (*gold >= petPrice) {
        *gold = *gold - petPrice;
        printf("You Bought a Pet (-%d) (Avl. Balance: %d)\n", petPrice, *gold);
      } else {
        printf("You don't have enough Gold Coins to buy a Pet\n");
      }
    } else if (choice == 5) {
      printf("Have a Good Day! You exit the Shop\n");
      printf("Avaliable Gold Coin: %d\n", *gold);
      saveGame(*gold, *hp, *portions, *hasKatana);
      break;
    } else {
      printf("Invalid Choice.\n");
    }
  }
}

void home(int *hp, int *gold, int *portions, int *hasKatana, int *experience) {
  int choice = 0;

  while (choice != 3) {
    printf("You arrive at a safe house\n");
    printf("You have %d Health, %d Gold, %d Healing Portions, %d Katana\n", *hp,
           *gold, *portions, *hasKatana);
    printf("Enter Merchant Shop (Option 1)\n");
    printf("Enter Dungeon (Option 2)\n");
    printf("Enter Option: ");
    scanf("%d", &choice);

    switch (choice) {
    case 1:
      enterMerchantShop(hp, gold, portions, hasKatana, experience);
      break;
    case 2:
      enterDungeon(hp, gold, portions, *hasKatana);
      break;
    case 3:
      printf("Saving and leaving the game. Goodbye.\n");
      saveGame(*gold, *hp, *portions, *hasKatana);
      break;
    default:
      printf("Invalid Choice");
      break;
    }
  }
}

void loadGame(int *gold, int *hp, int *portion, int *hasKatana) {
  file = fopen("save.txt", "r");
  if (file != NULL) {
    fscanf(file, "%d %d %d %d", gold, hp, portion, hasKatana);
    printf("Game Loaded Successful\n");
    fclose(file);
  } else {
    *gold = 10;
    *hp = 100;
    *portion = 0;
    *hasKatana = 0;
    printf("New game has started\n");
  }
}

int main() {
  int gold;
  int hp;
  int portions = 0;
  int hasKatana = 0;
  int experience = 0;

  loadGame(&gold, &hp, &portions, &hasKatana);

  home(&hp, &gold, &portions, &hasKatana, &experience);

  return 0;
}