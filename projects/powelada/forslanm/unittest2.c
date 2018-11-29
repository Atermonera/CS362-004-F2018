// Adam Powell
// CS362 Fall 2018
// unit test 2
// test gainCard(): 

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
	int k[10] = { adventurer, council_room, feast, gardens, mine
		, remodel, smithy, village, baron, great_hall };
	struct gameState testGame;
	
	memset(&testGame, 23, sizeof(struct gameState));   // clear the game state for testGame
	int result = -1;
	result = initializeGame(numPlayer, k, seed, &testGame); // initialize a new game

#if (NOISY_TEST == 1)
	if(result != 0)
		printf("Failed to initialize game\n");
#endif
	assert(result == 0);

	int iHandSizeP2 = testGame.handCount[1];
	int iDeckSizeP2 = testGame.deckCount[1];
	int iDiscardP2 = testGame.discardCount[1];

	int iSupply = testGame.supplyCount[3];
	int iHandSize = testGame.handCount[0];
	int iDeckSize = testGame.deckCount[0];
	int iDiscard = testGame.discardCount[0];
// p1 tests

	// gain card to hand
		result = gainCard(3, &testGame, 2, 0);
		#if (NOISY_TEST == 1)
			printf("Player %d hand size is %d, expected %d\n", 1, testGame.handCount[1], (iHandSize + 1));
		#endif
		assert(testGame.handCount[0] == (iHandSize + 1));
	// gain card to discard
		result = gainCard(3, &testGame, 0, 0);
		#if (NOISY_TEST == 1)
			printf("Player %d discard size is %d, expected %d\n", 1, testGame.discardCount[0], (iDiscard + 1));
		#endif
		assert(testGame.discardCount[0] == (iDiscard + 1));
	// gain card to deck
		result = gainCard(3, &testGame, 1, 0);
		#if (NOISY_TEST == 1)
			printf("Player %d deck size is %d, expected %d\n", 1, testGame.deckCount[1], (iDeckSize + 1));
		#endif
		assert(testGame.deckCount[0] == (iDeckSize + 1));
	// supply decreased
		#if (NOISY_TEST == 1)
			printf("Supply size is %d, expected %d\n", testGame.supplyCount[3], (iSupply - 3));
		#endif
		assert(testGame.supplyCount[3] == (iSupply - 3));

	// check other player remains constant
		#if (NOISY_TEST == 1)
			printf("Player %d hand size is %d, expected %d\n", 2,  testGame.handCount[1], iHandSizeP2);
		#endif
		assert(iHandSizeP2 == testGame.handCount[1]);

		#if (NOISY_TEST == 1)
			printf("Player %d deck size is %d, expected %d\n", 2, testGame.deckCount[1], iDeckSizeP2);
		#endif
		assert(iDeckSizeP2 == testGame.deckCount[1]);

		#if (NOISY_TEST == 1)
			printf("Player %d discard size is %d, expected %d\n", 2, testGame.discardCount[1], iDiscardP2);
		#endif
		assert(iDiscardP2 == testGame.discardCount[1]);

	// check 0 supply 
		testGame.supplyCount[3] = 0;
		result = gainCard(3, &testGame, 2, 0);
		#if (NOISY_TEST == 1)
			printf("Result is %d, expected -1\n", result);
		#endif
		assert(result == -1);
	
		//reset p1 initial values
		iHandSize = testGame.handCount[0];
		iDeckSize = testGame.deckCount[0];
		iDiscard = testGame.discardCount[0];

		iSupply = testGame.supplyCount[4];

	// gain card to hand
	result = gainCard(4, &testGame, 2, 1);
		#if (NOISY_TEST == 1)
			printf("Player %d hand size is %d, expected %d\n", 2, testGame.handCount[1], (iHandSize + 1));
		#endif
	assert(testGame.handCount[1] == (iHandSizeP2 + 1));
	// gain card to discard
	result = gainCard(4, &testGame, 0, 1);
		#if (NOISY_TEST == 1)
			printf("Player %d discard size is %d, expected %d\n", 2, testGame.discardCount[1], (iDiscardP2 + 1));
		#endif
	assert(testGame.discardCount[1] == (iDiscardP2 + 1));
	// gain card to deck
	result = gainCard(4, &testGame, 1, 1);
		#if (NOISY_TEST == 1)
			printf("Player %d deck size is %d, expected %d\n", 2, testGame.deckCount[1], (iDeckSizeP2 + 1));
		#endif
	assert(testGame.deckCount[1] == (iDeckSizeP2 + 1));
	// supply decreased
		#if (NOISY_TEST == 1)
			printf("Supply size is %d, expected %d\n", testGame.supplyCount[4], (iSupply - 3));
		#endif
	assert(testGame.supplyCount[4] == (iSupply - 3));

	// check other player remains constant

	#if (NOISY_TEST == 1)
			printf("Player %d hand size is %d, expected %d\n", 1, testGame.handCount[0], iHandSize);
	#endif
	assert(iHandSize == testGame.handCount[0]);

	#if (NOISY_TEST == 1)
			printf("Player %d deck size is %d, expected %d\n", 1, testGame.deckCount[0], iDeckSize);
	#endif
	assert(iDeckSize == testGame.deckCount[0]);

	#if (NOISY_TEST == 1)
		printf("Player %d discard size is %d, expected %d\n", 1, testGame.discardCount[0], iDiscard);
	#endif
	assert(iDiscard == testGame.discardCount[1]);

	printf("All tests passed! for gainCard()\n");

	return 0;
}