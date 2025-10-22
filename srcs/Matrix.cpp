#include "Matrix.hpp"

Matrix::Matrix()
{
	m.fill(0.0f);
	m[0] = m[5] = m[10] = m[15] = 1.0f;
}

Matrix::~Matrix() {}

float	Matrix::operator()(int row, int col) const
{
	return m[col * 4 + row];
}

float	&Matrix::operator()(int row, int col)
{
	return m[col * 4 + row];
}

Matrix	Matrix::operator*(const Matrix& matrix) const
{
	Matrix R;

	for (int row = 0; row < 4; ++row) {
		for (int col = 0; col < 4; ++col) {
			float sum = 0.0f;
			for (int k = 0; k < 4; ++k) {
				sum += (*this)(row,k) * matrix(k, col);
			}
			R(row, col) = sum;
		}
	}
	return R;
}

Matrix		Matrix::identity()
{
	return Matrix();
}

const float	*Matrix::data() const
{
	return m.data();
}

array<float, 4>	Matrix::mulVec4(float x, float y, float z, float w)
{
	array<float, 4> r{};
	for (int row = 0; row < 4; ++row) {
		r[row] = (*this)(row, 0) * x + (*this)(row, 1) * y + (*this)(row, 2) * z + (*this)(row, 3) * w;
	}

	return r;
}

Matrix	Matrix::translate(float tx, float ty, float tz)
{
	Matrix T = Matrix::identity();
	T(0, 3) = tx;
	T(1, 3) = ty;
	T(2, 3) = tz;
	return T;
}

Matrix	Matrix::scale(float sx, float sy, float sz)
{
	Matrix S;
	S.m.fill(0.0f);
	S(0, 0) = sx;
	S(1, 1) = sy;
	S(2, 2) = sz;
	S(3, 3) = 1.0f;
	return S;	
}

Matrix	Matrix::rotateX(float radians)
{
	float c = std::cos(radians), s = std::sin(radians);
	Matrix R = Matrix::identity();
	R(1, 1) = c;
	R(2, 1) = s;
	R(1, 2) = -s;
	R(2, 2) = c;
	return R;
}

Matrix	Matrix::rotateY(float radians)
{
	float c = std::cos(radians), s = std::sin(radians);
	Matrix R = Matrix::identity();
	R(0, 0) = c;
	R(2, 0) = -s;
	R(0, 2) = s;
	R(2, 2) = c;
	return R;
}

Matrix	Matrix::rotateZ(float radians)
{
	float c = std::cos(radians), s = std::sin(radians);
	Matrix R = Matrix::identity();
	R(0, 0) = c;
	R(1, 0) = s;
	R(0, 1) = -s;
	R(1, 1) = c;
	return R;
}

Matrix	Matrix::rotateAxis(const Vec3& axis, float radians)
{
	Vec3 a = axis.normalized();
	float x = a.x, y = a.y, z = a.z;
	float c = cos(radians), s = sin(radians);
	float t = 1.0f - c;
	Matrix R;

	R.m = {
		t*x*x + c,		t*x*y + s*z,	t*x*z - s*y,	0.0f,
		t*x*y - s*z,	t*y*y + c,		t*y*z + s*x,	0.0f,
		t*x*z + s*y,	t*y*z - s*x,	t*z*z + c,		0.0f,
		0.0f,			0.0f,			0.0f,			1.0f
	};
	return R;
}

Matrix	Matrix::perspective(float fov_deg, float aspect, float near, float far)
{
	assert(near > 0.0f && far > near);
	float fov_rad = fov_deg * (M_PI / 180.0f);
	float f = 1.0f / tan(fov_rad * 0.5f);

	Matrix P;
	for (int i = 0; i < 16; ++i) P.m[i] = 0.0f;
	P(0, 0) = f / aspect;
	P(1, 1) = f;
	P(2, 2) = (far + near) / (near - far);
	P(2, 3) = (2.0f * far * near) / (near - far);
	P(3, 2) = -1.0f;
	
	return P;
}

Matrix	Matrix::lookAt(const Vec3& eye, const Vec3& center, const Vec3& up)
{
	Vec3 f = (center - eye).normalized(); // forward
	Vec3 s = Vec3::cross(f, up).normalized(); // right
	Vec3 u = Vec3::cross(s, f); // recomputed up
	Matrix M = Matrix::identity();

	M(0,0) = s.x;	M(1, 0) = s.y;		M(2, 0) = s.z;		M(3, 0) = 0.0f;
	M(0,1) = u.x;	M(1, 1) = u.y;		M(2, 1) = u.z;		M(3, 1) = 0.0f;
	M(0,2) = -f.x;	M(1, 2) = -f.y;		M(2, 2) = -f.z;		M(3, 2) = 0.0f;
	M(0, 3) = -Vec3::dot(s, eye);
	M(1, 3) = -Vec3::dot(u, eye);
	M(2, 3) = Vec3::dot(f, eye);
	M(3, 3) = 1.0f;

	return M;
}