#include "stdafx.h"
#include "AthleteRecord.h"
#include "Athlete.h"
#include "List.h"
#include "LinkedList.h"
#include "Util.h"



Athlete * AthleteRecord::copyValue(Athlete * copyItem)
{
	Athlete * tempCopy = new Athlete(*copyItem);
	return tempCopy;
}

AthleteRecord::AthleteRecord()
{
	backupCount = 0;
	backupHashPtr = 0;
	hashPtr = 0;
	readInputFile(item, hashPtr);
	count = item.size();
}

void AthleteRecord::add(string input, string age, string country, string year)
{
	Athlete* temp = new Athlete(input, age, country, year);
	item.insert(temp, compareValue);
	hashPtr->insert(temp);
}

void AthleteRecord::deleteData(string input)
{
	cout << "You are in the deleteData function of DataRecord" << endl;
	bool success = false;
	Athlete * deleteItem = new Athlete(input, "unknown", "unknown", "unknown");

	heapSearch.update(deleteItem, compareHeap, checkDuplicate);

	success = item.remove(deleteItem, compareValue);

	if (success == true)
	{
		cout << input << " was deleted from BST." << endl;
	}
	else
		cout << input << " is not found in the BST." << endl;

	success = hashPtr->deleteAthlete(deleteItem);

	if (success == true)
	{
		cout << input << " was deleted from HashTable." << endl;
	}
	else
		cout << input << " is not found in HashTable." << endl;
}

bool AthleteRecord::search(string input)
{
	bool found = false;
	Athlete* returnedItem;

	found = hashPtr->findAthlete(input, returnedItem);
	if (found == false)
	{
		cout << input << " is not found among these athletes: " << endl;
		item.inOrder(print);
		cout << endl;
	}
	else
	{
		returnedItem->updateSearch();
		heapSearch.add(returnedItem, compareHeap, checkDuplicate);
		cout << endl;
		returnedItem->printAll();
		cout << endl;
	}

	return found;
}

void AthleteRecord::compare()
{
	string data;
	string choice1, choice2, choice3, choice4;
	char loc;
	int location;
	char key = ' ';
	int i = 1;
	bool found = false;
	List<Athlete*> compareList;
	Athlete * compareAthlete;
	bool validInput;

	cout << "What athletes would you like to compare? " << endl;

	do
	{
		cout << "\t First Athlete: ";
		getline(cin, choice1);

		validInput = checkError(choice1);

		if (validInput)
		{
			found = hashPtr->findAthlete(choice1, compareAthlete);
			if (found)
			{
				compareList.insert(compareAthlete, 1);
				i++;
			}
			if (!found)
			{
				bstKey();
			}
		}
	} while (!found || !validInput);

	do
	{
		cout << "\t Second Athlete: ";
		getline(cin, choice2);

		validInput = checkError(choice2);

		if (validInput)
		{

			found = hashPtr->findAthlete(choice2, compareAthlete);
			if (found)
			{
				compareList.insert(compareAthlete, 2);
				i++;
			}
			if (!found)
			{
				bstKey();
			}

		}
	} while (!found || !validInput);

	compareList.displayList(displayLinkedList);

	while (key != 'e')
	{
		if (i <= 4)
		{
			cout << "\t a. Compare another athlete" << endl;
		}
		cout << "\t p. Put athletes together" << endl;
		cout << "\t e. Exit to Menu Chocies" << endl;
		cout << "Choice: ";
		cin >> key;
		key = tolower(key);
		cin.ignore(100, '\n');

		if (key == 'a' && i <= 4)
		{
			do
			{
				cout << "\t Next Athlete: ";
				getline(cin, choice3);
				do
				{
					cout << "\t Location: ";
					cin >> loc;
					cin.ignore(100, '\n');
					if (!isdigit(loc))
					{
						cout << "\t Input has to be a number" << endl;
					}
				} while (!isdigit(loc));

				found = hashPtr->findAthlete(choice3, compareAthlete);
				if (!found)
				{
					bstKey();
				}
			} while (!found);

			if (found)
			{
				char * temp = &loc;
				if (atoi(temp) > i)
				{
					location = i;
				}
				else
				{

					location = atoi(temp);
				}

				compareList.insert(compareAthlete, location);
				i++;
			}
			compareList.displayList(displayLinkedList);
		}
		else if (key == 'p')
		{
			char location1, location2;
			char * temp = NULL;

			do
			{
				cout << "\t Location: ";
				cin >> location1;
				cin.ignore(100, '\n');
				if (!isdigit(location1))
				{
					cout << "\t Input has to be a number" << endl;
				}
				else
				{
					temp = &location1;
					if (atoi(temp) > i)
					{
						cout << "\t Input has to be in between the number of athlete\n";
					}
				}
			} while (!isdigit(location1) || (atoi(temp) > i));
			do
			{
				cout << "\t and: ";
				cin >> location2;
				cin.ignore(100, '\n');
				if (!isdigit(location2))
				{
					cout << "\t Input has to be a number" << endl;
				}
				else
				{
					temp = &location2;
					if (atoi(temp) > i)
					{
						cout << "\t Input has to be in between the number of athlete\n";
					}
				}
			} while (!isdigit(location2) || (atoi(temp) > i));

			char * tempLocation1 = &location1;
			char * tempLocation2 = &location2;
			Athlete * holdValue1;
			Athlete * holdValue2;
			compareList.getEntry(atoi(tempLocation1), holdValue1);
			compareList.getEntry(atoi(tempLocation2), holdValue2);

			compareList.remove(atoi(tempLocation1));
			compareList.remove(atoi(tempLocation2) - 1);

			compareList.insert(holdValue1, 1);
			compareList.insert(holdValue2, 2);



			compareList.displayList(displayLinkedList);
		}
		else if (key == 'e')
		{
			cout << "\t Exit compare option\n";
		}
		else
		{
			cout << "\t Invalid input\n";
		}
	}

}

void AthleteRecord::mostSearched(int num)
{
	if (heapSearch.isEmpty())
	{
		cout << "There is no athlete which is searched" << endl;
		return;
	}

	Athlete * tempArr[10];
	Athlete * hold;
	int check = num;

	if (heapSearch.getNumberOfNodes() < num)
	{
		check = heapSearch.getNumberOfNodes();
		cout << "The number of athletes that have been searched up to now is less than your resqu" << endl;
	}

	cout << endl;

	for (int i = 0; i < check; i++)
	{
		heapSearch.getTop(hold);
		tempArr[i] = hold;
		heapSearch.remove(compareHeap);

		cout << "Number " << i + 1 << endl;
		tempArr[i]->printAll();
		cout << endl;
	}
	cout << endl;
	while (check < 10 && heapSearch.getTop(hold) && tempArr[check - 1]->getNumSearch() == hold->getNumSearch())
	{
		tempArr[check] = hold;
		cout << "Number " << check + 1 << endl;
		tempArr[check]->printAll();
		cout << endl;
		heapSearch.remove(compareHeap);
		check++;
	}

	for (int i = 0; i < check; i++)
	{
		heapSearch.add(tempArr[i], compareHeap, checkDuplicate);
	}
}

