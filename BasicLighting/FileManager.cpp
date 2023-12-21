#include "FileManager.h"

FileManager::FileManager()
{
}

FileManager::~FileManager()
{
}

void FileManager::SaveFile(std::vector<Light>& lights, std::vector<Cube>& cubes, std::vector<Key>& keys, std::string& fileName)
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

	newStream.close();
}

void FileManager::LoadFile(std::vector<Light>& lights, std::vector<Cube>& cubes, std::vector<Key>& keys, Shader& lightShader, Shader& cubeShader, ModelLoader &modelLoader, std::string fileName)
{
	std::ifstream newStream("Maps/" + fileName + ".txt");
	std::string line;
	bool isColors = false;
	bool isCube = false;
	bool isKey = false;

	while (std::getline(newStream, line))
	{
		if (line.find("#Light_Coordinates") != std::string::npos)
			continue;

		if (line.find("#Cube_Coordinates") != std::string::npos)
		{
			isCube = true;
			continue;
		}
		if (line.find("#Key_Coordinates") != std::string::npos)
		{
			isCube = false;
			isKey = true;
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

			if (!isCube && !isKey)
			{
				Light light;
				light.SetShader(lightShader);
				light.Position = glm::vec3(std::stoi(stringList[0]), std::stoi(stringList[1]), std::stoi(stringList[2]));
				light.SetObjectColor(std::stof(stringList[3]), std::stof(stringList[4]), std::stof(stringList[5]));
				light.SetModel(modelLoader);
				light.SetName("test" + std::to_string(lights.size()));
				lights.push_back(light);
			}
			else if (isCube)
			{
				Cube cube;
				cube.SetShader(cubeShader);
				cube.Position = glm::vec3(std::stoi(stringList[0]), std::stoi(stringList[1]), std::stoi(stringList[2]));
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
				key.SetModel(modelLoader);

				key.Position = glm::vec3(std::stoi(stringList[0]), std::stoi(stringList[1]), std::stoi(stringList[2]));
				key.SetObjectColor(std::stof(stringList[3]), std::stof(stringList[4]), std::stof(stringList[5]));


				//cube.SetObjectColor();
				key.SetName("test" + std::to_string(keys.size()));
				keys.push_back(key);
			}
		}
	}
	isCube = false;
	newStream.close();
}

