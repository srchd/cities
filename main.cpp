
//#include <iostream>
#include "city.h"
#include "tourist.h"
#include <vector>
#include <fstream>

#define JAPAN 0
#define MODERN 1
#define TRASH 2

using namespace std;

void read(const string& fname, City*& c, vector<Tourist*>& t, int& _years) {
	ifstream f(fname.c_str());
	if (f.fail()) {
		cout << "Wrong file name!\n";
		exit(1);
	}
	int data;

	f >> data;
	cout << data << endl;
	if (data >= 1 && data <= 33)
		c = Bad::instance(data);
	else if (data >= 34 && data <= 67)
		c = Avg::instance(data);
	else
		c = Good::instance(data);
	f >> _years;
	cout << _years << endl;

	int j, m, tr;
	while (f >> j >> m >> tr) {
		t.push_back(new Japanese(j));
		t.push_back(new Modern(m));
		t.push_back(new Trash(tr));
		cout << j << ' ' << m << ' ' << tr << endl;
	}
	f.close();
	/*for (Tourist* x : t) {
		x->literally(c);
	}*/
}

void simulate(vector<Tourist*>& _t, City*& c, int _sim_y) {
	cout << "==================== BEGINNING OF YEAR " << _sim_y << " ===============================" << endl;
	//Generate _lit variable
	_t[JAPAN]->literally(c);
	_t[MODERN]->literally(c);
	_t[TRASH]->literally(c);
	cout << "Japanese:\n\t";
	cout << _t[JAPAN] << endl;
	_t[JAPAN]->downgrade(c);
	cout << "Modern:\n\t";
	cout << _t[MODERN] << endl;
	_t[MODERN]->downgrade(c);
	cout << "People with littering habit:\n\t";
	cout << _t[TRASH] << endl;
	_t[TRASH]->downgrade(c);
	cout << "This year's income: " << c->get_money() << endl;
	cout << "City before renovation:\n\t";
	c = c->change(c->get_e());
	cout << c << endl;
	
	c->upgrade();
	_t.erase(_t.begin(), _t.begin() + 3);
	cout << "====================== END OF YEAR " << _sim_y << " ========================================" << endl;
}

template <typename Item>
void destroy(vector<Item*> &vec) {
	for (unsigned int i = 0; i < vec.size(); i++) {
		delete vec[i];
	}
}

void destroy_citi_states() {
	Good::destroy();
	Avg::destroy();
	Bad::destroy();
}


//#define NORMAL_MODE
#ifdef NORMAL_MODE

int main(){
	City* c;
	vector<Tourist*> _tourists;
	int years;
	string fnam;
	cout << "File name: "; cin >> fnam; cout << endl;

	read(fnam, c, _tourists, years);
	int sim_year = 1;
	while (sim_year <= years){
		simulate(_tourists, c, sim_year);
		sim_year++;
	}

	cout << "\n\nAfter " << years << " of simulation:\n\t";
	cout << c;

	destroy(_tourists);
	destroy_citi_states();
	return 0;
}
#else
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

void catch_read(const string& fname, City*& c, vector<Tourist*>& t, int& _years) {
	ifstream f(fname.c_str());
	int data;

	f >> data;
	//cout << data;
	if (data >= 1 && data <= 33)
		c = Bad::instance(data);
	else if (data >= 34 && data <= 67)
		c = Avg::instance(data);
	else
		c = Good::instance(data);
	f >> _years;

	int j, m, tr;
	while (f >> j >> m >> tr) {
		t.push_back(new Japanese(j));
		t.push_back(new Modern(m));
		t.push_back(new Trash(tr));
	}
	f.close();
}

void catch_simulate(vector<Tourist*>& _t, City*& c) {
	//Generate _lit variable
	_t[JAPAN]->literally(c);
	_t[MODERN]->literally(c);
	_t[TRASH]->literally(c);
	//cout << _t[JAPAN]->get_lit() << " " << _t[MODERN]->get_lit() << " " << _t[TRASH]->get_lit() << endl;
	_t[JAPAN]->downgrade(c);
	_t[MODERN]->downgrade(c);
	_t[TRASH]->downgrade(c);
	//cout << c->get_e() << endl;
	c = c->change(c->get_e());
	c->upgrade();
	_t.erase(_t.begin(), _t.begin() + 3);
}

