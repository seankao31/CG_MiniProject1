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

#define SCENE "test2"

SceneManager *sm;
Scene *scene;
View *view;
Light *light;

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

int main(int argc, char** argv)
{
	sm = new SceneManager(SCENE);
	view = new View(sm->view_file);
	light = new Light(sm->light_file);
	scene = new Scene(sm->scene_file);

	glutInit(&argc, argv);
	glutInitWindowSize(view->viewport[2], view->viewport[3]);
	glutInitWindowPosition(view->viewport[0], view->viewport[1]);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutCreateWindow("Assignment1");
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

	view->apply();
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
		view->eye = view->eye + look_direction * sm->zoom_speed * look_direction.length();
		std::cout << "Zoom in" << std::endl;
		glutPostRedisplay();
		break;
	case 's':
		view->eye = view->eye - look_direction * sm->zoom_speed * look_direction.length();
		std::cout << "Zoom out" << std::endl;
		glutPostRedisplay();
		break;
	case 'a':
		view->rotation = (view->rotation + 20) % 360;
		glutPostRedisplay();
		break;
	case 'd':
		view->rotation = (view->rotation - 20) % 360;
		glutPostRedisplay();
		break;
	default:
		if ('1' <= key && key <= '9')
		{
			std::cout << "Select " << key << std::endl;
			scene->select = key - '1';
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
			std::cout << "left down at " << x << ' ' << y << std::endl;
		}
		else if (state == GLUT_UP)
		{
			mouse_info.left_button_pressing = false;
			std::cout << "left up at " << x << ' ' << y << std::endl;
		}
	}
}

void motion(int x, int y)
{
	if (mouse_info.left_button_pressing && 0 <= scene->select && scene->select < scene->models.size())
	{
		scene->models[scene->select].translate[0] += sm->drag_speed * (x - mouse_info.x);
		scene->models[scene->select].translate[1] -= sm->drag_speed * (y - mouse_info.y);
		mouse_info.x = x;
		mouse_info.y = y;
		std::cout << "left moving at " << x << ' ' << y << std::endl;
		glutPostRedisplay();
	}
}
