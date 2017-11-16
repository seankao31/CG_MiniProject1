#pragma once
#include <string>
#include "View.h"
#include "Light.h"
#include "Scene.h"

class SceneManager
{
public:
	View *view;
	Light *light;
	Scene *scene;
	std::string view_file, light_file, scene_file;
	double zoom_speed, drag_speed;
	int rotate_speed;

	SceneManager(const std::string&);
	~SceneManager();

	void Init();
	void CameraZoomIn();
	void CameraZoomOut();
	void CameraRotateLeft();
	void CameraRotateRight();
	void SelectObject(int);
	void ObjectTranslate(int, int);
};

