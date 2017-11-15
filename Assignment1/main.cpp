#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "mesh.h"
#include "glut.h"
#include "View.h"
#include "Light.h"
#include "Scene.h"


Scene *scene;
View *view;
Light *light;

int windowSize[2];

void display();
void reshape(GLsizei , GLsizei );

int main(int argc, char** argv)
{
	view = new View("view.view");
	light = new Light("light.light");
	scene = new Scene("scene.scene");

	glutInit(&argc, argv);
	glutInitWindowSize(view->viewport[2] - view->viewport[0], view->viewport[3] - view->viewport[1]);
	glutInitWindowPosition(view->viewport[0], view->viewport[1]);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutCreateWindow("Assignment1");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMainLoop();

	return 0;
}

void display()
{
	// clear the buffer
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);      //�M����color
	glClearDepth(1.0f);                        // Depth Buffer (�N�Oz buffer) Setup
	glEnable(GL_DEPTH_TEST);                   // Enables Depth Testing
	glDepthFunc(GL_LEQUAL);                    // The Type Of Depth Test To Do
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//�o���e���M���¦�åB�M��z buffer

	view->apply();
	glutReshapeWindow(windowSize[0], windowSize[1]);

	//�`�Nlight��m���]�w�A�n�bgluLookAt����
	light->apply();

	scene->apply();

	glutSwapBuffers();
}

void reshape(GLsizei w, GLsizei h)
{
	windowSize[0] = w;
	windowSize[1] = h;
}

