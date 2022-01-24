#include "shader_buffer.hpp"
#include "logger.hpp"
#include "tools.hpp"

#include <fstream>
#include <sstream>

using std::ifstream;
using std::ofstream;

ShaderBuffer::ShaderBuffer(const string& vertexFileName, const string& fragmentFileName)
{
	const auto rootPath = Tools::getRootDirectoryPath();
	const auto vertexPath = string("engine\\shaders\\" + vertexFileName);
	const auto fragmentPath = string("engine\\shaders\\" + fragmentFileName);
	const auto shaderName = vertexFileName.substr(0, vertexFileName.size() - 5);

	if(!Tools::isFileExisting(rootPath + vertexPath))
	{
		Logger::throwFatalWarning("Directory `engine\\` is missing or corrupted!");
	}

	if(!Tools::isFileExisting(rootPath + fragmentPath))
	{
		Logger::throwFatalWarning("Directory `engine\\` is missing or corrupted!");
	}

	auto vertexFile = ifstream(rootPath + vertexPath);
	auto fragmentFile = ifstream(rootPath + fragmentPath);
	ostringstream vertexStream;
	ostringstream fragmentStream;
	vertexStream << vertexFile.rdbuf();
	fragmentStream << fragmentFile.rdbuf();
	vertexFile.close();
	fragmentFile.close();

	auto vertexCodeString = vertexStream.str();
	auto fragmentCodeString = fragmentStream.str();
	auto vertexCode = vertexCodeString.c_str();
	auto fragmentCode = fragmentCodeString.c_str();

	auto vertexID = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexID, 1, &vertexCode, nullptr);
	glCompileShader(vertexID);

	int vertexStatus;
	glGetShaderiv(vertexID, GL_COMPILE_STATUS, &vertexStatus);
	if(!vertexStatus)
	{
		char log[512];
		glGetShaderInfoLog(vertexID, 512, nullptr, log);
		Logger::throwError("ShaderBuffer::_createProgram::1 ---> ", shaderName, " ", log);
	}

	auto fragmentID = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentID, 1, &fragmentCode, nullptr);
	glCompileShader(fragmentID);

	int fragmentStatus;
	glGetShaderiv(fragmentID, GL_COMPILE_STATUS, &fragmentStatus);
	if(!fragmentStatus)
	{
		char log[512];
		glGetShaderInfoLog(fragmentID, 512, nullptr, log);
		Logger::throwError("ShaderBuffer::_createProgram::2 ---> ", shaderName, " ", log);
	}

	_programID = glCreateProgram();
	glAttachShader(_programID, vertexID);
	glAttachShader(_programID, fragmentID);
	glLinkProgram(_programID);

	int programStatus;
	glGetProgramiv(_programID, GL_LINK_STATUS, &programStatus);
	if(!programStatus)
	{
		char log[512];
		glGetProgramInfoLog(_programID, 512, nullptr, log);
		Logger::throwError("ShaderBuffer::_createProgram::3 ---> ", shaderName, " ", log);
	}

	glDeleteShader(vertexID);
	glDeleteShader(fragmentID);

	Logger::throwInfo("Loaded shader: \"engine\\shaders\\" + vertexFileName + "\"");
	Logger::throwInfo("Loaded shader: \"engine\\shaders\\" + fragmentFileName + "\"");
}

ShaderBuffer::~ShaderBuffer()
{
	glDeleteProgram(_programID);
}

const BufferId ShaderBuffer::getUniformID(const string& name)
{
	auto cacheIterator = _uniformCache.find(name);

	if(cacheIterator != _uniformCache.end())
	{
		return cacheIterator->second;
	}

	auto id = glGetUniformLocation(_programID, name.c_str());

	if(id == -1)
	{
		Logger::throwError("ShaderBuffer::_getUniformID ---> ", name);
	}

	_uniformCache.insert(make_pair(name, id));

	return id;
}

void ShaderBuffer::bind()
{
	glUseProgram(_programID);
}

void ShaderBuffer::unbind()
{
	glUseProgram(0);
}

const BufferId ShaderBuffer::getProgramID() const
{
	return _programID;
}

void ShaderBuffer::_uploadUniform(const BufferId& uniformID, const bool& data)
{
	glUniform1i(uniformID, data);
}

void ShaderBuffer::_uploadUniform(const BufferId& uniformID, const int& data)
{
	glUniform1i(uniformID, data);
}

void ShaderBuffer::_uploadUniform(const BufferId& uniformID, const float& data)
{
	glUniform1f(uniformID, data);
}

void ShaderBuffer::_uploadUniform(const BufferId& uniformID, const double& data)
{
	glUniform1d(uniformID, data);
}

void ShaderBuffer::_uploadUniform(const BufferId& uniformID, const fvec2& data)
{
	glUniform2f(uniformID, data.x, data.y);
}

void ShaderBuffer::_uploadUniform(const BufferId& uniformID, const fvec3& data)
{
	glUniform3f(uniformID, data.x, data.y, data.z);
}

void ShaderBuffer::_uploadUniform(const BufferId& uniformID, const fvec4& data)
{
	glUniform4f(uniformID, data.x, data.y, data.z, data.w);
}

void ShaderBuffer::_uploadUniform(const BufferId& uniformID, const mat22& data)
{
	glUniformMatrix2fv(uniformID, 1, GL_FALSE, data.f);
}

void ShaderBuffer::_uploadUniform(const BufferId& uniformID, const mat33& data)
{
	glUniformMatrix3fv(uniformID, 1, GL_FALSE, data.f);
}

void ShaderBuffer::_uploadUniform(const BufferId& uniformID, const mat44& data)
{
	glUniformMatrix4fv(uniformID, 1, GL_FALSE, data.f);
}