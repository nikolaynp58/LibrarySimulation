#include "User.h"

User::User() : User("noname") {}

User::User(const char* name):readPrints(), currPrints() {
	try {
		this->setName(name);
	}
	catch (std::bad_alloc& e) {
		std::cout << "Memory allocation problem";
	}
	catch (std::invalid_argument& e) {
		std::cout << e.what();
	}
}

User::User(const User& other) {
	try{
	this->setName(other.name);
	}
	catch (std::bad_alloc& e) {
		std::cout << "Memory allocation problem";
	}
	this->readPrints = other.readPrints;
	this->currPrints = other.currPrints;
}

User& User::operator=(const User& other) {
	if (this != &other) {
		char* tmp = nullptr;
		try {
			this->copy(tmp, other.name);
		}
		catch (std::bad_alloc& e) {
			std::cout << "Memory allocation problem";
		}
		this->clean();
		this->name = tmp;
		this->readPrints = other.readPrints;
		this->currPrints = other.currPrints;
	}
	return *this;
}

User::~User() {
	this->clean();
}

void User::clean() {
	delete[] this->name;
}

const char* User::getName() const {
	return this->name;
}

void User::setName(const char* name){
	if (this->isCorrectString(name)) {
		this->copy(this->name, name);
	}
	else throw std::invalid_argument("Invalid name give");
}

bool User::isCorrectString(const char* string) {
	return string && string[0] != '\0';
}

void User::copy(char*& dest, const char* source) {
	size_t len = strlen(source);
	dest = new char[len + 1];
	strcpy_s(dest, len + 1, source);
}

bool User::operator==(const User& other) const{
	return !strcmp(this->name, other.name);
}

bool User::operator!=(const User& other) const {
	return !(*this == other);
}

bool User::operator<(const User& other) const {
	return this->readPrints.getSize() < other.readPrints.getSize();
}

bool User::operator>(const User& other) const {
	return !(*this < other);
}

bool User::operator<=(const User& other) const {
	return this->readPrints.getSize() <= other.readPrints.getSize();
}

bool User::operator>=(const User& other) const {
	return !(*this <= other);
}

User& User::operator+=(const PrintedEdition* print) {
	if (this->currPrints.getSize() == 5) {
		throw std::out_of_range("Can't read more than 5 prints at a time");
	}
	this->currPrints.push(print);
	this->readPrints.push(print);
	return *this;
}

User User::operator+(const PrintedEdition* print) const{
	if (this->currPrints.getSize() == 5) {
		throw std::out_of_range("Can't read more than 5 prints at a time");
	}
	User tmp = *this;
	tmp += print;
	return tmp;
}

User& User::operator-=(const PrintedEdition* print){
	if (this->currPrints.getSize() == 0) {
		throw std::out_of_range("No prints in read");
	}
	this->currPrints.removePrint(print->getLibNum());
	return *this;
}

User User::operator-(const PrintedEdition* print) const {
	if (this->currPrints.getSize() == 0) {
		throw std::out_of_range("No prints in read");
	}
	User tmp = *this;
	tmp -= print;
	return tmp;
}

void User::operator[](unsigned libNum) const {
	for (size_t i = 0; i < this->currPrints.getSize(); i++) {
		if (this->currPrints[i]->getLibNum() == libNum) {
			std::cout << "Print is currently being red";
			return;
		}
	}
	for (size_t i = 0; i < this->readPrints.getSize(); i++) {
		if (this->readPrints[i]->getLibNum() == libNum) {
			std::cout << "Print is already read";
			return;
		}
	}
	std::cout << "Print has not been taken";
}

PEArray User::getCurr() const{
	return this->currPrints;
}

PEArray User::getRead() const {
	return this->readPrints;
}

void User::print() const {
	std::cout << this->name << std::endl << "current reads : {";
	for (unsigned i = 0; i < this->currPrints.getSize(); i++) {
		this->currPrints[i]->print();
	}
	std::cout << "}" << std::endl;
	std::cout << "read prints : {";
	for (unsigned i = 0; i < this->readPrints.getSize(); i++) {
		this->readPrints[i]->print();
	}
	std::cout << "}" << std::endl;
}

void User::write(std::ofstream& out) {
	if (!out) {
		throw "File is not good";
	}
	size_t nameSize = strlen(this->name);
	out.write(reinterpret_cast<const char*>(&nameSize), sizeof(nameSize));
	out.write(this->name, nameSize);
	this->currPrints.write(out);
	this->readPrints.write(out);
}

void User::read(std::ifstream& in) {
	if (!in) {
		throw "File is not good";
	}
	size_t nameSize = 0;
	in.read(reinterpret_cast<char*>(&nameSize), sizeof(nameSize));
	char* tmpName = new char[nameSize + 1];
	in.read(tmpName, nameSize);
	tmpName[nameSize] = '\0';
	this->setName(tmpName);
	this->currPrints.read(in);
	this->readPrints.read(in);
	delete[] tmpName;
}