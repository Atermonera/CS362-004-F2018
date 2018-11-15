#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "rngs.h"

#define TRUE 1
#define FALSE 0

#define ERROR -1
#define assert(EX, msg) if (!(EX)) { printf(msg); return ERROR; }

int checkGreatHallEffect(int p, int h, struct gameState *post){
	struct gameState pre;
	memcpy(&pre, post, sizeof(struct gameState));

	int r;
// 	printf("PRE: p%d |  HaC%d | DeC%d | DiC%d | Ac%d\n", p, pre.handCount[p], pre.deckCount[p], pre.discardCount[p], pre.numActions);
   
	r = cardEffect(great_hall, 0, 0, 0, post, h, 0);

	drawCard(p, &pre);
	pre.numActions++;
	discardCard(h, p, &pre, 0);
//	printf("PO1: p%d |  HaC%d | DeC%d | DiC%d | Ac%d\n", p, pre.handCount[p], pre.deckCount[p], pre.discardCount[p], pre.numActions);
//	printf("PO2: p%d |  HaC%d | DeC%d | DiC%d | Ac%d\n", p, post->handCount[p], post->deckCount[p], post->discardCount[p], post->numActions);
	
	assert(r == 0, "TEST FAIL: great_hall returns non=0\n");
	assert(memcmp(&pre, post, sizeof(struct gameState)) == 0, "TEST FAIL: great_hall incorrect function\n");
	return 0;
}

int main(){
	int i, p, k;
	int passflag = TRUE;
	struct gameState G;
	
	SelectStream(2);
	PutSeed(3);
	
	printf("Testing adventurer.\n");
	
	for(i = 0; i < 1000; i++){
		G.numPlayers = floor(Random() * (MAX_PLAYERS - 1)) + 1; // Force non-0 number of players
		G.whoseTurn = floor(Random() * G.numPlayers);
		p = G.whoseTurn;
		G.deckCount[p] = floor(Random() * MAX_DECK);
		G.discardCount[p] = floor(Random() * MAX_DECK - G.deckCount[p]); // Can't have more cards in deck+discard than can fit in deck
		G.handCount[p] = floor(Random() * (MAX_HAND - G.deckCount[p] - G.discardCount[p]));
		G.playedCardCount = floor(Random() * (MAX_DECK - G.deckCount[p] - G.discardCount[p] - G.handCount[p]));
		
		// Populate deck
		for(k = 0; k < G.deckCount[p]; k++)
			G.deck[p][k] = floor(Random() * treasure_map);
		
		// Populate discard
		for(k = 0; k < G.discardCount[p]; k++)
			G.discard[p][k] = floor(Random() * treasure_map);
		
		// Populate hand
		for(k = 0; k < G.handCount[p] - 1; k++)
			G.hand[p][k] = floor(Random() * treasure_map);
		G.hand[p][G.handCount[p]] = treasure_map; // Last card in hand is the one we want to test
		
		// Populate played card
		for(k = 0; k < G.playedCardCount; k++)
			G.playedCards[k] = floor(Random() * treasure_map);
		
		if(checkGreatHallEffect(G.whoseTurn, G.handCount[p], &G) == ERROR)
			passflag = FALSE;
	}
	if(passflag) // Implicit TRUE check
		printf ("ALL TESTS OK\n");
	
	return 0;
}