#pragma once
#include <string>
#include "FreeImage.h"
#include "glew.h"
#include "glut.h"

class Texture
{
public:
	std::string file_name;
	unsigned int texObject[1];
	int iWidth, iHeight;

	Texture(const std::string&);
	Texture();
	~Texture();

	void LoadTexture();
	void ApplyTexture();
	void DisapplyTexture();
};

