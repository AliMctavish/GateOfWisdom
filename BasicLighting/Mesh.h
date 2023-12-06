#pragma once
#ifndef MESH_H
#define MESH_H

#include "stb_image.h"
#include "Shader.h"
#include <vector>


struct Vertex_Struct {
	glm::vec3 Position;
	glm::vec2 Normal;
	glm::vec2 TexCoords;
};

struct Texture_Struct {
	unsigned int id;
	std::string type;
	std::string path;
};


class Mesh {
public:
	// mesh data
	std::vector<Vertex_Struct>       Vertices;
	std::vector<unsigned int>		 Indices;
	std::vector<Texture_Struct>      Textures;

	Mesh(std::vector<Vertex_Struct> vertices, std::vector<unsigned int> indices, std::vector<Texture_Struct> textures);
	void Draw(Shader& shader);
private:
	//  render data
	unsigned int VAO, VBO, EBO;

	void setupMesh();
};
#endif