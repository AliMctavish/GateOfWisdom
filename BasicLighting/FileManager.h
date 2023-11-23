#pragma once
#include <vector>
#include "Cube.h"
#include "Light.h"
#define Available_Textures 5
#define WallTexturePath 0
#define GroundTexturePath 1
#define BoxTexturePath 2

static const char* m_texturePath[Available_Textures] = {"Assests/wall.jpg","Assests/lol.jpg","Assests/ds.jpg"};

class FileManager {
public : 
	enum ObjectType {
		Lights = 0,
		CubeObject = 1,
	};
	FileManager();
	~FileManager();
	inline static const char* SelectTextureFile(int index) { return m_texturePath[index]; }
	static void SaveFile(std::vector<Light> &lights ,std::vector<Cube> &cubes);
	static void LoadFile(std::vector<Light> &lights,std::vector<Cube> &cubes , Shader& lightShader , Shader& cubeShader);
};
