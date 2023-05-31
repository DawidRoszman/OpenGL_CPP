#include <iostream>

using namespace std;

void printNum(int num){
  cout << "num = " << num << endl;
}

void increment(int &num){
  num++;
}

void decrement(int *num){
  cout << "Zmienna x jest pod adresem " << num << " jest " << *num << endl;
  *num = 20;
}


int main() {

  int num = 10;

  increment(num);
  decrement(&num);

  printNum(num);

  return 0;
}
