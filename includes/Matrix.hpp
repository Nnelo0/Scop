#pragma once
#include "Vec3.hpp"
#include <iomanip>
#include <cassert>
#include <array>
#include <cmath>
#include <fstream>

using namespace std;

#define RESET	"\033[0m"
#define RED		"\033[31m"
#define GREEN	"\033[32m"
#define YELLOW	"\033[33m"
#define BLUE	"\033[34m"
#define MAGENTA	"\033[35m"
#define CYAN	"\033[36m"

class Matrix
{
	public:
		using arr = array<float, 16>;
	private:
		arr m;
	public:
		Matrix();
		~Matrix();
		
		float	operator()(int row, int col) const;
		float	&operator()(int row, int col);
		Matrix	operator*(const Matrix& matrix) const;
		
		static Matrix	identity();
		const float		*data() const;

		array<float, 4>	mulVec4(float x, float y, float z, float w=1.0f);
		static Matrix	translate(float tx, float ty, float tz);
		static Matrix	scale(float sx, float sy, float sz);
		static Matrix	rotateX(float radians);
		static Matrix	rotateY(float radians);
		static Matrix	rotateZ(float radians);
		static Matrix	rotateAxis(const Vec3& Axis, float radians);
		static Matrix	perspective(float fov_deg, float aspect, float near, float far);
		static Matrix	lookAt(const Vec3& eye, const Vec3& center, const Vec3& up);
};