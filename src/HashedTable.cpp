#include "stdafx.h"
#include "HashedTable.h"
#include <iomanip>
#include "Util.h"

HashedTable::HashedTable(HashedTable* oldTable, const vector <Athlete*> &array, int numOfAthletes)
{
	this->size = oldTable->size;
	this->numberOfAthletes = numOfAthletes;
	this->nodePtr = new HashTable[this->size];

	for (int i = 0; i < size; i++)
	{
		this->nodePtr[i].setWasUsed(oldTable->nodePtr[i].hadBeenUsed());
		this->nodePtr[i].collisionIncrease(oldTable->nodePtr[i].getCollisions());

		if (oldTable->nodePtr[i].hadBeenUsed() && oldTable->nodePtr[i].getItemPtr() != 0)
		{
			bool   found = false;
			int    counter = 0;
			string name = (oldTable->nodePtr[i].getItemPtr())->getName();

			while (found == false && counter < numOfAthletes)
			{
				if (array[counter] != 0)
				{
					if (array[counter]->getName() != name)
						counter++;
					else if (array[counter]->getName() == name)
						break;
				}
			}

			if (array[counter]->getName() == name)
			{
				found = true;
				this->nodePtr[i].setItemPtr(array[counter]);
			}
		}
	}
}

string HashedTable::stringToLower(string name)
{
	for (unsigned int i = 0; i<name.length(); i++)
		name[i] = tolower(name[i]);
	return name;
}

int HashedTable::collisionResolution(int index, string name)
{
	string temp;
	for (int i = 0; i< name.length(); i++)
	{
		temp += name[name.length() - i - 1];
	}
	index += hashingFunction(temp);
	return index;
}




bool HashedTable::insert(Athlete *itemPtr)
{
	int numberColls = 0;
	if ((100.0*numberOfAthletes / size) >= 75)
	{
		cout << "Now rehashing the table due to increase in load factore" << endl;
		int newArraySize = size * 2;


		/* if the number is even, make it odd (2 is special case) */
		if (newArraySize % 2 == 0 && newArraySize != 2){
			newArraySize += 1;
		}
		/* while its not a prime number, check the next odd number */
		while (!isPrime(newArraySize)){
			newArraySize += 2;
		}

		// allocate new bed. note: uses () to value-initialize nullptr entries
		HashedTable newHashTable = 0;

		//fill in the new temp table with old info
		for (int i = 0; i < size; ++i)
		{
			string name = nodePtr[i].getItemPtr()->getName();
			string age = nodePtr[i].getItemPtr()->getAge();
			string country = nodePtr[i].getItemPtr()->getCountry();
			string year = nodePtr[i].getItemPtr()->getYear();
			Athlete* temp = new Athlete(name, age, country, year);

			int index = 0;
			index = hashingFunction(name);

			while (newHashTable.nodePtr[index].hadBeenUsed() && newHashTable.nodePtr[index].getItemPtr() != 0)
			{
				// Check if the athletes at the current node is equal to the one trying to be inserted
				if (newHashTable.nodePtr[index].getItemPtr()->getName() == name && nodePtr[index].getItemPtr()->getAge() == age && nodePtr[index].getItemPtr()->getYear() == year && nodePtr[index].getItemPtr()->getCountry() == country)
				{
					cout << "Item already exists in the list. Insert will not happen to avoid duplicates: ";
					string temp = newHashTable.nodePtr[index].getItemPtr()->getName();
					cout << temp << endl;
					return false;
				}
				index = (collisionResolution(index, name) % newArraySize);
				numberColls++;
			}

			newHashTable.nodePtr[index].setItemPtr(temp);
			newHashTable.nodePtr[index].collisionIncrease(numberColls);
			newHashTable.numberOfAthletes++;
		}

		delete[] nodePtr;
		nodePtr = newHashTable.nodePtr;
		size = newArraySize;
		numberOfAthletes = newHashTable.numberOfAthletes;
		return true;
	}

	else {

		if (itemPtr == 0)
			return false;
		string name = itemPtr->getName();
		int index = 0;
		index = hashingFunction(name);

		while (nodePtr[index].hadBeenUsed() && nodePtr[index].getItemPtr() != 0)
		{
			// Check if the athletes at the current node is equal to the one trying to be inserted
			if (nodePtr[index].getItemPtr()->getName() == itemPtr->getName() && nodePtr[index].getItemPtr()->getAge() == itemPtr->getAge() && nodePtr[index].getItemPtr()->getYear() == itemPtr->getYear() && nodePtr[index].getItemPtr()->getCountry() == itemPtr->getCountry())
			{
				cout << "Item already exists in the list. Insert will not happen to avoid duplicates: ";
				string temp = nodePtr[index].getItemPtr()->getName();
				cout << temp << endl;
				return false;
			}
			index = (collisionResolution(index, itemPtr->getName())) % size;
			numberColls++;
		}

		nodePtr[index].setItemPtr(itemPtr);
		nodePtr[index].collisionIncrease(numberColls);

		numberOfAthletes++;
		return true;
	}
}

void HashedTable::display(void visit(Athlete* ptr))
{
	for (int i = 0; i < size; i++)
	{
		if (nodePtr[i].hadBeenUsed() && nodePtr[i].getItemPtr() != 0)
		{
			visit(nodePtr[i].getItemPtr());
		}
	}
}

