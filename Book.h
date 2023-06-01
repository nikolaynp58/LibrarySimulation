#pragma once
#include "PrintedEdition.h"

class Book : virtual public PrintedEdition {
public:
	Book();
	Book(const char*,const char*,unsigned, unsigned,const char*,const char*, short);
	Book(const Book&);
	Book& operator=(const Book&);
	virtual ~Book() override;
	virtual void printOwn() const override;
	virtual PrintedEdition* clone() const;
protected:
	char* author;
	char* publisher;
	short genre;
	virtual void clean() override;
	virtual void write(std::ofstream&) const override;
	virtual void read(std::ifstream&) override;
private:
	void setAuthor(const char*);
	void setPublisher(const char*);
};