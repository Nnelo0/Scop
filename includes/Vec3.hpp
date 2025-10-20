#pragma once
#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;

class Vec3
{
	public:
		float x, y, z;
	public:

		Vec3(/* args */);
		Vec3(float x, float y, float z);
		~Vec3();

		Vec3 operator+(const Vec3 &vec3) const;
		Vec3 operator-(const Vec3 &vec3) const;
		Vec3 operator/(float n) const;
		Vec3 operator*(float n) const;

		Vec3 operator+=(const Vec3 &vec3);
		Vec3 operator-=(const Vec3 &vec3);
		Vec3 operator/=(float n);
		Vec3 operator*=(float n);

		bool operator==(const Vec3 &vec3) const;
		bool operator!=(const Vec3 &vec3) const;

		float length() const;
		Vec3 normalized() const;
		static float dot(const Vec3& a, const Vec3& b);
		static Vec3 cross(const Vec3& a, const Vec3& b);
		
};
