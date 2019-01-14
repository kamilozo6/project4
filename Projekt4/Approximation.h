#pragma once
#include <stdint.h>
#include <cmath>
#include "Vector.h"
#include "Matrix.h"
#include "Methods.h"
#include <map>

#define GAUSS_OPTIMIZE_MAX_AGENTS 70
#define GAUSS_MAX_AGENTS 70
#define GAUSS_SEIDEL_OPTIMIZE_MAX_AGENTS 70
#define EIGEN_MAX_AGENTS 70


class Approximation
{
public:

	FILE *f1, *f2, *f3, *f4;

	Approximation();
	~Approximation();

	void GaussWithOptimization();

	void GaussWithoutOptimization();

	void GaussSeidelWithOptimization();

	void Eigen();

	uint32_t CountSizeFromAgentsValue(uint32_t agents);

	void Approximate(uint32_t degree, std::map<uint32_t, double_t> times);
};

