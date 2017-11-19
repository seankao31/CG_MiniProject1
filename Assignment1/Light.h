#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "glut.h"

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
		~LIGHT() {};
	};

public:
	std::vector<LIGHT> lights;
	GLfloat ambient[4] = { 1.0 };

	Light();
	Light(const std::string&);
	~Light();

	void Init(const std::string&);
	void LoadLight(const std::string&);
	void Apply();
	void Print();
};

