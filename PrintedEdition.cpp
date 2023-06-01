#include  "PrintedEdition.h"

PrintedEdition::PrintedEdition() : PrintedEdition("nothing", "nothing", 0, 0) {}

PrintedEdition::PrintedEdition(const char* heading,const char* description,unsigned libraryNum, unsigned yearOfIssue):
	libraryNum(libraryNum),
	yearOfIssue(yearOfIssue){
	try {
		this->setHeading(heading);
		this->setDescription(description);
	}
	catch (std::bad_alloc& e) {
		std::cout << "Memory allocation problem";
		if (this->heading != nullptr) {
			delete[] this->heading;
		}
	}
	catch (std::invalid_argument& e) {
		std::cout << e.what();
	}
}

PrintedEdition::PrintedEdition(const PrintedEdition& other): PrintedEdition(other.heading, other.description,
other.libraryNum, other.yearOfIssue) {}

PrintedEdition& PrintedEdition::operator=(const PrintedEdition& other) {
	if (this != &other) {
		char* headingTmp = nullptr;
		char* descriptionTmp = nullptr;
		try {
			this->copy(headingTmp, other.heading);
			this->copy(descriptionTmp, other.description);
		}
		catch (std::bad_alloc& e) {
			std::cout << "Memory allocation problem";
			if (headingTmp != nullptr) {
				delete[] headingTmp;
			}
		}
		this->clean();
		this->heading = headingTmp;
		this->description = descriptionTmp;
		this->libraryNum = other.libraryNum;
		this->yearOfIssue = other.yearOfIssue;
	}
	return *this;
}


void PrintedEdition::setHeading(const char* heading) {
	if (this->isCorrectString(heading)) {
		this->copy(this->heading, heading);
	}
	else throw std::invalid_argument("Invalid heading given");
}

void PrintedEdition::setDescription(const char* description) {
	if (this->isCorrectString(description)) {
		this->copy(this->description, description);
	}
	else throw std::invalid_argument("Invalid description given");
}

PrintedEdition::~PrintedEdition() {
	this->clean();
}

void PrintedEdition::clean() {
	delete[] this->heading;
	delete[] this->description;
}

unsigned PrintedEdition::getLibNum() const {
	return this->libraryNum;
}

void PrintedEdition::print() const {
	std::cout << "HEADING: " << this->heading << " ";
	std::cout << "TYPE: " << this->type << " ";
	std::cout << "DESCRIPTIONS: " << this->description << " ";
	std::cout << "LIBRARY NUM: " << this->libraryNum << std::endl;
}

bool PrintedEdition::isCorrectString(const char* string) {
	return string && string[0] != '\0';
}

void PrintedEdition::copy(char*& dest, const char* source) {
	size_t len = strlen(source);
	dest = new char[len + 1];
	strcpy_s(dest, len + 1, source);
}

void PrintedEdition::writePrint(std::ofstream& out) const {
	if (!out) {
		throw "File is not good";
	}
	short typeNum = 0;
	switch (this->type)
	{
	case PERIODICAL:
		typeNum = 1;
		break;
	case COMICS:
		typeNum = 2;
		break;
	}
	out.write(reinterpret_cast<const char*>(&typeNum), sizeof(typeNum));
	size_t headingSize = strlen(this->heading);
	size_t descSize = strlen(this->description);
	out.write(reinterpret_cast<const char*>(&headingSize), sizeof(heading));
	out.write(this->heading, headingSize);
	out.write(reinterpret_cast<const char*>(&descSize), sizeof(descSize));
	out.write(this->description, descSize);
	out.write(reinterpret_cast<const char*>(&this->libraryNum), sizeof(this->libraryNum));
	out.write(reinterpret_cast<const char*>(&this->yearOfIssue), sizeof(this->yearOfIssue));
	this->write(out);
}

void PrintedEdition::readPrint(std::ifstream& in) {
	if (!in) {
		throw "File is not good";
	}
	size_t headingSize = 0;
	size_t descSize = 0;
	char* headingTmp = nullptr;
	char* descTmp = nullptr;
	try {
		in.read(reinterpret_cast<char*>(&headingSize), sizeof(headingSize));
		headingTmp = new char[headingSize + 1];
		in.read(headingTmp, headingSize);
		headingTmp[headingSize] = '\0';
		this->setHeading(headingTmp);
		in.read(reinterpret_cast<char*>(&descSize), sizeof(descSize));
		descTmp = new char[descSize + 1];
		in.read(descTmp, descSize);
		descTmp[descSize] = '\0';
		this->setDescription(descTmp);
	}
	catch (std::bad_alloc& e) {
		std::cout << "Memory allocation problem";
		if (this->heading != nullptr) {
			delete[] this->heading;
		}
	}
	in.read(reinterpret_cast<char*>(&this->libraryNum), sizeof(this->libraryNum));
	in.read(reinterpret_cast<char*>(&this->yearOfIssue), sizeof(this->yearOfIssue));
	this->read(in);
	delete[] headingTmp;
	delete[] descTmp;
}