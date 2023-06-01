#include "PEArray.h"
#include <iostream>

PEArray::PEArray() : PEArray(1){}

PEArray::PEArray(unsigned size) : size(0), cappacity(size) {
	try {
		this->data = new PrintedEdition * [this->cappacity];
	}
	catch (std::bad_alloc& e) {
		std::cout << "Memory allocation problem";
	}
}

PEArray::PEArray(const PEArray& other) :size(other.size), cappacity(other.cappacity) {
	try {
		this->data = new PrintedEdition * [other.cappacity];
	}
	catch (std::bad_alloc& e) {
		std::cout << "Memory allocation problem";
	}
	for (size_t i = 0; i < other.size; i++) {
		this->data[i] = other.data[i]->clone();
	}
}

PEArray::~PEArray() {
	for (size_t i = 0; i < this->size; i++) {
		delete this->data[i];
	}
	delete[] this->data;
}

PEArray& PEArray::operator=(const PEArray& other) {
	if (this != &other) {
		PrintedEdition** tmp = nullptr;
		try {
			tmp = new PrintedEdition * [other.cappacity];
		}
		catch (std::bad_alloc& e) {
			std::cout << "Memory allocation problem";
		}
		for (unsigned i = 0; i < this->size; i++) {
			delete this->data[i];
		}
		delete[] this->data;
		this->data = tmp;
		this->size = other.size;
		this->cappacity = other.cappacity;
		for (unsigned i = 0; i < other.size; i++) {
			this->data[i] = other.data[i]->clone();
		}
	}
	return *this;
}

PrintedEdition* PEArray::operator[](unsigned index) const{
	if (index < 0 || index > this->size) {
		throw std::out_of_range("Index out of range");
	}
	return data[index];
}

void PEArray::push(const PrintedEdition* newPrint) {
	if (this->size == this->cappacity) {
		unsigned newCappacity = this->cappacity * 2;
		PrintedEdition** tmp = nullptr;

		try {
			tmp = new PrintedEdition * [newCappacity];
		}
		catch (std::bad_alloc& e) {
			std::cout << "Memory allocation problem";
		}

		for (unsigned i = 0; i < this->size; i++) {
			tmp[i] = this->data[i]->clone();
			delete this->data[i];
		}
		delete[] this->data;
		this->data = tmp;
		this->cappacity = newCappacity;
	}
	this->data[size++] = newPrint->clone();
}

bool PEArray::removePrint(unsigned libNum) {
	bool found = false;
	for (unsigned i = 0; i < this->size; i++) {
		if (this->data[i]->getLibNum() == libNum) {
			found = true;
			delete this->data[i];
			for (unsigned j = i; j < this->size - 1; j++) {
				data[j] = data[j+1]->clone();
			}
		}
	}
	if (!found) {
		return false;
	}
	this->size--;
	return true;
}

unsigned PEArray::getSize() const{
	return this->size;
}

void PEArray::printAll() const {
	for (unsigned i = 0; i < this->size; i++) {
		this->data[i]->print();
	}
}

void PEArray::write(std::ofstream& out) const {
	if (!out) {
		throw "File is not good";
	}
	out.write(reinterpret_cast<const char*>(&this->size), sizeof(this->size));
	for (unsigned i = 0; i < this->size; i++) {
		this->data[i]->writePrint(out);
	}
}

void PEArray::read(std::ifstream& in) {
	if (!in) {
		throw "File is not good";
	}
	unsigned size = 0;
	in.read(reinterpret_cast<char*>(&size), sizeof(size));
	for (unsigned i = 0; i < size; i++) {
		short type = 0;
		in.read(reinterpret_cast<char*>(&type), sizeof(type));
		PrintedEdition* tmp = nullptr;
		try {
			switch (type)
			{
			case 0:
				tmp = new Book;
				break;
			case 1:
				tmp = new PeriodicalEdition;
				break;
			case 2:
				tmp = new Comics;
				break;
			}
		}
		catch (std::bad_alloc& e) {
			std::cout << "Memory allocation problem";
		}
		tmp->readPrint(in);
		this->push(tmp);
	}
}