#ifndef _HUFFMANTREE_
#define _HUFFMANTREE_

#include <fstream>
#include <iostream>

#include "map.hpp"
#include "pair.hpp"
#include "list.hpp"
#include "stack.hpp"
#include "priority_queue.hpp"
#include "gexception.h"


template <typename T>
class HuffmanTree {

public:

	HuffmanTree () {};

	void print_ftable (const std::string);

	void make_ftable (const T*, const int);

	void make_codes ();

	void print_codes (const std::string);

	void make_huffman_tree ();

	void print_huffman_tree (const std::string);

	void encode (const std::string, const std::string);

	void decode (const std::string, const std::string);

	void clear ();

	~HuffmanTree ();

private:

	Map<T, int> ftable;

	struct Node {

		Node (const T& data) : data (data) {}

		int id{};
		Node* p{};
		Node* l{};
		Node* r{};
		T data;
	};

	Node* root{};
	List<Node*> enodes;

	Map<T, Pair<bool*, int>> codes;
};


template <typename T>
void HuffmanTree<T>::print_ftable (const std::string fileName) {
    
	std::ofstream out (fileName);
	if (!out)
		throw gexception (gexception::OpenFile);

	for (auto& w : ftable)
		out << w.first << " " << w.second << "\n";

    out.close ();
}


template <typename T>
void HuffmanTree<T>::make_ftable (const T* data, const int length) {
	
	ftable.clear ();

	Pair<T, int>* p;
	for (int i{}; i < length; i++) {

		p = ftable.find (data [i]);
		if (p != 0)
			p->second++;
		else
			ftable.insert (data[i], 1);
	}
}


template <typename T>
void HuffmanTree<T>::make_huffman_tree () {

	if (ftable.size () == 0) {

		root = nullptr;
		return;
	}

	PriorityQueue<Pair<int, Node*>> PQ;
	
	int id{};
	for (auto& w : ftable) {

		Node* n = new (std::nothrow) Node (w.first);
		if (n == nullptr)
			throw gexception (gexception::MemAlloc);
		n->id = id;
		Pair<int, Node*> p (w.second, n);
		PQ.push (p);
		enodes.push_back (n);
		id++;
	}

	id = -1;
	while (PQ.size () > 1) {

		Pair<int, Node*> p1 = PQ.front ();
		PQ.pop ();
		Pair<int, Node*> p2 = PQ.front ();
		PQ.pop ();

		Node* n = new (std::nothrow) Node (T());
		if (n == nullptr)
			throw gexception (gexception::MemAlloc);
		n->l = p1.second;
		n->r = p2.second;
		n->p = 0;
		n->id = id;
		id--;
		p1.second->p = n;
		p2.second->p = n;

		Pair<int, Node*> p (p1.first + p2.first, n);
		PQ.push (p);
	}

	root = PQ.front ().second;
}


template <typename T>
void HuffmanTree<T>::print_huffman_tree (const std::string fileName) {

	std::ofstream out (fileName);
	if (!out)
		throw gexception (gexception::OpenFile);

	out << "digraph graphname {\n";

	if (root != nullptr) {

		Stack<Node*> nodes;
		nodes.push (root);

		while (!nodes.empty ()) {

			Node* n = nodes.top ();
			nodes.pop ();

			if (n->id < 0)
				out << n->id << " [label = \" \"];\n";
			else
				out << n->id << " [label = \"" << n->data << "\"];\n";
			if (n->l != 0) {
				nodes.push (n->l);
				out << n->id << " -> " << n->l->id << " [label = 0];\n";
			}
			if (n->r != 0) {
				nodes.push (n->r);
				out << n->id << " -> " << n->r->id << " [label = 1];\n";
			}
		}
	}
	out << "}";

	out.close ();
}


template <typename T>
void HuffmanTree<T>::make_codes () {

	for (auto& w : enodes) {

		Node* n{w};
		T s{n->data};
		int k{};
		Node* cn{n};
		while (cn->p != 0) {

			cn = cn->p;
			k++;
		}
		bool* fcodes = new (std::nothrow) bool [k];
		if (fcodes == nullptr)
			throw gexception (gexception::MemAlloc);
		cn = n;
		Pair<bool*, int> p (fcodes, k);
		while (cn->p != 0) {

			k--;
			if (cn->p->l == cn)
				fcodes[k] = false;
			else
				fcodes[k] = true;
			cn = cn->p;
		}

		codes.insert (s, p);
	}
}


