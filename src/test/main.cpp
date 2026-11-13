#include<memory>
#include<iostream>

using namespace std;

int main () {	

	int* p;
	cout << p << "\n";
	p = new int;
	cout << p << "\n";
	delete p;
	cout << p << "\n";

}
