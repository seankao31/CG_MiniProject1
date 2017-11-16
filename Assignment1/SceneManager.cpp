#include <string>
#include <iostream>
#include "SceneManager.h"
#include "Vec3d.h"

using namespace std;

SceneManager::SceneManager(const string &name = "test1")
{
	if (name == "test1")
	{
		view_file = "view.view";
		light_file = "light.light";
		scene_file = "scene.scene";
		zoom_speed = 0.0001;
		rotate_speed = 15;
		drag_speed = 0.2;
	}
	else if (name == "test2")
	{
		view_file = "scene2.view";
		light_file = "scene2.light";
		scene_file = "scene2.scene";
		zoom_speed = 0.005;
		rotate_speed = 10;
		drag_speed = 0.05;
	}
	else
	{
		cerr << "No such scene \"" << name << "\" exists" << endl;
		return;
	}
	Init();
}

SceneManager::~SceneManager()
{
}

void SceneManager::Init()
{
	view = new View(view_file);
	light = new Light(light_file);
	scene = new Scene(scene_file);
}

void SceneManager::CameraZoomIn()
{
	Vec3d look_direction = view->vat - view->eye;
	view->eye = view->eye + look_direction * zoom_speed * look_direction.length();
	std::cout << "Zoom in" << std::endl;
}

void SceneManager::CameraZoomOut()
{
	Vec3d look_direction = view->vat - view->eye;
	view->eye = view->eye - look_direction * zoom_speed * look_direction.length();
	std::cout << "Zoom out" << std::endl;
}

void SceneManager::CameraRotateLeft()
{
	view->rotation = (view->rotation + rotate_speed) % 360;
	cout << "Rotate left" << endl;
}

void SceneManager::CameraRotateRight()
{
	view->rotation = (view->rotation - rotate_speed) % 360;
	cout << "Rotate right" << endl;
}

void SceneManager::SelectObject(int key)
{
	scene->Select(key - '1');
	cout << "Select " << key - '0';
	if (scene->select >= 0)
	{
		cout << " successed" << endl;
	}
	else
	{
		cout << " failed" << endl;
	}
}

void SceneManager::ObjectTranslate(int delta_x, int delta_y)
{
	if (scene->select >= 0)
	{
		scene->models[scene->select].translate[0] += drag_speed * delta_x;
		scene->models[scene->select].translate[1] -= drag_speed * delta_y;
		cout << "Object " << scene->select + 1 << " translated " << delta_x << ", " << delta_y << endl;
	}
}
