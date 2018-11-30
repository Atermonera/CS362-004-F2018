#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "rngs.h"

#define ERROR -1
#define assert(EX, msg) if (!(EX)) { printf(msg); return ERROR; }

// Structurally similar to testDrawCard.c,
// performing the operation and memcmp()ing the result with a manual operation
int checkDiscardCard(int p, int h, int d, struct gameState *post){
	struct gameState pre;
	memcpy(&pre, post, sizeof(struct gameState));

	int r;
	
//	printf("discardCard PRE: p %d HC %d DeC %d DiC %d\n", p, pre.handCount[p], pre.deckCount[p], pre.discardCount[p]);
//	printf("p%d | h%d | t%d\n", p, h, d);
	r = discardCard(h, p, post, d);
	// printf ("drawCard POST: p %d HC %d DeC %d DiC %d\n", p, post->handCount[p], post->deckCount[p], post->discardCount[p]);

	// Ensure that there IS a hand to discard from
	// discardCard should have no effect if not
	if(pre.handCount){
		// If we aren't trashing the card, add it to the discard pile
		if(d != 1)
			pre.discard[p][pre.discardCount[p]++] = pre.hand[p][h]; // post-inc playedCardCount
		
		// Discarding the only card in hand, or the last card in hand
		if(pre.handCount[p] == 1 || (pre.handCount[p]-1) == h){
			pre.hand[p][h] = -1;
			pre.handCount[p]--;
		} 
		else{
			pre.hand[p][h] = pre.hand[p][pre.handCount[p]-1];
			pre.hand[p][--pre.handCount[p]] = -1; // Post-dec handCount
		}
	}
	
	assert(r == 0, "TEST FAIL: discardCard returns non0\n");
	assert(memcmp(&pre, post, sizeof(struct gameState)) == 0, "TEST FAIL: discardCard incorrect function\n");
	return 0;
}

int main () {
	int i, t, h, n, r, p, deckCount, discardCount, handCount;
	int passflag = 1;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};

	struct gameState G;
  
	printf ("Testing discardCard.\n");

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
		G.playedCardCount = floor(Random() * MAX_DECK);
		h = floor(Random() * G.handCount[p]); // Discard a random card
		t = floor(Random() * 2);	// Randomly trash or discard
		if(checkDiscardCard(p, h, t, &G) == ERROR)
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
					for(i = 0; i < handCount; i++){
						checkDiscardCard(p, i, 0, &G); // Check both trashing
						checkDiscardCard(p, i, 1, &G); // And discarding
					}
				}
			}
		}
	}

	return 0;
}
