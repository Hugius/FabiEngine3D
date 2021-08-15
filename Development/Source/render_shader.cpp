#include "render_shader.hpp"
#include "logger.hpp"
#include "tools.hpp"

#include <fstream>
#include <sstream>
#include <filesystem>

using std::ifstream;
using std::ofstream;
using std::filesystem::exists;

RenderShader::RenderShader(const string& vertexFilename, const string& fragmentFilename)
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
	const auto vertexPath = ("engine_assets\\shaders\\" + _vertexFilename);
	const auto fragmentPath = ("engine_assets\\shaders\\" + _fragmentFilename);

	// Check if vertex shader file exists
	if (!exists(rootDir + vertexPath))
	{
		Logger::throwFatalError("RenderShader::RenderShader::1");
	}

	// Check if fragment shader file exists
	if (!exists(rootDir + fragmentPath))
	{
		Logger::throwFatalError("RenderShader::RenderShader::2");
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

void RenderShader::_createProgram(const char* vShaderCode, const char* fShaderCode)
{
	// Compile the shaders
	unsigned int vertex, fragment;
	int success;
	char infoLog[512]; // For errors

	// Vertex shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, nullptr);
	glCompileShader(vertex);

	// Errors vertex shader
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success) 
	{
		glGetShaderInfoLog(vertex, 512, nullptr, infoLog);
		Logger::throwFatalError("RenderShader::_createProgram::1");
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
		Logger::throwFatalError("RenderShader::_createProgram::2");
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
		Logger::throwFatalError("RenderShader::_createProgram::3");
	}

	// Delete the no longer needed shaders
	glDeleteShader(vertex);
	glDeleteShader(fragment);

	// Logging
	Logger::throwInfo("Loaded vertex shader: \"shaders\\" + _vertexFilename + "\"");
	Logger::throwInfo("Loaded fragment shader: \"shaders\\" + _fragmentFilename + "\"");
}

UniformID RenderShader::_getUniformID(const string& uniformID)
{
	auto it = _uniformCache.find(uniformID);
	if (it == _uniformCache.end())
	{
		// Retrieve uniform location
		auto uniform = glGetUniformLocation(_program, uniformID.c_str());
		if (uniform == -1)
		{
			Logger::throwFatalError("RenderShader::_getUniformID");
		}

		// Cache uniform
		_uniformCache.insert(make_pair(uniformID, uniform));

		// Return new uniform
		return uniform;
	}
	else {
		return it->second; // Return existing uniform
	}
}

void RenderShader::bind()
{
	glUseProgram(_program);
}

void RenderShader::unbind()
{
	glUseProgram(0);
}

void RenderShader::_uploadUniform(const UniformID& uniformID, const bool& data)
{
	glUniform1i(uniformID, data);
}

void RenderShader::_uploadUniform(const UniformID& uniformID, const int& data)
{
	glUniform1i(uniformID, data);
}

void RenderShader::_uploadUniform(const UniformID& uniformID, const float& data)
{
	glUniform1f(uniformID, data);
}

void RenderShader::_uploadUniform(const UniformID& uniformID, const double& data)
{
	glUniform1d(uniformID, data);
}

void RenderShader::_uploadUniform(const UniformID& uniformID, const Vec2& data)
{
	glUniform2f(uniformID, data.x, data.y);
}

void RenderShader::_uploadUniform(const UniformID& uniformID, const Vec3& data)
{
	glUniform3f(uniformID, data.x, data.y, data.z);
}

void RenderShader::_uploadUniform(const UniformID& uniformID, const Vec4& data)
{
	glUniform4f(uniformID, data.x, data.y, data.z, data.w);
}

void RenderShader::_uploadUniform(const UniformID& uniformID, const Matrix33& data)
{
	glUniformMatrix3fv(uniformID, 1, GL_FALSE, data.f);
}

void RenderShader::_uploadUniform(const UniformID& uniformID, const Matrix44& data)
{
	glUniformMatrix4fv(uniformID, 1, GL_FALSE, data.f);
}