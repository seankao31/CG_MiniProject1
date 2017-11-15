#include "Light.h"
#include <fstream>
#include <iostream>

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

void Light::LoadLight(const string &light_file)
{
	fstream fin("light.light", fstream::in);
	string term;
	while (fin >> term)
	{
		if (term == "light")
		{
			LIGHT light;
			fin >> light.position[0] >> light.position[1] >> light.position[2];
			fin >> light.ambient[0] >> light.ambient[1] >> light.ambient[2];
			fin >> light.diffuse[0] >> light.diffuse[1] >> light.diffuse[2];
			fin >> light.specular[0] >> light.specular[1] >> light.specular[2];
			lights.push_back(light);
		}
		else if (term == "ambient")
		{
			fin >> ambient[0] >> ambient[1] >> ambient[2];
		}
		else
		{
			cout << "light file error" << endl;
		}
	}
	fin.close();
	print();
}

void Light::print()
{
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
	cout << endl;
}
