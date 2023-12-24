#include "FileManager.h"

FileManager::FileManager()
{
}

FileManager::~FileManager()
{
}

// WARNING : code smell down here :D 

void FileManager::SaveFile(std::vector<Light>& lights, std::vector<Cube>& cubes
	, std::vector<Key>& keys, std::vector<Enemy>& enemies,
	Machine& machine, Gate& gate, std::string& fileName)
{
	std::ofstream newStream("Maps/" + fileName + ".txt");
	newStream << "#Light_Coordinates" << std::endl;
	for (Light& light : lights)
	{
		newStream << light.Position.x << " " <<
			light.Position.y << " " <<
			light.Position.z << " " <<
			light.Color[0] << " " <<
			light.Color[1] << " " <<
			light.Color[2] << std::endl;

		std::cout << "saving light data" << std::endl;
	}
	newStream << "#Cube_Coordinates" << std::endl;
	for (Cube& cube : cubes)
	{
		newStream << cube.Position.x << " " <<
			cube.Position.y << " " <<
			cube.Position.z << " " <<
			cube.Color[0] << " " <<
			cube.Color[1] << " " <<
			cube.Color[2] << " " <<
			cube.Size.x << " " <<
			cube.Size.y << " " <<
			cube.Size.z << " " <<
			cube.GetTexutreIndex() <<
			std::endl;

		std::cout << "saving object data" << std::endl;
	}
	newStream << "#Key_Coordinates" << std::endl;
	for (Key& key : keys)
	{
		newStream << key.Position.x << " " <<
			key.Position.y << " " <<
			key.Position.z << " " <<
			key.Color[0] << " " <<
			key.Color[1] << " " <<
			key.Color[2] << " " <<
			key.Size.x << " " <<
			key.Size.y << " " <<
			key.Size.z << " " <<
			std::endl;

		std::cout << "saving keys data" << std::endl;
	}

	newStream << "#Enemy_Coordinates" << std::endl;
	for (Enemy& enemy : enemies)
	{
		newStream << enemy.Position.x << " " <<
			enemy.Position.y << " " <<
			enemy.Position.z << " " <<
			enemy.Color[0] << " " <<
			enemy.Color[1] << " " <<
			enemy.Color[2] << " " <<
			enemy.Size.x << " " <<
			enemy.Size.y << " " <<
			enemy.Size.z << " " <<
			std::endl;

		std::cout << "saving enemies data" << std::endl;
	}
	newStream << "#Machine_Coordinates" << std::endl;

	newStream << machine.Position.x << " " <<
		machine.Position.y << " " <<
		machine.Position.z << " " <<
		machine.rotateY << " " <<
		std::endl;

	newStream << "#Gate_Coordinates" << std::endl;

	newStream << gate.Position.x << " " <<
		gate.Position.y << " " <<
		gate.Position.z << " " <<
		gate.rotateY << " " <<
		std::endl;

	newStream.close();
}

