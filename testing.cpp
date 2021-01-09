#include <iostream>
#include "parsing.h"
#include "mergeSort.h"
#include "rolling.h"
#include <string>
#include <math.h>
#include <time.h>

using namespace std;

int main(){
	
	// First test: Can it parse correctly?
	
	string dicerolls[10] = {"d10","2d10","2d10dl1","2d10dh1","2d10+2","2d10-2","2d10<5","2d10=5","2d10>5","2d10dl1+5=3"};
	
	dicecode code;
	
	for(int i=0;i<10;i++){
		cout << dicerolls[i] << endl;
		code = parseEntry(dicerolls[i]);
		if(code.multiple){
			cout << "Multiple dice" << endl;
			cout << "Dice num: " << code.num << endl;
		}
		else{
			cout << "One die" << endl;
		}
		cout << "Die type: " << code.type << endl;
		cout << "Drop any?: ";
		if(code.drop){
			cout << "yes" << endl;
			cout << "drop type: " << code.droplh << ", drop num: " << code.dropnum << endl;
		}
		else{
			cout << "no" << endl;
		}
		cout << "Add or subtract?: ";
		if(code.addsub){
			cout << "yes" << endl;
			cout << "number: " << code.c << endl;
		}
		else{
			cout << "no" << endl;
		}
		cout << "Compare?: ";
		if(code.compare){
			cout << "yes" << endl;
			cout << "compare type: " << code.compareop << ", compare num: " << code.comparenum << endl;
		}
		else{
			cout << "no" << endl;
		}
		cout << "Success!\n\n" << endl;
	}
	
	// test mergesort
	/*int *arr = new int[5];
	int a[5] = {5,2,6,3,1};
	arr = a;
	for(int i=0;i<5;i++){
		cout << *(arr+i) << " ";
	}
	
	cout << endl;
	mergeSort(arr,0,5);
	
	for(int i=0;i<5;i++){
		cout << *(arr+i) << " ";
	}
	cout << endl;*/
	
	/*for(int i=1;i<10;i++){
		cout << (rand() % 100) << endl;
	}
	return 0;*/
	 
	// Second test: roll functions
	/*srand(time(NULL)); // seeds random
	int dicenum = 2;
	int dicetype = 4;
	int dropped = 1;
	int addconst = 0;
	int summedrolls = 0;
	int addedconst = 0;
	char compare = '>';
	int comparenum = 5;
	bool verbose = true;
	int *rolls = new int[dicenum];
	rolls = rollMult(dicenum,dicetype);
	cout << "Rolled " << dicenum << "d" << dicetype << "dl" << dropped << ": ";
	for(int i=0;i<dicenum;i++){
		cout << *(rolls+i) << ". ";
	}
	cout << endl;
	
	int *droppedRolls = new int[dicenum-dropped];
	droppedRolls = dropRolls(dicenum,rolls,'l',dropped,verbose);
	cout << "Dropping " << dropped << ": ";
	for(int i=0;i<dicenum-dropped;i++){
		cout << *(droppedRolls+i) << " ";
	}
	cout << endl;
	
	summedrolls = sumRolls(dicenum-dropped, droppedRolls);
	cout << "Sum: " << summedrolls << endl;
	
	addedconst = addMods(summedrolls, addconst);
	cout << "With mod: " << addedconst << endl;
	
	bool bigger = false;
	bigger = compareRoll(addedconst,compare,comparenum);
	if(bigger){
		cout << addedconst << compare << comparenum;
	}
	else{
		cout << comparenum << compare << addedconst;
	}
	
	cout << endl;*/
	
	// Third test: probability equations
	
	
}

