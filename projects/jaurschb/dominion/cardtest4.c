#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
//#include <assert.h>

#define assert(EX, msg) if(!EX){ printf(msg); };

int main(){
  printf("\n--- TESTING GREATHALL ---\n");

  //cardEffect game
  struct gameState game1;
  int cards[10] = { adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy };
  initializeGame(4, cards, 5, &game1);
  int player = whoseTurn(&game1);

  //create copy of game state for manual testing
  struct gameState game2;
  memcpy(&game2, &game1, sizeof(struct gameState));

  cardEffect(great_hall, 0, 0, 0, &game1, game1.handCount[player], 0);

  //Manually act out great_hall
  int newplayer = whoseTurn(&game2);

  drawCard(newplayer, &game2);
  game2.numActions++;
  discardCard(game2.handCount[newplayer] - 1, newplayer, &game2, 0);


  //see if the games are similar
  assert(memcmp(&game1, &game2, sizeof(struct gameState)) == 0, "\n-- GREATHALL FAILED --\n");

  printf("\n--- TESTING GREATHALL COMPLETED ---\n");
  return 0;
}
