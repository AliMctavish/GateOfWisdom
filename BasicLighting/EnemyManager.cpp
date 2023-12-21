#include "EntityManager.h"

void EntityManager::SetEntities(std::vector<Enemy>& enemies, std::vector<Cube>& cubes, std::vector<Key>& keys, std::vector<Light>& lights)
{
	m_Enemies = enemies;
	m_Cubes = cubes;
	m_Keys = keys;
	m_Lights = lights;
}

void EntityManager::DrawEnemies()
{
	for (Enemy& enemy : m_Enemies)
		enemy.Draw();
}

void EntityManager::DrawKeys()
{
	for (Key& key : m_Keys)
		key.Draw();
}

void EntityManager::DrawLights()
{
	for (Light& light : m_Lights)
		light.Draw();
}

void EntityManager::DrawCubes()
{
	for (Cube& cube : m_Cubes)
		cube.Draw();
}

void EntityManager::DrawCubesWithLights()
{

}
