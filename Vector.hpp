#pragma once

#include <vector>

class Vector{
public:
	Vector(int size = 3);
	Vector(float x, float y, float z);
	void init(float d[]);
	void init(std::vector<float> d);
	float& operator[] (int off);
	const float& operator[] (int off)const;
	Vector operator* (float scale);
	Vector operator* (const Vector& other);
	Vector operator+ (const Vector& other);
	Vector operator- (const Vector& other);
	void normalize();
	void reduce(int d);
	void print();
	float length();
	static float dotProduct(const Vector& u, const Vector& v);
	static Vector crossProduct(const Vector& u, const Vector& v);
public:
	int size;
public:
	std::vector<float>m;
};



