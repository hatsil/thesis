#include "cubicSplineModel.hpp"

namespace thesis {
CubicSplineModel::CubicSplineModel(uint numIndices):
	ts(numIndices),
	indices(numIndices) {
	double denom = (double)(numIndices - 1);
	for(uint i = 0; i < numIndices; ++i) {
		indices[i] = i;
		double t = (double)i / denom;
		double t2 = t * t;
		double t3 = t * t * t;
		ts[i] = { float(t3), float(t2), float(t), 1 };
	}
}

CubicSplineModel::~CubicSplineModel() {}

} /* namespace thesis */
