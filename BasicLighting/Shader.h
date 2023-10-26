#pragma once
#include <iostream>
#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <string>
#include <sstream>

enum struct ShaderType {
	vertex_shader = 0, fragment_shader = 1
};

class Shader {
private :
	unsigned int vertex_id;
	unsigned int fragment_id;
public :
	Shader();
	~Shader();
	void SetShaders(std::string vertexFileName, std::string fragmentFileName);
	std::string ReadShaderFromFile(std::string fileName);
	unsigned int shader_program;
	unsigned int CompileShader(std::string& sourceFile , ShaderType type);

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
	void setFloat(const std::string& name, float value) const
	{
		glUniform1f(glGetUniformLocation(shader_program, name.c_str()), value);
	}
	void set4Float(const std::string& name, float v1,float v2, float v3 , float v4) const
	{
		glUniform4f(glGetUniformLocation(shader_program, name.c_str()),v1,v2,v3,v4);
	}
};
