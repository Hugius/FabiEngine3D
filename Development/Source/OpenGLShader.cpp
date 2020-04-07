#include <fstream>
#include <sstream>

#include <WE3D/OpenGLShader.hpp>
#include <WE3D/Logger.hpp>

OpenGLShader::OpenGLShader(const string & vertexPath, const string & fragmentPath)
{
	p_name = vertexPath.substr(0, vertexPath.size() - 5);
	string vertexCode;
	string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	vShaderFile.exceptions(std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::badbit);
	p_vertexPath   = vertexPath;
	p_fragmentPath = fragmentPath;

	// Open the shader text files
	try 
	{
		vShaderFile.open("../Engine/Shaders/" + p_vertexPath);
		fShaderFile.open("../Engine/Shaders/" + p_fragmentPath);
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

	p_createProgram(vShaderCode, fShaderCode);
}

OpenGLShader::~OpenGLShader()
{

}

void OpenGLShader::p_createProgram(const GLchar * vShaderCode, const GLchar * fShaderCode)
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
		Logger::getInst().throwError("Shader error at " + p_vertexPath + ": " + infoLog);
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
		Logger::getInst().throwError("Shader error at " + p_fragmentPath + ": " + infoLog);
	}

	// Shader program
	p_program = glCreateProgram();
	glAttachShader(p_program, vertex);
	glAttachShader(p_program, fragment);
	glLinkProgram(p_program);

	// Linking errors 
	glGetProgramiv(p_program, GL_LINK_STATUS, &success);
	if (!success) 
	{
		glGetProgramInfoLog(p_program, 512, NULL, infoLog);
		Logger::getInst().throwError("Shader error at " + p_fragmentPath.substr(0, p_fragmentPath.size()-5) + ": " + infoLog);
	}

	// Delete the no longer needed shaders
	glDeleteShader(vertex);
	glDeleteShader(fragment);

	Logger::getInst().throwInfo("Loaded vertex shader: ../Engine/Shaders/" + p_vertexPath);
	Logger::getInst().throwInfo("Loaded fragment shader: ../Engine/Shaders/" + p_fragmentPath);
}

void OpenGLShader::bind()
{
	glUseProgram(p_program);
}

void OpenGLShader::unbind()
{
	glUseProgram(0);
}