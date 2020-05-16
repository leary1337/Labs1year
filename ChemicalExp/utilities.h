#pragma once 
using namespace std;

// Инициализация таблицы взаимодействия веществ
int **init_table(int **table, int numPairs);
// Проверка на корректность ввода пользователя (элемент таблицы)
bool is_correct_element(int element);
// Заполнение таблицы взаимодействия (заполняет пользователь)
int **fill_of_table(int **table, int numPairs);
// Вывод введенной таблицы в консоль
void display_table(int **table, int numPairs);
// Проверка на корректность ввода пользователя (кол-во пар смешиваемых веществ)
bool is_correct_nums(int numPairs);
// Получение от пользователя кол-ва пар смешиваемых элементов
int get_num_pairs();
// Получение от пользователя кол-ва смешиваемых элементов в опыте
int get_num_mixed();
// Ввод пользователем элементов для опыта
int *fill_chain_elem(int *chainElem, int numMixed);