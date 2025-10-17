#include "Vec3.hpp"

ostream &operator<<(ostream &os, const Vec3& v)
{
	os << "{" << v._x << ", " << v._y << ", " << v._z << "}" << endl;
	return os;
}

Vec3::Vec3():_x(0),_y(0),_z(0) {}

Vec3::~Vec3() {}

Vec3::Vec3(float x, float y, float z):_x(x),_y(y),_z(z) {}

Vec3 Vec3::operator+(const Vec3 &vec3) const
{
	return {_x + vec3._x, _y + vec3._y, _z + vec3._z};
}

Vec3 Vec3::operator-(const Vec3 &vec3) const
{
	return {_x - vec3._x, _y - vec3._y, _z - vec3._z};
}

Vec3 Vec3::operator/(float n) const
{
	return {_x / n, _y / n, _z / n};
}

Vec3 Vec3::operator*(float n) const
{
	return {_x * n, _y * n, _z * n};
}

Vec3 Vec3::operator+=(const Vec3 &vec3)
{
	_x += vec3._x;
	_y += vec3._y;
	_z += vec3._z;

	return *this;
}

Vec3 Vec3::operator-=(const Vec3 &vec3)
{
	_x -= vec3._x;
	_y -= vec3._y;
	_z -= vec3._z;

	return *this;
}

Vec3 Vec3::operator/=(float n)
{
	_x /= n;
	_y /= n;
	_z /= n;

	return *this;
}

Vec3 Vec3::operator*=(float n)
{
	_x *= n;
	_y *= n;
	_z *= n;

	return *this;
}

bool Vec3::operator==(const Vec3 &vec3) const
{
	return _x == vec3._x && _y == vec3._y && _z == vec3._z;
}

bool Vec3::operator!=(const Vec3 &vec3) const
{
	return !(*this == vec3);
}

float Vec3::length() const
{
	return sqrt(_x*_x + _y*_y + _z*_z);
}

/*keep the direction but standardize the length*/
Vec3 Vec3::normalized() const
{
	float len = length();
	if (len == 0.0f) return {0, 0, 0};
	return {_x / len, _y / len, _z / len}; 
}

/*Used to project one vector onto another, to calculate the angle between vectors, for lighting, etc.*/
float Vec3::dot(const Vec3& a, const Vec3& b)
{
	return a._x * b._x + a._y * b._y + a._z * b._z;
}

/*Used to build orthonormal basis (right, up, forward)*/
Vec3 Vec3::cross(const Vec3& a, const Vec3& b)
{
	return {a._y * b._z - a._z * b._y,
			a._z * b._x - a._x * b._z,
			a._x * b._y - a._y * b._x};
}
