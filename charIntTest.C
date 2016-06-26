#include <iostream>
using namespace std;

int main() {
	int x = 48;
	cout << "x is an int" << endl;
	cout << "x is " << x << endl;
	cout << "(char)x is " << (char)x << endl;
	cout << "(int)(char)x is " << (int)(char)x << endl;
	char y = 48;
	cout << "y is a char" << endl;
	cout << "y is " << y << " [**THIS IS WEIRD**] " << endl;
	cout << "(int)y is " << (int)y << endl;
	cout << "(char)(int)y is " << (char)(int)y << endl;
}
