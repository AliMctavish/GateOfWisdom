#pragma once
#include <vector>
#include "Cube.h"
#include "Light.h"
#include "Key.h"
#include "Enemy.h"
#include "Machine.h"
#include "Gate.h"
#define WallTexturePath 1
#define GroundTexturePath 2
#define BoxTexturePath 3
#define IMAGE_TEXTRUE_PATH_0 4
#define IMAGE_TEXTRUE_PATH_1 5

class FileManager {
public : 
	enum ObjectType {
		Lights = 0,
		CubeObject = 1,
	};
	FileManager();
	~FileManager();
	static void SaveFile(std::vector<Light> &lights ,
		std::vector<Cube> &cubes ,std::vector<Key> &keys,
		std::vector<Enemy> &enemies,Machine &machine ,Gate &gate,std::string& fileName , Player &player);

	static void LoadFile(std::vector<Light> &lights,
		std::vector<Cube> &cubes , std::vector<Key>& keys
		, std::vector<Enemy>& enemies, Machine& machine, Gate& gate,
		Shader& lightShader, Shader& cubeShader , Shader& modelShader,
		ModelLoader &modelLoader,std::string fileName , Player &player);
};
