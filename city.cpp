#include "city.h"
#include "tourist.h"

using namespace std;

std::ostream &operator<<(std::ostream &os, const City* city) {
	os << "Status points: " << city->get_state() << " Category: " << city->type();
	return os;
}

Good* Good::_instance = nullptr;
Good* Good::instance(int k, int m) {
	if (_instance == nullptr) {
		_instance = new Good();
		_instance->_state = k;
		_instance->_money = m;
	}
	return _instance;
}
void Good::destroy() {
	if (nullptr != _instance) delete _instance;
}
void Good::downgrade(Japanese* p) {
	_state -= 0;
	_money += p->get_lit() * 100000;
	if (_state < 1) _state = 1;
	if (_state >= 1 && _state <= 33) {
		_e = BAD;
	}
	else if (_state >= 34 && _state <= 67) {
		_e = AVG;
	}
	else
		_e = GOOD;
}
void Good::downgrade(Modern* p) {
	_state -= p->get_lit() / 100;
	_money += p->get_lit() * 100000;
	if (_state < 1) _state = 1;
	if (_state >= 1 && _state <= 33) {
		_e = BAD;
	}
	else if (_state >= 34 && _state <= 67) {
		_e = AVG;
	}
	else
		_e = GOOD;
}
void Good::downgrade(Trash* p) {
	_state -= p->get_lit() / 50;
	_money += p->get_lit() * 100000;
	if (_state < 1) _state = 1;
	if (_state >= 1 && _state <= 33) {
		_e = BAD;
	}
	else if (_state >= 34 && _state <= 67) {
		_e = AVG;
	}
	else
		_e = GOOD;
}
std::string Good::type() const {
	return "good";
}
City* Good::change(ChangeTo e) const {
	if (e == BAD)
		return Bad::instance(_state, _money);
	else if (e == AVG)
		return Avg::instance(_state, _money);
	else
		return Good::instance(_state, _money);
}
void Good::upgrade() {
	if (_money > 1000000000) {
		_money -= 1000000000;
		_state += _money / 20000000;
	}
	if (_state > 100)
		_state = 100;
	_money = 0;
}
//-------------------------AVG-------------------------------------------------------------------
Avg* Avg::_instance = nullptr;
Avg* Avg::instance(int k, int m) {
	if (_instance == nullptr) {
		_instance = new Avg();
		_instance->_state = k;
		_instance->_money = m;
	}
	return _instance;
}
void Avg::destroy() {
	if (nullptr != _instance) delete _instance;
}
void Avg::downgrade(Japanese* p) {
	_state -= 0;
	_money += p->get_lit() * 100000;
	if (_state < 1) _state = 1;
	if (_state >= 1 && _state <= 33) {
		_e = BAD;
	}
	else if (_state >= 68) {
		_e = GOOD;
	}
	else _e = AVG;
}
void Avg::downgrade(Modern* p) {
	_state -= p->get_lit() / 100;
	_money += p->get_lit() * 100000;
	if (_state < 1) _state = 1;
	if (_state >= 1 && _state <= 33) {
		_e = BAD;
	}
	else if (_state >= 68) {
		_e = GOOD;
	}
	else
		_e = AVG;
}
void Avg::downgrade(Trash* p) {
	_state -= p->get_lit() / 50;
	_money += p->get_lit() * 100000;
	if (_state < 1) _state = 1;
	if (_state >= 1 && _state <= 33) {
		_e = BAD;
	}
	else if (_state >= 68) {
		_e = GOOD;
	}
	else
		_e = AVG;
}
std::string Avg::type() const {
	return "avg";
}
City* Avg::change(ChangeTo e) const {
	if (e == BAD)
		return Bad::instance(_state, _money);
	else if (e == GOOD)
		return Good::instance(_state, _money);
	else
		return Avg::instance(_state, _money);
}
void Avg::upgrade() {
	if (_money > 1000000000) {
		_money -= 1000000000;
		_state += _money / 20000000;
	}
	if (_state > 100)
		_state = 100;
	_money = 0;
}
//-----------------------BAD----------------------------------------------------------------------
Bad* Bad::_instance = nullptr;
Bad* Bad::instance(int k, int m) {
	if (_instance == nullptr) {
		_instance = new Bad();
		_instance->_state = k;
		_instance->_money = m;
	}
	return _instance;
}
void Bad::destroy() {
	if (nullptr != _instance) delete _instance;
}
void Bad::downgrade(Japanese* p) {
	_state -= 0;
	_money += p->get_lit()* 100000;
	if (_state < 1) _state = 1;
	if (_state >= 34 && _state <= 67) {
		_e = AVG;
	}
	else if (_state >= 68) {
		_e = GOOD;
	}
	else
		_e = BAD;
}
void Bad::downgrade(Modern* p) {
	_state -= p->get_lit() / 100;
	_money += p->get_lit() * 100000;
	if (_state < 1) _state = 1;
	if (_state >= 34 && _state <= 67) {
		_e = BAD;
	}
	else if (_state >= 68) {
		_e = GOOD;
	}
	else
		_e = BAD;
}
void Bad::downgrade(Trash* p) {
	_state -= p->get_lit() / 50;
	_money += p->get_lit() * 100000;
	if (_state < 1) _state = 1;
	if (_state >= 34 && _state <= 67) {
		_e = BAD;
	}
	else if (_state >= 68) {
		_e = GOOD;
	}
	else
		_e = BAD;
}
std::string Bad::type() const {
	return "bad";
}
City* Bad::change(ChangeTo e) const {
	if (e == AVG)
		return Avg::instance(_state, _money);
	else if (e == GOOD)
		return Good::instance(_state, _money);
	else
		return Bad::instance(_state, _money);
}
void Bad::upgrade() {
	if (_money > 1000000000) {
		_money -= 1000000000;
		_state += _money / 20000000;
	}
	if (_state > 100)
		_state = 100;
	_money = 0;
}