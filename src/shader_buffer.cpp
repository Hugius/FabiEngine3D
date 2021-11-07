#include "shader_buffer.hpp"
#include "logger.hpp"
#include "tools.hpp"

#include <fstream>
#include <sstream>
#include <filesystem>

using std::ifstream;
using std::ofstream;
using std::filesystem::exists;

ShaderBuffer::ShaderBuffer(const string& vertexFilename, const string& fragmentFilename)
{
	// Temporary values
	_name = vertexFilename.substr(0, vertexFilename.size() - 5);
	_vertexFilename = vertexFilename;
	_fragmentFilename = fragmentFilename;
	string vertexCode;
	string fragmentCode;
	ifstream vertexFile;
	ifstream fragmentFile;

	// Compose file paths
	const auto rootDir = Tools::getRootDirectory();
	const auto vertexPath = ("shaders\\" + _vertexFilename);
	const auto fragmentPath = ("shaders\\" + _fragmentFilename);

	// Check if vertex shader file exists
	if(!exists(rootDir + vertexPath))
	{
		Logger::throwFatalWarning("Directory `shaders\\` is missing or corrupted!");
	}

	// Check if fragment shader file exists
	if(!exists(rootDir + fragmentPath))
	{
		Logger::throwFatalWarning("Directory `shaders\\` is missing or corrupted!");
	}

	// Open the shader text files
	vertexFile.open(rootDir + vertexPath);
	fragmentFile.open(rootDir + fragmentPath);

	// Extract shader code
	ostringstream vShaderStream, fShaderStream;
	vShaderStream << vertexFile.rdbuf();
	fShaderStream << fragmentFile.rdbuf();
	vertexFile.close();
	fragmentFile.close();
	vertexCode = vShaderStream.str();
	fragmentCode = fShaderStream.str();
	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();

	// Create shader program
	_createProgram(vShaderCode, fShaderCode);
}

void ShaderBuffer::_createProgram(const char* vertexShaderCode, const char* fragmentShaderCode)
{
	// Compile the shaders
	unsigned int vertex, fragment;
	int success;
	char infoLog[512]; // For errors

	// Vertex shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vertexShaderCode, nullptr);
	glCompileShader(vertex);

	// Errors vertex shader
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		glGetShaderInfoLog(vertex, 512, nullptr, infoLog);
		Logger::throwError("ShaderBuffer::_createProgram::1 ---> ", _name, " ", infoLog);
	}

	// Fragment shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fragmentShaderCode, nullptr);
	glCompileShader(fragment);

	// Errors fragment shader
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		glGetShaderInfoLog(fragment, 512, nullptr, infoLog);
		Logger::throwError("ShaderBuffer::_createProgram::2 ---> ", _name, " ", infoLog);
	}

	// Shader program
	_program = glCreateProgram();
	glAttachShader(_program, vertex);
	glAttachShader(_program, fragment);
	glLinkProgram(_program);

	// Linking errors 
	glGetProgramiv(_program, GL_LINK_STATUS, &success);
	if(!success)
	{
		glGetProgramInfoLog(_program, 512, nullptr, infoLog);
		Logger::throwError("ShaderBuffer::_createProgram::3 ---> ", _name, " ", infoLog);
	}

	// Delete the no longer needed shaders
	glDeleteShader(vertex);
	glDeleteShader(fragment);

	// Logging
	Logger::throwInfo("Loaded vertex shader: \"shaders\\" + _vertexFilename + "\"");
	Logger::throwInfo("Loaded fragment shader: \"shaders\\" + _fragmentFilename + "\"");
}

const UniformID ShaderBuffer::_getUniformID(const string& uniformID)
{
	auto it = _uniformCache.find(uniformID);
	if(it == _uniformCache.end())
	{
		// Retrieve uniform location
		auto uniform = glGetUniformLocation(_program, uniformID.c_str());
		if(uniform == -1)
		{
			Logger::throwError("ShaderBuffer::_getUniformID ---> ", uniformID);
		}

		// Cache uniform
		_uniformCache.insert(make_pair(uniformID, uniform));

		// Return new uniform
		return uniform;
	}
	else
	{
		return it->second; // Return existing uniform
	}
}

void ShaderBuffer::bind()
{
	glUseProgram(_program);
}

void ShaderBuffer::unbind()
{
	glUseProgram(0);
}

void ShaderBuffer::_uploadUniform(const UniformID& uniformID, const bool& data)
{
	glUniform1i(uniformID, data);
}

void ShaderBuffer::_uploadUniform(const UniformID& uniformID, const int& data)
{
	glUniform1i(uniformID, data);
}

void ShaderBuffer::_uploadUniform(const UniformID& uniformID, const float& data)
{
	glUniform1f(uniformID, data);
}

void ShaderBuffer::_uploadUniform(const UniformID& uniformID, const double& data)
{
	glUniform1d(uniformID, data);
}

void ShaderBuffer::_uploadUniform(const UniformID& uniformID, const Vec2& data)
{
	glUniform2f(uniformID, data.x, data.y);
}

void ShaderBuffer::_uploadUniform(const UniformID& uniformID, const Vec3& data)
{
	glUniform3f(uniformID, data.x, data.y, data.z);
}

void ShaderBuffer::_uploadUniform(const UniformID& uniformID, const Vec4& data)
{
	glUniform4f(uniformID, data.x, data.y, data.z, data.w);
}

void ShaderBuffer::_uploadUniform(const UniformID& uniformID, const Matrix33& data)
{
	glUniformMatrix3fv(uniformID, 1, GL_FALSE, data.f);
}

void ShaderBuffer::_uploadUniform(const UniformID& uniformID, const Matrix44& data)
{
	glUniformMatrix4fv(uniformID, 1, GL_FALSE, data.f);
}