template <typename T>
void HuffmanTree<T>::print_codes (const std::string fileName) {

	std::ofstream out (fileName);
	if (!out)
		throw gexception (gexception::OpenFile);

	for (auto& w : codes) {

		out << w.first << " ";
		for (int i = 0; i < w.second.second; i++)
			out << w.second.first[i];
		out << "\n";
	}

	out.close ();
}


template <typename T>
void HuffmanTree<T>::encode (const std::string inFileName, const std::string outFileName) {

	std::ifstream in (inFileName, std::ios::binary);
	if (!in)
		throw gexception (gexception::OpenFile);

	in.seekg (0, in.end);
	size_t len{static_cast<size_t>(in.tellg ())};
	in.seekg (0);
	char* data = new (std::nothrow) char [len];
	if (data == nullptr)
		throw gexception (gexception::MemAlloc);
	in.read (data, len);
	in.close ();

	make_ftable (data, len);

	make_huffman_tree ();

	make_codes ();

	std::ofstream out (outFileName, std::ios::binary);
	if (!out)
		throw gexception (gexception::OpenFile);

	int n{static_cast<int>(ftable.size ())};
	out.write ((char*)&n, sizeof (int));
	for (auto& w : ftable) {

		out.write ((char*)&w.first, sizeof (T));
		out.write ((char*)&w.second, sizeof (int));
	}

	int lenInt{static_cast<int>(len)};
	out.write ((char*)&lenInt, sizeof (int));
	char buf{};
	char one{1};
	int nb{};
	for (int i{}; i < len; i++) {

		bool* fcodes = codes.find (data[i])->second.first;
		int clen = codes.find (data[i])->second.second;
		for (int j{}; j < clen; j++) {

			if (fcodes[j])
				buf = buf | one;

			nb++;
				
			if (i == len - 1 && j == clen - 1) {
				buf = buf << (8 - nb);
				nb = 8;
			}
			if (nb == 8) {
				out.write (&buf, 1);
				buf = 0;
				nb = 0;
			}
			buf = buf << 1;
		}
	}

	out.close ();

	delete[] data;
}


template <typename T>
void HuffmanTree<T>::decode (const std::string inFileName, const std::string outFileName) {

	std::ifstream in (inFileName, std::ios::binary);
	if (!in)
		throw gexception (gexception::OpenFile);

	int n{};
	in.read ((char*)&n, sizeof (int));
	T s{};
	int f{};
	for (int i{}; i < n; i++) {

		in.read ((char*)&s, sizeof (T));
		in.read ((char*)&f, sizeof (int));

		ftable.insert (s, f);
	}

	int len{};
	in.read ((char*)&len, sizeof (int));
	char* data = new (std::nothrow) char [len];
	if (data == nullptr)
		throw gexception (gexception::MemAlloc);
	in.read (data, len);
	in.close ();

	make_huffman_tree ();

	std::ofstream out (outFileName, std::ios::binary);
	if (!out)
		throw gexception (gexception::OpenFile);

	if (root != nullptr && root->l == nullptr && root->r == nullptr) {

		for (int i{}; i < len; i++)
			out.write ((char*)&root->data, sizeof (T));
		out.close ();
		delete[] data;
		return;
	}

	unsigned char one{128};
	int nn{};
	int nb{};
	char buf{};
	if (len > 0)
		buf = data[nn];
	for (int i{}; i < len; i++) {

		Node* n{root};

		while (true) {

			if ((buf | one) == buf)
				n = n->r;
			else
				n = n->l;
			buf = buf << 1;
			nb++;

			if (nb == 8) {
				nn++;
				if (nn < len)
					buf = data[nn];
				nb = 0;
			}
			if (n->id >= 0) {
				char s = n->data;
				out.write ((char*)&s, 1);
				break;
			}
		}
	}

	out.close ();
	delete[] data;
}


template <typename T>
void HuffmanTree<T>::clear () {

	Stack<Node*> nodes;
	if (root != nullptr)
		nodes.push (root);

	while (!nodes.empty ()) {

		Node* n{nodes.top ()};
		nodes.pop ();
		if (n->l != nullptr)
			nodes.push (n->l);
		if (n->r != nullptr)
			nodes.push (n->r);

		delete n;
	}

	for (auto& w : codes)
		delete [] w.second.first;

	root = nullptr;
	enodes.clear ();
	ftable.clear ();
}


template <typename T>
HuffmanTree<T>::~HuffmanTree () {

	clear ();
}

#endif