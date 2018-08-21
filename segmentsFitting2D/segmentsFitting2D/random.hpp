#pragma once

namespace thesis {
	double random();
	class URBG {
	public:
		typedef unsigned int result_type;
		static result_type min();
		static result_type max();
		result_type operator()();
	};
}