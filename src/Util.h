
#ifndef _Util_H_
#define _Util_H_


#include "Athlete.h"
#include "BinarySearchTree.h"
#include "HashedTable.h"

// Functions defined in the main file
void readInputFile(BinarySearchTree<Athlete*> &item, HashedTable * &hashPtr);
void readInputFile(BinarySearchTree<Athlete*> &item, HashedTable * &hashPtr);
void deleteMemory();
bool compareValue(Athlete * operand1, Athlete * operand2, string symbol);
Athlete* copyValue(Athlete* copyItem);
void indentedTree(Athlete * & anItem, int width);
bool compareHeap(Athlete * operand1, Athlete * operand2, string symbol);
bool checkDuplicate(Athlete * operand1, Athlete * operand2);
void displayLinkedList(Athlete * item);
bool checkError(string & input);
int isPrime(int input); /* Function that checks whether or not a given number is
* a prime number or not.
*/


#endif _Util_H_