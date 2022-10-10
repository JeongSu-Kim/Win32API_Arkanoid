#include "stdafx.h"
#include "vector3.h"

Vector3::Vector3()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
}

Vector3::Vector3(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector3::~Vector3()
{
}

float Vector3::lenth()
{
	return sqrt(x * x + y * y + z * z);
}

void Vector3::normalize()
{
	float lenth = this->lenth();
	this->x /= lenth;
	this->y /= lenth;
	this->z /= lenth;
}

Vector3 Vector3::normal()
{
	float lenth = this->lenth();
	Vector3 normal = Vector3(this->x /= lenth, this->y /= lenth, this->z /= lenth);

	return normal;
}

float Vector3::dotp(const Vector3 & other)
{
	return this->x * other.x + this->y * other.y + this->z * other.z;
}

Vector3 Vector3::crossp(const Vector3 & other)
{
	Vector3 cross = Vector3(this->y * other.z - this->z * other.y
		, this->z * other.x - this->x * other.z
		, this->x * other.y - this->y * other.x);

	return cross;
}

Vector3 Vector3::operator*(float value)
{
	return Vector3(this->x * value, this->y * value, this->z * value);
}

Vector3 operator*(float value, const Vector3& vec)
{
	return Vector3(vec.x * value, vec.y * value, vec.z * value);
}

Vector3 Vector3::operator+(const Vector3& vec) const
{
	return Vector3(this->x + vec.x, this->y + vec.y, this->z + vec.z);
}

Vector3 Vector3::operator-(const Vector3& vec) const
{
	return Vector3(this->x - vec.x, this->y - vec.y, this->z - vec.z);
}
