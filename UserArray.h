#pragma once
#include "User.h"

class UserArray {
public:
	UserArray();
	UserArray(unsigned);
	UserArray(const UserArray&);
	~UserArray();
	UserArray& operator=(const UserArray&);
	User& operator[](unsigned) const;
	void push(const User&);
	void printAllReading(unsigned) const;
	void print() const;
	void sort();
	bool isSorted() const;
	unsigned getSize() const;
	bool removeUser(const char*);
	void wrtie(std::ofstream&) const;
	void read(std::ifstream&);
private:
	User* data;
	unsigned size;
	unsigned cappacity;
};