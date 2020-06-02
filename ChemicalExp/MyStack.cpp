#ifdef _MYSTACK_
#include <stdexcept>

template <class T>
MyStack<T>::MyStack() {
  size = 10;
  top = 0;
  arr = new T[size];
}

template <class T>
MyStack<T>::MyStack(int n) {
  size = n;
  top = 0;
  arr = new T[size];
}

// Destructor
template <class T>
MyStack<T>::~MyStack(void) {
  delete[] arr;
}

template <class T>
bool MyStack<T>::isFull() {
    if (top == size) {   
        return true;
    }
    else
        return false;
}

template <class T>
bool MyStack<T>::isEmpty() {
    if (top == 0) {   
        return true;
    }
    else
        return false;
}

template <class T>
void MyStack<T>::push(T x) {
    if(!isFull()) {
        arr[top] = x;
        top++;
    }
    else
        throw std::runtime_error("stack is full");
}

template <class T>
void MyStack<T>::pop() {
    if(!isEmpty()) {
        top--;
    }
    else {
        throw std::runtime_error("stack is empty");
    }
}

template <class T>
T MyStack<T>::getTop() {
    if (!isEmpty())
        return arr[top-1];
    else {
        throw std::runtime_error("stack is empty");
    }
}

template <class T>
void MyStack<T>::print() { 
    int i;

    if (!isEmpty())
        for (i = top-1; i >= 0; i--)
            std::cout << arr[i] << "\n";
    else
        std::cout << "Stack is empty\n";
}
#endif