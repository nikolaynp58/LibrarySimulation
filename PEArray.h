#pragma once
#include "PrintedEdition.h"
#include "Book.h"
#include "PeriodicalEdition.h"
#include "Comics.h"

class PEArray {
public:
	PEArray();
	PEArray(unsigned);
	PEArray(const PEArray&);
	~PEArray();
	PEArray& operator=(const PEArray&);
	PrintedEdition* operator[](unsigned) const;
	void push(const PrintedEdition*);
	void printAll() const;
	unsigned getSize() const;
	bool removePrint(unsigned);
	void write(std::ofstream&) const;
	void read(std::ifstream&);
private:
	PrintedEdition** data;
	unsigned size;
	unsigned cappacity;
};