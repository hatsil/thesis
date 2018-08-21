#include <cstdlib>
#include <iostream>
#include "random.hpp"

int main() {
	std::cout << "hello thesis" << std::endl;
	for (int i = 0; i < 10; ++i)
		std::cout << thesis::random() << std::endl;
	std::system("pause");
	return 1;
}

