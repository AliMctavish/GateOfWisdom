#pragma once
#include <iostream>
#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <string>
#include <sstream>
#include "glm/glm.hpp"

enum struct ShaderType {
	vertex_shader = 0, fragment_shader = 1
};

class Shader {
private :
	uint32_t vertex_id;
	uint32_t fragment_id;
public :
	Shader();
	~Shader();
	void SetShaders(std::string vertexFileName, std::string fragmentFileName);
	std::string ReadShaderFromFile(std::string fileName);
	uint32_t shader_program;
	uint32_t CompileShader(std::string& sourceFile , ShaderType type);

	void Bind();
	void UnBind();

	void setBool(const std::string& name, bool value) const
	{
		glUniform1i(glGetUniformLocation(shader_program, name.c_str()), (int)value);
	}
	void setInt(const std::string& name, int value) const
	{
		glUniform1i(glGetUniformLocation(shader_program, name.c_str()), value);
	}
	void setVec3(const std::string& name, const glm::vec3& value) const
	{
		glUniform3fv(glGetUniformLocation(shader_program, name.c_str()), 1, &value[0]);
	}
	void setVec3f(const std::string& name, float v1, float v2, float v3)
	{
		glUniform3f(glGetUniformLocation(shader_program, name.c_str()), v1, v2, v3);
	}
	void setFloat(const std::string& name, float value) const
	{
		glUniform1f(glGetUniformLocation(shader_program, name.c_str()), value);
	}
	void set4Float(const std::string& name, float v1,float v2, float v3 , float v4) const
	{
		glUniform4f(glGetUniformLocation(shader_program, name.c_str()),v1,v2,v3,v4);
	}
	void Set3Float(const std::string& name, float& v1, float& v2, float& v3)
	{
		glUniform3f(glGetUniformLocation(shader_program, name.c_str()), v1, v2, v3);
	}
	void SetMat4(const std::string& name,const glm::mat4 &value) const
	{
		glUniformMatrix4fv(glGetUniformLocation(shader_program, name.c_str()), 1, GL_FALSE,&value[0][0]);
	}
};
