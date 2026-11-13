#ifndef _VEC_
#define _VEC_

#include <map>
#include <format>
#include <iostream>

#include "gexception.h"


class vec {

public:

	vec ();
	vec (int, int);
	vec(std::initializer_list<int>);
	vec (const vec&);
	vec (vec&&) noexcept;
	vec& operator= (const vec&);
	vec& operator= (vec&&) noexcept;
	vec& operator++ ();
	vec operator++ (int);
	friend std::ostream& operator<< (std::ostream&, const vec&);
	friend vec operator+ (const vec&, const vec&);
	friend bool operator!= (const vec&, const vec&);
	friend bool operator== (const vec&, const vec&);
	friend bool operator< (const vec&, const vec&);
	friend struct std::formatter<vec>;
	~vec ();

	int* data{};

private:

	void print(int, const vec*, int*);
	const vec* find_object(const vec*, int*);


	static std::map<int, std::string> name;

	static std::map<const vec*, std::string> object2Id;
	static std::map<int*, std::string> data2Id;
	static std::map<int*, const vec*> data2object;

	static char objectId;
	static char dataId;
	static const int two;
	static const char firs_id;
};

const char vec::firs_id{64};
const int vec::two{2};

std::map<int, std::string> vec::name{
	{1, "Default Constructor"},
	{2, "Constructor (params)"},
	{3, "Constructor (list)"},
	{4, "Copy constructor"},
	{5, "Move constructor"},
	{6, "Copy assignment"},
	{7, "Move assignment"}, 
	{8, "Destructor"}
};

char vec::objectId{firs_id};
char vec::dataId{firs_id};
std::map<const vec*, std::string> vec::object2Id;
std::map<int*, std::string> vec::data2Id;
std::map<int*, const vec*> vec::data2object;


const vec* vec::find_object(const vec* o, int* d) {

	auto it_o = object2Id.find(o);
	auto it_d = data2Id.find(d);

	if (it_o == object2Id.end() && it_d != data2Id.end()) {
		auto it_do = data2object.find(it_d->first);
		if (it_do == data2object.end())
			return nullptr;
		else
			return it_do->second;

		auto it_oo = object2Id.find((const vec*)it_do->second);
		if (it_oo == object2Id.end())
			return nullptr;

		return it_oo->first;
	}
	//else if (it_o != object2Id.end())
	//	return it_o->first;
	else
		return nullptr;
}


