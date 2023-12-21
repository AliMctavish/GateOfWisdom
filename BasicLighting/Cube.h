#pragma once
#include "BaseObject.h"
#include "Texture.h"
#include "Model.h"

#define Texture_Type_Wall  1
#define Texture_Type_Ground  2
#define Texture_Type_Box  3

class Cube : public BaseObject{
private: 
	void Init();
	uint16_t m_TextureIndex;
public : 
	Material material;
	Texture texture;
	//Model model = Model("Models/Test/plat.obj", false);
	bool collided = false;
	bool isInterpolated = false;
	int cubeId;
	float angle;
	float rotateX,rotateY,rotateZ;
	Cube();
	~Cube();
	uint16_t inline GetTexutreIndex() { return m_TextureIndex; }
	glm::mat4 inline GetModel() { return m_Model; }
	void Update();
	void Draw();
	void SetTextureData(uint16_t textureIndex);
	void Rotate(float angle);
	void RotateOnY(float angle);
};
