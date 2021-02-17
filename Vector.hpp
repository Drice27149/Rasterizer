#pragma once

#include <vector>

class Vector{
public:
	Vector(int size = 3);
	void init(float d[]);
	void init(std::vector<float> d);
	float& operator[] (int off);
	Vector operator* (Vector& other);
	Vector operator* (float scale);
	Vector operator+ (Vector& other);
	Vector operator- (Vector& other);
	void normalize();
	float length();
	static float dotProduct(Vector u, Vector v);
	static Vector crossProduct(Vector u, Vector v);
public:
	int size;
private:
	std::vector<float>m;
};



