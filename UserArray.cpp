#include "UserArray.h"

UserArray::UserArray() : UserArray(1){}

UserArray::UserArray(unsigned size) : size(0), cappacity(size * 2) {
	try {
		this->data = new User[this->cappacity * 2];
	}
	catch (std::bad_alloc& e) {
		std::cout << "Memory allocation problem";
	}
}

UserArray::UserArray(const UserArray& other) : size(other.size), cappacity(other.cappacity) {
	try {
		this->data = new User[other.cappacity];
	}
	catch (std::bad_alloc& e) {
		std::cout << "Memory allocation problem";
	}
	for (int i = 0; i < other.size; i++) {
		this->data[i] = other.data[i];
	}
}

UserArray::~UserArray() {
	delete[] data;
}

UserArray& UserArray::operator=(const UserArray& other) {
	if (this != &other) {
		User* tmp = nullptr;
		try {
			tmp = new User[other.cappacity];
		}
		catch (std::bad_alloc& e) {
			std::cout << "Memory allocation problem";
		}
		delete[] this->data;
		this->data = tmp;
		this->size = other.size;
		this->cappacity = other.cappacity;
		for (int i = 0; i < other.size; i++) {
			this->data[i] = other.data[i];
		}
	}
	return *this;
}

User& UserArray::operator[](unsigned index) const{
	if (index < 0 || index > this->size) {
		throw std::out_of_range("Index out of range");
	}
	return data[index];
}

void UserArray::push(const User& newUser) {
	if (this->size == this->cappacity) {
		this->cappacity = this->cappacity * 2;
		User* tmp = nullptr;
		try {
			tmp = new User[this->cappacity];
		}
		catch (std::bad_alloc& e) {
			std::cout << "Memory allocation problem";
		}
		for (int i = 0; i < this->size; i++) {
			tmp[i] = this->data[i];
		}
		delete[] this->data;
		this->data = tmp;
	}
	this->data[size++] = newUser;
}

bool UserArray::removeUser(const char* name) {
	bool found = false;
	for (int i = 0; i < this->size; i++) {
		if (!strcmp(name, data[i].getName())) {
			found = true;
			for (int j = i; j < this->size - 1; j++) {
				this->data[j] = this->data[j + 1];
			}
		}
	}
	if (!found) {
		return false;
	}
	this->size--;
	return true;
}

unsigned UserArray::getSize() const{
	return this->size;
}

void UserArray::printAllReading(unsigned libnum) const {
	for (unsigned i = 0; i < this->size; i++) {
		PEArray curr = this->data[i].getCurr();
		for (unsigned j = 0; j < curr.getSize(); j++) {
			if (curr[j]->getLibNum() == libnum) {
				std::cout << this->data[i].getName();
			}
		}
	}
}

void UserArray::sort() {
	for (int i = 0; i < this->size - 1; ++i) {
		for (int j = 0; j < this->size - i - 1; ++j) {
			if (this->data[j] > this->data[j + 1]) {
				std::swap(this->data[j], this->data[j + 1]);
			}
		}
	}
}

void UserArray::print() const {
	for (unsigned i = 0; i < this->size; i++) {
		this->data[i].print();
	}
}

bool UserArray::isSorted() const {
	for (unsigned i = 0; i < this->size - 1; ++i) {
		if (this->data[i] > this->data[i + 1]) {
			return false;
		}
	}
	return true;
}

void UserArray::wrtie(std::ofstream& out) const {
	if (!out) {
		throw "File is not good";
	}
	out.write(reinterpret_cast<const char*>(&this->size), sizeof(this->size));
	for (unsigned i = 0; i < this->size; i++) {
		this->data[i].write(out);
	}
}

void UserArray::read(std::ifstream& in) {
	if (!in) {
		throw "File is not good";
	}
	unsigned size = 0;
	in.read(reinterpret_cast<char*>(&size), sizeof(size));
	for (unsigned i = 0; i < size; i++) {
		User tmp;
		tmp.read(in);
		this->push(tmp);
	}
}