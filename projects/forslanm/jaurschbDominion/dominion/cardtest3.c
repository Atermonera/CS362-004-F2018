#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "rngs.h"

#define ERROR -1
#define assert(EX, msg) if (!(EX)) { printf(msg); return ERROR; }

int checkVillageEffect(int p, int h, struct gameState *post){
	struct gameState pre;
	memcpy(&pre, post, sizeof(struct gameState));

	int r;
	r = cardEffect(village, 0, 0, 0, post, h, 0);
//	printf("PRE: p%d |  HaC%d | DeC%d | DiC%d | Ac%d\n", p, pre.handCount[p], pre.deckCount[p], pre.discardCount[p], pre.numActions);
	drawCard(p, &pre);
	pre.numActions += 2;
	discardCard(h, p, &pre, 0);
//	printf("PO1: p%d |  HaC%d | DeC%d | DiC%d | Ac%d\n", p, pre.handCount[p], pre.deckCount[p], pre.discardCount[p], pre.numActions);
//	printf("PO2: p%d |  HaC%d | DeC%d | DiC%d | Ac%d\n", p, post->handCount[p], post->deckCount[p], post->discardCount[p], post->numActions);
//	if(memcmp(&pre, post, sizeof(struct gameState))){
//		printf("PO1: p%d |  HaC%d | DeC%d | DiC%d | Ac%d\n", p, pre.handCount[p], pre.deckCount[p], pre.discardCount[p], pre.numActions);
//		printf("PO2: p%d |  HaC%d | DeC%d | DiC%d | Ac%d\n", p, post->handCount[p], post->deckCount[p], post->discardCount[p], post->numActions);
		
//		printf("Deck 1\t|\tDeck 2\n");
//		int i;
//		for(i = 0; i < pre.deckCount[p]; i++){
//			printf("%d\t|\t%d\n", pre.deck[p][i], post->deck[p][i]);
//		}
//	}
	
	assert(r == 0, "TEST FAIL: village returns non-0\n");
	assert(memcmp(&pre, post, sizeof(struct gameState)) == 0, "TEST FAIL: village incorrect function\n");
	return 0;
}

int main () {
	int i, n, r, p, deckCount, discardCount, handCount;
	int passflag = 1;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};

	struct gameState G;
  
	printf ("Testing village.\n");

	printf ("RANDOM TESTS.\n");

	SelectStream(2);
	PutSeed(3);

	for (n = 0; n < 2000; n++) {
		for (i = 0; i < sizeof(struct gameState); i++) {
			((char*)&G)[i] = floor(Random() * 256);
		}
		G.whoseTurn = floor(Random() * 2);
		p = G.whoseTurn;
		G.deckCount[p] = floor(Random() * MAX_DECK);
		G.discardCount[p] = floor(Random() * MAX_DECK);
		G.handCount[p] = floor(Random() * MAX_HAND);
		G.hand[p][G.handCount[p]] = village;
		G.numActions = floor(Random() * 10);
		if(checkVillageEffect(G.whoseTurn, G.handCount[p], &G) == ERROR)
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
					G.hand[p][G.handCount[p]] = village;
					checkVillageEffect(G.whoseTurn, G.handCount[p], &G);
				}
			}
		}
	}

	return 0;
}
