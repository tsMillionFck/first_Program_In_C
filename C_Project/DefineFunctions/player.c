#include "../Header/player.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int percentageChance() {
  srand(time(NULL));
  int randomValue = rand() % 100;
  return randomValue;
}