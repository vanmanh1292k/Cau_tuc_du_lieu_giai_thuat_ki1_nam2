#include <list>
#include<fstream>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <time.h>
#define CLOCKS_PER_SEC  1000000	/* [XSI] */

using  namespace std;

const int TABLE_SIZE = 10;

struct Product {
	string name;
	string id;
};

class Hash {
	list<Product>* table;

public:
	Hash() {
		table = new list<Product>[TABLE_SIZE];
	}
	int hashFunction(int x) {
		return (x % TABLE_SIZE);
	}

	void get_file(ifstream& fileIn, Product& prd) {
		getline(fileIn, prd.name, ';');
		getline(fileIn, prd.id);
	}

	void insertData(Product prd[], int& n) {
		ofstream fileOut;
		fileOut.open("C:/Users/taoth/test.txt");
		int number;

		cout << "\nHow many Product do you want to add?" << endl;
		cout << "Please input number: ";
		cin >> number;

		for (int i = 1; i <= number; i++) {
			cin.ignore();
			cout << "Input name of Product: " << i << ": ";
			getline(cin, prd[i].name);
			cout << "Input Product's number: ";
			cin >> prd[i].id;
			cout << endl;
			int x = atoi(prd[i].id.c_str());
			int j = hashFunction(x);
			table[j].push_back(prd[i]);

			fileOut << prd[i].name << ";" << prd[i].id << endl;
		}
	}



	void readFile() {
		ifstream fileIn;
		fileIn.open("C:/Users/taoth/test.txt");

		while (fileIn.eof() == false) {
			Product prd;
			get_file(fileIn, prd);
			int x = atoi(prd.id.c_str());
			int j = hashFunction(x);
			table[j].push_back(prd);
		}
	}



	void deleteData(ifstream& fileIn) {
		int readerNumber;
		cout << "Enter Product number to delete: ";
		cin >> readerNumber;
		int index = hashFunction(readerNumber);
		list<Product>::iterator i;
		for (i = table[index].begin(); i != table[index].end(); ++i) {
			if (atoi(i->id.c_str()) == readerNumber) {
				break;
			}
		}
		if (i != table[index].end()) {
			cout << "Reader " << i->name << " has been removed from list!\n";
			table[index].erase(i);
		}
		else {
			cout << "Product number is not in this list!\n";
		}


		ofstream nf;
		nf.open("C:/Users/taoth/temp.txt");
		Product pr1;
		get_file(fileIn, pr1);
		while (!fileIn.eof()) {
			if (pr1.id != to_string(readerNumber)) {
				nf << pr1.name << ";" << pr1.id << endl;
			}
			get_file(fileIn, pr1);
		}
		nf.close();
		fileIn.close();
		remove("C:/Users/taoth/test.txt");
		rename("C:/Users/taoth/temp.txt", "C:/Users/taoth/test.txt");

	}


	void search() {
		int readerNumber;
		cout << "Enter Product number to find: ";
		cin >> readerNumber;
		int index = hashFunction(readerNumber);

		list<Product>::iterator i;
		bool check = false;
		for (i = table[index].begin(); i != table[index].end(); ++i) {
			if (i->id == to_string(readerNumber)) {
				check = true;
				cout << "Record found:\n";
				cout << "\tProduct Number\t\tName\n";
				cout << "\t" << i->id << "\t\t\t" << i->name << "\n";
			}
		}

		if (!check) {
			cout << "Cannot find this Product!\n";
		}
	}



	void displayHash() {
		cout << "Index\t\tProduct Name\n";
		for (int i = 0; i < 10; ++i) {
			cout << i << ": ";
			for (auto x : table[i]) {
				cout << " --> " << x.name;
			}
			cout << endl;
		}
	}
};



int main()
{
	Product prd[100];
	int n;
	ifstream in("C:/Users/taoth/test.txt", ios::in);
	if (!in) {
		cerr << "File can't be opened! " << endl;
		system("PAUSE");
		exit(1);
	}


	clock_t start, end;
	double time_used;

	Hash t = Hash();
	cout << "------------------------Menu------------------------\n";
	cout << "[1] - Insert new Product\n";
	cout << "[2] - ReadFile\n";
	cout << "[3] - Delete a Product\n";
	cout << "[4] - Find a Product\n";
	cout << "[5] - Display hash table\n";
	cout << "[0] - Exit program\n";
	cout << "----------------------------------------------------\n";

	int choice = 0;
	do
	{
		cout << "Input your choice: ";
		cin >> choice;
		cout << "----------------------------------------------------\n";

		switch (choice)
		{
		case 1:
			t.insertData(prd, n);
			cout << "Done!\n";
			break;
		case 2:
			t.readFile();
			break;
		case 3:
			t.deleteData(in);
			break;
		case 4:
			start = clock();
			t.search();
			end = clock();
			time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
			cout << "time: " << time_used << endl;
			break;
		case 5:
			t.displayHash();
			break;
		case 0:
			cout << "Thanks for using program!\n";
			break;
		default:
			break;
		}
		cout << "----------------------------------------------------\n";
	} while (choice != 0);

	system("pause");

	in.close();
	return 0;
}

