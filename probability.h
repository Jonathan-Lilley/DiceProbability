#ifndef PROBABILITY_H
#define PROBABILITY_H

/* Calculations file
 * 
 * This file contains the main calculation functions
 * It includes:
 * - roll dice -- rollDice(dicecode [struct])
 * - calculate averages of dice -- diceAvg(dicecode [struct])
 * - incorporate dropped dice -- dropProb(dicecode [struct]?)
 * - compare probabilities -- probabilityCompare(dicecode [struct])
 * - return probability of certain results 
 * 
 * More may be included later
 * 
 * Quick notes:
 * Die notation should be YdXd[l/h]Z+C[</=/>]A; where...
 * 		Y is the number of dice
 * 		X is the type of die
 * 		lh is drop/keep (low or high)
 * 		Z is the number to drop/keep
 * 		C is a constant modifier
 * 		[</<=/=/>=/>] indicates a desired comparison result
 * 		A is a constant comparison
 * 
 * quick lookups while my keyboard is borked
 * 7 8 9 0 & () *
 */

#include <iostream>
#include "parsing.h"
#include "mergeSort.h"
#include <math.h>

// Rolls a single die of type
int rollOne(int type){
	return ((rand()%1000)%type);
}

// Gets the rolls of multiple dice
int* rollMult(int num, int type){
	int* allRolls[num];
	for(int i;i<num;i++){
		*(allRolls+1) = rollOne(type);
	}
	return allRolls;
}

// Drops rolls
int* dropRolls(int num, int *rolls, int droptype, int drops){
	int* selectedRolls[num-drops];
	mergeSort(rolls);
	for(int i=0;i<num-drops;i++){
		if(droptype == 'h'){
			*(selectedRolls+i) = *(rolls+i);
		}
		else if(droptype == 'l'){
			*(selectedRolls+num-i-1) = *(rolls+num-i-1);
		}
	}
	return selectedRolls;
}

// Sums rolls
int sumRolls(int num, int *rolls){
	int summedRolls = 0;
	for(int i=0;i<num;i++){
		summedRolls += *(rolls + i);
	}
	return summedRolls;
}

// Adds modifiers
int addMods(int rollSum, int c){
	return rollSum + c;
}

// Comparison
bool compareRoll(int rollSum, char compareop, int comparenum){
	if(compareop == '<' && rollSum < comparenum){
		return true;
	}
	else if(compareop == '=' && rollSum == comparenum){
		return true;
	}
	else if(compareop == '>' && rollSum > comparenum){
		return true;
	}
	else{
		// include a cout for debugging here
		return false;
	}
}

#endif