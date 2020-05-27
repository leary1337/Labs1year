#pragma once

using namespace std; 

#define MAX 1000 

class Stack { 
    int top; 
    int a[MAX]; // Maximum size of Stack 

public: 

    Stack() { top = -1; } 
    bool push(int x); 
    int pop(); 
    int peek(); 
    bool isEmpty(); 
    int Top();
}; 



