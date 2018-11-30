// Adam Powell
// CS362 Fall 2018
// card test 3
// Great Hall: 


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "Great Hall"


int asserttrue(int a, int b, int c)
{
	if (a != b)
	{
		printf("%s TEST FAILED test: %d\n", TESTCARD, c);
		return 1;
	}

	return 0;
}

int main() {
	int fFlag = 0;
	int newCards = 0;
	int discarded = 1;
	int xtraCoins = 0;
	int shuffledCards = 0;

	int i, j, m;
	int handPos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	int remove1, remove2;
	int seed = 1000;
	int numPlayers = 2;
	int thisPlayer = 0;

	struct gameState Game, testGame;
	int k[10] = { adventurer, embargo, village, minion, mine, cutpurse,
		sea_hag, tribute, smithy, council_room };

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &Game);

	memcpy(&testGame, &Game, sizeof(struct gameState));


	int result = cardEffect(great_hall, choice1, choice2, choice3, &testGame, handPos, &bonus);
	fFlag += asserttrue(result, 0,0);

	fFlag += asserttrue(testGame.handCount[testGame.whoseTurn], Game.handCount[Game.whoseTurn] ,1); // handsize should remain the same
	fFlag += asserttrue(testGame.playedCardCount, (Game.playedCardCount + 1),2); 
	fFlag += asserttrue(testGame.numActions, Game.numActions + 1,3); 

	

	if(fFlag == 0)
		printf("Test Succesful for card %s\n", TESTCARD);


	return 0;
}

