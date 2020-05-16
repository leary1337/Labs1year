#include <iostream>
#include "utilities.h"

using namespace std;

// Инициализация таблицы взаимодействия веществ
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

// Проверка на корректность ввода пользователя (элемент таблицы)
bool is_correct_element(int element) {
	if (element <= 0) {
		cout << "Incorrect name of chemical element" << endl;
		return false;
	}

	return true;
}

// Заполнение таблицы взаимодействия (заполняет пользователь)
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
	
// Вывод введенной таблицы в консоль
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

// Проверка на корректность ввода пользователя (кол-во пар смешиваемых веществ)
bool is_correct_nums(int numPairs) {
	if (numPairs <= 0){
		cout << "Incorrect the number" << endl;
		return false;
	}
	return true;
}

// Получение от пользователя кол-ва пар смешиваемых элементов
int get_num_pairs() {
	int numPairs;
	
	cout << "Enter the number of pairs of chemical elements" << endl;
	cout << "IMPORTANT! 1 and 2 is not equal to 2 and 1!" << endl;

	cin >> numPairs;
	
	return numPairs;
}

// Получение от пользователя кол-ва смешиваемых элементов в опыте
int get_num_mixed() {
	int numMixed;

	cout << "Enter the number of element to mix" << endl;

	cin >> numMixed;

	if (!(is_correct_nums(numMixed)))
		return 0;

	return numMixed;
}

// Ввод пользователем элементов для опыта
int *fill_chain_elem(int *chainElem, int numMixed) {
	int i;
	
	if (!(chainElem = new (nothrow) int[numMixed]))
		return NULL;

	cout << "Enter the elements to mix" << endl;
	for (i = 0; i < numMixed; i++) {
		cin >> chainElem[i];
		if (!(is_correct_nums(chainElem[i])))
			return NULL;
		
	}

	return chainElem;
}
