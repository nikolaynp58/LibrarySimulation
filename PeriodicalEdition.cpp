#include "PeriodicalEdition.h"

PeriodicalEdition::PeriodicalEdition(): PeriodicalEdition(nullptr, nullptr, 0, 0, YEARLY, 0) {}

PeriodicalEdition::PeriodicalEdition(const char* heading,const char* description,unsigned libraryNum, 
	unsigned yearOfIssue, const Period& period, unsigned number): 
	PrintedEdition(heading, description, libraryNum, yearOfIssue), period(period), number(number) {
	this->type = PERIODICAL;
}

PeriodicalEdition::~PeriodicalEdition() {}

PeriodicalEdition::PeriodicalEdition(const PeriodicalEdition& other):PrintedEdition(other), period(other.period), number(other.number) {
	this->type = PERIODICAL;
}

PeriodicalEdition& PeriodicalEdition::operator=(const PeriodicalEdition& other) {
	if (this != &other) {
		PrintedEdition::operator=(other);
		this->period = other.period;
		this->number = other.number;
		this->type = PERIODICAL;
	}
	return *this;
}

PrintedEdition* PeriodicalEdition::clone() const {
	return new PeriodicalEdition(*this);
}

void PeriodicalEdition::printOwn() const {
	std::cout << "(" << this->period << "," << this->number << ")" << std::endl;
}

void PeriodicalEdition::write(std::ofstream& out) const {
	short periodNum = 0;
	switch (this->period)
	{
	case MONTHLY:
		periodNum = 1;
		break;
	case YEARLY:
		periodNum = 2;
		break;
	}
	out.write(reinterpret_cast<const char*>(&periodNum), sizeof(periodNum));
	out.write(reinterpret_cast<const char*>(&this->number), sizeof(this->number));
}

void PeriodicalEdition::read(std::ifstream& in) {
	short periodNum = 0;
	in.read(reinterpret_cast<char*>(&periodNum), sizeof(periodNum));
	switch (this->period)
	{
	case WEEKLY:
		this->period = WEEKLY;
		break;
	case MONTHLY:
		this->period = MONTHLY;
		break;
	case YEARLY:
		this->period = YEARLY;
		break;
	}
	in.read(reinterpret_cast<char*>(&this->number), sizeof(this->number));
}