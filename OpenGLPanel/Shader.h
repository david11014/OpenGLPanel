#ifndef SHADER_H
#define SHADER_H
#include <string>
#include <glad/glad.h>

class Shader
{
public:

	GLuint Program = 0; //shader program ID
	std::string vertexCode;
	std::string fragmentCode;
	bool success = true;
	Shader() = delete;
	Shader(const std::string vPath, const std::string fPath);
	~Shader() {};
	bool import_shader();
	void Use();
};

#endif