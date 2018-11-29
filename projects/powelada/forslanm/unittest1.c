// Adam Powell
// CS362 Fall 2018
// unit test 1
// test isGameOver: 

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

	if(result != 0)
		printf("Failed to initialize game\n");
	assert(result == 0);

//test 1 supply pile depleted not province
	testGame.supplyCount[1] = 0;
	result = isGameOver(&testGame);
#if (NOISY_TEST == 1)
	printf("Result = %d, expected = 0\n", result);
#endif
	assert(result == 0);


	// Reset Game;
	memset(&testGame, 23, sizeof(struct gameState));   // clear the game state for testGame
	result = -1;
	result = initializeGame(numPlayer, k, seed, &testGame); // initialize a new game


	if (result != 0)
		printf("Failed to initialize game\n");
	assert(result == 0);

	//test 2 supply pile depleted not province
	testGame.supplyCount[2] = 0;
	testGame.supplyCount[5] = 0;
	result = isGameOver(&testGame);
#if (NOISY_TEST == 1)
	printf("Result = %d, expected = 0\n", result);
#endif
	assert(result == 0);

	// Reset Game;
	memset(&testGame, 23, sizeof(struct gameState));   // clear the game state for testGame
	result = -1;
	result = initializeGame(numPlayer, k, seed, &testGame); // initialize a new game


	if (result != 0)
		printf("Failed to initialize game\n");
	assert(result == 0);


	//test 3 supply pile depleted not province
	testGame.supplyCount[4] = 0;
	testGame.supplyCount[6] = 0;
	testGame.supplyCount[7] = 0;
	result = isGameOver(&testGame);
#if (NOISY_TEST == 1)
	printf("Result = %d, expected = 1\n", result);
#endif
	assert(result == 1);

	// Reset Game;
	memset(&testGame, 23, sizeof(struct gameState));   // clear the game state for testGame
	result = -1;
	result = initializeGame(numPlayer, k, seed, &testGame); // initialize a new game


	if (result != 0)
		printf("Failed to initialize game\n");
	assert(result == 0);


	//test province supply pile depleted not province
	testGame.supplyCount[3] = 0;
	result = isGameOver(&testGame);
#if (NOISY_TEST == 1)
	printf("Result = %d, expected = 1\n", result);
#endif
	assert(result == 1);

	// Reset Game;
	memset(&testGame, 23, sizeof(struct gameState));   // clear the game state for testGame
	result = -1;
	result = initializeGame(numPlayer, k, seed, &testGame); // initialize a new game

#if (NOISY_TEST == 1)
	if (result != 0)
		printf("Failed to initialize game\n");
#endif
	assert(result == 0);


	//test all supply piles depleted not province
	for(int j=0; j < 10; j++)
		testGame.supplyCount[j] = 0;
	result = isGameOver(&testGame);
#if (NOISY_TEST == 1)
	printf("Result = %d, expected = 1\n", result);
#endif
	assert(result == 1);


	printf("All tests passed! for isGameOver()\n");

	return 0;
}