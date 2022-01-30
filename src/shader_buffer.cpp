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

	auto vertexId = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexId, 1, &vertexCode, nullptr);
	glCompileShader(vertexId);

	int vertexStatus;
	glGetShaderiv(vertexId, GL_COMPILE_STATUS, &vertexStatus);
	if(!vertexStatus)
	{
		char log[512];
		glGetShaderInfoLog(vertexId, 512, nullptr, log);

		Logger::throwDebug(shaderName);
		Logger::throwDebug(log);
		abort();
	}

	auto fragmentId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentId, 1, &fragmentCode, nullptr);
	glCompileShader(fragmentId);

	int fragmentStatus;
	glGetShaderiv(fragmentId, GL_COMPILE_STATUS, &fragmentStatus);
	if(!fragmentStatus)
	{
		char log[512];
		glGetShaderInfoLog(fragmentId, 512, nullptr, log);

		Logger::throwDebug(shaderName);
		Logger::throwDebug(log);
		abort();
	}

	_programId = glCreateProgram();
	glAttachShader(_programId, vertexId);
	glAttachShader(_programId, fragmentId);
	glLinkProgram(_programId);

	int programStatus;
	glGetProgramiv(_programId, GL_LINK_STATUS, &programStatus);
	if(!programStatus)
	{
		char log[512];
		glGetProgramInfoLog(_programId, 512, nullptr, log);

		Logger::throwDebug(shaderName);
		Logger::throwDebug(log);
		abort();
	}

	glDeleteShader(vertexId);
	glDeleteShader(fragmentId);

	Logger::throwInfo("Loaded shader: \"engine\\shaders\\" + vertexFileName + "\"");
	Logger::throwInfo("Loaded shader: \"engine\\shaders\\" + fragmentFileName + "\"");
}

ShaderBuffer::~ShaderBuffer()
{
	glDeleteProgram(_programId);
}

const BufferId ShaderBuffer::getUniformId(const string& name)
{
	auto cacheIterator = _uniformCache.find(name);

	if(cacheIterator != _uniformCache.end())
	{
		return cacheIterator->second;
	}

	auto id = glGetUniformLocation(_programId, name.c_str());

	if(id == -1)
	{
		Logger::throwDebug(name);
		abort();
	}

	_uniformCache.insert(make_pair(name, id));

	return id;
}

void ShaderBuffer::bind()
{
	glUseProgram(_programId);
}

void ShaderBuffer::unbind()
{
	glUseProgram(0);
}

const BufferId ShaderBuffer::getProgramId() const
{
	return _programId;
}

void ShaderBuffer::_uploadUniform(const BufferId& uniformId, const bool& data)
{
	glUniform1i(uniformId, data);
}

void ShaderBuffer::_uploadUniform(const BufferId& uniformId, const int& data)
{
	glUniform1i(uniformId, data);
}

void ShaderBuffer::_uploadUniform(const BufferId& uniformId, const float& data)
{
	glUniform1f(uniformId, data);
}

void ShaderBuffer::_uploadUniform(const BufferId& uniformId, const double& data)
{
	glUniform1d(uniformId, data);
}

void ShaderBuffer::_uploadUniform(const BufferId& uniformId, const fvec2& data)
{
	glUniform2f(uniformId, data.x, data.y);
}

void ShaderBuffer::_uploadUniform(const BufferId& uniformId, const fvec3& data)
{
	glUniform3f(uniformId, data.x, data.y, data.z);
}

void ShaderBuffer::_uploadUniform(const BufferId& uniformId, const fvec4& data)
{
	glUniform4f(uniformId, data.x, data.y, data.z, data.w);
}

void ShaderBuffer::_uploadUniform(const BufferId& uniformId, const mat22& data)
{
	glUniformMatrix2fv(uniformId, 1, GL_FALSE, data.f);
}

void ShaderBuffer::_uploadUniform(const BufferId& uniformId, const mat33& data)
{
	glUniformMatrix3fv(uniformId, 1, GL_FALSE, data.f);
}

void ShaderBuffer::_uploadUniform(const BufferId& uniformId, const mat44& data)
{
	glUniformMatrix4fv(uniformId, 1, GL_FALSE, data.f);
}