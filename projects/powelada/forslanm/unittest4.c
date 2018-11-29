// Adam Powell
// CS362 Fall 2018
// unit test 1
// test shuffle: 

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 0

int main() {
	int seed = 1000;
	int numPlayer = 2;
	int player = 0; // test player 
	int k[10] = { adventurer, council_room, feast, gardens, mine
		, remodel, smithy, village, baron, great_hall };
	struct gameState testGame;

	memset(&testGame, 23, sizeof(struct gameState));   // clear the game state for testGame
	int result = -1;
	result = initializeGame(numPlayer, k, seed, &testGame); // initialize a new game

#if (NOISY_TEST == 1)
	if (result != 0)
		printf("Failed to initialize game\n");
#endif
	assert(result == 0);


	// add two of each kingdom card
	for (int i = 0; i < 20; i++)
	{
		result = gainCard(k[i % 10], &testGame, 1, player);
	}

	int newDeck[MAX_DECK];

	for (int i = 0; i < testGame.deckCount[player]; i++) {
		newDeck[i] = testGame.deck[player][i];
	}

	int test = shuffle(player, &testGame);

#if (NOISY_TEST == 1)
	if (test != 0)
		printf("Failed to shuffle deck\n");
#endif
	assert(test == 0);

	test = 0;

	for (int i = 0; i < testGame.deckCount[player]; i++) {
		if 	(newDeck[i] != testGame.deck[player][i])
		{
			test = 1;
		}
		
	}

#if (NOISY_TEST == 1)
	if (test != 0)
		printf("Deck Order has been changed\n");
	else
		printf("Deck Order has failed to be changed\n");
#endif
	assert(test == 1);


	printf("All tests passed! for shuffle()\n");

	return 0;
}