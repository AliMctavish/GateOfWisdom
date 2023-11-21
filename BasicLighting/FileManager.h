#pragma once
#include "Cube.h"
#include "Light.h"
#include <vector>

class FileManager {
private : 
public : 
	enum ObjectType {
		Lights = 0,
		CubeObject = 1,
	};
	FileManager();
	~FileManager();
	static void SaveFile(std::vector<Light> &lights ,std::vector<Cube> &cubes);
	static void LoadFile(std::vector<Light> &lights,std::vector<Cube> &cubes , Shader& lightShader , Shader& cubeShader);
};
