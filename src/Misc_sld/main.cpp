#include "sld.hpp"


int main () {

	int* a = new int;
	int* b = new int[3];

	delete a;
	delete[] b;
}