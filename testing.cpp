#include <iostream>
#include "parsing.h"
#include "mergeSort.h"
#include "probability.h"
#include <string>
#include <math.h>
#include <time.h>

using namespace std;

int main(){
	
	// First test: Can it parse correctly?
	
	/*string dicerolls[9] = {"2d10","2d10dl1","2d10dh1","2d10+2","2d10-2","2d10<5","2d10=5","2d10>5","2d10dl1+5=3"};
	
	dicecode code;
	
	for(int i=0;i<9;i++){
		cout << dicerolls[i] << endl;
		code = parseEntry(dicerolls[i]);
		cout << "Dice num: " << code.num << endl;
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
	}*/
	
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
	
	// Second test: Probability functions
	
	/*for(int i=1;i<10;i++){
		cout << (rand() % 100) << endl;
	}
	return 0;*/
	 
	srand(time(NULL)); // seeds random
	int dicenum = 2;
	int dicetype = 20;
	int dropped = 1;
	bool verbose = true;
	int *rolls = new int[dicenum];
	rolls = rollMult(dicenum,dicetype);
	cout << "Rolled " << dicenum << "d" << dicetype << "dl" << dropped << ": ";
	for(int i=0;i<dicenum;i++){
		cout << *(rolls+i) << " ";
	}
	cout << endl;
	
	int *droppedRolls = new int[dicenum-dropped];
	droppedRolls = dropRolls(dicenum,rolls,'l',dropped,verbose);
	cout << "Dropping " << dropped << ": ";
	for(int i=0;i<dicenum-dropped;i++){
		cout << *(droppedRolls+i) << " ";
	}
	cout << endl;
	
}

