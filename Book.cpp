#include "Book.h"

Book::Book() : Book("nothing", "nothing", 0, 0, "nothing", "nothing", 0) {}

Book::Book(const char* heading,const char* description,unsigned librarayNum,const unsigned yearOfIssue,const char* author,
	const char* publisher, short genre) :
	PrintedEdition(heading, description, librarayNum, yearOfIssue), genre(genre) {
	this->type = BOOK;
	try {
		this->setAuthor(author);
		this->setPublisher(publisher);
	}
	catch (std::bad_alloc& e) {
		std::cout << "Memory allocation problem";
		if (this->author != nullptr) {
			delete[] this->author;
		}
	}
	catch (std::invalid_argument& e) {
		std::cout << e.what();
	}
}

Book::Book(const Book& other): PrintedEdition(other) {
	this->type = BOOK;
	try {
		this->setAuthor(other.author);
		this->setPublisher(other.publisher);
	}
	catch (std::bad_alloc& e) {
		std::cout << "Memory allocation problem";
		if (this->author != nullptr) {
			delete[] this->author;
		}
	}
	catch (std::invalid_argument& e) {
		std::cout << e.what();
	}
}

Book& Book::operator=(const Book& other) {
	if (this != &other) {
		PrintedEdition::operator=(other);
		char* authorTmp = nullptr;
		char* publisherTmp = nullptr;
		try {
			this->copy(authorTmp, other.author);
			this->copy(publisherTmp, this->publisher);
		}
		catch (std::bad_alloc& e) {
			std::cout << "Memory allocation problem";
			if (authorTmp != nullptr) {
				delete[] authorTmp;
			}
		}
		this->clean();
		this->author = authorTmp;
		this->publisher = publisherTmp;
		this->genre = other.genre;
		this->type = BOOK;
	}
	return *this;
}

void Book::setAuthor(const char* author) {
	if (this->isCorrectString(author)) {
		this->copy(this->author, author);
	}
	else throw std::invalid_argument("Incorrect author give");
}

void Book::setPublisher(const char* publisher) {
	if (this->isCorrectString(publisher)) {
		this->copy(this->publisher, publisher);
	}
	else throw std::invalid_argument("Incorrect publisher given");
}

Book::~Book() {
	this->clean();
}

void Book::clean() {
	delete[] this->author;
	delete[] this->publisher;
}

PrintedEdition* Book::clone() const {
	return new Book(*this);
}

void Book::printOwn() const {
	std::cout << "(" << this->author << "," << this->publisher << ")" << std::endl;
}

void Book::write(std::ofstream& out) const {
	if (!out) {
		throw "File is not good";
	}
	size_t authorSize = strlen(this->author);
	size_t publisherSize = strlen(this->publisher);
	out.write(reinterpret_cast<const char*>(&authorSize), sizeof(authorSize));
	out.write(this->author, authorSize);
	out.write(reinterpret_cast<const char*>(&publisherSize), sizeof(publisherSize));
	out.write(this->publisher, publisherSize);
	out.write(reinterpret_cast<const char*>(&this->genre), sizeof(this->genre));
}

void Book::read(std::ifstream& in) {
	if (!in) {
		throw "File is not good";
	}
	size_t authorSize = 0;
	size_t publisherSize = 0;
	char* authorTmp = nullptr;
	char* publisherTmp = nullptr;
	try {
		in.read(reinterpret_cast<char*>(&authorSize), sizeof(authorSize));
		char* authorTmp = new char[authorSize + 1];
		in.read(authorTmp, authorSize);
		authorTmp[authorSize] = '\0';
		this->setAuthor(authorTmp);
		in.read(reinterpret_cast<char*>(&publisherSize), sizeof(publisherSize));
		char* publisherTmp = new char[publisherSize + 1];
		in.read(publisherTmp, publisherSize);
		publisherTmp[publisherSize - 1] = '\0';
		this->setPublisher(publisherTmp);
	}
	catch (std::bad_alloc& e) {
		std::cout << "Memory allocation problem";
		if (this->author != nullptr) {
			delete[] this->author;
		}
	}
	in.read(reinterpret_cast<char*>(&this->genre), sizeof(this->genre));
	delete[] authorTmp;
	delete[] publisherTmp;
}