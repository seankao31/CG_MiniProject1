#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Mesh.h"
#include "glut.h"
#include "View.h"
#include "Light.h"
#include "Scene.h"
#include "SceneManager.h"

#define SCENE "test1"
// 0.00005 for test1, 0.005 for test2
#define ZOOM_SPEED 0.00005
// for test1, for test2
#define ROTATE_SPEED 20

Scene *scene;
View *view;
Light *light;

int windowSize[2];

void display();
void reshape(GLsizei, GLsizei);
void keyboard(unsigned char, int, int);

int main(int argc, char** argv)
{
	SceneManager sm(SCENE);
	view = new View(sm.view_file);
	light = new Light(sm.light_file);
	scene = new Scene(sm.scene_file);

	glutInit(&argc, argv);
	glutInitWindowSize(view->viewport[2], view->viewport[3]);
	glutInitWindowPosition(view->viewport[0], view->viewport[1]);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutCreateWindow("Assignment1");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMainLoop();

	return 0;
}

void display()
{
	// clear the buffer
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);      //清除用color
	glClearDepth(1.0f);                        // Depth Buffer (就是z buffer) Setup
	glEnable(GL_DEPTH_TEST);                   // Enables Depth Testing
	glDepthFunc(GL_LEQUAL);                    // The Type Of Depth Test To Do
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//這行把畫面清成黑色並且清除z buffer

	view->apply();
	//glutReshapeWindow(windowSize[0], windowSize[1]);

	//注意light位置的設定，要在gluLookAt之後
	light->apply();

	scene->apply();

	glutSwapBuffers();
}

void reshape(GLsizei w, GLsizei h)
{
	windowSize[0] = w;
	windowSize[1] = h;
}

void keyboard(unsigned char key, int x, int y)
{
	Vec3d look_direction = view->vat - view->eye;
	switch (key)
	{
	case 'w':
		view->eye = view->eye + look_direction * ZOOM_SPEED * look_direction.length();
		glutPostRedisplay();
		break;
	case 's':
		view->eye = view->eye - look_direction * ZOOM_SPEED * look_direction.length();
		glutPostRedisplay();
		break;
	}
}

