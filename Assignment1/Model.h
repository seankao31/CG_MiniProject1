#pragma once
#include <string>
#include "FreeImage.h"
#include "glew.h"
#include "glut.h"
#include "Mesh.h"
#include "Texture.h"

class Model
{
public:
	std::string object_file;
	GLfloat scale[3];
	GLfloat rotate[4];
	GLfloat translate[4];
	GLfloat additional_translate[4];
	Mesh *object;

	Texture texture;

	Model();
	~Model();

	void Reset();
	void Render();

private:
	void ApplyMaterial(int);
	void TRStransform();
	void ApplyTexture();
	void DisapplyTexture();
	void DrawFace(int);
};