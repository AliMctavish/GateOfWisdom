#pragma once
#include "BaseObject.h"
#include "Texture.h"

#define Texture_Type_Wall  1
#define Texture_Type_Ground  2
#define Texture_Type_Box  3

class Cube : public BaseObject{
	void Init();
	uint16_t m_TextureIndex;
public : 
	Material material;
	Texture texture;
	bool collided = false;
	bool isInterpolated = false;
	int cubeId;
	glm::vec3 Size;
	float angle;
	float rotateX,rotateY,rotateZ;
	Cube();
	~Cube();
	uint16_t inline GetTexutreIndex() { return m_TextureIndex; }
	std::string inline GetName() { return _name; }
	glm::mat4 inline GetModel() { return m_Model; }
	void Update();
	void Draw();
	void SetTextureData(uint16_t textureIndex);
	void Rotate(float angle);
	void RotateOnY(float angle);
	void Resize(glm::vec3& size);
};
