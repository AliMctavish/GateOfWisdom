#pragma once
#include "BaseObject.h"
#include "Texture.h"

class Cube : public BaseObject{
public : 
	Material material;
	Texture texture;
	bool collided = false;
	int cubeId;
	glm::vec3 Size;
	float angle;
	float rotateX,rotateY,rotateZ;
	Cube();
	~Cube();
	std::string GetName() { return _name; }
	glm::mat4 inline GetModel() { return m_Model; }
	void Update();
	void Draw();
	void SetShaderData();
	void Rotate(float angle);
	void RotateOnY(float angle);
	void Resize(glm::vec3& size);
	void Init();
};
