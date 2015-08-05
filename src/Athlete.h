
#ifndef _Athlete_H_
#define _Athlete_H_


#include <string>
using namespace std; 


class Athlete
{
public:
	string name;
	string age;
	string country;
	string year;
	int numSearch;
public:
	Athlete();
	Athlete(string n, string a, string c, string y, int num = 0);
	void setName(string n);
	void setAge(string a);
	void setCountry(string c);
	void setYear(string y);

	void updateSearch();	// Increments the search function

	// Getters -- returns the data
	string getName() const;
	string getAge() const;
	string getCountry() const;
	string getYear() const;

	int getNumSearch() const;	// Gets the number searched

	//Overload Operators
	bool operator > (const Athlete &obj) const;
	bool operator < (const Athlete &obj) const;
	bool operator == (const Athlete &obj) const;

	void printKey(); // Prints out the key(name of the athlete)
	void printLayout();
	void printAll() ; // prints out everything
};

#endif _Athlete_H_