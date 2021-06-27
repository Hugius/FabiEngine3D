#include "render_shader.hpp"
#include "logger.hpp"
#include "tools.hpp"

#include <fstream>
#include <sstream>
#include <filesystem>

RenderShader::RenderShader(const string& vertexFileName, const string& fragmentFileName)
{
	// Temporary values
	_name = vertexFileName.substr(0, vertexFileName.size() - 5);
	_vertexFileName = vertexFileName;
	_fragmentFileName = fragmentFileName;
	string vertexCode;
	string fragmentCode;
	std::ifstream vertexFile;
	std::ifstream fragmentFile;

	// Compose file paths
	const string rootDir = Tools::getRootDirectory();
	const auto vertexPath = "engine_assets\\shaders\\" + _vertexFileName;
	const auto fragmentPath = "engine_assets\\shaders\\" + _fragmentFileName;

	// Check if vertex shader file exists
	if (!std::filesystem::exists(rootDir + vertexPath))
	{
		Logger::throwError("Cannot load shader file: \"" + vertexPath + "\"!");
	}

	// Check if fragment shader file exists
	if (!std::filesystem::exists(rootDir + fragmentPath))
	{
		Logger::throwError("Cannot load shader file: \"" + fragmentPath + "\"!");
	}

	// Open the shader text files
	vertexFile.open(rootDir + vertexPath);
	fragmentFile.open(rootDir + fragmentPath);

	// Extract shader code
	std::ostringstream vShaderStream, fShaderStream;
	vShaderStream << vertexFile.rdbuf();
	fShaderStream << fragmentFile.rdbuf();
	vertexFile.close();
	fragmentFile.close();
	vertexCode = vShaderStream.str();
	fragmentCode = fShaderStream.str();
	const GLchar* vShaderCode = vertexCode.c_str();
	const GLchar* fShaderCode = fragmentCode.c_str();

	// Create shader program
	_createProgram(vShaderCode, fShaderCode);
}

void RenderShader::_createProgram(const GLchar * vShaderCode, const GLchar * fShaderCode)
{
	// Compile the shaders
	GLuint vertex, fragment;
	GLint success;
	GLchar infoLog[512]; // For errors

	// Vertex shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, nullptr);
	glCompileShader(vertex);

	// Errors vertex shader
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success) 
	{
		glGetShaderInfoLog(vertex, 512, nullptr, infoLog);
		Logger::throwError("Shader error at " + _vertexFileName + ": " + infoLog);
	}

	// Fragment shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, nullptr);
	glCompileShader(fragment);

	// Errors fragment shader
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success) 
	{
		glGetShaderInfoLog(fragment, 512, nullptr, infoLog);
		Logger::throwError("Shader error at " + _fragmentFileName + ": " + infoLog);
	}

	// Shader program
	_program = glCreateProgram();
	glAttachShader(_program, vertex);
	glAttachShader(_program, fragment);
	glLinkProgram(_program);

	// Linking errors 
	glGetProgramiv(_program, GL_LINK_STATUS, &success);
	if (!success) 
	{
		glGetProgramInfoLog(_program, 512, nullptr, infoLog);
		Logger::throwError("Shader error at " + _fragmentFileName.substr(0, _fragmentFileName.size()-5) + ": " + infoLog);
	}

	// Delete the no longer needed shaders
	glDeleteShader(vertex);
	glDeleteShader(fragment);

	// Logging
	Logger::throwInfo("Loaded vertex shader: \"shaders\\" + _vertexFileName + "\"");
	Logger::throwInfo("Loaded fragment shader: \"shaders\\" + _fragmentFileName + "\"");
}

void RenderShader::bind()
{
	glUseProgram(_program);
}

void RenderShader::unbind()
{
	glUseProgram(0);
}