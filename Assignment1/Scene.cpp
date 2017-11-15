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

void Scene::apply()
{
	for (auto model : models)
	{
		int lastMaterial = -1;
		for (size_t i = 0; i < model.object->fTotal; ++i)
		{
			// set material property if this face used different material
			if (lastMaterial != model.object->faceList[i].m)
			{
				lastMaterial = (int)model.object->faceList[i].m;
				glMaterialfv(GL_FRONT, GL_AMBIENT, model.object->mList[lastMaterial].Ka);
				glMaterialfv(GL_FRONT, GL_DIFFUSE, model.object->mList[lastMaterial].Kd);
				glMaterialfv(GL_FRONT, GL_SPECULAR, model.object->mList[lastMaterial].Ks);
				glMaterialfv(GL_FRONT, GL_SHININESS, &model.object->mList[lastMaterial].Ns);

				//you can obtain the texture name by object->mList[lastMaterial].map_Kd
				//load them once in the main function before mainloop
				//bind them in display function here
			}

			glMatrixMode(GL_MODELVIEW);

			glPushMatrix();

			glTranslatef(model.translate[0], model.translate[1], model.translate[2]);
			glRotatef(model.rotate[0], model.rotate[1], model.rotate[2], model.rotate[3]);
			glScalef(model.scale[0], model.scale[1], model.scale[2]);

			glBegin(GL_TRIANGLES);
			for (size_t j = 0; j<3; ++j)
			{
				//textex corrd. object->tList[object->faceList[i][j].t].ptr
				glNormal3fv(model.object->nList[model.object->faceList[i][j].n].ptr);
				glVertex3fv(model.object->vList[model.object->faceList[i][j].v].ptr);
			}
			glEnd();


			glPopMatrix();
		}
	}
		
}
