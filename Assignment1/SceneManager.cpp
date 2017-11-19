#include <string>
#include <iostream>
#include "SceneManager.h"
#include "Vec3d.h"

using namespace std;

SceneManager::SceneManager(int test)
{
	test_state = test;
	Init();
}

SceneManager::~SceneManager()
{
}

SceneManager& SceneManager::GetInstance(int test = 1)
{
	static SceneManager instance(test);
	return instance;
}

void SceneManager::Init()
{
	LoadTestScenes();
	view = test_scenes[test_state].view;
	light = test_scenes[test_state].light;
	scene = test_scenes[test_state].scene;
	zoom_speed = test_scenes[test_state].zoom_speed;
	rotate_speed = test_scenes[test_state].rotate_speed;
	drag_speed = test_scenes[test_state].drag_speed;
}

void SceneManager::LoadTestScenes()
{
	TEST_SCENE test_scene;

	test_scene.view = new View("view.view");
	test_scene.light = new Light("light.light");
	test_scene.scene = new Scene("scene.scene");
	test_scene.zoom_speed = 0.0001;
	test_scene.rotate_speed = 15;
	test_scene.drag_speed = 0.2;

	test_scenes.push_back(test_scene);

	test_scene.view = new View("scene2.view");
	test_scene.light = new Light("scene2.light");
	test_scene.scene = new Scene("scene2.scene");
	test_scene.zoom_speed = 0.005;
	test_scene.rotate_speed = 10;
	test_scene.drag_speed = 0.05;

	test_scenes.push_back(test_scene);
}

void SceneManager::ToggleTestScene()
{
	test_state += 1;
	test_state %= test_scenes.size();
	view = test_scenes[test_state].view;
	light = test_scenes[test_state].light;
	scene = test_scenes[test_state].scene;
	zoom_speed = test_scenes[test_state].zoom_speed;
	rotate_speed = test_scenes[test_state].rotate_speed;
	drag_speed = test_scenes[test_state].drag_speed;
	for (size_t i = 0; i < 8; ++i)
	{
		glDisable(GL_LIGHT0 + i);
	}
	glutReshapeWindow(view->viewport[2], view->viewport[3]);
}

void SceneManager::Render()
{
	view->Apply();
	light->Apply();
	scene->Apply();
}

void SceneManager::Reset()
{
	view->zoom.clear();
	view->rotation = 0;
	for (auto &model : scene->models)
	{
		model.Reset();
	}
}

void SceneManager::CameraZoomIn()
{
	Vec3d look_direction = view->vat - view->eye - view->zoom;
	view->zoom = view->zoom + look_direction * zoom_speed * look_direction.length();
	std::cout << "Zoom in" << std::endl;
}

void SceneManager::CameraZoomOut()
{
	Vec3d look_direction = view->vat - view->eye - view->zoom;
	view->zoom = view->zoom - look_direction * zoom_speed * look_direction.length();
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
		cout << " success" << endl;
	}
	else
	{
		cout << " fail" << endl;
	}
}

void SceneManager::ObjectTranslate(int delta_x, int neg_delta_y)
{
	if (scene->select >= 0)
	{
		int delta_y = -neg_delta_y;
		scene->models[scene->select].additional_translate[0] += drag_speed * delta_x;
		scene->models[scene->select].additional_translate[1] += drag_speed * delta_y;
		cout << "Object " << scene->select + 1 << " translated " << delta_x << ", " << delta_y << endl;
	}
}
