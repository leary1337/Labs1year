#include <iostream>
#include "mixed.h"
#include "MyStack.h"

using namespace std;

// Функция смешивания элементов по таблице взаимодействия
// Параметры:
// chainElem - элементы которые будем класть в пробирку,
// numMixed - кол-во таких элементов,
// table - таблица взаимодействия элементов,
// testTube - пробирка (непосредственно стэк),
// numPairs - кол-во пар элементов в таблице, 
// 	которые образуют взаимодействие (кол-во строк в таблице)
void mixed(int *chainElem, int numMixed, int **table, MyStack <int> &testTube, int numPairs) {
	int i, j;
	bool check;

	for (i = 1; i < numMixed; i++) {
		check = true;
		for (j = 0; j < numPairs; j++) {
			if (testTube.getTop() == table[j][0] && chainElem[i] == table[j][1]) {
				testTube.pop();
				testTube.push(table[j][2]);
				check = true;
				break;
			}
			else 
				check = false;
		}
		if(!check)
			testTube.push(chainElem[i]);
	}

	return;
}

// Функция изначально кладет первый элемент в пробирку и далее запускает функцию mixed, 
// 	которая продолжит класть элементы и проверять их на взаимодействие, если оно обнаружено в таблице
// 		тогда смешаем и запишем результат
MyStack <int> put_elem(int *chainElem, int numMixed, int **table, int numPairs) {
	MyStack <int> testTube;

	testTube.push(chainElem[0]);

	mixed(chainElem, numMixed, table, testTube, numPairs);

	return testTube;
}

