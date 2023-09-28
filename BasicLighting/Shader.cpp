#include "Shader.h"



Shader::Shader(std::string vertexFileName, std::string fragmentFileName)
{
    std::string vertex_source   = ReadShaderFromFile(vertexFileName);
    std::string fragment_source = ReadShaderFromFile(fragmentFileName);
	
	this->vertex_id   = CompileShader(vertex_source , ShaderType::vertex_shader);
	this->fragment_id = CompileShader(fragment_source , ShaderType::fragment_shader);

	this->shader_program = glCreateProgram();
	glAttachShader(this->shader_program, this->vertex_id);
	glAttachShader(this->shader_program, this->fragment_id);
	glLinkProgram(this->shader_program);

	int success;
	char infoLog[512];
	glGetProgramiv(this->shader_program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(this->shader_program, 512, NULL, infoLog);
		std::cout << "something wrong with the shader program" << infoLog << std::endl;
	}

	this->Bind();
}
void Shader::Bind()
{
	glUseProgram(this->shader_program);
}

void Shader::UnBind()
{
	glDeleteShader(this->vertex_id);
	glDeleteShader(this->fragment_id);
	glUseProgram(0);
}

Shader::~Shader()
{
	UnBind();
}

std::string Shader::ReadShaderFromFile(std::string fileName)
{
	std::ifstream fileStream;
	std::stringstream result;
	std::string resultAsString;

	fileStream.open(fileName);

	result << fileStream.rdbuf();

	fileStream.close();
	return result.str();
}

unsigned int Shader::CompileShader(std::string& sourceFile , ShaderType type)
{
	unsigned int shader_id;
	const char* shader_source = sourceFile.c_str();

	if(type == ShaderType::vertex_shader)
		shader_id = glCreateShader(GL_VERTEX_SHADER);
	else
		shader_id = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(shader_id, 1, &shader_source, NULL);
	glCompileShader(shader_id);

	int success;
	char infoLog[512];
	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader_id, 512, NULL, infoLog);
		std::cout << "something wrong with your " << sourceFile <<" shader : " << infoLog << std::endl;
	}
	return shader_id;
}





