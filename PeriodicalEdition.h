#pragma once
#include "PrintedEdition.h"

enum Period {
	WEEKLY,
	MONTHLY,
	YEARLY
};

class PeriodicalEdition : virtual public PrintedEdition {
public:
	PeriodicalEdition();
	PeriodicalEdition(const char*,const char*,unsigned ,unsigned,const Period&, unsigned);
	PeriodicalEdition(const PeriodicalEdition&);
	PeriodicalEdition& operator=(const PeriodicalEdition&);
	virtual ~PeriodicalEdition() override;
	virtual void printOwn() const override;
	virtual PrintedEdition* clone() const;
protected:
	virtual void write(std::ofstream&) const override;
	virtual void read(std::ifstream&) override;
	Period period;
	unsigned number;
};