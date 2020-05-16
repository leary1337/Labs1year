#pragma once
using namespace std;

int **init_table(int **table, int numPairs);
int **fill_of_table(int **table, int numPairs);
void display_table(int **table, int numPairs);
bool is_correct_nums(int numPairs);
int get_num_pairs();