void HashedTable::displayStats()
{
	int     temp = 0;
	int     maxColls = 0;
	string  athletesMaxColls;
	cout << "There are " << numberOfAthletes << " athletes in the directory" << endl;
	cout << "The size of the Hash Table is: " << size << endl;
	cout << "The load factor is " << fixed << setprecision(2) << (100.0*numberOfAthletes / size) << "%\n" << endl;

	for (int i = 0; i < size; i++)
	{
		if (nodePtr[i].hadBeenUsed() && nodePtr[i].getItemPtr() != 0)
		{
			temp = nodePtr[i].getCollisions();

			if (temp > maxColls && temp > 0)
			{
				maxColls = temp;
				athletesMaxColls.clear();
				athletesMaxColls = (nodePtr[i].getItemPtr())->getName();
				athletesMaxColls += ", ";
			}
			else if (temp == maxColls && temp != 0)
			{
				athletesMaxColls += (nodePtr[i].getItemPtr())->getName();
				athletesMaxColls += ", ";
			}
		}
	}
	if (maxColls > 0)
	{
		cout << "Max number of collisions is " << maxColls << " which occurs at athletes: " << endl;
		cout << athletesMaxColls << endl;
		cout << endl << endl;
	}
}

bool HashedTable::findAthlete(string name, Athlete* & pointerToAthlete)
{
	name = stringToLower(name);
	if (numberOfAthletes == 0)
		return false;
	bool found = false;
	int index = 0;
	index = hashingFunction(name);

	while ((nodePtr[index].hadBeenUsed()) && nodePtr[index].getItemPtr() != 0
		&& (stringToLower((nodePtr[index].getItemPtr())->getName())) != name)
	{
		index = (collisionResolution(index, name)) % size;
	}

	if ((nodePtr[index].hadBeenUsed()) &&
		nodePtr[index].getItemPtr() != 0 &&
		(stringToLower((nodePtr[index].getItemPtr())->getName())) == name)
	{
		pointerToAthlete = nodePtr[index].getItemPtr();
		found = true;
		return found;
	}
	else
		return false;
}

bool HashedTable::deleteAthlete(string name)
{
	if (numberOfAthletes == 0)
		return false;
	int index = 0;
	index = hashingFunction(name);

	while (nodePtr[index].hadBeenUsed())
	{
		if (nodePtr[index].getItemPtr() == 0)
			index = (collisionResolution(index, name)) % size;
		else if ((nodePtr[index].getItemPtr())->getName() != name)
			index = (collisionResolution(index, name)) % size;
		else if ((nodePtr[index].getItemPtr())->getName() == name)
		{
			nodePtr[index].setItemPtr(0);
			nodePtr[index].collisionIncrease(0);
			numberOfAthletes--;
			return true;
		}
		else
			return false;
	}
	return false;
}

bool HashedTable::deleteAthlete(Athlete* itemPtr)
{
	if (numberOfAthletes == 0)
		return false;
	int index = 0;
	index = hashingFunction(itemPtr->getName());

	while (nodePtr[index].hadBeenUsed())
	{
		if (nodePtr[index].getItemPtr() == 0)
			index = (collisionResolution(index, itemPtr->getName())) % size;
		else if (!(*(nodePtr[index].getItemPtr()) == *itemPtr))
			index = (collisionResolution(index, itemPtr->getName())) % size;
		else if (*(nodePtr[index].getItemPtr()) == *itemPtr)
		{
			nodePtr[index].setItemPtr(0);
			nodePtr[index].collisionIncrease(0);
			numberOfAthletes--;
			return true;
		}
		else
			return false;
	}
	return false;
}
int HashedTable::hashingFunction(string name)
{
	long int placement = 0;
	int i = 1;
	int a = i;


	name = stringToLower(name);
	while (i <= name.length())
	{
		if (a > 6)
			a = 3;
		switch (name[i - 1])
		{
		case('e') : placement += 1 * pow(3.18, a);
			break;
		case('t') : placement += 2 * pow(2.988, a);
			break;
		case('a') : placement += 3 * pow(3.98, a);
			break;
		case('o') : placement += 4 * pow(3.98, a);
			break;
		case('i') : placement += 5 * pow(3.98, a);
			break;
		case('n') : placement += 6 * pow(3.98, a);
			break;
		case('s') : placement += 7 * pow(3.98, a);
			break;
		case('h') : placement += 8 * pow(3.98, a);
			break;
		case('r') : placement += 9 * pow(3.98, a);
			break;
		case('d') : placement += 10 * pow(3.2128, a);
			break;
		case('l') : placement += 11 * pow(3.2018, a);
			break;
		case('c') : placement += 12 * pow(3.1008, a);
			break;
		case('u') : placement += 13 * pow(3.338, a);
			break;
		case('m') : placement += 14 * pow(3.328, a);
			break;
		case('w') : placement += 15 * pow(3.318, a);
			break;
		case('f') : placement += 16 * pow(3.308, a);
			break;
		case('g') : placement += 17 * pow(3.208, a);
			break;
		case('y') : placement += 18 * pow(3.808, a);
			break;
		case('p') : placement += 19 * pow(3.48, a);
			break;
		case('b') : placement += 20 * pow(2.8, a);
			break;
		case('v') : placement += 21 * pow(3.98, a);
			break;
		case('k') : placement += 22 * pow(3.08, a)*(i + 0.324);
			break;
		case('j') : placement += 23 * pow(3.9, a)*(i + 0.334);
			break;
		case('x') : placement += 24 * pow(3.48, a)*(i + 0.344);
			break;
		case('q') : placement += 25 * pow(3.18, a)*(i + 0.354);
			break;
		case('z') : placement += 26 * pow(3.28, a)*(i + 0.364);
			break;
		default: placement += 31;
		}
		placement = (placement%size);
		i++;
		a = i;
	}

	return static_cast<int>(placement);
}
