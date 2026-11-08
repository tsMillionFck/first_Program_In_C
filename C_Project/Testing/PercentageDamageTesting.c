#include "../Header/player.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main() {
  srand(time(NULL));
  int rollDice = rand() % 4;
  printf("%d", rollDice);
  return 0;
}