void FileManager::LoadFile(std::vector<Light>& lights, std::vector<Cube>& cubes, std::vector<Key>& keys, std::vector<Enemy>& enemies, Machine& machine, Gate& gate, Shader& lightShader, Shader& cubeShader, Shader& modelShader, ModelLoader& modelLoader, std::string fileName)
{
	std::ifstream newStream("Maps/" + fileName + ".txt");
	std::string line;
	bool isLight = false;
	bool isColors = false;
	bool isCube = false;
	bool isKey = false;
	bool isEnemy = false;
	bool isMachine = false;
	bool isGate = false;

	while (std::getline(newStream, line))
	{
		if (line.find("#Light_Coordinates") != std::string::npos)
		{
			isLight = true;
			continue;
		}

		if (line.find("#Cube_Coordinates") != std::string::npos)
		{
			isCube = true;
			isLight = false;
			continue;
		}
		if (line.find("#Key_Coordinates") != std::string::npos)
		{
			isCube = false;
			isLight = false;
			isKey = true;
			continue;
		}
		if (line.find("#Enemy_Coordinates") != std::string::npos)
		{
			isCube = false;
			isKey = false;
			isLight = false;
			isEnemy = true;
			continue;
		}
		if (line.find("#Machine_Coordinates") != std::string::npos)
		{
			isCube = false;
			isKey = false;
			isEnemy = false;
			isLight = false;
			isMachine = true;
			continue;
		}
		if (line.find("#Gate_Coordinates") != std::string::npos)
		{
			isCube = false;
			isKey = false;
			isEnemy = false;
			isMachine = false;
			isLight = false;
			isGate = true;
			continue;
		}

		std::stringstream subStream(line);
		std::string subString;
		std::vector<std::string> stringList;

		while (std::getline(subStream, subString, ' '))
		{
			//std::cout << "Loading data into project" << std::endl;
			//std::cout << subString << std::endl;
			stringList.push_back(subString);
		}
		if (stringList.size() > 0)
		{

			if (isLight)
			{
				Light light;
				light.SetShader(lightShader);
				light.SetPosition(glm::vec3(std::stoi(stringList[0]), std::stoi(stringList[1]), std::stoi(stringList[2])));
				light.SetObjectColor(std::stof(stringList[3]), std::stof(stringList[4]), std::stof(stringList[5]));
				//light.SetModel(modelLoader);
				light.SetName("test" + std::to_string(lights.size()));
				lights.push_back(light);
			}
			else if (isCube)
			{
				Cube cube;
				cube.SetShader(cubeShader);
				cube.SetPosition(glm::vec3(std::stoi(stringList[0]), std::stoi(stringList[1]), std::stoi(stringList[2])));
				cube.SetObjectColor(std::stof(stringList[3]), std::stof(stringList[4]), std::stof(stringList[5]));
				cube.Size.x = std::stof(stringList[6]);
				cube.Size.y = std::stof(stringList[7]);
				cube.Size.z = std::stof(stringList[8]);
				cube.SetTextureData(std::stoi(stringList[9]));
				//cube.SetObjectColor();
				cube.SetName("test" + std::to_string(cubes.size()));
				cubes.push_back(cube);
			}
			else if (isKey)
			{
				Key key;
				key.SetShader(lightShader);
				//key.SetModel(modelLoader);
				key.SetPosition(glm::vec3(std::stoi(stringList[0]), std::stoi(stringList[1]), std::stoi(stringList[2])));
				key.SetObjectColor(std::stof(stringList[3]), std::stof(stringList[4]), std::stof(stringList[5]));
				//cube.SetObjectColor();
				key.SetName("test" + std::to_string(keys.size()));
				keys.push_back(key);
			}
			else if (isEnemy)
			{
				Enemy enemy;
				enemy.SetShader(modelShader);
				//enemy.SetModel(modelLoader);
				enemy.SetPosition(glm::vec3(std::stoi(stringList[0]), std::stoi(stringList[1]), std::stoi(stringList[2])));
				enemy.SetObjectColor(std::stof(stringList[3]), std::stof(stringList[4]), std::stof(stringList[5]));
				//cube.SetObjectColor();
				enemy.SetName("test" + std::to_string(enemies.size()));
				enemies.push_back(enemy);
			}
			else if (isMachine)
			{
				Machine _machine;
				_machine.SetShader(lightShader);
				//_machine.SetModel(modelLoader);
				_machine.SetPosition(glm::vec3(std::stoi(stringList[0]), std::stoi(stringList[1]), std::stoi(stringList[2])));
				_machine.rotateY = std::stof(stringList[3]);
				machine = _machine;
			}
			else if (isGate)
			{
				Gate _gate;
				_gate.SetShader(lightShader);
				//_gate.SetModel(modelLoader);
				_gate.SetPosition(glm::vec3(std::stoi(stringList[0]), std::stoi(stringList[1]), std::stoi(stringList[2])));
				_gate.rotateY = std::stoi(stringList[3]);

				for (Light& light : lights)
				{
					_gate.ProcessColor(light.Color[0], light.Color[1], light.Color[2]);
				}
				float offset = 0;
				for (int i = 0; i < _gate.m_Colors.size(); i++) {
					RequiredColor requiredColor;
					requiredColor.SetShader(lightShader);
					if (i < _gate.m_Colors.size())
						requiredColor.SetObjectColor(_gate.m_Colors[i][0], _gate.m_Colors[i][1], _gate.m_Colors[i][2]);
					requiredColor.SetPosition(_gate.Position + 10.f+ offset + glm::vec3(0,30,0));
					_gate.RequiredColors.push_back(requiredColor);
					offset+=10;
				}
				gate = _gate;
			}

		}
	}
	newStream.close();
}

