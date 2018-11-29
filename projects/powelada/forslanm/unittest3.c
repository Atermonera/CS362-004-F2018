// Adam Powell
// CS362 Fall 2018
// unit test 1
// test endTurn(): 

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
	int numPlayer = 4;
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
	
	for (int i = 1; i < 2 * numPlayer; i++)
	{
		int nReturn = endTurn(&testGame);

		#if (NOISY_TEST == 1)
			printf("Current player is %d, expected %d\n",testGame.whoseTurn, (i%numPlayer));
		#endif
		assert(testGame.whoseTurn == (i%numPlayer));

		#if (NOISY_TEST == 1)
			printf("Hand size is %d, expected 5\n", testGame.handCount[i%numPlayer]);
		#endif
		assert(testGame.handCount[i%numPlayer] == 5);

		#if (NOISY_TEST == 1)
			printf("Game phase is %d, expected 0\n", testGame.phase);
		#endif
			assert(testGame.phase == 0);

		#if (NOISY_TEST == 1)
			printf("Played card count is %d, expected 0\n", testGame.playedCardCount);
		#endif
			assert(testGame.playedCardCount == 0);

		#if (NOISY_TEST == 1)
			printf("Number of buys count is %d, expected 1\n", testGame.numBuys);
		#endif
			assert(testGame.numBuys == 1);

		#if (NOISY_TEST == 1)
			printf("Number of actions count is %d, expected 1\n", testGame.numActions);
		#endif
			assert(testGame.numActions == 1);
		
		#if (NOISY_TEST == 1)
			printf("Return is %d, expected 0\n", nReturn);
		#endif
			assert(nReturn == 0);
	}



	printf("All tests passed! for endTurn()\n");

	return 0;
}