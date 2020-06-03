#ifndef _MYSTACK_
#define _MYSTACK_

template <class T>
class MyStack {
public:
    // Конструктор (создает пустой стек размером 10)
    MyStack();

    // Конструктор
    // Параметры: n - размер создаваемого стека
    // Создает пустой стек размера n
    MyStack(int n);

    // Деструктор
    ~MyStack();

    // Метод получения вершины
    T getTop();

    // Стек пуст?
    bool isEmpty();
    // Стек полон?
    bool isFull();

    // Метод вставки
    // Параметры: x - вставляемое в стек значение
    void push(T x);

    // Метод удаления
    void pop();

    // Печать стека
    void print();

private:
    T* arr;
    int size;
    int top;
};

#endif
