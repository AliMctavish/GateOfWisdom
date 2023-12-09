#pragma once
#include <vector>
#include "Enemy.h"

class EnemyManager {
private :
	Shader m_Shader;
	float timer = 10;
public : 
	EnemyManager(Shader &shader) : m_Shader(shader) { };
	void EnemyGenerator(std::vector<Enemy> enemies)
	{
		std::cout << glfwGetTime() << std::endl;
		timer -= glfwGetTime();
		if (timer < 0)
		{
			Enemy enemy;
			enemy.SetShader(m_Shader);
			enemy.SetRandomLocation();
			enemies.push_back(enemy);
			timer = 10;
		}
	}
};
