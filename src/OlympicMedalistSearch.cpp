// OlympicMedalistSearch.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <string>
#include <iomanip>
#include <iostream>
#include <cctype>
#include <vector>
#include "math.h"
#include <fstream>
#include <cstdlib>
#include <istream>
#include <sstream>
#include <queue>
#include "Athlete.h"
#include "AthleteRecord.h"
#include "Util.h"


using namespace std;


int main()
{
	AthleteRecord test;

	char key = ' ';
	string input, type, rating, miles;
	bool backup = false, save = true;

	while (key != 'q')
	{
		cout << "***** MAIN MENU *****" << endl
			<< "\t a. Add New Data" << endl
			<< "\t d. Delete Data" << endl
			<< "\t f. Find and Display Data Using Primary Key" << endl
			<< "\t l. List Data" << endl
			<< "\t p. Print Indented Tree" << endl
			<< "\t h. Hash Statistics" << endl;


		cout << "\t c. Compare Data" << endl
			<< "\t m. Most Searched (Honors)" << endl
			<< "\t s. Save" << endl
			<< "\t q. Quit" << endl << endl;

		cout << "Choice: ";
		cin >> key;
		key = tolower(key);

		cin.ignore(100, '\n');


		if (key == 'a')
		{

			bool validInput = true;

			cout << "Enter new athlete: ";

			getline(cin, input);

			validInput = checkError(input);

			if (validInput && test.search(input) == false)
			{

				cout << "Please enter the age: ";
				//cin.ignore(100, '\n');
				getline(cin, type);
				cout << "Please enter the country: ";
				//cin.ignore(100, '\n');
				getline(cin, rating);
				cout << "Please enter the year: ";
				//cin.ignore(100, '\n');
				getline(cin, miles);

				test.add(input, type, rating, miles);
				save = false;
			}
			else if (validInput)
				cout << "Already exists" << endl;
		}
		else if (key == 'd')
		{

			cout << "Enter an athlete to be deleted: ";
			getline(cin, input);

			bool validInput;
			validInput = checkError(input);

			if (validInput && test.search(input) == true)
			{
				save = false;
				test.deleteData(input);
			}
			else
				cout << "Does not exist" << endl;
		}
		else if (key == 'f')
		{
			cout << "Enter an athlete to be found: ";
			getline(cin, input);

			bool validInput;

			validInput = checkError(input);

			if (validInput && test.search(input) == false)
				cout << input << " is not found in the list" << endl;
		}
		else if (key == 'l')
		{
			cout << "\t h. Hash Table Data" << endl
				<< "\t b. BST Sorted Order" << endl;
			cout << "Choice: ";
			cin >> key;
			key = tolower(key);

			cin.ignore(100, '\n');

			if (key == 'h')
			{
				test.hashList();
			}
			else if (key == 'b')
			{
				test.bstKey();
			}
		}

		else if (key == 'p')
		{

			cout << "\t a. Preorder Print" << endl
				<< "\t b. Inorder Print" << endl
				<< "\t c. Postorder Print" << endl;
			cout << "Choice: ";
			cin >> key;
			key = tolower(key);

			cin.ignore(100, '\n');

			if (key == 'a')
			{
				test.preOrder();
			}
			else if (key == 'b')
			{
				test.inOrder();
			}

			else if (key == 'c')
			{
				test.postOrder();
			}

		}

		else if (key == 'h')
		{
			test.hashStats();
		}

		else if (key == 'c')
		{
			test.compare();
		}

		else if (key == 'm')
		{
			int num = 0;
			string input;
			bool validInput;

			do
			{
				validInput = true;
				cout << "Most searched athlete: " << endl;
				cout << "How many athletes do you want to display (max is 10): ";
				cin >> input;
				cin.ignore(100, '\n');
				if (input.size() >= 100)
				{
					validInput = false;
				}
				else
				{
					for (int i = 0; i < input.size() && validInput; i++)
					{
						if (isalpha(input[i]))
						{
							validInput = false;
						}
					}
				}
				if (!validInput)
				{
					cout << "Invalid input. Input is only number from 1 to 10.\n";
				}
			} while (!validInput);

			istringstream convert(input);
			if (!(convert >> num))
				num = 10;

			if (num > 10)
				num = 10;
			test.mostSearched(num);
		}


		else if (key == 's')
		{
			test.breadthSave();
		}

		else if (key != 'q')
			cout << "Not a valid menu choice." << endl;

		else if (key == 'q')
		{
			do
			{
				cout << "\t y. Quit without saving data" << endl
					<< "\t n. Quit & Save Data" << endl;
				cout << "Choice: ";
				cin >> key;
				key = tolower(key);

				cin.ignore(100, '\n');

			} while (key != 'n' && key != 'y');

			if (key == 'n')
			{
				test.breadthSave();
				return 0;
			}
			else
				return 0;
		}
	}
}