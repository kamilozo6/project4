#pragma once
#include <stdint.h>
#include <cmath>
#include "Vector.h"
#include "Matrix.h"
#include "Methods.h"

#define GAUSS_OPTIMIZE_MAX_AGENTS 500

class Approximation
{
public:
	Approximation();
	~Approximation();

	void GaussWithOptimization();

	uint32_t CountSizeFromAgentsValue(uint32_t agents);
};

