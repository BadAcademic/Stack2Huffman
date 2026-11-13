#include <iostream>

#include "queue_s.h"


int main () {

	QueueS Q;

	Q.push ("apple");
	Q.push ("brown");
	Q.push ("cucumber");

	while (!Q.empty ()) {
		std::cout << "stack size: " << Q.size () << ", front element: " << Q.front () << "\n";
		Q.pop ();
	}

	return 0;
}

