#pragma once
#ifndef MESH_H
#define MESH_H

#include "Shader.h"
#include <vector>


struct Vertex_Struct {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
	glm::vec3 Tangent;
	glm::vec3 Bitangent;
	int m_BoneIDs[4];
	float m_Weights[4];

	glm::vec3 PositionUp = glm::vec3(0,0,1);
};

struct Texture_Struct {
	unsigned int id;
	std::string type;
	std::string path;
};


class Mesh {
public:
	// mesh data
	std::vector<Vertex_Struct>       vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture_Struct>      textures;

	Mesh(std::vector<Vertex_Struct> vertices, std::vector<unsigned int> indices, std::vector<Texture_Struct> textures);
	void Draw(Shader& shader);
private:
	//  render data
	unsigned int VAO, VBO, EBO;

	void setupMesh();
};
#endif