#include "pch.h"
#include "Methods.h"


Methods::Methods()
{
}


Methods::~Methods()
{
}

Vector * Methods::Gauss(Matrix * baseA, Vector * baseB)
{
	Vector *vectorX = Vector::Create(baseB->GetVectorSize()), vectorB;
	Matrix matrixA;


}
