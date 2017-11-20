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
	for (auto &texture : textures)
	{
		texture.LoadTexture();
	}
	FreeImage_DeInitialise();
}