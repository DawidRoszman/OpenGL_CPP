#include <iostream>

using namespace std;

int main(){
  cout << "Rozmiar inta to " << sizeof( int ) << endl;
  cout << "Rozmiar shorta to " << sizeof( short ) << endl;
  cout << "Rozmiar longa to " << sizeof( long ) << endl;
  cout << "Rozmiar double to " << sizeof( double ) << endl;
  cout << "Rozmiar float to " << sizeof( float ) << endl;
  cout << "Rozmiar long double to " << sizeof( long double ) << endl;

  unsigned int a = -10;
  char b = 10;
  cout << "Unsigned int a = -10 to " << a << endl;
  cout << "Char b = 10 to " << b << endl;
  

  return 0;
}
