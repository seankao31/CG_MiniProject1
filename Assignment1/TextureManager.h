#pragma once
#include <vector>
#include <string>
#include "FreeImage.h"
#include "glew.h"
#include "glut.h"
#include "Texture.h"

class TextureManager
{
private:
	TextureManager();
public:

	std::vector<Texture*> textures;

	~TextureManager();

	static TextureManager& GetInstance();
	TextureManager(TextureManager const&) = delete;
	void operator=(TextureManager const&) = delete;

	void LoadTextures();
};

