#pragma once
#include <cmath>
#include <iostream>
#include "glut.h"
class Vec3d
{
public:
	GLdouble ptr[3];

	Vec3d();
	Vec3d(GLdouble*);
	~Vec3d();

	const Vec3d operator+(const Vec3d&) const;
	const Vec3d operator-(const Vec3d&) const;
	const Vec3d operator*(const double&) const;
	const Vec3d operator/(const double&) const;
	friend std::ostream& operator<<(std::ostream&, const Vec3d&);
	GLdouble& operator[](size_t);
	GLdouble dot(Vec3d, Vec3d);
	Vec3d cross(Vec3d, Vec3d);
	GLdouble length();
	void clear();
};

