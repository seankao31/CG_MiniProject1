#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Mesh.h"
#include "FreeImage.h"
#include "glew.h"
#include "glut.h"
#include "View.h"
#include "Light.h"
#include "Scene.h"
#include "SceneManager.h"
#include "TextureManager.h"

int windowSize[2];

void display();
void reshape(GLsizei, GLsizei);
void keyboard(unsigned char, int, int);
void mouse(int, int, int, int);
void motion(int, int);

struct Mouse
{
	bool left_button_pressing = false;
	int x, y;
} mouse_info;

SceneManager& sm = SceneManager::GetInstance();
TextureManager& tm = TextureManager::GetInstance();

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(sm.view->viewport[2], sm.view->viewport[3]);
	glutInitWindowPosition(sm.view->viewport[0], sm.view->viewport[1]);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutCreateWindow("Assignment1");
	glewInit();
	tm.LoadTextures();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
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

	sm.Render();
	glutSwapBuffers();
}

void reshape(GLsizei w, GLsizei h)
{
	windowSize[0] = w;
	windowSize[1] = h;
}

void keyboard(unsigned char key, int x, int y)
{
	Vec3d look_direction = sm.view->vat - sm.view->eye;
	switch (key)
	{
	case 'r':
		sm.Reset();
		glutPostRedisplay();
		break;
	case 't':
		sm.ToggleTestScene();
		glutPostRedisplay();
		break;
	case 'w':
		sm.CameraZoomIn();
		glutPostRedisplay();
		break;
	case 's':
		sm.CameraZoomOut();
		glutPostRedisplay();
		break;
	case 'a':
		sm.CameraRotateLeft();
		glutPostRedisplay();
		break;
	case 'd':
		sm.CameraRotateRight();
		glutPostRedisplay();
		break;
	default:
		if ('1' <= key && key <= '9')
		{
			sm.SelectObject(key);
		}
	}
}

void mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
	{
		if (state == GLUT_DOWN)
		{
			mouse_info.left_button_pressing = true;
			mouse_info.x = x;
			mouse_info.y = y;
		}
		else if (state == GLUT_UP)
		{
			mouse_info.left_button_pressing = false;
		}
	}
}

void motion(int x, int y)
{
	if (mouse_info.left_button_pressing)
	{
		sm.ObjectTranslate(x - mouse_info.x, y - mouse_info.y);
		mouse_info.x = x;
		mouse_info.y = y;
		glutPostRedisplay();
	}
}
