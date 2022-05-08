#ifndef RANDINT_H
#define RANDINT_H

#include <random>
#include <functional>

class RandInt {
public:
	RandInt(int lo, int hi);
	int operator()() const { return r(); }
	operator int() const { return r(); }
private:
	std::random_device rd;
	std::function<int()> r;
};

#endif
