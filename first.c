#include <stdio.h>
FILE *file;

int main() {
  int gold;
  int hp;
  int portions = 0;
  int hasKatana = 0;

  int portionPrice = 80;
  int daggerPrice = 50;
  int katanaPrice = 100;
  int petPrice = 1000;

  int choice;

  {
    file = fopen("save.txt", "r");
    if (file != NULL) {
      fscanf(file, "%d %d %d %d", &gold, &hp, &portions, &hasKatana);
      fclose(file);
      printf("Loaded Game Successful with Current Balance of %d. Hp: %d, "
             "Portions: %d, hasKatana: %d\n",
             gold, hp, portions, hasKatana);
    } else {
      gold = 120;
      hp = 100;
      portions = 0;
      hasKatana = 0;
      printf("New Game Started. Balance: %d\n", gold);
    }
  }

  printf("You arrive at the Outpost Merchant.\n");
  printf("You have: %d Gold Coin.\n", gold);

  if (gold < 50) {
    printf("You dont have enough Gold Coin to buy anything\n");
  } else {
    while (choice != 5) {
      printf("You can Buy: \n");
      {
        printf("Current Balance: %d\n", gold);
        printf("1. Katana (Cost: %d)\n", katanaPrice);
        printf("3. Dagger (Cost: %d)\n", daggerPrice);
        printf("2. Health Potion (Cost: %d)\n", portionPrice);
        printf("4. Pet (Cost: %d)\n", petPrice);
      };

      printf("Enter Option (1,2,3,4): ");
      scanf("%d", &choice);
      if (choice == 1) {
        if (gold >= katanaPrice) {
          gold = gold - katanaPrice;
          printf("You Bought a Katana (-%d) (Avl. Balance: %d)\n", katanaPrice,
                 gold);
          hasKatana = 1;
        } else {
          printf("You don't have enough Gold Coins to buy a Katana\n");
        }
      } else if (choice == 3) {
        if (gold >= portionPrice) {
          gold = gold - portionPrice;
          printf("You Bought a Health Potion (-%d) (Avl. Balance: %d)\n",
                 portionPrice, gold);
          portions++;
        } else {
          printf("You don't have enough Gold Coins to buy a Health Potion\n");
        }
      } else if (choice == 2) {
        if (gold >= daggerPrice) {
          gold = gold - daggerPrice;
          printf("You Bought a Dagger (-%d) (Avl. Balance: %d)\n", daggerPrice,
                 gold);
        } else {
          printf("You don't have enough Gold Coins to buy a Dagger\n");
        }
      } else if (choice == 4) {
        if (gold >= petPrice) {
          gold = gold - petPrice;
          printf("You Bought a Pet (-%d) (Avl. Balance: %d)\n", petPrice, gold);
        } else {
          printf("You don't have enough Gold Coins to buy a Pet\n");
        }
      } else if (choice == 5) {
        printf("Have a Good Day! You exit the Shop\n");
        printf("Avaliable Gold Coin: %d\n", gold);
        file = fopen("save.txt", "w");
        fprintf(file, "%d %d %d %d\n", gold, hp, portions, hasKatana);
        fclose(file);
        printf("Progress Saved");
      } else {
        printf("Invalid Choice.\n");
      }
    }
  }

  //   if (gold >= portionPrice) {
  //     gold = gold - portionPrice;
  //     printf("Health Postion (-%d) Bought!\n", portionPrice);
  //     printf("Balance %d Gold Coins\n", gold);
  //     portions++;
  //   } else {
  //     int needed = portionPrice - gold;
  //     printf(
  //         "You need %d Gold Coin more to buy a Health Portion. (Av. Balance:
  //         %d " "Gold Coin)", needed, gold);
  //   };

  return 0;
};