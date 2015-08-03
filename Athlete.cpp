#include "stdafx.h"
#include "Athlete.h"; 
#include <string>
#include <iostream>

using namespace std; 

Athlete::Athlete()
{
	name = age = country = year = "";
	numSearch = 0;
}



Athlete:: Athlete(string n, string a, string c, string y, int num)
{
	name = n;
	age = a;
	country = c;
	year = y;
	numSearch = num;
}



// setters -- sets the data
void Athlete:: setName(string n)	        { name = n; }
void Athlete:: setAge(string a)	        { age = a; }
void Athlete::setCountry(string c)		{ country = c; }
void Athlete::setYear(string y)		    { year = y; }

void Athlete::updateSearch()			{ numSearch++; }	// Increments the search function

// Getters -- returns the data
string Athlete::getName() const	    { return name; }
string Athlete::getAge() const		{ return age; }
string Athlete::getCountry() const	{ return country; }
string Athlete::getYear() const		{ return year; }

int Athlete::getNumSearch() const	{ return numSearch; }	// Gets the number searched

void Athlete::printKey() { cout << left << getName() << endl; }	// Prints out the key (name of the athlete)


void Athlete::printLayout() { cout << left << getName() << "," << getAge() << "," << getCountry() << "," << getYear() << endl; }


void Athlete::printAll() {
	cout << "Name: " << getName() << endl << "Age: " << getAge() << endl
		<< "Country: " << getCountry() << endl << "Year: " << getYear() << endl << "Searching times: " <<
		getNumSearch() << endl;
}

bool Athlete::operator > (const Athlete &obj) const
{
	int holdSize1 = static_cast<int>(name.size());
	int holdSize2 = static_cast<int>(obj.name.size());
	int holdSize = holdSize1;

	if (holdSize1 < holdSize2)
	{
		holdSize = holdSize2;
	}

	string name1 = name;
	string name2 = obj.name;

	for (int i = 0; i < holdSize; i++)
	{
		if (i < holdSize1)
			name1[i] = tolower(name1[i]);
		if (i < holdSize2)
			name2[i] = tolower(name2[i]);
	}

	if (name1 > name2)
		return true;
	else
		return false;
}

bool Athlete::operator < (const Athlete &obj) const
{
	int holdSize1 = static_cast<int>(name.size());
	int holdSize2 = static_cast<int>(obj.name.size());
	int holdSize = holdSize1;

	if (holdSize1 < holdSize2)
	{
		holdSize = holdSize2;
	}

	string name1 = name;
	string name2 = obj.name;

	for (int i = 0; i < holdSize; i++)
	{
		if (i < holdSize1)
			name1[i] = tolower(name1[i]);
		if (i < holdSize2)
			name2[i] = tolower(name2[i]);
	}

	if (name1 < name2)
		return true;
	else
		return false;
}

bool Athlete::operator == (const Athlete&obj) const
{
	int holdSize1 = static_cast<int>(name.size());
	int holdSize2 = static_cast<int>(obj.name.size());
	int holdSize = holdSize1;

	if (holdSize1 < holdSize2)
	{
		holdSize = holdSize2;
	}

	string name1 = name;
	string name2 = obj.name;

	for (int i = 0; i < holdSize; i++)
	{
		if (i < holdSize1)
			name1[i] = tolower(name1[i]);
		if (i < holdSize2)
			name2[i] = tolower(name2[i]);
	}

	if (name1 == name2)
		return true;
	else
		return false;
}