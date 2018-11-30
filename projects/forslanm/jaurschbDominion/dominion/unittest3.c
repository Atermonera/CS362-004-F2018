#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "rngs.h"

#define ERROR -1
#define assert(EX, msg) if (!(EX)) { printf(msg); return ERROR; }

int checkFullDeckCount(int p, int c, struct gameState *g){

	int r, i, count = 0;
	char buffer[256];
	r = fullDeckCount(p, c, g);
	
	for(i = 0; i < g->handCount[p]; i++)
		if(g->hand[p][i] == c)
			count++;
	
	for(i = 0; i < g->deckCount[p]; i++)
		if(g->deck[p][i] == c)
			count++;
	
	for(i = 0; i < g->discardCount[p]; i++)
		if(g->discard[p][i] == c)
			count++;

	sprintf(buffer, "TEST FAIL: FullDeckCount incorrect count\n p%d | c%d | r%d | count%d\n", p, c, r, count);
	assert(r == count, buffer);
	return 0;
}

int main () {
	int i, c, n, r, p, deckCount, discardCount, handCount;
	int passflag = 1;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};

	struct gameState G;
  
	printf ("Testing updateCoins.\n");

	printf ("RANDOM TESTS.\n");

	SelectStream(2);
	PutSeed(3);

	for (n = 0; n < 2000; n++) {
		for (i = 0; i < sizeof(struct gameState); i++) {
			((char*)&G)[i] = floor(Random() * 256);
		}
		p = floor(Random() * 2);
		G.deckCount[p] = floor(Random() * MAX_DECK);
		G.discardCount[p] = floor(Random() * MAX_DECK);
		G.handCount[p] = floor(Random() * MAX_HAND);
		c = floor(Random() * (treasure_map+1));
		if(checkFullDeckCount(p, c, &G) == ERROR)
			passflag = 0;
	}
	if(passflag)
		printf ("ALL TESTS OK\n");

	exit(0);
  
	printf ("SIMPLE FIXED TESTS.\n");
	for (p = 0; p < 2; p++) {
		for (deckCount = 0; deckCount < 5; deckCount++) {
			for (discardCount = 0; discardCount < 5; discardCount++) {
				for (handCount = 0; handCount < 5; handCount++) {
					memset(&G, 23, sizeof(struct gameState)); 
					r = initializeGame(2, k, 1, &G);
					G.deckCount[p] = deckCount;
					memset(G.deck[p], 0, sizeof(int) * deckCount);
					G.discardCount[p] = discardCount;
					memset(G.discard[p], 0, sizeof(int) * discardCount);
					G.handCount[p] = handCount;
					memset(G.hand[p], 0, sizeof(int) * handCount);
					c = floor(Random() * (treasure_map+1));
					checkFullDeckCount(p, c, &G);
				}
			}
		}
	}

	return 0;
}
