#pragma once
#include <cmath>
#include "glut.h"
class Vec3
{
public:
	GLdouble ptr[3];

	Vec3();
	Vec3(GLdouble*);
	~Vec3();

	const Vec3 operator+(const Vec3&) const;
	const Vec3 operator-(const Vec3&) const;
	inline GLdouble& operator[](size_t);
	GLdouble length();
};

