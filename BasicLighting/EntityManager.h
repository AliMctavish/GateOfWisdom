#pragma once
#include "Enemy.h"
#include "Key.h"
#include "Light.h"
#include "Cube.h"

class EntityManager {
private : 
	std::vector<Enemy> m_Enemies;
	std::vector<Key> m_Keys;
	std::vector<Light> m_Lights;
	std::vector<Cube> m_Cubes;
public :
	void SetEntities(std::vector<Enemy>& enemies, std::vector<Cube>& cubes, std::vector<Key>& keys, std::vector<Light>& lights);
	void DrawEnemies();
	void DrawCubes();
	void DrawKeys();
	void DrawLights();
	void DrawCubesWithLights();
};