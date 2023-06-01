#pragma once
#include "UserArray.h"
#include "PrintedEdition.h"

class Library {
public:
	static Library& getInstance();
	void addPrint(const PrintedEdition*);
	void removePrint(const unsigned);
	void printPrints() const;
	void addUsers(const User&);
	void removeUser(const char*);
	void printUsersReadingPrint(unsigned) const;
	void printUsers();
	void takePrint(const unsigned, const char*);
	void getPrintBack(const unsigned, const char*);
	void readFile(std::ifstream&);
	void writeFile(std::ofstream&) const;
	PEArray getPrints() const;
	UserArray getUsers() const;
private:
	Library();
	Library(const Library&);
	~Library();
	UserArray users;
	PEArray prints;
};