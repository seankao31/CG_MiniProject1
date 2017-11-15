#pragma once
#include <string>

class SceneManager
{
public:
	std::string view_file, light_file, scene_file;

	SceneManager(const std::string&);
	~SceneManager();
};

