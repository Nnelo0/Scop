#include "Vec3.hpp"

ostream &operator<<(ostream &os, const Vec3& v)
{
	os << "{" << v.x << ", " << v.y << ", " << v.z << "}" << endl;
	return os;
}

Vec3::Vec3():x(0),y(0),z(0) {}

Vec3::~Vec3() {}

Vec3::Vec3(float _x, float _y, float _z):x(_x),y(_y),z(_z) {}

Vec3 Vec3::operator+(const Vec3 &vec3) const
{
	return {x + vec3.x, y + vec3.y, z + vec3.z};
}

Vec3 Vec3::operator-(const Vec3 &vec3) const
{
	return {x - vec3.x, y - vec3.y, z - vec3.z};
}

Vec3 Vec3::operator/(float n) const
{
	return {x / n, y / n, z / n};
}

Vec3 Vec3::operator*(float n) const
{
	return {x * n, y * n, z * n};
}

Vec3 Vec3::operator+=(const Vec3 &vec3)
{
	x += vec3.x;
	y += vec3.y;
	z += vec3.z;

	return *this;
}

Vec3 Vec3::operator-=(const Vec3 &vec3)
{
	x -= vec3.x;
	y -= vec3.y;
	z -= vec3.z;

	return *this;
}

Vec3 Vec3::operator/=(float n)
{
	x /= n;
	y /= n;
	z /= n;

	return *this;
}

Vec3 Vec3::operator*=(float n)
{
	x *= n;
	y *= n;
	z *= n;

	return *this;
}

bool Vec3::operator==(const Vec3 &vec3) const
{
	return x == vec3.x && y == vec3.y && z == vec3.z;
}

bool Vec3::operator!=(const Vec3 &vec3) const
{
	return !(*this == vec3);
}

float Vec3::length() const
{
	return sqrt(x*x + y*y + z*z);
}

/*keep the direction but standardize the length*/
Vec3 Vec3::normalized() const
{
	float len = length();
	if (len == 0.0f) return {0, 0, 0};
	return {x / len, y / len, z / len}; 
}

/*Used to project one vector onto another, to calculate the angle between vectors, for lighting, etc.*/
float Vec3::dot(const Vec3& a, const Vec3& b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

/*Used to build orthonormal basis (right, up, forward)*/
Vec3 Vec3::cross(const Vec3& a, const Vec3& b)
{
	return {a.y * b.z - a.z * b.y,
			a.z * b.x - a.x * b.z,
			a.x * b.y - a.y * b.x};
}
