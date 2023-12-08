#pragma once
#ifndef MODEL_H
#define MODEL_H

#include "stb_image.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include"Mesh.h"

class Model {
public:
    bool gammaCorrection;
    // model data
    glm::vec3 position;
    glm::vec3 size;
    std::vector<Mesh> meshes;
    std::string directory;
    std::vector<Texture_Struct> textures_loaded;


    Model();
    Model(std::string const& path, bool gamma = false) : gammaCorrection(gamma)
    {
        loadModel(path);
    }
    void Draw(Shader& shader);
private:
    void loadModel(std::string const &path);
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    unsigned int  TextureFromFile(const char* path, const std::string& directory, bool gamma);
    std::vector<Texture_Struct> loadMaterialTextures(aiMaterial* mat, aiTextureType type,
        std::string typeName);
};

#endif