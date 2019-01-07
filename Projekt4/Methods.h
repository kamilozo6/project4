#pragma once

#include "Matrix.h"
#include "Vector.h"


class Methods
{
public:
	Methods();
	~Methods();

	static Vector* Gauss(Matrix *baseA, Vector *baseB);
};

