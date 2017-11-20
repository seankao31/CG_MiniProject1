#include <iostream>
#include "Texture.h"

using namespace std;

Texture::Texture()
{
}

Texture::~Texture()
{
}

NoTexture::NoTexture()
{
}

NoTexture::~NoTexture()
{
}

void NoTexture::LoadTexture()
{
}

void NoTexture::ApplyTexture()
{
}

void NoTexture::DisapplyTexture()
{
}

void NoTexture::SetTexCoord(float *point)
{
}

SingleTexture::SingleTexture(const string &name)
{
	file_name = name;
}

SingleTexture::SingleTexture()
{
}

SingleTexture::~SingleTexture()
{
}

void SingleTexture::LoadTexture()
{
	glGenTextures(1, texObject);
	FIBITMAP *pImage = FreeImage_Load(FreeImage_GetFileType(file_name.c_str(), 0), file_name.c_str());
	FIBITMAP *p32BitsImage = FreeImage_ConvertTo32Bits(pImage);
	int iWidth = FreeImage_GetWidth(p32BitsImage);
	int iHeight = FreeImage_GetHeight(p32BitsImage);

	glBindTexture(GL_TEXTURE_2D, texObject[0]);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, iWidth, iHeight, 0,
		GL_BGRA, GL_UNSIGNED_BYTE, (void*)FreeImage_GetBits(p32BitsImage));
	
	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	
	/*
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, baseLevel);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, masLevel);
	*/
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	FreeImage_Unload(p32BitsImage);
	FreeImage_Unload(pImage);
}

void SingleTexture::ApplyTexture()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texObject[0]);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.5f);
}

void SingleTexture::DisapplyTexture()
{
	glDisable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void SingleTexture::SetTexCoord(float *point)
{
	glTexCoord2f(point[0], point[1]);
}

MultiTexture::MultiTexture(const string &name1, const string &name2)
{
	file_name[0] = name1;
	file_name[1] = name2;
}

MultiTexture::MultiTexture()
{
}

MultiTexture::~MultiTexture()
{
}

void MultiTexture::LoadTexture()
{
	glGenTextures(2, texObject);
	for (size_t i = 0; i < 2; ++i)
	{
		FIBITMAP *pImage = FreeImage_Load(FreeImage_GetFileType(file_name[i].c_str(), 0), file_name[i].c_str());
		FIBITMAP *p32BitsImage = FreeImage_ConvertTo32Bits(pImage);
		int iWidth = FreeImage_GetWidth(p32BitsImage);
		int iHeight = FreeImage_GetHeight(p32BitsImage);

		glBindTexture(GL_TEXTURE_2D, texObject[i]);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, iWidth, iHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, (void*)FreeImage_GetBits(p32BitsImage));

		glGenerateMipmap(GL_TEXTURE_2D);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);

		/*
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, baseLevel);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, masLevel);
		*/
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

		FreeImage_Unload(p32BitsImage);
		FreeImage_Unload(pImage);
	}
}

void MultiTexture::ApplyTexture()
{
	//bind texture 0
	glActiveTexture(GL_TEXTURE0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texObject[0]);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE);
	glTexEnvf(GL_TEXTURE_ENV, GL_COMBINE_RGB, GL_MODULATE);
	//bind texture 1
	glActiveTexture(GL_TEXTURE1);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texObject[1]);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE);
	glTexEnvf(GL_TEXTURE_ENV, GL_COMBINE_RGB, GL_MODULATE);
}

void MultiTexture::DisapplyTexture()
{
	//unbind texture 1
	glActiveTexture(GL_TEXTURE1);
	glDisable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
	//unbind texture 0
	glActiveTexture(GL_TEXTURE0);
	glDisable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void MultiTexture::SetTexCoord(float *point)
{
	glMultiTexCoord2f(GL_TEXTURE0, point[0], point[1]);
	glMultiTexCoord2f(GL_TEXTURE1, point[0], point[1]);
}