#pragma once
#include "PEArray.h"

class User{
public:
	User();
	User(const char*);
	User(const User&);
	User& operator=(const User&);
	~User();
	const char* getName() const;
	void write(std::ofstream&);
	void read(std::ifstream&);
	PEArray getCurr() const;
	PEArray getRead() const;
	bool operator==(const User&) const;
	bool operator!=(const User&) const;
	bool operator<(const User&) const;
	bool operator<=(const User&) const;
	bool operator>(const User&) const;
	bool operator>=(const User&) const;
	void operator[](unsigned) const;
	User operator+(const PrintedEdition*) const;
	User& operator+=(const PrintedEdition*);
	User operator-(const PrintedEdition*) const;
	User& operator-=(const PrintedEdition*);
	void print() const;
private:
	bool isCorrectString(const char*);
	void copy(char*&, const char*);
	void setName(const char*);
	void clean();
	char* name;
	PEArray currPrints;
	PEArray readPrints;
};