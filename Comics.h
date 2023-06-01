#pragma once
#include "Book.h"
#include "PeriodicalEdition.h"

class Comics : public Book, public PeriodicalEdition {
public:
	Comics();
	Comics(const char*,const char*,unsigned, unsigned,const char*,const char*,short,const Period&, int);
	Comics(const Comics&);
	Comics&operator=(const Comics&);
	virtual void printOwn() const override;
	virtual PrintedEdition* clone() const;
private:
	virtual void write(std::ofstream&) const override;
	virtual void read(std::ifstream&) override;
};