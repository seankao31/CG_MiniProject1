#pragma once
#include "glut.h"
#include <string>
#include <vector>
class Light
{
	class LIGHT
	{
	public:
		GLfloat position[4] = { 1.0 };
		GLfloat ambient[4] = { 1.0 };
		GLfloat diffuse[4] = { 1.0 };
		GLfloat specular[4] = { 1.0 };

		LIGHT() {};
	};

public:
	std::vector<LIGHT> lights;
	GLfloat ambient[4] = { 1.0 };

	Light();
	Light(const std::string&);
	~Light();

	void LoadLight(const std::string&);
	void print();
	void apply();
};

