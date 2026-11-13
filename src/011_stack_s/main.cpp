#include <string>
#include <format>
#include <iostream>

#include "stack_s.h"


//int main () {
//
//	StackS S;
//
//	S.push("1");
//	S.push("2");
//	S.push("3");
//
//	S.pop();
//	S.pop();
//	S.pop();
//
//	return (0);
//}


int main () {

	StackS S;

	S.push ("apple");
	S.push ("brown");
	S.push ("cucumber");

	while (!S.empty ()) {
		std::cout << "stack size: " << S.size () << ", top element: " << S.top () << "\n";
		S.pop ();
	}

	return (0);
}
