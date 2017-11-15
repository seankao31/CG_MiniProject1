#pragma once
#include <string>
#include <vector>
#include "glut.h"


class View
{
public:
	GLdouble eye[3], vat[3], vup[3], fovy, dnear, dfar;
	int viewport[4];

	View();
	View(const std::string&);
	~View();

	void Init(const std::string&);
	void LoadView(const std::string&);
	void apply();
	void print();
};

