/*
*	УСЛОВИЕ:
*	Имеется n веществ. 
*	Задана таблица взаимодействия:
*	некоторым парам веществ ставится в соответствие вешество, 
*	получаемое в результате их взаимодействия. 
*	Задана последовательность помещения веществ в пробирку. 
*	Если в пробирке рядом оказываются реагирующие вещества, 
*	они мгновенно превращаются в третье вешество согласно таблице. 
*	Определите, какие вещества останутся в пробирке.
*	
*	Author: Kalabin Danil
*/

/*		TESTS:
*	Input: 
	3
	1 2 3
	3 1 4
	4 2 1
	4
	1 2 1 2
*	Output:
	1

*	Input: 
	1
	1 2 3
	4
	1 2 1 2
*	Output:
	3
	3

*	Input: 
	1
	1 2 3
	3
	4 5 6
*	Output:
	6
	5
	4

*	Input: 
	1
	1 0 3
	3
	4 5 6
*	Output:
	Incorrect name of chemical element
*/

#include <iostream>
#include "utilities.h"
#include "mixed.h"
#include "Stack.h"

using namespace std;

int main() {
	int numPairs, numMixed;
	int **table = NULL, *chainElem = NULL;
	Stack testTube;

	numPairs = get_num_pairs();
	if (!(is_correct_nums(numPairs)))
		return 0;

	if (!(table = init_table(table, numPairs)))
		return 1;

	if (!(table = fill_of_table(table,numPairs)))
		return 0;

	display_table(table, numPairs);

	if (!(numMixed = get_num_mixed()))
		return 0;

	if(!(chainElem = fill_chain_elem(chainElem, numMixed)))
		return 0;

	testTube = put_elem(chainElem, numMixed, table, numPairs);
	
	print_testTube(testTube);

	return 0;
}