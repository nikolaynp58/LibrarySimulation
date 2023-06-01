#include "Comics.h"

Comics::Comics() : Comics(nullptr, nullptr, 0, 0, nullptr, nullptr, 0, YEARLY, 0) {}

Comics::Comics(const char* heading,const char* description,unsigned libraryNum, unsigned yearOfIssue,
				const char* author,const char* publisher, short genre,const Period& period, int number):
				PrintedEdition(heading, description, libraryNum, yearOfIssue),
				Book(heading, description, libraryNum, yearOfIssue, author, publisher, genre),
				PeriodicalEdition(heading, description, libraryNum, yearOfIssue, period, number)
{
	this->type = COMICS;
}

Comics::Comics(const Comics& other):PrintedEdition(other), Book(other), PeriodicalEdition(other) {
	this->type = COMICS;
}

Comics& Comics::operator=(const Comics& other) {
	if (this != &other) {
		Book::operator=(other);
		PeriodicalEdition::operator=(other);
		this->type = COMICS;
	}
	return *this;
}

PrintedEdition* Comics::clone() const {
	return new Comics(*this);
}

void Comics::printOwn() const {
	Book::printOwn();
	PeriodicalEdition::printOwn();
}

void Comics::write(std::ofstream& out) const {
	Book::write(out);
	PeriodicalEdition::write(out);
}

void Comics::read(std::ifstream& in){
	Book::read(in);
	PeriodicalEdition::read(in);
}