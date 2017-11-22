#pragma once
#include <string>
#include <vector>
#include "FreeImage.h"
#include "glew.h"
#include "glut.h"
#include "Mesh.h"
#include "Model.h"
#include "Texture.h"

class Scene
{
public:
	std::vector<Model> models;
	std::vector<Mesh*> objects;

	int select;

	Scene();
	Scene(const std::string&);
	~Scene();

	void Init(const std::string&);
	void LoadScene(const std::string&);
	void Apply();
	void Select(int);
};

