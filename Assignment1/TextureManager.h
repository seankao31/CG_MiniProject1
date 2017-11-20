#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include "FreeImage.h"
#include "glew.h"
#include "glut.h"
#include "Texture.h"

class TextureManager
{
private:
	TextureManager();
public:

	std::vector<Texture> textures;
	std::unordered_map<std::string, size_t> file_to_index;

	~TextureManager();

	static TextureManager& GetInstance();
	TextureManager(TextureManager const&) = delete;
	void operator=(TextureManager const&) = delete;

	void LoadTextures();
};

