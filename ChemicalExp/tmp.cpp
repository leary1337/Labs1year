#include "MyStack.h"
#include <iostream>

using namespace std;

int main()
{
  MyStack<int> int_st;
  
  int_st.push(3);
  int_st.push(2);
  int_st.push(1);
  
  cout << int_st.pop() << " -- ";
  cout << int_st.getTop() << "\n";
  cout << int_st.pop() << " -- ";
  cout << int_st.pop() << endl << endl;
  
  return 0;
}