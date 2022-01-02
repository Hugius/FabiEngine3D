#include "shader_buffer.hpp"
#include "logger.hpp"
#include "tools.hpp"

#include <fstream>
#include <sstream>

using std::ifstream;
using std::ofstream;

ShaderBuffer::ShaderBuffer(const string& vertexFileName, const string& fragmentFileName)
{
	_name = vertexFileName.substr(0, vertexFileName.size() - 5);
	_vertexFileName = vertexFileName;
	_fragmentFileName = fragmentFileName;

	const auto rootPath = Tools::getRootDirectoryPath();
	const auto vertexPath = ("engine\\shaders\\" + _vertexFileName);
	const auto fragmentPath = ("engine\\shaders\\" + _fragmentFileName);

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
		Logger::throwError("ShaderBuffer::_createProgram::1 ---> ", _name, " ", log);
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
		Logger::throwError("ShaderBuffer::_createProgram::2 ---> ", _name, " ", log);
	}

	_program = glCreateProgram();
	glAttachShader(_program, vertexID);
	glAttachShader(_program, fragmentID);
	glLinkProgram(_program);

	int programStatus;
	glGetProgramiv(_program, GL_LINK_STATUS, &programStatus);
	if(!programStatus)
	{
		char log[512];
		glGetProgramInfoLog(_program, 512, nullptr, log);
		Logger::throwError("ShaderBuffer::_createProgram::3 ---> ", _name, " ", log);
	}

	glDeleteShader(vertexID);
	glDeleteShader(fragmentID);

	Logger::throwInfo("Loaded vertex shader: \"engine\\shaders\\" + _vertexFileName + "\"");
	Logger::throwInfo("Loaded fragment shader: \"engine\\shaders\\" + _fragmentFileName + "\"");
}

ShaderBuffer::~ShaderBuffer()
{
	glDeleteProgram(_program);
}

const BufferID ShaderBuffer::_getUniformID(const string& uniformID)
{
	auto iterator = _uniformCache.find(uniformID);
	if(iterator == _uniformCache.end())
	{
		auto uniform = glGetUniformLocation(_program, uniformID.c_str());
		if(uniform == -1)
		{
			Logger::throwError("ShaderBuffer::_getUniformID ---> ", uniformID);
		}

		_uniformCache.insert(make_pair(uniformID, uniform));

		return uniform;
	}
	else
	{
		return iterator->second;
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

void ShaderBuffer::_uploadUniform(const BufferID& uniformID, const bool& data)
{
	glUniform1i(uniformID, data);
}

void ShaderBuffer::_uploadUniform(const BufferID& uniformID, const int& data)
{
	glUniform1i(uniformID, data);
}

void ShaderBuffer::_uploadUniform(const BufferID& uniformID, const float& data)
{
	glUniform1f(uniformID, data);
}

void ShaderBuffer::_uploadUniform(const BufferID& uniformID, const double& data)
{
	glUniform1d(uniformID, data);
}

void ShaderBuffer::_uploadUniform(const BufferID& uniformID, const fvec2& data)
{
	glUniform2f(uniformID, data.x, data.y);
}

void ShaderBuffer::_uploadUniform(const BufferID& uniformID, const fvec3& data)
{
	glUniform3f(uniformID, data.x, data.y, data.z);
}

void ShaderBuffer::_uploadUniform(const BufferID& uniformID, const fvec4& data)
{
	glUniform4f(uniformID, data.x, data.y, data.z, data.w);
}

void ShaderBuffer::_uploadUniform(const BufferID& uniformID, const mat33& data)
{
	glUniformMatrix3fv(uniformID, 1, GL_FALSE, data.f);
}

void ShaderBuffer::_uploadUniform(const BufferID& uniformID, const mat44& data)
{
	glUniformMatrix4fv(uniformID, 1, GL_FALSE, data.f);
}