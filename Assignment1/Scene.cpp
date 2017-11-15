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
	LoadScene(scene_file);
	cout << "Scene" << endl;
	for (auto model : models)
	{
		Mesh *object = new Mesh(model.object_file);
		objects.push_back(object);
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
	for (size_t i = 0; i < objects.size(); ++i)
	{
		int lastMaterial = -1;
		for (size_t j = 0; j < objects[i]->fTotal; ++j)
		{
			// set material property if this face used different material
			if (lastMaterial != objects[i]->faceList[j].m)
			{
				lastMaterial = (int)objects[i]->faceList[j].m;
				glMaterialfv(GL_FRONT, GL_AMBIENT, objects[i]->mList[lastMaterial].Ka);
				glMaterialfv(GL_FRONT, GL_DIFFUSE, objects[i]->mList[lastMaterial].Kd);
				glMaterialfv(GL_FRONT, GL_SPECULAR, objects[i]->mList[lastMaterial].Ks);
				glMaterialfv(GL_FRONT, GL_SHININESS, &objects[i]->mList[lastMaterial].Ns);

				//you can obtain the texture name by object->mList[lastMaterial].map_Kd
				//load them once in the main function before mainloop
				//bind them in display function here
			}

			glMatrixMode(GL_MODELVIEW);

			glPushMatrix();

			glTranslatef(models[i].translate[0], models[i].translate[1], models[i].translate[2]);
			glRotatef(models[i].rotate[0], models[i].rotate[1], models[i].rotate[2], models[i].rotate[3]);
			glScalef(models[i].scale[0], models[i].scale[1], models[i].scale[2]);

			glBegin(GL_TRIANGLES);
			for (size_t k = 0; k<3; ++k)
			{
				//textex corrd. object->tList[object->faceList[i][j].t].ptr
				glNormal3fv(objects[i]->nList[objects[i]->faceList[j][k].n].ptr);
				glVertex3fv(objects[i]->vList[objects[i]->faceList[j][k].v].ptr);
			}
			glEnd();


			glPopMatrix();
		}
	}
		
}