TEST_CASE("city starts in bad, no tourists", "inp1.txt") {
	City* c;
	vector<Tourist*> _t;
	int _y;
	catch_read("inp1.txt", c, _t, _y);

	CHECK(c->type() == "bad");
	CHECK(_t.size() == 0);

	//destroy_citi_states();
	destroy(_t);
}

TEST_CASE("city starts in bad, with tourists", "inp2.txt") {
	City* c;
	vector<Tourist*> _t;
	int _y;
	catch_read("inp2.txt", c, _t, _y);

	CHECK(c->type() == "bad");
	CHECK_FALSE(_t.size() == 0);

	//destroy_citi_states();
	destroy(_t);
}

TEST_CASE("city starts in bad, with tourists, not increasing", "inp3.txt") {
	City* c;
	vector<Tourist*> _t;
	int _y;
	catch_read("inp3.txt", c, _t, _y);

	CHECK(c->type() == "bad");
	CHECK_FALSE(_t.size() == 0);
	int _s = 1;
	while (_s <= _y) {
		catch_simulate(_t, c);
		_s++;
		CHECK(c->type() == "bad");
		CHECK((c->get_state() <= 33 && c->get_state() >= 1));
	}
	CHECK(c->type() == "bad");
	CHECK((c->get_state() <= 33 && c->get_state() >= 1));

	//destroy_citi_states();
	destroy(_t);
}

TEST_CASE("city starts in bad, with japanese, can not increase", "inp4.txt") {
	City* c;
	vector<Tourist*> _t;
	int _y;
	catch_read("inp4.txt", c, _t, _y);

	CHECK(c->type() == "bad");
	CHECK_FALSE(_t.size() == 0);
	int _s = 1;
	while (_s <= _y) {
		catch_simulate(_t, c);
		_s++;
	}
	CHECK(c->type() == "bad");
	CHECK((c->get_state() <= 33 && c->get_state() >= 1));

	destroy(_t);
}
//================================================== STARTS IN AVG ====================================

TEST_CASE("city starts in avg, no tourists", "inp5.txt") {
	City* c;
	vector<Tourist*> _t;
	int _y;
	catch_read("inp5.txt", c, _t, _y);

	CHECK(c->type() == "avg");
	CHECK(_t.size() == 0);

	//destroy_citi_states();
	destroy(_t);
}
TEST_CASE("city starts in avg, with tourists", "inp6.txt") {
	City* c;
	vector<Tourist*> _t;
	int _y;
	catch_read("inp6.txt", c, _t, _y);

	CHECK(c->type() == "avg");
	CHECK_FALSE(_t.size() == 0);

	//destroy_citi_states();
	destroy(_t);
}
TEST_CASE("city starts in avg, with tourists, not increasing/decreasing", "inp7.txt") {
	City* c;
	vector<Tourist*> _t;
	int _y;
	catch_read("inp7.txt", c, _t, _y);

	CHECK(c->type() == "avg");
	CHECK_FALSE(_t.size() == 0);
	int _s = 1;
	while (_s <= _y) {
		catch_simulate(_t, c);
		_s++;
		CHECK(c->type() == "avg");
		CHECK((c->get_state() <= 67 && c->get_state() >= 34));
	}
	CHECK(c->type() == "avg");
	CHECK((c->get_state() <= 67 && c->get_state() >= 34));

	//destroy_citi_states();
	destroy(_t);
}


TEST_CASE("city starts in avg, with tourists, decreasing after first year", "inp8.txt") {
	City* c;
	vector<Tourist*> _t;
	int _y;
	catch_read("inp8.txt", c, _t, _y);

	CHECK(c->type() == "avg");
	CHECK_FALSE(_t.size() == 0);
	int _s = 1;
	while (_s <= _y) {
		catch_simulate(_t, c);
		_s++;
		CHECK(c->type() == "bad");
		CHECK((c->get_state() <= 33 && c->get_state() >= 1));
	}
	CHECK(c->type() == "bad");
	CHECK((c->get_state() <= 33 && c->get_state() >= 1));
	destroy(_t);
}

