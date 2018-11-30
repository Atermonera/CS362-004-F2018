// Adam Powell
// CS362 Fall 2018
// unit test 1
// cardtest1 adventurer: 


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "adventurer"


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

	int btreasure = 0;
	int atreasure = 0;
	int ctreasure = 0;

	struct gameState Game, testGame;
	int k[10] = { adventurer, embargo, village, minion, mine, cutpurse,
		sea_hag, tribute, smithy, council_room };

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &Game);

	memcpy(&testGame, &Game, sizeof(struct gameState));

	for (i = 0; i < Game.handCount[Game.whoseTurn]; i++)
	{
		if (Game.hand[Game.whoseTurn][i] == copper || Game.hand[Game.whoseTurn][i] == silver || Game.hand[Game.whoseTurn][i] == gold)
			atreasure++;
	}

	int result = cardEffect(adventurer, choice1, choice2, choice3, &testGame, handPos, &bonus);
	fFlag += asserttrue(result, 0,0);
	fFlag += asserttrue(testGame.playedCardCount, (Game.playedCardCount + 1), 3);

	for (i = 0; i < testGame.handCount[testGame.whoseTurn]; i++)
	{
		if (testGame.hand[testGame.whoseTurn][i] == copper || testGame.hand[testGame.whoseTurn][i] == silver || testGame.hand[testGame.whoseTurn][i] == gold)
			btreasure++;
	}

	result = cardEffect(adventurer, choice1, choice2, choice3, &testGame, handPos, &bonus);
	fFlag += asserttrue(result, 0,0);
	fFlag += asserttrue(testGame.playedCardCount, (Game.playedCardCount + 2), 3);

	for (i = 0; i < testGame.handCount[testGame.whoseTurn]; i++)
	{
		if (testGame.hand[testGame.whoseTurn][i] == copper || testGame.hand[testGame.whoseTurn][i] == silver || testGame.hand[testGame.whoseTurn][i] == gold)
			ctreasure++;
	}

	fFlag += asserttrue(btreasure, atreasure + 2,1); // test that two new treasures were added.
	fFlag += asserttrue(ctreasure, atreasure + 4,2);



	if(fFlag == 0)
		printf("Test Succesful for card %s\n", TESTCARD);


	return 0;
}

