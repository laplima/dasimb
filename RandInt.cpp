#include "RandInt.h"

RandInt::RandInt(int lo, int hi)
	: r{[lo, hi, this]() {
		std::default_random_engine gen{this->rd()};
        std::uniform_int_distribution<int> uid{lo, hi};
        return uid(gen); }}
{
}
