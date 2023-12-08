#pragma once
#include "Model.h"
class ModelLoader {
private : 
	Model Sphere;
	Model Enemy;
public:
	enum Type {
		Type_Sphere = 0,
		Type_Enemy = 1,
	};
	void InitializeModels()
	{
		Sphere = Model("Models/Test/dot.obj");
		Enemy = Model("Models/Enemy/Enemy.obj");
	}

	Model GetModel(Type type)
	{
		Model selectedModel;
		switch (type)
		{
		case ModelLoader::Type_Sphere:
			selectedModel = Sphere;
			break;
		case ModelLoader::Type_Enemy:
			selectedModel = Enemy;
			break;
		default:
			break;
		}

		return selectedModel;
	}
};
