#include "Texture.h"

using namespace std;

Texture::Texture(const string &name)
{
	file_name = name;
}

Texture::Texture()
{
}

Texture::~Texture()
{
}

void Texture::LoadTexture()
{
	glGenTextures(1, texObject);
	FIBITMAP *pImage = FreeImage_Load(FreeImage_GetFileType(file_name.c_str(), 0), file_name.c_str());
	FIBITMAP *p32BitsImage = FreeImage_ConvertTo32Bits(pImage);
	iWidth = FreeImage_GetWidth(p32BitsImage);
	iHeight = FreeImage_GetHeight(p32BitsImage);

	glBindTexture(GL_TEXTURE_2D, texObject[0]);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, iWidth, iHeight, 0,
		GL_BGRA, GL_UNSIGNED_BYTE, (void*)FreeImage_GetBits(p32BitsImage));
	/*
	glGenerateMipmap(GL_TEXTURE_2D);
	// these come AFTER glTexImage
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	*/
	/*
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, baseLevel);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, masLevel);
	*/
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	FreeImage_Unload(p32BitsImage);
	FreeImage_Unload(pImage);
}

void Texture::ApplyTexture()
{

}

void Texture::DisapplyTexture()
{

}
