#include "Vec3d.h"

using namespace std;

Vec3d::Vec3d(GLdouble *v)
{
	for (size_t i = 0; i < 3; ++i)
	{
		ptr[i] = v[i];
	}
}

Vec3d::Vec3d()
{
	for (size_t i = 0; i < 3; ++i)
	{
		ptr[i] = 0;
	}
}

Vec3d::~Vec3d()
{
}

const Vec3d Vec3d::operator+(const Vec3d &rhs) const
{
	Vec3d vec3d;
	vec3d.ptr[0] = this->ptr[0] + rhs.ptr[0];
	vec3d.ptr[1] = this->ptr[1] + rhs.ptr[1];
	vec3d.ptr[2] = this->ptr[2] + rhs.ptr[2];
	return vec3d;
}

const Vec3d Vec3d::operator-(const Vec3d &rhs) const
{
	Vec3d vec3d;
	vec3d.ptr[0] = this->ptr[0] - rhs.ptr[0];
	vec3d.ptr[1] = this->ptr[1] - rhs.ptr[1];
	vec3d.ptr[2] = this->ptr[2] - rhs.ptr[2];
	return vec3d;
}

const Vec3d Vec3d::operator*(const double &rhs) const
{
	Vec3d vec3d;
	vec3d.ptr[0] = this->ptr[0] * rhs;
	vec3d.ptr[1] = this->ptr[1] * rhs;
	vec3d.ptr[2] = this->ptr[2] * rhs;
	return vec3d;
}

const Vec3d Vec3d::operator/(const double &rhs) const
{
	if (rhs == 0)
	{
		cerr << "divided by 0 error" << endl;
		return *this;
	}
	Vec3d vec3d;
	vec3d.ptr[0] = this->ptr[0] / rhs;
	vec3d.ptr[1] = this->ptr[1] / rhs;
	vec3d.ptr[2] = this->ptr[2] / rhs;
	return vec3d;
}

ostream& operator<<(ostream& os, const Vec3d &vec3d)
{
	os << vec3d.ptr[0] << ' ' << vec3d.ptr[1] << ' ' << vec3d.ptr[2];
	return os;
}

GLdouble& Vec3d::operator[](size_t index)
{
	return ptr[index];
}

GLdouble Vec3d::length()
{
	return sqrt(pow(ptr[0], 2) + pow(ptr[1], 2) + pow(ptr[2], 2));
}

void Vec3d::clear()
{
	for (size_t i = 0; i < 3; ++i)
	{
		ptr[i] = 0;
	}
}

GLdouble dot(Vec3d lhs, Vec3d rhs)
{
	return lhs[0] * rhs[0] + lhs[1] * rhs[1] + lhs[2] * rhs[2];
}

Vec3d cross(Vec3d lhs, Vec3d rhs)
{
	Vec3d vec3d;
	vec3d[0] = lhs[1] * rhs[2] - lhs[2] * rhs[1];
	vec3d[1] = lhs[2] * rhs[0] - lhs[0] * rhs[2];
	vec3d[2] = lhs[0] * rhs[1] - lhs[1] * rhs[0];
	return vec3d;
}