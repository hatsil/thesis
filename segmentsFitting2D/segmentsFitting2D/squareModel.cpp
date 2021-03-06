#include "squareModel.hpp"

namespace thesis {
SquareModel::SquareModel():
	positions({ {-1, 1}, {-1, -1}, {1, -1}, {1, 1} }),
	texCoords({ {0, 0}, {0, 1}, {1, 1}, {1, 0} }),
	indices({ 0, 2, 1, 0, 3, 2 }) {}

SquareModel::~SquareModel() {}

} /* namespace thesis */
