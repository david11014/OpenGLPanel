#include "Stdafx.h"
#include "Shader.h"
#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader(const std::string vertexPath, const std::string fragmentPath)
{
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	
	vShaderFile.exceptions(std::ifstream::badbit|std::ifstream::failbit);
	fShaderFile.exceptions(std::ifstream::badbit|std::ifstream::failbit);

	try
	{
		HMODULE hModule = GetModuleHandleW(NULL);
		WCHAR path[MAX_PATH];
		GetModuleFileNameW(hModule, path, MAX_PATH);
		std::wstring ws(path);
		std::string str(ws.begin(), ws.end());
		std::cout << str << std::endl;
		
		//open file
		//vShaderFile.open(vertexPath.c_str());
		vShaderFile.open("C:\\Users\\david\\OneDrive\\Documents\\GitHub\\OpenGLPanel\\Debug\\vertexShader.glsl");
		
		//fShaderFile.open(fragmentPath.c_str());
		fShaderFile.open("C:\\Users\\david\\OneDrive\\Documents\\GitHub\\OpenGLPanel\\Debug\\fragmentShader.glsl");
		std::stringstream vShaderStream, fShaderStream;
		//read file
		vShaderStream << vShaderFile.rdbuf();		
		fShaderStream << fShaderFile.rdbuf();
		
		

		//close file
		vShaderFile.close();
		fShaderFile.close();
		//convert to string;
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();


	}
	catch (std::ifstream::failure e)
	{
		std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ: " << strerror(errno)  << "\n"<< e.what() << std::endl;
		success = false;
		return;
	}

	GLint gl_success;
	GLchar infoLog[512];
	// Vertex shader
	GLuint vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	const char * vertexShaderSource_str = vertexCode.c_str();
	glShaderSource(vertexShader, 1, &vertexShaderSource_str, NULL);
	glCompileShader(vertexShader);
	// Check for compile time errors	
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &gl_success);
	if (!gl_success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::string log = infoLog;
		set_error("ERROR::SHADER::VERTEX::COMPILATION_FAILED " + log);
		success = false;
		return;
	}

	// fragment shader
	GLuint fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	const char * fragmentShaderSource_str = fragmentCode.c_str();
	glShaderSource(fragmentShader, 1, &fragmentShaderSource_str, NULL);
	glCompileShader(fragmentShader);
	// Check for compile time errors
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &gl_success);
	if (!gl_success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::string log = infoLog;
		set_error("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED " + log);
		success = false;
		return;
	}

	Program = glCreateProgram();
	glAttachShader(Program, vertexShader);
	glAttachShader(Program, fragmentShader);
	glLinkProgram(Program);
	// Check for linking errors
	glGetProgramiv(Program, GL_LINK_STATUS, &gl_success);
	if (!gl_success) {
		glGetProgramInfoLog(Program, 512, NULL, infoLog);
		std::string log = infoLog;
		set_error("ERROR::SHADER::PROGRAM::LINKING_FAILED " + log);
		success = false;
		return;
	}

	//delete shader
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

}

void Shader::Use()
{
	glUseProgram(this->Program);
}

bool Shader::import_shader()
{
	GLint gl_success;
	GLchar infoLog[512];
	// Vertex shader
	GLuint vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	const char * vertexShaderSource_str = vertexCode.c_str();
	glShaderSource(vertexShader, 1, &vertexShaderSource_str, NULL);
	glCompileShader(vertexShader);
	// Check for compile time errors	
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &gl_success);
	if (!gl_success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::string log = infoLog;
		set_error("ERROR::SHADER::VERTEX::COMPILATION_FAILED " + log);
		return false;
	}

	// fragment shader
	GLuint fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	const char * fragmentShaderSource_str = fragmentCode.c_str();
	glShaderSource(fragmentShader, 1, &fragmentShaderSource_str, NULL);
	glCompileShader(fragmentShader);
	// Check for compile time errors
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &gl_success);
	if (!gl_success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::string log = infoLog;
		set_error("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED " + log);
		return false;
	}

	Program = glCreateProgram();
	glAttachShader(Program, vertexShader);
	glAttachShader(Program, fragmentShader);
	glLinkProgram(Program);
	// Check for linking errors
	glGetProgramiv(Program, GL_LINK_STATUS, &gl_success);
	if (!gl_success) {
		glGetProgramInfoLog(Program, 512, NULL, infoLog);
		std::string log = infoLog;
		set_error("ERROR::SHADER::PROGRAM::LINKING_FAILED " + log);
		return false;
	}

	//delete shader
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return true;
}