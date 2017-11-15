#include "Vec3.h"

Vec3::Vec3(GLdouble *v)
{
	for (size_t i = 0; i<3; i++)
		ptr[i] = v[i];
}

Vec3::Vec3()
{
}

Vec3::~Vec3()
{
}

const Vec3 Vec3::operator+(const Vec3 &rhs) const
{
	Vec3 vec3;
	vec3.ptr[0] = this->ptr[0] + rhs.ptr[0];
	vec3.ptr[1] = this->ptr[1] + rhs.ptr[1];
	vec3.ptr[2] = this->ptr[2] + rhs.ptr[2];
}

const Vec3 Vec3::operator-(const Vec3 &rhs) const
{
	Vec3 vec3;
	vec3.ptr[0] = this->ptr[0] - rhs.ptr[0];
	vec3.ptr[1] = this->ptr[1] - rhs.ptr[1];
	vec3.ptr[2] = this->ptr[2] - rhs.ptr[2];
}

inline GLdouble& Vec3::operator[](size_t index)
{
	return ptr[index];
}

GLdouble Vec3::length()
{
	return sqrt(pow(ptr[0], 2) + pow(ptr[1], 2) + pow(ptr[2], 2));
}