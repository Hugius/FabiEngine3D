#include <fstream>
#include <sstream>

#include "OpenGLShader.hpp"
#include "Logger.hpp"

OpenGLShader::OpenGLShader(const string & vertexFileName, const string & fragmentFileName)
{
	// Variables
	_name = vertexFileName.substr(0, vertexFileName.size() - 5);
	string vertexCode;
	string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	vShaderFile.exceptions(std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::badbit);
	_vertexFileName   = vertexFileName;
	_fragmentFileName = fragmentFileName;

	// Get application root directory
	char buffer[256]; size_t len = sizeof(buffer);
	GetModuleFileName(NULL, buffer, len);
	string fullDir = buffer;
	fullDir = fullDir.substr(0, fullDir.size() - 25);

	// Open the shader text files
	try 
	{
		vShaderFile.open(fullDir + "Engine\\Shaders\\" + _vertexFileName);
		fShaderFile.open(fullDir + "Engine\\Shaders\\" + _fragmentFileName);
		std::stringstream vShaderStream, fShaderStream;
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		vShaderFile.close();
		fShaderFile.close();
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e) 
	{
		Logger::getInst().throwError("Shader text files could not be opened!");
	}

	const GLchar* vShaderCode = vertexCode.c_str();
	const GLchar * fShaderCode = fragmentCode.c_str();

	_createProgram(vShaderCode, fShaderCode);
}

OpenGLShader::~OpenGLShader()
{

}

void OpenGLShader::_createProgram(const GLchar * vShaderCode, const GLchar * fShaderCode)
{
	// Compile the shaders
	GLuint vertex, fragment;
	GLint success;
	GLchar infoLog[512]; // For errors

	// Vertex shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);

	// Errors vertex shader
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success) 
	{
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		Logger::getInst().throwError("Shader error at " + _vertexFileName + ": " + infoLog);
	}

	// Fragment shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);

	// Errors fragment shader
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success) 
	{
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		Logger::getInst().throwError("Shader error at " + _fragmentFileName + ": " + infoLog);
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
		glGetProgramInfoLog(_program, 512, NULL, infoLog);
		Logger::getInst().throwError("Shader error at " + _fragmentFileName.substr(0, _fragmentFileName.size()-5) + ": " + infoLog);
	}

	// Delete the no longer needed shaders
	glDeleteShader(vertex);
	glDeleteShader(fragment);

	// Logging
	Logger::getInst().throwInfo("Loaded vertex shader: Engine\\Shaders\\" + _vertexFileName);
	Logger::getInst().throwInfo("Loaded fragment shader: Engine\\Shaders\\" + _fragmentFileName);
}

void OpenGLShader::bind()
{
	glUseProgram(_program);
}

void OpenGLShader::unbind()
{
	glUseProgram(0);
}