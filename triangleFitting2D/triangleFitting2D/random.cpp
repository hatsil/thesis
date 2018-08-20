#include "random.hpp"

extern "C" unsigned long long my_rand();

double thesis::random() {
	return (double)my_rand() / ~0ULL;
}