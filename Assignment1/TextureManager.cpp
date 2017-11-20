#include <iostream>
#include "TextureManager.h"

using namespace std;

TextureManager::TextureManager()
{
}

TextureManager::~TextureManager()
{
}

TextureManager& TextureManager::GetInstance()
{
	static TextureManager instance;
	return instance;
}

void TextureManager::LoadTextures()
{
	FreeImage_Initialise();
	for (size_t i = 0; i < textures.size(); ++i)
	{
		textures[i].LoadTexture();
	}
	FreeImage_DeInitialise();
}