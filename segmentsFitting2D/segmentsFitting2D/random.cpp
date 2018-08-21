#include "random.hpp"

extern "C" unsigned int my_rand();

double thesis::random() {
	return (double)my_rand() / ((unsigned long long)~0U + 1ULL);
}

thesis::URBG::result_type thesis::URBG::min() {
	return 0U;
}

thesis::URBG::result_type thesis::URBG::max() {
	return ~0U;
}

thesis::URBG::result_type thesis::URBG::operator()() {
	return my_rand();
}