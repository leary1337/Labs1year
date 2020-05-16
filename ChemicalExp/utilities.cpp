#include <iostream>
#include "utilities.h"

using namespace std;

bool is_correct_nums(int numPairs) {
	if (numPairs <= 0){
		cout << "Incorrect the number" << endl;
		return false;
	}
	return true;
}

int get_num_pairs() {
	int numPairs;
	
	cout << "Enter the number of pairs of chemical elements" << endl;
	cout << "IMPORTANT! 1 and 2 is not equal to 2 and 1!" << endl;

	cin >> numPairs;
	
	return numPairs;
}

int **fill_of_table(int **table, int numPairs) {
	int i, j;

	cout << "Fill the table of chemical substantions (ex: 1 2 3 (1+2=3))" << endl;
	cout << "P.S. Elements are numbered from one" << endl; 

	for (i = 0; i < numPairs; i++) {
		for (j = 0; j < 3; j++) {
			cin >> table[i][j];
			if (!(is_correct_element(table[i][j])))
				return NULL;
		}
	}

	return table;
}
	
void display_table(int **table, int numPairs) {
	int i, j;

	cout << "Your table of chemical elements:" << endl;

	for (i = 0; i < numPairs; i++) {
		for (j = 0; j < 3; j++) {
			cout << table[i][j] << " ";
		}
		cout << endl;
	}
}

int **init_table(int **table, int numPairs) {
	int i;

	table = new (nothrow) int*[numPairs];
	if (!table) {
		cout << "Memory is not allocated" << endl;
		return NULL;
	}

	for (i = 0; i < numPairs; i++) {
		table[i] = new (nothrow) int[3];
		if (!table[i]) {
			cout << "Memory is not allocated" << endl;
			return NULL;
		}
	}

	return table;
}