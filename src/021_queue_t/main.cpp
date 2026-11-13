#include <string>
#include <iostream>

#include "queue_t.hpp"


int main () {

	QueueT<int> S1;
	QueueT<std::string> S2;

	const int n{5};
	int a[]{1, 2, 3, 4, 5};
	std::string b[]{"apple", "brown", "carrot", "dream", "falcon"};

	for (int i{}; i < n; i++) {
		S1.push (a[i]);
		S2.push (b[i]);
	}

	for (int i{}; i < n; i++) {
		std::cout << S1.front () << " " << S2.front () << "\n";
		S1.pop ();
		S2.pop ();
	}

	return 0;
}
