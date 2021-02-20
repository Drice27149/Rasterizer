#include "Matrix.hpp"

Matrix::Matrix(int row, int col): row(row), col(col){
	for(int i = 0; i < row; i++){
		std::vector<float> r;
		r.resize(col);
		m.push_back(r);
	}
}

std::vector<float>& Matrix::operator[] (int off){
	assert(off >= 0 && off < row);
	return m[off];
}

Matrix Matrix::operator* (Matrix& other){
	assert(col == other.row);
	Matrix res(row, other.col);
	for(int i = 0; i < row; i++){
		for(int j = 0; j < other.col; j++){
			float current = 0.0f;
			for(int k = 0; k < col; k++){
				current += (*this)[i][k] * other[k][j];
			}
			res[i][j] = current;
		}
	}
	return res;
}

Vector Matrix::operator* (Vector& v){
	Matrix& u = *(this);
	assert(u.row == u.col && u.row == v.size);
	
	Vector res(u.row);
	for(int i = 0; i < u.row; i++){
		res[i] = 0.0f;
		for(int j = 0; j < u.col; j++){
			res[i] += u[i][j] * v[j];
		}	
	}
	return res;
}

void Matrix::init(float d[]){
	for(int i = 0; i < row; i++){
		for(int j = 0; j < col; j++){
			m[i][j] = d[i * col + j];
		}
	}
}

void Matrix::print(){
	printf("row = %d, col = %d\n",row, col);
	for(int i = 0; i < row; i++){
		for(int j = 0; j < col; j++){
			printf("%.3f ",m[i][j]);
		}
		printf("\n");
	}
}

