#include "stdafx.h"

#include <Shader.h>

using namespace RenderEngineNS;

Shader::Shader(const GLchar* vertexPath, const GLchar* fragmentPath)
{
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	vShaderFile.exceptions(std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::badbit);

	try
	{
		//OpenFile
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);

		std::stringstream vShaderStream, fShaderStream;
		//ReadFile into buffer
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		//Close File Handelers
		vShaderFile.close();
		fShaderFile.close();

		//Convert Stream to string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << __FILE__ << __LINE__ << std::endl;
		//Log::Logger("ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ", __FILE__, __LINE__, LogLevel::FILE);
	}

	const GLchar* vShaderCode = vertexCode.c_str();
	const GLchar* fShaderCode = fragmentCode.c_str();

	//Compile Shaders
	GLuint vertex, fragement;
	GLint success;
	GLchar infoLog[512];

	//Vertex Shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, nullptr);
	glCompileShader(vertex);
	//Print Errors
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::COMPILATION" << std::endl;
		//Log::Logger("ERROR::SHADER::COMPILATION", LogLevel::FILE);
		//Log::Logger(infoLog, LogLevel::FILE);
	}

	//Fragement Shader
	fragement = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragement, 1, &fShaderCode, nullptr);
	glCompileShader(fragement);
	//Print Errors
	glGetShaderiv(fragement, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragement, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::FRAGEMENT::COMPILATION_FAILED" << std::endl;
		//Log::Logger("ERROR::SHADER::FRAGEMENT::COMPILATION_FAILED", LogLevel::FILE);
	}

	//ShaderProgram
	m_program = glCreateProgram();
	glAttachShader(m_program, vertex);
	glAttachShader(m_program, fragement);
	glLinkProgram(m_program);
	//Print Linking Errors
	glGetProgramiv(m_program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(m_program, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED" << std::endl;
		//Log::Logger("ERROR::SHADER::PROGRAM::LINKING_FAILED", LogLevel::FILE);
	}

	//Delete Shaders
	glDeleteShader(vertex);
	glDeleteShader(fragement);
}


GLuint Shader::GetProgram() const
{
	return m_program;
}
