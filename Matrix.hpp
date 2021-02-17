#pragma once

#include <cassert>
#include <vector>
#include "Vector.hpp"

class Matrix{
public:
	Matrix(int row, int col);
	void init(float d[]);
	std::vector<float>& operator[] (int off);
	Matrix operator* (Matrix& other);
	Vector operator* (Vector& other);
protected:
	std::vector<std::vector<float> > m;
public:
	int row;
	int col;
};




