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
	}
	else if (name == "test2")
	{
		view_file = "scene2.view";
		light_file = "scene2.light";
		scene_file = "scene2.scene";
	}
	else
	{
		cerr << "No such scene \"" << name << "\" exists" << endl;
	}
}

SceneManager::~SceneManager()
{
}
