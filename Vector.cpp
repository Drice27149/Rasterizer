#include <cmath>
#include "Vector.hpp"

Vector::Vector(int size): size(size){
	m.resize(size);
}

Vector::Vector(float x, float y, float z): size(3){
	m.resize(3);
	m[0] = x;
	m[1] = y;
	m[2] = z;
}

float& Vector::operator[] (int off){
	assert(off >= 0 && off < size);
	
	return m[off];
}

Vector Vector::operator* (Vector& v){
	Vector& u = *(this);
	assert(u.size == v.size);
	
	Vector res(u.size);
	for(int i = 0; i < u.size; i++) res[i] = u[i] * v[i];
	return res;
}

Vector Vector::operator* (float scale){
	Vector& u = *(this);
	Vector res(u.size);
	for(int i = 0; i < u.size; i++) res[i] = u[i] * scale;
	return res;
}

Vector Vector::operator+ (Vector& v){
	Vector& u = *(this);
	assert(u.size == v.size);
	
	Vector res(u.size);
	for(int i = 0; i < u.size; i++){
		res[i] = u[i] + v[i];
	}
	return res;
}

Vector Vector::operator- (Vector& v){
	Vector& u = *(this);
	assert(u.size == v.size);
	
	Vector res(u.size);
	for(int i = 0; i < u.size; i++){
		res[i] = u[i] - v[i];
	}
	return res;
}

float Vector::dotProduct(Vector u,Vector v){
	assert(u.size == v.size);

	float res = 0.0f;
	for(int i = 0; i < u.size; i++) res += u[i] * v[i];
	return res;
}

Vector Vector::crossProduct(Vector u, Vector v){
	assert(u.size == v.size && u.size == 3);
	
	Vector res(3);
 	res[0] = u[1]*v[2] - u[2]*v[1];
 	res[1] = u[2]*v[0] - u[0]*v[2];
 	res[2] = u[0]*v[1] - u[1]*v[0];
	return res;
}

void Vector::normalize(){
	assert(size == 3);

	float len = Vector::length();
	for(int i = 0; i < 3; i++) m[i] /= len;
}

float Vector::length(){
	assert(size == 3);
	
	return sqrt(m[0]*m[0] + m[1]*m[1] + m[2]*m[2]);
}

void Vector::init(float d[]){
	for(int i = 0; i < size; i++) m[i] = d[i];
}	

void Vector::init(std::vector<float> d){
	assert(d.size() == m.size());
	
	for(int i = 0; i < size; i++) m[i] = d[i];
}