void vec::print(int id, const vec* rObject, int* rData) {

	auto lObject = this;
	auto lData = data;

	std::string lObjectId{};
	std::string lDataId{};
	std::string rObjectId{};
	std::string rDataId{};

	std::string lData1{};
	std::string lData2{};
	std::string rData1{};
	std::string rData2{};
	std::string lObjectAddr{};
	std::string rObjectAddr{};
	std::string lDataAddr{};
	std::string rDataAddr{};

	switch (id) {

		// initializtion constructors
	case 1:
	case 2:
	case 3: {

		objectId++;
		object2Id[lObject] = objectId;
		dataId++;
		data2Id[lData] = dataId;
		data2object[lData] = lObject;

		lObjectId = objectId;
		lDataId = dataId;
		lObjectAddr = std::format("{:x}", (size_t)lObject);
		lDataAddr = std::format("{:x}", (size_t)lData);

		std::cout << std::format("{}:\t{}\t*{} ({}, {}){:14}{:>12}{:17}{:>12}\n", name[id], lObjectId, lDataId, data[0], data[1], ' ', lObjectAddr, ' ', lDataAddr) << std::flush;
		break;
	}
		  // copy constructor
	case 4: {

		objectId++;
		object2Id[lObject] = objectId;
		dataId++;
		data2Id[lData] = dataId;
		data2object[lData] = lObject;

		lObjectId = objectId;
		lDataId = dataId;
		lObjectAddr = std::format("{:x}", (size_t)lObject);
		lDataAddr = std::format("{:x}", (size_t)lData);

		const vec* old = find_object(rObject, rData);
		if (old != nullptr)
			rObjectId = object2Id[old] + " m";
		else
			rObjectId = object2Id.find(rObject) != object2Id.end() ? object2Id[rObject] : "?";

		rDataId = data2Id.find(rData) != data2Id.end() ? data2Id[rData] : "?";
		rObjectAddr = std::format("{:x}", (size_t)rObject);
		rDataAddr = std::format("{:x}", (size_t)rData);

		std::cout << std::format("{}:\t{} < {}\t*{} ({}, {}) < *{} ({}, {})  {:>12} < {:>12}  {:>12} < {:>12}\n", name[id], lObjectId, rObjectId, lDataId, lData[0], lData[1], rDataId, rData[0], rData[1], lObjectAddr, rObjectAddr, lDataAddr, rDataAddr) << std::flush;
		break;
	}

		  // move constructor
	case 5: {

		objectId++;
		object2Id[lObject] = objectId;

		auto it = data2object.find(rData);
		if (it != data2object.end()) {
			data2object.erase(rData);
			data2object[rData] = lObject;
		}
		else
			std::cout << "Something strange 1\n";

		lObjectId = objectId;
		lDataId = dataId;
		lObjectAddr = std::format("{:x}", (size_t)lObject);
		lDataAddr = std::format("{:x}", (size_t)lData);

		const vec* old = find_object(rObject, rData);
		if (old != nullptr)
			rObjectId = object2Id[old] + " m";
		else
			rObjectId = object2Id.find(rObject) != object2Id.end() ? object2Id[rObject] : "?";
		rDataId = data2Id.find(rData) != data2Id.end() ? data2Id[rData] : "?";

		std::cout << std::format("{}:\t{} < {}\t*{} ({}, {}){:14}{:>12}{:17}{:>12}\n", name[id], lObjectId, rObjectId, lDataId, lData[0], lData[1], ' ', lObjectAddr, ' ', lDataAddr) << std::flush;
		break;
	}
		  // copy assignment
	case 6: {

		lObjectId = objectId;
		lDataId = dataId;

		const vec* oldl = find_object(lObject, lData);
		if (oldl != nullptr)
			lObjectId = object2Id[oldl] + " m";
		else
			lObjectId = object2Id.find(lObject) != object2Id.end() ? object2Id[lObject] : "?";
		lDataId = data2Id.find(lData) != data2Id.end() ? data2Id[lData] : "?";

		const vec* oldr = find_object(rObject, rData);
		if (oldr != nullptr)
			rObjectId = object2Id[oldr] + " m";
		else
			rObjectId = object2Id.find(rObject) != object2Id.end() ? object2Id[rObject] : "?";
		rDataId = data2Id.find(rData) != data2Id.end() ? data2Id[rData] : "?";

		std::cout << std::format("{}:\t{} = {}\t*{} ({}, {}) = *{} ({}, {})  {:>12x} = {:>12x}  {:>12x} = {:>12x}\n", name[id], lObjectId, rObjectId, lDataId, lData[0], lData[1], rDataId, rData[0], rData[1], (size_t)lObject, (size_t)rObject, (size_t)lData, (size_t)rData) << std::flush;
		break;
	}
		  // move assignment
	case 7: {

		lObjectId = objectId;
		lDataId = dataId;

		auto it = data2object.find(rData);
		if (it != data2object.end()) {
			data2object.erase(rData);
			data2object[rData] = lObject;
		}
		else
			std::cout << "Something strange 2\n";

		const vec* oldl = find_object(lObject, lData);
		if (oldl != nullptr)
			lObjectId = object2Id[oldl] + " m";
		else
			lObjectId = object2Id.find(lObject) != object2Id.end() ? object2Id[lObject] : "?";
		lDataId = data2Id.find(lData) != data2Id.end() ? data2Id[lData] : "?";

		const vec* oldr = find_object(rObject, rData);
		if (oldr != nullptr)
			rObjectId = object2Id[oldr] + " m";
		else
			rObjectId = object2Id.find(rObject) != object2Id.end() ? object2Id[rObject] : "?";
		rDataId = data2Id.find(rData) != data2Id.end() ? data2Id[rData] : "?";

		std::cout << std::format("{}:\t{} = {}\t*{} ({}, {}){:14}{:>12}{:17}{:>12}\n", name[id], lObjectId, rObjectId, lDataId, lData[0], lData[1], ' ', lObjectAddr, ' ', lDataAddr) << std::flush;
		break;
	}
		  // desructor
	case 8: {

		const vec* old = find_object(lObject, lData);
		if (old != nullptr)
			lObjectId = object2Id[old] + " m";
		else
			lObjectId = object2Id.find(lObject) != object2Id.end() ? object2Id[lObject] : "?";

		if (lData != nullptr)
			object2Id.erase(old);

		if (lObjectId != "?" || lObjectId != "m")
			object2Id.erase(lObject);
		lDataId = data2Id.find(lData) != data2Id.end() ? data2Id[lData] : "0";

		lData1 = lData != nullptr ? std::to_string(lData[0]) : "-";
		lData2 = lData != nullptr ? std::to_string(lData[1]) : "-";

		lObjectAddr = std::format("{:x}", (size_t)lObject);
		lDataAddr = lData == 0 ? "moved" : std::format("{:x}", (size_t)lData);

		std::cout << std::format("{}:\t\t{}\t*{} ({}, {}){:14}{:>12}{:17}{:>12}\n", name[id], lObjectId, lDataId, lData1, lData2, ' ', lObjectAddr, ' ', lDataAddr) << std::flush;

		if (object2Id.size() == 0) {

			objectId = firs_id;
			dataId = firs_id;
			data2Id.clear();
			data2object.clear();
		}
		break;
	}
	}
}


