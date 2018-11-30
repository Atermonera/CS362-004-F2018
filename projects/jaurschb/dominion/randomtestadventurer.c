#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
//#include <assert.h>

#define assert(EX, msg) if(!EX){ printf(msg); return -1; };

int randtestAdventurer(int player, struct gameState* game1){
  //create copy of game state for manual testing
  struct gameState game2;
  memcpy(&game2, game1, sizeof(struct gameState));

  cardEffect(adventurer, 0, 0, 0, game1, game1->handCount[player], 0);
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
  assert(memcmp(game1, &game2, sizeof(struct gameState)) == 0, "\n-- ADVENTURER TESTING FAILED --\n");
  return 0; //will return -1 if error, otherwise will return 0
}

int main(){

  printf("\n--- RANDOM TESTING ADVENTURER ---\n");
  //Setting up random environment
  int i, j, player;
  int failedtest = 0;
  struct gameState game1;

  SelectStream(2);
  PutSeed(3);

  //randomization of game state
  for(i = 0; i < 200; i++){
    for (j = 0; j < sizeof(struct gameState); j++) {
      ((char*)&game1)[j] = floor(Random() * 256);
    }
    game1.numPlayers = floor(Random() * 3) + 1; //results in 1-4
    player = floor(Random() * game1.numPlayers);
    game1.whoseTurn = player;
    game1.deckCount[player] = floor(Random() * MAX_DECK);
    game1.discardCount[player] = floor(Random() * (MAX_DECK - game1.deckCount[player]));
    game1.handCount[player] = floor(Random() * MAX_HAND);
    game1.playedCardCount = floor(Random() * (MAX_DECK - game1.deckCount[player]));

    //create random card combinations of the player's hand, discard, deck, and playedCards
    for(j=0; j<game1.handCount[player]; j++){
      game1.hand[player][j] = floor(Random() * 27);
    }game1.hand[player][game1.handCount[player]] = 27; //want to test this card
    for(j=0; j<game1.discardCount[player]; j++){
      game1.discard[player][j] = floor(Random() * 27);
    }for(j=0; j<game1.deckCount[player]; j++){
      game1.deck[player][j] = floor(Random() * 27);
    }for(j=0; j<game1.playedCardCount; j++){
      game1.playedCards[player] = floor(Random() * 27);
    }


    //test the card
    if(randtestAdventurer(player, &game1) == -1){
      failedtest = 1;
      break;
    };
  }
  if(failedtest == 0){
    printf("\n--- RANDOM TESTING ADVENTURER COMPLETED & PASSED ---\n");
  }
  return 0;
}
