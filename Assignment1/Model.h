#pragma once
#include <string>
#include "glut.h"
#include "Mesh.h"

class Model
{
public:
	std::string object_file;
	GLfloat scale[3];
	GLfloat rotate[4];
	GLfloat translate[4];
	GLfloat additional_translate[4];
	Mesh *object;

	Model();
	~Model();

	void Reset();
	void Render();

private:
	void ApplyMaterial(int);
	void TRStransform();
	void DrawFace(int);
};