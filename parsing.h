#ifndef PARSING_H
#define PARSING_H

/* Parsing file
 * 
 * This file contains the main calculation functions
 * It includes:
 * - string to int functions (two part function)
 * - parse dice notation (return parsed data in a struct)
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
#include <string>
#include <math.h>

using namespace std;

// A struct to record the data from a parsed dicecode
typedef struct dicecode {
	int num = -1; // number of dice
	int type = -1; // type of die
	bool drop = false; // drop any?
	char droplh = '0'; // high or low
	int dropnum = -1; // how many drop?
	bool addsub = false; // add or sub a constant?
	int c = -1; // constant to add 
	bool compare = false; // compare to a value?
	char compareop = '0'; // what kind of comparison?
	int comparenum = -1; // what number to compare to?
} dicecode;

// Get an integer from a string
int stringToInt(string intString){
	int parsed = 0;
	int power;
	int curInt;
	//cout << "Parsing: " << intString << endl;
	//cout << "string length is " << intString.length() << endl;
	// loops through the int chars in the string
	// not making it into loop? why not...
	for(int i=0;i<intString.length();i++){
		//cout << "Hit loop!" << endl;
		power = pow(10,intString.length()-i-1); // gets current e level
		curInt = (intString[i] - '0'); // gets current integer
		//cout << "cur numb: " << curInt << ", power " << power << endl;
		parsed +=  curInt * power; // adds the current full int to parsed
	}
	return parsed;
}

// Checks if number is between 0 and 9
bool checkRange(int inp){
	if(inp-'0' >= 0 && inp-'0' <= 9){
		return true;
	}
	return false;
}

// Extracts string for stringToInt, then runs it through stringToInt
// pointers cuz im too lazy to figure out a different way to increment the counter outside of the function too
int getStringNum(int *counter, string stringNum){
	/*cout << "stringnum " << stringNum << endl;
	cout << "counter " << *counter << endl;*/
	string number;
	while(*counter < stringNum.length()){
		if(checkRange(stringNum[*counter])){
			number += stringNum[*counter];
			*counter+=1;
		}
		else{
			break;
		}
	}
	int stringint = stringToInt(number);
	return stringint;
}


dicecode parseEntry(string codeString){
	dicecode entry; // dicecode struct to return
	
	int counter = 0; // for looping through codeString
	char dk; // drop/keep char
	char addsub; // determines if add or subtract
	char compare; // determines if comparison
	
	
	// Dice number and type block; variables here: dicecode.num, dicecode.type
	// grab number of dice
	int a = getStringNum(&counter, codeString);
	entry.num = a; // This should get to ether 'd' or end of string
	// checks for end of string
	// If 'd' is the end of string or it hit the end of the string, return an error and entry
	// counter++ moves on from 'd', as its just a parsing point; if it hits the end of string, it means it didnt have
	//		anything after 'd', or it didnt have 'd' at all
	if(++counter >= codeString.length()){
		cout << "Error: incorrect input format. Proper formatting is YdX." << endl;
		return entry;
	}
	// grab type of die
	entry.type = getStringNum(&counter, codeString); // should get to either the next modifier or end of string
	// checks for end of string
	// End of string here is fine, it'd just be a full die notation with no modifiers; return the dicecode struct
	// Not counter++ because if the function stopped due to hitting a non-int, you need that for consecutive functions
	// Use >= on the offchance that its longer? not sure why it would be tho
	if(counter >= codeString.length()){
		return entry;
	}
	
	
	// Drop or keep block; varables here: dicecode.drop, dicecode.droplh, dicecode.dropnum
	// grab if drop or keep
	if(codeString[counter] == 'd'){
		char lh = codeString[++counter];
		entry.drop = true;
	}
	// catches if drop low or high
	if(codeString[counter] == 'l'){ // low
		entry.droplh = codeString[counter++];
	}
	if(codeString[counter] == 'h'){ // high
		 entry.droplh = codeString[counter++];
	}
	// default low
	else{
		 entry.droplh = 'l';
	}
	// checks for end of string
	// dont need counter++ because it already ++ in previous part
	if(counter >= codeString.length()){
		cout << "Error: incorrect input format. Proper formatting is YdX[d/k]Z." << endl;
		return entry;
	}
	// grabs dropnumber
	if(entry.drop){
		entry.dropnum = getStringNum(&counter, codeString);
	}
	// checks for end of string
	if(counter >= codeString.length()){
		return entry;
	}
	
	
	// grab if theres a constant; variables here: dicecode.addsub, dicecode.c
	char addsubchar;
	if(codeString[counter] == '+' or codeString[counter] == '-'){
		addsubchar = codeString[counter];
		entry.addsub = true;
	}
	// checks for end of string
	// dont need counter++ because it already ++ in previous part
	if(counter >= codeString.length()){
		cout << "Error: incorrect input format. Proper formatting is YdX[+/-]C." << endl;
		return entry;
	}
	// grabs constant number
	if(entry.addsub){
		// If add
		if(addsubchar == '+'){
			counter++;
			entry.c = getStringNum(&counter, codeString);
		}
		// If sub
		else if(addsubchar == '-'){
			counter++;
			entry.c = 0 - getStringNum(&counter, codeString);
		}
		// Catches if something weird happens
		else{
			cout << "Something went wrong in if statement at 163" << endl;
			return entry;
		}
	}
	// checks for end of string
	if(counter == codeString.length()){
		return entry;
	}
	
	
	// grab if comparison; variables here: dicecode.compare, dicecode.compareop, dicecode.comparenum
	char ops[3] = {'<','=','>'};
	for(int i=0;i<3;i++){
		if(codeString[counter] == ops[i]){
			entry.compare = true;
			entry.compareop = ops[i];
			counter++;
		}
	}
	// end of string check
	if(compare == codeString.length()){
		cout << "Error: incorrect input format. Proper formatting is YdX[</=/>]A." << endl;
		return entry;
	}
	// grab comparenum
	if(entry.compare){
		entry.comparenum = getStringNum(&counter, codeString);
	}
	
	// Final return, assuming everything functioned right.
	return entry;
	
}


#endif