#pragma once
#include <iostream>
#include <fstream>

enum Type{
	BOOK,
	PERIODICAL,
	COMICS
};

class PrintedEdition {
public:
	PrintedEdition();
	PrintedEdition(const char*,const char*,unsigned, unsigned);
	PrintedEdition(const PrintedEdition&);
	PrintedEdition& operator=(const PrintedEdition&);
	virtual PrintedEdition* clone() const = 0;
	virtual ~PrintedEdition();
	unsigned getLibNum() const;
	void print() const;
	void writePrint(std::ofstream&) const;
	void readPrint(std::ifstream&);
protected:
	virtual void write(std::ofstream&) const = 0;
	virtual void read(std::ifstream&) = 0;
	virtual void clean();
	virtual void printOwn() const = 0;
	bool isCorrectString(const char*);
	void copy(char*&, const char*);
	char* heading;
	char* description;
	unsigned libraryNum;
	unsigned yearOfIssue;
	Type type;
private:
	void setHeading(const char*);
	void setDescription(const char*);
};