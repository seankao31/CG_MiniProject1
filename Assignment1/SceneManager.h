#pragma once
#include <string>

class SceneManager
{
public:
	std::string view_file, light_file, scene_file;
	double zoom_speed, drag_speed;
	int rotate_speed;

	SceneManager(const std::string&);
	~SceneManager();
};

