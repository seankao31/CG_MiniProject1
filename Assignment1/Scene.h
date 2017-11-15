#pragma once
#include <string>
#include <vector>
#include "glut.h"
#include "mesh.h"

class Scene
{
	class Model
	{
	public:
		std::string object_file;
		GLfloat scale[3];
		GLfloat rotate[4];
		GLfloat translate[4];

		Model() {};
		~Model() {};
	};

public:
	std::vector<Model> models;
	std::vector<mesh*> objects;

	Scene();
	Scene(const std::string&);
	~Scene();

	void Init(const std::string&);
	void LoadScene(const std::string&);
	void apply();
	void print();
};

