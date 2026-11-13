#include <string>
#include <fstream>
#include <iostream>

#include "huffman_tree.hpp"

void file2string(std::string, std::string&);


int main ()
{
	std::string dataFile = "big_data.txt";

	std::string frequencyFile{"AA_frequency.txt"};
	std::string treeFile{"AB_huffman_tree.dv"};
	std::string codesFile{"AC_codes.txt"};
	std::string codeFile{"AD_encoded_data.bin"};
	std::string decodeFile{"AE_decoded_data.txt"};

// -------------------------------------------------
	HuffmanTree<char> HTc;
	HTc.encode (dataFile, codeFile);

	HuffmanTree<char> HTd;
	HTd.decode (codeFile, decodeFile);
// -------------------------------------------------

//-------------------------------------------------
	{
		std::string data{"beep boop beer!"};

		HuffmanTree<char> HTa;
		HTa.make_ftable (data.c_str (), data.size ());
		HTa.print_ftable (frequencyFile);

		HTa.make_huffman_tree ();
		HTa.print_huffman_tree (treeFile);

		HTa.make_codes ();
		HTa.print_codes (codesFile);
	}
//-------------------------------------------------

// -------------------------------------------------
	{
		std::string data;
		HuffmanTree<char> HTa;
		file2string (dataFile, data);

		HTa.make_ftable (data.c_str (), data.size ());
		HTa.print_ftable (frequencyFile);

		HTa.make_huffman_tree ();
		HTa.print_huffman_tree (treeFile);

		HTa.make_codes ();
		HTa.print_codes (codesFile);
	}
// -------------------------------------------------

	return (0);
}


void file2string(std::string file, std::string& text) {

	std::ifstream in(file, std::ios::binary);
	if (!in) {
		std::cout << "Can't open file " << file;
		return;
	}

	in.seekg(0, in.end);
	int size = in.tellg();
	in.seekg(0);
	text.resize(size);
	in.read(text.data(), size);
	in.close();
}