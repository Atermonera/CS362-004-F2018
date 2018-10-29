#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
//#include <assert.h>

#define assert(EX, msg) if(!EX){ printf(msg);};

int main(){
  printf("\n--- TESTING ISGAMEOVER ---\n");

  struct gameState game;
	int cards[10] = { adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy };
	initializeGame(4, cards, 5, &game);

  int gameover = isGameOver(&game);
  assert(gameover == 0, "\n-- ISGAMEOVER FAILED --\n");


  printf("\n--- TESTING ISGAMEOVER COMPLETE ---\n");
  return 0;
}
