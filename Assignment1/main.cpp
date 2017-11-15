#include "mesh.h"
#include "glut.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

mesh *object;

int windowSize[2];

void light();
void view();
void display();
void reshape(GLsizei , GLsizei );

int main(int argc, char** argv)
{
	object = new mesh("box.obj");

	glutInit(&argc, argv);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutCreateWindow("Assignment1");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMainLoop();

	return 0;
}

void view()
{
	GLdouble eye[3], vat[3], vup[3], fovy, dnear, dfar;
	GLint viewport[4];

	std::fstream fin("view.view", std::fstream::in);
	std::string term;

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

	// viewport transformation
	glViewport(viewport[0], viewport[1], viewport[2], viewport[3]);
	glutReshapeWindow(viewport[2], viewport[3]);

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

typedef struct LIGHT
{
	GLfloat position[4] = { 1.0 };
	GLfloat ambient[4] = { 1.0 };
	GLfloat diffuse[4] = { 1.0 };
	GLfloat specular[4] = { 1.0 };
} LIGHT;

void light()
{
	std::fstream fin("light.light", std::fstream::in);
	std::string term;
	std::vector<LIGHT> lights;
	GLfloat ambient[4] = { 1.0 };
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
			std::cout << "light file error" << std::endl;
		}
	}
	fin.close();

	glShadeModel(GL_SMOOTH);

	// z buffer enable
	glEnable(GL_DEPTH_TEST);

	// enable lighting
	glEnable(GL_LIGHTING);
	// set light property
	for (int i = 0; i < lights.size(); ++i)
	{
		glEnable(GL_LIGHT0 + i);
		glLightfv(GL_LIGHT0 + i, GL_POSITION, lights[i].position);
		glLightfv(GL_LIGHT0 + i, GL_DIFFUSE, lights[i].diffuse);
		glLightfv(GL_LIGHT0 + i, GL_SPECULAR, lights[i].specular);
		glLightfv(GL_LIGHT0 + i, GL_AMBIENT, lights[i].ambient);
	}
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);
}

void display()
{
	// clear the buffer
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);      //清除用color
	glClearDepth(1.0f);                        // Depth Buffer (就是z buffer) Setup
	glEnable(GL_DEPTH_TEST);                   // Enables Depth Testing
	glDepthFunc(GL_LEQUAL);                    // The Type Of Depth Test To Do
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//這行把畫面清成黑色並且清除z buffer

	view();

	//注意light位置的設定，要在gluLookAt之後
	light();

	int lastMaterial = -1;
	for(size_t i=0;i < object->fTotal;++i)
	{
		// set material property if this face used different material
		if(lastMaterial != object->faceList[i].m)
		{
			lastMaterial = (int)object->faceList[i].m;
			glMaterialfv(GL_FRONT, GL_AMBIENT  , object->mList[lastMaterial].Ka);
			glMaterialfv(GL_FRONT, GL_DIFFUSE  , object->mList[lastMaterial].Kd);
			glMaterialfv(GL_FRONT, GL_SPECULAR , object->mList[lastMaterial].Ks);
			glMaterialfv(GL_FRONT, GL_SHININESS, &object->mList[lastMaterial].Ns);

			//you can obtain the texture name by object->mList[lastMaterial].map_Kd
			//load them once in the main function before mainloop
			//bind them in display function here
		}

		glMatrixMode(GL_MODELVIEW);
		
		glPushMatrix();

		glTranslatef(-200.0, 0.0, 0.0);
		glRotatef(0.0, 0.0, 1.0, 0.0);
		glScalef(1.0, 1.0, 1.0);
		
		glBegin(GL_TRIANGLES);
		for (size_t j=0;j<3;++j)
		{
			//textex corrd. object->tList[object->faceList[i][j].t].ptr
			glNormal3fv(object->nList[object->faceList[i][j].n].ptr);
			glVertex3fv(object->vList[object->faceList[i][j].v].ptr);	
		}
		glEnd();


		glPopMatrix();
	}

	glutSwapBuffers();
}

void reshape(GLsizei w, GLsizei h)
{
	windowSize[0] = w;
	windowSize[1] = h;
}

