#pragma once

#include "Matrix.h"
#include "Vector.h"

#define PRECISION 0.0000000001

class Methods
{
public:
	Methods();
	~Methods();

	static Vector* Gauss(Matrix *baseA, Vector *baseB, double_t *time = nullptr);
	static Vector* GaussSeidel(Matrix *baseA, Vector *baseB, double_t *time = nullptr);
	static void Eigen(Matrix *baseA, Vector *baseB, double_t *time = nullptr);

};

