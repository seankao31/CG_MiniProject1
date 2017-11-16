#pragma once
#include <string>
#include <vector>
#include "glut.h"
#include "Mesh.h"

class Scene
{
	class Model
	{
	public:
		std::string object_file;
		GLfloat scale[3];
		GLfloat rotate[4];
		GLfloat translate[4];
		GLfloat additional_translate[4];
		Mesh *object;

		Model()
		{
			for (size_t i = 0; i < 4; ++i)
			{
				additional_translate[i] = 0;
			}
		}
		~Model() {};

		void reset()
		{
			for (size_t i = 0; i < 4; ++i)
			{
				additional_translate[i] = 0;
			}
		}
	};

public:
	std::vector<Model> models;
	std::vector<Mesh*> objects;
	int select;

	Scene();
	Scene(const std::string&);
	~Scene();

	void Init(const std::string&);
	void LoadScene(const std::string&);
	void apply();
	void Select(int);
};

