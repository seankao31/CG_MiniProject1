#include <string>
#include <iostream>
#include "SceneManager.h"

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
	}
}

SceneManager::~SceneManager()
{
}