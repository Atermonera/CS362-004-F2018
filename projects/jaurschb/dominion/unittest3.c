#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
//#include <assert.h>

#define assert(EX, msg) if(!EX){ printf(msg);};

int main(int argc, char const *argv[]) {
  printf("\n--- TESTING FULLDECKCOUNT ---\n");

  struct gameState game;
  int cards[10] = { adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy };
  initializeGame(2, cards, 5, &game);

  int card = rand() % 10;
  printf("card#: %d\n", card); //remove later
  //Check Functions count of deckcount
  int countedcards = fullDeckCount(1, card, &game);

  //Manually check deck count of card
  int i;
  int count = 0;
  for(i = 0; i < game.handCount[1]; i++){
    if(game.hand[1][i] == card){ count++; }
  }for(i = 0; i < game.deckCount[1]; i++){
    if(game.hand[1][i] == card){ count++; }
  }for(i = 0; i < game.discardCount[1]; i++){
    if(game.hand[1][i] == card){ count++; }
  }

  assert(count == countedcards, "\n-- FULLDECKCOUNT FAILED -- \n");

  printf("\n--- TESTING FULLDECKCOUNT COMPLETE ---\n");
  return 0;
}
