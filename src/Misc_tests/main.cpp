#include <format>
#include <iostream>

#include "gexception.h"


int main () {

	try {

	}
	catch (gexception& e) {

		std::cerr << std::format ("gexception caught: {}\n", e.message ());
	}
}