TEST_CASE("city starts in avg, with tourists, decreasing after second year", "inp9.txt") {
	City* c;
	vector<Tourist*> _t;
	int _y;
	catch_read("inp9.txt", c, _t, _y);

	CHECK(c->type() == "avg");
	CHECK(c->get_state() == 50);
	CHECK_FALSE(_t.size() == 0);
	
	catch_simulate(_t, c);
	CHECK(c->type() == "avg");
	CHECK((c->get_state() <= 67 && c->get_state() >= 34));

	catch_simulate(_t, c);
	CHECK(c->type() == "bad");
	CHECK((c->get_state() <= 33 && c->get_state() >= 1));

	destroy(_t);
}
TEST_CASE("city starts in avg, with tourists, increasing after first year", "inp10.txt") {
	City* c;
	vector<Tourist*> _t;
	int _y;
	catch_read("inp10.txt", c, _t, _y);

	CHECK(c->type() == "avg");
	CHECK(c->get_state() == 60);
	CHECK_FALSE(_t.size() == 0);

	catch_simulate(_t, c);
	CHECK(c->type() == "good");
	CHECK((c->get_state() <= 100 && c->get_state() >= 68));

	destroy(_t);
}

TEST_CASE("city starts in avg, with tourists, increasing after second year", "inp11.txt") {
	City* c;
	vector<Tourist*> _t;
	int _y;
	catch_read("inp11.txt", c, _t, _y);

	CHECK(c->type() == "avg");
	CHECK(c->get_state() == 50);
	CHECK_FALSE(_t.size() == 0);

	catch_simulate(_t, c);
	CHECK(c->type() == "avg");

	catch_simulate(_t, c);
	CHECK(c->type() == "good");
	CHECK((c->get_state() <= 100 && c->get_state() >= 68));

	destroy(_t);
}
//=================================================================== STARTS IN GOOD =========================================
TEST_CASE("city starts in good, no tourists", "inp12.txt") {
	City* c;
	vector<Tourist*> _t;
	int _y;
	catch_read("inp12.txt", c, _t, _y);

	CHECK(c->type() == "good");
	CHECK(_t.size() == 0);

	//destroy_citi_states();
	destroy(_t);
}
TEST_CASE("city starts in good, with tourists", "inp13.txt") {
	City* c;
	vector<Tourist*> _t;
	int _y;
	catch_read("inp13.txt", c, _t, _y);

	CHECK(c->type() == "good");
	CHECK_FALSE(_t.size() == 0);

	//destroy_citi_states();
	destroy(_t);
}
TEST_CASE("city starts in good, with tourists, not decreasing", "inp14.txt") {
	City* c;
	vector<Tourist*> _t;
	int _y;
	catch_read("inp14.txt", c, _t, _y);

	CHECK(c->type() == "good");
	CHECK_FALSE(_t.size() == 0);
	int _s = 1;
	while (_s <= _y) {
		catch_simulate(_t, c);
		_s++;
		CHECK(c->type() == "good");
		CHECK((c->get_state() <= 100 && c->get_state() >= 68));
	}
	CHECK(c->type() == "good");
	CHECK((c->get_state() <= 100 && c->get_state() >= 68));

	//destroy_citi_states();
	destroy(_t);
}
TEST_CASE("city starts in good, with tourists, decreasing after first year", "inp15.txt") {
	City* c;
	vector<Tourist*> _t;
	int _y;
	catch_read("inp15.txt", c, _t, _y);

	CHECK(c->type() == "good");
	CHECK_FALSE(_t.size() == 0);
	int _s = 1;
	while (_s <= _y) {
		catch_simulate(_t, c);
		_s++;
		CHECK(c->type() == "avg");
		CHECK((c->get_state() <= 67 && c->get_state() >= 34));
	}
	CHECK(c->type() == "avg");
	CHECK((c->get_state() <= 67 && c->get_state() >= 34));
	destroy(_t);
}
TEST_CASE("city starts in good, with tourists, decreasing after second year", "inp16.txt") {
	City* c;
	vector<Tourist*> _t;
	int _y;
	catch_read("inp16.txt", c, _t, _y);

	CHECK(c->type() == "good");
	CHECK(c->get_state() == 80);
	CHECK_FALSE(_t.size() == 0);

	catch_simulate(_t, c);
	CHECK(c->type() == "good");
	CHECK((c->get_state() <= 100 && c->get_state() >= 68));

	catch_simulate(_t, c);
	CHECK(c->type() == "avg");
	CHECK((c->get_state() <= 67 && c->get_state() >= 34));

	destroy(_t);
}
#endif // NORMAL_MODE
