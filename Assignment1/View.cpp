#include <fstream>
#include <iostream>
#include "View.h"

using namespace std;

View::View(const string &view_file)
{
	Init(view_file);
}

View::View()
{
}

View::~View()
{
}

void View::Init(const string &view_file)
{
	LoadView(view_file);
}

void View::LoadView(const string &view_file)
{
	fstream fin(view_file, fstream::in);
	string term;
	while (fin >> term)
	{
		if (term == "eye")
		{
			fin >> eye[0] >> eye[1] >> eye[2];
		}
		else if (term == "vat")
		{
			fin >> vat[0] >> vat[1] >> vat[2];
		}
		else if (term == "vup")
		{
			fin >> vup[0] >> vup[1] >> vup[2];
		}
		else if (term == "fovy")
		{
			fin >> fovy;
		}
		else if (term == "dnear")
		{
			fin >> dnear;
		}
		else if (term == "dfar")
		{
			fin >> dfar;
		}
		else if (term == "viewport")
		{
			fin >> viewport[0] >> viewport[1] >> viewport[2] >> viewport[3];
		}
		else
		{
			std::cout << "view file error" << std::endl;
		}
	}
	fin.close();
	print();
}

void View::apply()
{
	// viewport transformation
	glViewport(viewport[0], viewport[1], viewport[2], viewport[3]);

	// projection transformation
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fovy, (GLfloat)viewport[2] / (GLfloat)viewport[3], dnear, dfar);
	// viewing and modeling transformation
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(eye[0], eye[1], eye[2],// eye
		vat[0], vat[1], vat[2],     // center
		vup[0], vup[1], vup[2]);    // up
}

void View::print()
{
	cout << "View" << endl;
	cout << "eye: ";
	for (int i = 0; i < 3; ++i)
		cout << eye[i] << ' ';
	cout << endl;
	cout << "vat: ";
	for (int i = 0; i < 3; ++i)
		cout << vat[i] << ' ';
	cout << endl;
	cout << "vup: ";
	for (int i = 0; i < 3; ++i)
		cout << vup[i] << ' ';
	cout << endl;
	cout << "fovy: " << fovy << endl;
	cout << "dnear: " << dnear << endl;
	cout << "dfar: " << dfar << endl;
	cout << "viewport: ";
	for (int i = 0; i < 4; ++i)
		cout << viewport[i] << ' ';
	cout << endl;
	cout << endl;
}
