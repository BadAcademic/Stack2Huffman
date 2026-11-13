#include "sld.hpp"

#include "bin_tree_s.hpp"
#include "vec.hpp"

void simple_visual_test ();


int main () {

	try {

		simple_visual_test ();
	}
	catch (gexception& e) {

		std::cerr << std::format("exception caught: {}\n", e.message());
	}

	return (0);
}


void simple_visual_test () {

	BinTreeS<std::string> BT{
		"moon", "sky", "key", "bottom", "table", "paper", 
		"orange", "cucumber", "carrot", "potato", "forest", "key", "bottom", "table"
	};

	std::string str;
	str = BT.find ("cucumber") == nullptr ? "not found" : "found";
	std::cout << str << "\n";
	str = BT.find ("cucumber1") == nullptr ? "not found" : "found";
	std::cout << str << "\n";
	str = BT.find ("orange") == nullptr ? "not found" : "found";
	std::cout << str << "\n";
	str = BT.find ("orange1") == nullptr ? "not found" : "found";
	std::cout << str << "\n\n";

	BT.dprint ();
	std::cout << "\n\n";
	BT.pprint ();
	std::cout << "\n\n";
}