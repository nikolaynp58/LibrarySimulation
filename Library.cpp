#include "Library.h"

Library::Library(): prints(), users() {}

Library::~Library(){}

Library& Library::getInstance() {
	static Library instance;
	return instance;
}

void Library::addPrint(const PrintedEdition* print) {
	this->prints.push(print);
}

void Library::addUsers(const User& user) {
	this->users.push(user);
}

void Library::removePrint(unsigned libNum) {
	this->prints.removePrint(libNum);
}

void Library::removeUser(const char* name) {
	this->users.removeUser(name);
}

void Library::printPrints() const {
	if (this->prints.getSize() == 0) {
		std::cout <<"No prints to print";
		return;
	}
	for (unsigned i = 0; i < this->prints.getSize(); i++) {
		try {
			this->prints[i]->print();
		}
		catch (std::out_of_range& e) {
			std::cout << e.what();
		}
	}
}

void Library::takePrint(unsigned libNum, const char* name) {
	if (this->prints.getSize() == 0) {
		std::cout << "No prints";
		return;
	}
	else if (this->users.getSize() == 0) {
		std::cout << "No users to take print";
		return;
	}
	size_t userIndex = 0;
	size_t printIndex = 0;
	bool flag1 = false;
	bool flag2 = false;
	for (unsigned i = 0; i < this->users.getSize(); i++) {
		try {
			if (!strcmp(this->users[i].getName(), name)) {
				userIndex = i;
				flag1 = true;
				break;
			}
		}
		catch (std::out_of_range& e) {
			std::cout << e.what();
		}
	}
	if (!flag1) {
		throw std::invalid_argument("Name of user not found");
	}
	for (unsigned i = 0; i < this->prints.getSize(); i++) {
		try {
			if (this->prints[i]->getLibNum() == libNum) {
				printIndex = i;
				flag2 = true;
				break;
			}
		}
		catch (std::out_of_range& e) {
			std::cout << e.what();
		}
	}
	if (!flag2) {
		throw std::invalid_argument("Wrong library number given");
	}
	try {
		this->users[userIndex] += this->prints[printIndex];
		this->prints.removePrint(this->prints[printIndex]->getLibNum());
	}
	catch (std::out_of_range& e) {
		std::cout << e.what();
	}
}

void Library::printUsers(){
	if (this->users.getSize() == 0) {
		std::cout << "No users to print";
		return;
	}
	if (this->users.isSorted()) {
		this->users.print();
	}
	else {
		this->users.sort();
		this->users.print();
	}
}

void Library::getPrintBack(const unsigned libNum, const char* name) {
	if (this->users.getSize() == 0) {
		std::cout << "No users to take print";
		return;
	}
	size_t userIndex = 0;
	size_t printIndex = 0;
	bool flag1 = false;
	bool flag2 = false;
	for (unsigned i = 0; i < this->users.getSize(); i++) {
		try {
			if (!strcmp(this->users[i].getName(), name)) {
				userIndex = i;
				flag1 = true;
				break;
			}
		}
		catch (std::out_of_range& e) {
			std::cout << e.what();
		}
	}
	if (!flag1) {
		throw std::invalid_argument("Name of user not found");
	}
	try {
		PEArray tmp = this->users[userIndex].getCurr();
		for (unsigned i = 0; i < tmp.getSize(); i++) {
			if (tmp[i]->getLibNum() == libNum) {
				printIndex = i;
				flag2 = true;
				break;
			}
		}
		if (!flag2) {
			throw std::invalid_argument("Wrong library number given");
		}
		this->prints.push(tmp[printIndex]);
		try {
			this->users[userIndex] -= tmp[printIndex];
		}
		catch (std::out_of_range& e) {
			std::cout << e.what();
		}
	}
	catch (std::out_of_range& e) {
		std::cout << e.what();
	}
}

void Library::printUsersReadingPrint(unsigned libnum) const {
	if (this->users.getSize() == 0) {
		std::cout << "No users to take print";
		return;
	}
	this->users.printAllReading(libnum);
}

void Library::readFile(std::ifstream& in) {
	if (in.peek() == std::ifstream::traits_type::eof()) {
		return;
	}
	this->prints.read(in);
	this->users.read(in);
}

void Library::writeFile(std::ofstream& out) const {
	if (this->users.getSize() == 0 && this->prints.getSize() == 0) {
		return;
	}
	this->prints.write(out);
	this->users.wrtie(out);
}

PEArray Library::getPrints() const {
	return this->prints;
}

UserArray Library::getUsers() const {
	return this->users;
}