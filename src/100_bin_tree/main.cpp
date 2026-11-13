#include "sld.hpp"

#include <iostream>

#include "bin_tree.hpp"

void simple_visual_test ();


int main () {

	try {

		simple_visual_test ();
	}
	catch (gexception& e) {

		std::cerr << std::format ("exception caught: {}\n", e.message ());
	}

	return (0);
}


void simple_visual_test () {

	BinTree<std::string> BT {
		"noun", "sky", "violin", "table", "window", "queue", "pillow", "room",
		"home", "dream", "key", "bottom", "guest", "jack", "lady", "table", "window", "queue", "pillow"
	};

	for (auto& w : BT)
		std::cout << w << " ";
	std::cout << "\n\n";

	BinTree<std::string> BT1{BT};
	BinTree<std::string> BT2{std::move(BT1)};
	BinTree<std::string> BT3;
	BT3 = BT2;
	BinTree<std::string> BT4;
	BT4 = std::move (BT3);

	BT4.dprint ();
	std::cout << "\n";
	BT4.pprint ();
	std::cout << "\n\n";

	auto it1 = BT.begin ();
	auto it2 = BT4.begin ();
	while (it1 != BT.end () && it2 != BT4.end ()) {
		if (*it1 != *it2)
			std::cout << "Error\n";
		++it1;
		++it2;
	}
}
