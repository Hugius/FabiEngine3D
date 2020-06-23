#pragma once

#include <GLEW\\glew.h>
#include <map>
#include <GLM\\glm.hpp>
#include <GLM\\gtc/type_ptr.hpp>

using glm::vec2;
using glm::vec3;
using glm::vec4;
using glm::mat3;
using glm::mat4;
using std::map;

#include "Logger.hpp"

class OpenGLShader final
{
public:
	OpenGLShader(const string & vertexFileName, const string & fragmentFileName);
	~OpenGLShader();

	void bind();
	void unbind();
	
	template<class T> void uploadUniform(const string & name, const T & data) 
	{
		GLint loc = _getUniLoc(name);
		_uploadUniform(loc, data);
	}

private:
	GLuint _program;
	void _createProgram(const GLchar * vShaderCode, const GLchar * fShaderCode);
	map<string, GLint> _uniformMap;
	string _vertexFileName;
	string _fragmentFileName;
	string _name;

	// Get uniform location
	GLint _getUniLoc(const string & uniformName) 
	{
		auto it = _uniformMap.find(uniformName);
		if (it == _uniformMap.end()) { // Add location to the map
			GLint loc = glGetUniformLocation(_program, uniformName.c_str());
			if (loc == -1) {
				Logger::getInst().throwWarning("Uniform " + uniformName + " not found in shader " + _name);
			}
			_uniformMap.insert(std::make_pair(uniformName, loc));
			return loc;
		}
		else {
			return it->second; // Return existing location
		}
	}

	// Overloading the upload functions
	inline void _uploadUniform(const GLint & loc, const GLint & data)     { glUniform1i(loc, data); }
	inline void _uploadUniform(const GLint & loc, const float & data)     { glUniform1f(loc, data); }
	inline void _uploadUniform(const GLint & loc, const GLdouble & data)  { glUniform1d(loc, data); }
	inline void _uploadUniform(const GLint & loc, const GLboolean & data) { glUniform1i(loc, data); }
	inline void _uploadUniform(const GLint & loc, const vec2 & data)      { glUniform2f(loc, data.x, data.y); }
	inline void _uploadUniform(const GLint & loc, const vec3 & data)      { glUniform3f(loc, data.x, data.y, data.z); }
	inline void _uploadUniform(const GLint & loc, const vec4 & data)      { glUniform4f(loc, data.x, data.y, data.z, data.w); }
	inline void _uploadUniform(const GLint & loc, const mat3 & data)      { glUniformMatrix3fv(loc, 1, GL_FALSE, glm::value_ptr(data)); }
	inline void _uploadUniform(const GLint & loc, const mat4 & data)      { glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(data)); }
};