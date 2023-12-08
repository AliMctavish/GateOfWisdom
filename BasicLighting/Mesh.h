#pragma once
#ifndef MESH_H
#define MESH_H

#include "Shader.h"
#include <vector>

#define MAX_BONE_INFLUENCE 4

struct Vertex_Struct {
	glm::vec3 Position;
	// normal
	glm::vec3 Normal;
	// texCoords
	glm::vec2 TexCoords;
	// tangent
	glm::vec3 Tangent;
	// bitangent
	glm::vec3 Bitangent;
	//bone indexes which will influence this vertex
	int m_BoneIDs[MAX_BONE_INFLUENCE];
	//weights from each bone
	float m_Weights[MAX_BONE_INFLUENCE];

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