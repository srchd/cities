#pragma once
/*
	-	Author: Sipos Richárd
	-	Neptun: K9P7QZ
	-	Task : simulate the change of a city, writing it ti stdout every year
*/
#include "city.h"
class Tourist {
protected:
	int _planned;
	int _lit;
	Tourist(int planned) : _planned(planned) {}
public:
	virtual void downgrade(City* city) = 0;
	virtual void literally(City* city) = 0;
	virtual int get_lit() const = 0;
	virtual ~Tourist() {}
	friend std::ostream& operator<<(std::ostream& os, const Tourist* t) {
		os << "Planned: " << t->_planned << "\n\tBut actually came: " << t->_lit;
		return os;
	}
};

class Japanese : public Tourist {
public:
	Japanese(int planned) : Tourist(planned){}
	void downgrade(City* c) override { c->downgrade(this); }
	void literally(City* c) override {
		if (c->type() == "good") {
			_lit = _planned * 1.2;
		}
		else if (c->type() == "avg") {
			_lit = _planned;
		}
		else {
			_lit = 0;
		}
	}
	int get_lit() const override { return _lit; }
};

class Modern : public Tourist {
public:
	Modern(int planned) : Tourist(planned) {}
	void downgrade(City* c) override { c->downgrade(this); }
	void literally(City* c) override {
		if (c->type() == "good") {
			_lit = _planned * 1.3;
		}
		else if (c->type() == "avg") {
			_lit = _planned * 1.1;
		}
		else {
			_lit = _planned;
		}
	}
	int get_lit() const override { return _lit; }
};

class Trash : public Tourist {
public:
	Trash(int planned) : Tourist(planned) {}
	void downgrade(City* c) override { c->downgrade(this); }
	void literally(City* c) override {
		if (c->type() == "good") {
			_lit = _planned;
		}
		else if (c->type() == "avg") {
			_lit = _planned * 1.1;
		}
		else {
			_lit = _planned;
		}
	}
	int get_lit() const override { return _lit; }
};