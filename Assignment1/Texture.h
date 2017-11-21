#pragma once
#include <string>
#include <vector>
#include "FreeImage.h"
#include "glew.h"
#include "glut.h"

class Texture
{
public:
	Texture();
	~Texture();

	virtual void LoadTexture() = 0;
	virtual void ApplyTexture() = 0;
	virtual void DisapplyTexture() = 0;
	virtual void SetTexCoord(float *point) = 0;
};

class NoTexture : public Texture
{
public:
	NoTexture();
	~NoTexture();

	void LoadTexture();
	void ApplyTexture();
	void DisapplyTexture();
	void SetTexCoord(float *point = NULL);
};

class SingleTexture : public Texture
{
public:
	std::string file_name;
	unsigned int texObject[1];

	SingleTexture(const std::string&);
	SingleTexture();
	~SingleTexture();

	void LoadTexture();
	void ApplyTexture();
	void DisapplyTexture();
	void SetTexCoord(float*);
};

class MultiTexture : public Texture
{
public:
	std::string file_name[2];
	unsigned int texObject[2];

	MultiTexture(const std::string&, const std::string&);
	MultiTexture();
	~MultiTexture();

	void LoadTexture();
	void ApplyTexture();
	void DisapplyTexture();
	void SetTexCoord(float*);
};

class CubeMapTexture : public Texture
{
public:
	std::vector<std::string> file_names;
	unsigned int texObject[1];

	CubeMapTexture(const std::vector<std::string>&);
	CubeMapTexture();
	~CubeMapTexture();

	void LoadTexture();
	void ApplyTexture();
	void DisapplyTexture();
	void SetTexCoord(float *point = NULL);
};