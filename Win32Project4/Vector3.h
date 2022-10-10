#pragma once
#pragma once

#include "stdafx.h"

class Vector3
{
public:
	float x, y, z;

	Vector3();
	Vector3(float x, float y, float z);
	~Vector3();

	float lenth();
	void normalize();
	Vector3 normal();

	float dotp(const Vector3& other);
	Vector3 crossp(const Vector3& other);

	Vector3 operator*(float value);
	friend Vector3 operator*(float value, const Vector3 & vec);
	Vector3 operator+(const Vector3 &vec) const;
	Vector3 operator-(const Vector3 &vec) const;
};
