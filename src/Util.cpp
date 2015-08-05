#include "stdafx.h"
#include "Util.h"
#include "Athlete.h"
#include <iostream>
#include <fstream>
#include "HashedTable.h"

using namespace std; 

void readInputFile(BinarySearchTree<Athlete*> &item, HashedTable * &hashPtr)
{
	string name, age, country, year;
	ifstream inputFile;
	string fname;
	string blank;
	int count = 0;
	cout << "Please enter filename with extenstion: " << endl;
	getline(cin, fname);
	inputFile.open(fname.c_str());
	while (!inputFile.is_open())
	{
		cerr << "File opening error, please enter the correct file name and extension" << endl;
		getline(cin, fname);
		inputFile.open(fname.c_str());
	}



	while (inputFile.peek() != EOF)
	{
		getline(inputFile, blank);
		count++;
	}

	int arraySize = (count * 2);


	/* if the number is even, make it odd (2 is special case) */
	if (arraySize % 2 == 0 && arraySize != 2){
		arraySize += 1;
	}
	/* while its not a prime number, check the next odd number */
	while (!isPrime(arraySize)){
		arraySize += 2;
	}


	hashPtr = new HashedTable(arraySize);
	inputFile.close();

	inputFile.open(fname.c_str());

	while (inputFile.peek() != EOF && inputFile.peek() != 10)
	{
		getline(inputFile, name, ',');
		getline(inputFile, age, ',');
		getline(inputFile, country, ',');
		getline(inputFile, year);
		Athlete* temp = new Athlete(name, age, country, year);

		if (hashPtr->insert(temp))
			item.insert(temp, compareValue);
	}

	inputFile.close();
}

void deleteMemory()
{
	ifstream inputFile;
	inputFile.open("OutputFile.txt", std::ofstream::out | std::ofstream::trunc);
	inputFile.close();
}

bool compareValue(Athlete * operand1, Athlete * operand2, string symbol)
{
	if (symbol == "<")
	{
		return *operand1 < *operand2;
	}
	else if (symbol == ">")
	{
		return *operand1 > *operand2;
	}
	else if (symbol == "==")
	{
		return *operand1 == *operand2;
	}

	cout << "Invalid comparison symbol (<,>, ==)" << endl;
	return false;
}

Athlete* copyValue(Athlete* copyItem)
{
	Athlete *tempCopy = new Athlete(*copyItem);

	return tempCopy;
}

bool compareHeap(Athlete * operand1, Athlete * operand2, string symbol)
{
	if (symbol == "<")
	{
		return operand1->getNumSearch() < operand2->getNumSearch();
	}
	else if (symbol == ">")
	{
		return operand1->getNumSearch() > operand2->getNumSearch();
	}
	else if (symbol == "==")
	{
		return operand1->getNumSearch() == operand2->getNumSearch();
	}

	cout << "Invalid comparison symbol (<,>,==)" << endl;

	return false;
}

bool checkDuplicate(Athlete * operand1, Athlete * operand2)
{
	return *operand1 == *operand2;
}

void displayLinkedList(Athlete * item)
{
	item->printAll();
	cout << endl;
}

bool checkError(string & input)
{
	bool validInput;

	if (input.empty())
	{
		cout << "Need a name for athlete in order to work.\n";
		validInput = false;
	}

	if (!input.empty())
	{
		validInput = false;
		bool frontSpace = isspace(input[0]);
		bool backSpace = isspace(input[input.size() - 1]);

		for (unsigned int i = 0; i < input.size() && !validInput; i++)
		{
			if (isalnum(input[i]))
			{
				validInput = true;
			}
		}

		for (unsigned int i = 0; i < input.size() && validInput; i++)
		{
			while (frontSpace)
			{
				input.erase(0, 1);
				if (!isspace(input[0]))
					frontSpace = false;
			}

			while (backSpace)
			{
				input.erase(input.size() - 1, 1);
				if (!isspace(input[input.size() - 1]))
					backSpace = false;
			}
		}

		if (!validInput)
		{
			cout << "Name of athlete cannot contain space (' ') only.\n" << endl;
		}
	}

	return validInput;
}

int isPrime(int input){
	int i;

	int prime = true;

	if (input == 2){
		return true;
	}

	if (input % 2 == 0 || input <= 1){
		prime = false;
	}
	else {
		for (i = 3; i <= sqrt(input); i += 2){
			if (input%i == 0){
				prime = false;
			}
		}
	}
	return prime;
}
