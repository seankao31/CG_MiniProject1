#pragma once
#include <string>
#include <vector>
#include <cmath>
#include "glut.h"
#include "Vec3d.h"


class View
{
public:
	Vec3d eye, vat, vup;
	GLdouble fovy, dnear, dfar;
	int viewport[4];
	int rotation;
	Vec3d zoom;

	View();
	View(const std::string&);
	~View();

	void Init(const std::string&);
	void LoadView(const std::string&);
	void apply();
	void print();
};

