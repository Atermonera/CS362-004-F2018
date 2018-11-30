#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
//#include <assert.h>

#define assert(EX, msg) if(!EX){ printf(msg);};

int main(){
  printf("\n--- TESTING WHOSETURN ---\n");

  struct gameState game;
  int cards[10] = { adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy };
  initializeGame(2, cards, 5, &game);

  //check whoseTurn
  int giventurn = whoseTurn(&game);

  assert(giventurn == game.whoseTurn, "\n-- WHOSETURN FAILED --\n");


  printf("\n--- TESTING WHOSETURN COMPLETE ---\n");
}
