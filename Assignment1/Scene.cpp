#include <fstream>
#include <iostream>
#include "Scene.h"

using namespace std;

Scene::Scene(const string& scene_file)
{
	Init(scene_file);
}

Scene::Scene()
{
}

Scene::~Scene()
{
}

void Scene::Init(const string& scene_file)
{
	select = -1;
	LoadScene(scene_file);
	cout << "Scene" << endl;
	for (auto &model : models)
	{
		model.object = new Mesh(model.object_file);
	}
}

void Scene::LoadScene(const string& scene_file)
{
	fstream fin(scene_file, fstream::in);
	string term;
	while (fin >> term)
	{
		if (term == "model")
		{
			Model model;
			fin >> model.object_file;
			fin >> model.scale[0] >> model.scale[1] >> model.scale[2];
			fin >> model.rotate[0] >> model.rotate[1] >> model.rotate[2] >> model.rotate[3];
			fin >> model.translate[0] >> model.translate[1] >> model.translate[2];
			models.push_back(model);
		}
		else
		{
			cerr << "Scene: load file error" << endl;
			return;
		}
	}
	fin.close();
}

void Scene::Apply()
{
	for (auto model : models)
	{
		model.Render();
	}
		
}

void Scene::Select(int id)
{
	if (0 <= id && id < models.size())
	{
		select = id;
	}
	else
	{
		select = -1;
	}
}