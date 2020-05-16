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

#include <iostream>

using namespace std;

int main() {
	int numPairs;
	int **table = NULL;

	numPairs = get_num_pairs();
	if (!(is_correct_nums(numPairs)))
		return 0;

	if (!(table = init_table(table, numPairs)))
		return 1;

	if (!(table = fill_of_table(table, numPairs)))
		return 0;

	display_table(table, numPairs);
	
	return 0;
}