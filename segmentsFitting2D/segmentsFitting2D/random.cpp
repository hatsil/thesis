#include "random.hpp"

extern "C" unsigned int my_rand();

double thesis::random() {
	return (double)my_rand() / ((unsigned long long)~0U + 1ULL);
}