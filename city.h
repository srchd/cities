#pragma once
/*
	-	Author: Sipos Richárd
	-	Neptun: K9P7QZ
	-	Task : simulate the change of a city, writing it ti stdout every year
*/
#include <string>
#include <iostream>
class Japanese;
class Modern;
class Trash;

enum ChangeTo{
	GOOD,
	AVG,
	BAD
};

class City
{
public:
	virtual void downgrade(Japanese* p) = 0;
	virtual void downgrade(Modern* p) = 0;
	virtual void downgrade(Trash* p) = 0;
	virtual std::string type() const = 0;
	virtual City* change(ChangeTo e) const = 0;
	virtual void upgrade() = 0;
	virtual int get_state() const = 0;
	virtual ChangeTo get_e() const = 0;
	virtual int get_money() const = 0;
	virtual ~City() {}

	friend std::ostream& operator<<(std::ostream& os, const City* city);
protected:
	int _money;
	int _state;
	ChangeTo _e;
	City () {}
};

class Good : public City {
public:
	static Good* instance(int k, int m=0);
	void downgrade(Japanese* p) override;
	void downgrade(Modern* p) override;
	void downgrade(Trash* p) override;
	void upgrade() override;

	std::string type() const override;
	int get_state() const override { return _state; }
	ChangeTo get_e() const override { return _e; }
	int get_money() const override { return _money; }

	City* change(ChangeTo e) const override;
	static void destroy();
protected:
	Good(){}
private:
	static Good* _instance;
};

class Avg : public City {
public:
	static Avg* instance(int k, int m=0);
	void downgrade(Japanese* p) override;
	void downgrade(Modern* p) override;
	void downgrade(Trash* p) override;
	void upgrade() override;

	std::string type() const override;
	int get_state() const override { return _state; }
	ChangeTo get_e() const override { return _e; }
	int get_money() const override { return _money; }

	City* change(ChangeTo e) const override;
	static void destroy();
protected:
	Avg() {}
private:
	static Avg* _instance;
};

class Bad : public City {
public:
	static Bad* instance(int k, int m=0);
	void downgrade(Japanese* p) override;
	void downgrade(Modern* p) override;
	void downgrade(Trash* p) override;
	void upgrade() override;

	std::string type() const override;
	int get_state() const override { return _state; }
	ChangeTo get_e() const override { return _e; }
	int get_money() const override { return _money; }

	City* change(ChangeTo e) const override;
	static void destroy();
protected:
	Bad() {}
private:
	static Bad* _instance;
};