vec::vec () {

	data = new(std::nothrow) int[two];
	if (data == nullptr)
		throw gexception(gexception::MemAlloc);

	data[0] = 0;
	data[1] = 0;

	print(1, nullptr, nullptr);
}


vec::vec (int x, int y) {

	data = new(std::nothrow) int[two];
	if (data == nullptr)
		throw gexception(gexception::MemAlloc);

	data[0] = x;
	data[1] = y;

	print(2, nullptr, nullptr);
}


vec::vec(std::initializer_list<int> l) {

	data = new(std::nothrow) int[two];
	if (data == nullptr)
		throw gexception(gexception::MemAlloc);

	data[0] = 0;
	data[1] = 0;

	int n = 0;
	for (auto& o : l) {
		data[n] = o;
		n++;
		if (n > 1)
			break;
	}

	print(3, nullptr, nullptr);
}


vec::vec (const vec& o) {

	data = new(std::nothrow) int[two];
	if (data == nullptr)
		throw gexception(gexception::MemAlloc);

	data[0] = o.data[0];
	data[1] = o.data[1];

	print(4, &o, o.data);
}


vec::vec (vec&& o) noexcept {

	data = o.data;
	
	print(5, &o, o.data);

	o.data = nullptr;
}


vec& vec::operator= (const vec& o) {

	if (this == &o)
		return (*this);

	data[0] = o.data[0];
	data[1] = o.data[1];

	print(6, &o, o.data);

	return (*this);
}


vec& vec::operator= (vec&& o) noexcept {

	if (this == &o)
		return (*this);

	if (data != nullptr)
		delete[] data;

	data = o.data;

	print(7, &o, o.data);

	o.data = nullptr;

	return (*this);
}


vec::~vec () {

	print(8, nullptr, nullptr);

	if (data != nullptr) {
		delete[] data;
	}
	data = nullptr;
}


vec& vec::operator++ () {
	
	data[0]++;
	data[1]++;

	return *this;
}


vec vec::operator++ (int) {

	vec old{*this};
	operator++ ();

	return old;
}


std::ostream& operator<< (std::ostream& _out, const vec& a) {
	_out << std::format("({}, {})", a.data[0], a.data[1]);

	return (_out);
}


vec operator+ (const vec& a, const vec& b) {

	vec r;
	r.data[0] = a.data[0] + b.data[0];
	r.data[1] = a.data[1] + b.data[1];

	return r;
}


bool operator!= (const vec& a, const vec& b) {
	
	return a.data[0] != b.data[0] || a.data[1] != b.data[1];
}


bool operator== (const vec& a, const vec& b) {

	return a.data[0] == b.data[0] && a.data[1] == b.data[1];
}


bool operator< (const vec& a, const vec& b) {

	return a.data[0] < b.data[0] && a.data[1] < b.data[1];
}


template <>
struct std::formatter<vec> : std::formatter<std::string> {
	
	auto format(vec v, format_context& ctx) const {
		return formatter<string>::format(
			std::format("({}, {})", v.data[0], v.data[1]), ctx);
	}
};


template <>
class std::hash<vec> {
public:

	size_t operator() (const vec& o) const {

		return o.data[0] * 73856093 ^ o.data[1] * 83492791;
	}
};

#endif
