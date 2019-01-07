#pragma once
#include <unordered_map>

#define MATRIX_MAP std::unordered_map<uint32_t, double_t>

class Matrix
{
private:
	// array of maps, size is n*n
	MATRIX_MAP *matrixTable;
	uint32_t matrixSize;
public:
	Matrix();
	~Matrix();

	static Matrix* Create(uint32_t size);


#pragma region inlineFunc
	void SetMatrixSize(uint32_t size);
#pragma endregion

	void SetMatrixCell(uint32_t row, uint32_t collumn, double_t value);
	virtual void EvaluateProbability(uint32_t n);
	void ProbablilityForSpecificCase(uint32_t yes, uint32_t no, uint32_t n);
	uint32_t ReturnIndex(uint32_t yes, uint32_t no, uint32_t n);

	void WriteToConsole();
};

