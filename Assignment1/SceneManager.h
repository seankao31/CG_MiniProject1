#pragma once
#include <string>
#include <vector>
#include "View.h"
#include "Light.h"
#include "Scene.h"

class SceneManager
{
	class TEST_SCENE
	{
	public:
		View *view;
		Light *light;
		Scene *scene;
		double zoom_speed, drag_speed;
		int rotate_speed;

		TEST_SCENE() {};
		~TEST_SCENE() {};
	};

private:
	SceneManager(int);

public:
	std::vector<TEST_SCENE> test_scenes;
	View *view;
	Light *light;
	Scene *scene;
	double zoom_speed, drag_speed;
	int rotate_speed;

	int test_state;

	~SceneManager();

	static SceneManager& GetInstance(int);
	SceneManager(SceneManager const&) = delete;
	void operator=(SceneManager const&) = delete;

	void Init();
	void LoadTestScenes();
	void ToggleTestScene();
	void Render();
	void Reset();
	void CameraZoomIn();
	void CameraZoomOut();
	void CameraRotateLeft();
	void CameraRotateRight();
	void SelectObject(int);
	void ObjectTranslate(int, int);
};

