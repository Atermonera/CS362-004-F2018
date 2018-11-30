#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
//#include <assert.h>

#define assert(EX, msg) if(!EX){ printf(msg);};

int main(){

  printf("\n--- TESTING ADVENTURER ---\n");

  //cardEffect game
  struct gameState game1;
  int cards[10] = { adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy };
  initializeGame(4, cards, 5, &game1);
  int player = whoseTurn(&game1);

  //create copy of game state for manual testing
  struct gameState game2;
  memcpy(&game2, &game1, sizeof(struct gameState));

  cardEffect(adventurer, 0, 0, 0, &game1, game1.handCount[player], 0);

  //Manually act out adventurer
  int newplayer = whoseTurn(&game2);
  int treasurefound = 0;
  int timesShuffled = 0;
  int cardDrawn;
  while(treasurefound < 3){
    if(!game2.deckCount[newplayer] && timesShuffled++){
      break; //don't keep going through the deck if theres no treasure
    }drawCard(newplayer, &game2);
    cardDrawn = game2.hand[newplayer][game2.handCount[newplayer] - 1];
    //top card of hand is the card drawn
    if(cardDrawn == copper || cardDrawn == silver || cardDrawn == gold){
      treasurefound++;
    }else{
      discardCard(game2.handCount[newplayer], newplayer, &game2, 0);
    }
  }discardCard(game2.handCount[newplayer] - 1, newplayer, &game2, 0);

  //see if the games are similar
  assert(memcmp(&game1, &game2, sizeof(struct gameState)) == 0, "\n-- ADVENTURER FAILED --\n");

  printf("\n--- TESTING ADVENTURER COMPLETED ---\n");
  return 0;
}
