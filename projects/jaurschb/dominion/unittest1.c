#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
//#include <assert.h>

#define assert(EX, msg) if(!EX){ printf(msg);};

int checkGetCost(int Value, enum CARD cardgiven){
    int costgiven;
    costgiven = getCost(cardgiven);
    assert(costgiven == Value, "\n-- GETCOST FAILED TO RETURN CORRECT VALUE --\n");
    return 0;
}

int main(int argc, char const *argv[]) {
  int i = 0;
  enum CARD cardholder;
  int cardValue[27] = {0, 2, 5, 8, 0, 3, 6, 6, 5, 4, 4, 5, 4, 4, 3, 4,
    3, 5, 3, 5, 3, 4, 2, 5, 4, 4, 4};

  printf("\n--- TESTING GETCOST ---\n");
  for(i=0; i<27; i++){
    switch(i){
      case 0:
        cardholder = curse;
        break;
      case 1:
        cardholder = estate;
        break;
      case 2:
        cardholder = duchy;
        break;
      case 3:
        cardholder = province;
        break;
      case 4:
        cardholder = copper;
        break;
      case 5:
        cardholder = silver;
        break;
      case 6:
        cardholder = gold;
        break;
      case 7:
        cardholder = adventurer;
        break;
      case 8:
        cardholder = council_room;
        break;
      case 9:
        cardholder = feast;
        break;
      case 10:
        cardholder = gardens;
        break;
      case 11:
        cardholder = mine;
        break;
      case 12:
        cardholder = remodel;
        break;
      case 13:
        cardholder = smithy;
        break;
      case 14:
        cardholder = village;
        break;
      case 15:
        cardholder = baron;
        break;
      case 16:
        cardholder = great_hall;
        break;
      case 17:
        cardholder = minion;
        break;
      case 18:
        cardholder = steward;
        break;
      case 19:
        cardholder = tribute;
        break;
      case 20:
        cardholder = ambassador;
        break;
      case 21:
        cardholder = cutpurse;
        break;
      case 22:
        cardholder = embargo;
        break;
      case 23:
        cardholder = outpost;
        break;
      case 24:
        cardholder = salvager;
        break;
      case 25:
        cardholder = sea_hag;
        break;
      case 26:
        cardholder = treasure_map;
        break;
    }

    checkGetCost(cardValue[i], cardholder);
  }

  printf("\n--- TESTING GETCOST COMPLETED ---\n");
  return 0;
}
