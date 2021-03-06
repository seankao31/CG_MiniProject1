#include <fstream>
#include <iostream>
#include "Light.h"

using namespace std;

Light::Light(const string &light_file)
{
	LoadLight(light_file);
}

Light::Light()
{
}

Light::~Light()
{
}

void Light::Init(const string &light_file)
{
	LoadLight(light_file);
}

void Light::LoadLight(const string &light_file)
{
	fstream fin(light_file, fstream::in);
	string term;
	while (fin >> term)
	{
		if (term == "light")
		{
			LIGHT light;
			for (size_t i = 0; i < 3; ++i)
				fin >> light.position[i];
			for (size_t i = 0; i < 3; ++i)
				fin >> light.ambient[i];
			for (size_t i = 0; i < 3; ++i)
				fin >> light.diffuse[i];
			for (size_t i = 0; i < 3; ++i)
				fin >> light.specular[i];
			lights.push_back(light);
		}
		else if (term == "ambient")
		{
			for (size_t i = 0; i < 3; ++i)
				fin >> ambient[i];
		}
		else
		{
			cout << "Light: load file error" << endl;
			return;
		}
	}
	fin.close();
	Print();
}

void Light::Apply()
{
	glShadeModel(GL_SMOOTH);

	// z buffer enable
	glEnable(GL_DEPTH_TEST);

	// enable lighting
	glEnable(GL_LIGHTING);
	// set light property
	for (size_t i = 0; i < lights.size(); ++i)
	{
		glEnable(GL_LIGHT0 + i);
		glLightfv(GL_LIGHT0 + i, GL_POSITION, lights[i].position);
		glLightfv(GL_LIGHT0 + i, GL_DIFFUSE, lights[i].diffuse);
		glLightfv(GL_LIGHT0 + i, GL_SPECULAR, lights[i].specular);
		glLightfv(GL_LIGHT0 + i, GL_AMBIENT, lights[i].ambient);
	}
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);
}

void Light::Print()
{
	cout << lights.size() << " light(s)" << endl;
	for (auto light : lights)
	{
		cout << "Light" << endl;
		cout << "position: ";
		for (int i = 0; i < 4; ++i)
			cout << light.position[i] << ' ';
		cout << endl;
		cout << "ambient: ";
		for (int i = 0; i < 4; ++i)
			cout << light.ambient[i] << ' ';
		cout << endl;
		cout << "diffuse: ";
		for (int i = 0; i < 4; ++i)
			cout << light.diffuse[i] << ' ';
		cout << endl;
		cout << "specular: ";
		for (int i = 0; i < 4; ++i)
			cout << light.specular[i] << ' ';
		cout << endl;
		cout << endl;
	}
	cout << "Ambient" << endl;
	for (int i = 0; i < 4; ++i)
		cout << ambient[i] << ' ';
	cout << endl << endl;
}
