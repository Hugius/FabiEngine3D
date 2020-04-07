#pragma once

#include <GLEW/glew.h>
#include <map>
#include <GLM/glm.hpp>
#include <GLM/gtc/type_ptr.hpp>

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
	OpenGLShader(const string & vertexPath, const string & fragmentPath);
	~OpenGLShader();

	void bind();
	void unbind();
	
	template<class T> void uploadUniform(const string & name, const T & data) 
	{
		GLint loc = p_getUniLoc(name);
		p_uploadUniform(loc, data);
	}

private:
	GLuint p_program;
	void p_createProgram(const GLchar * vShaderCode, const GLchar * fShaderCode);
	map<string, GLint> p_uniformMap;
	string p_vertexPath;
	string p_fragmentPath;
	string p_name;

	// Get uniform location
	GLint p_getUniLoc(const string & uniformName) 
	{
		auto it = p_uniformMap.find(uniformName);
		if (it == p_uniformMap.end()) { // Add location to the map
			GLint loc = glGetUniformLocation(p_program, uniformName.c_str());
			if (loc == -1) {
				Logger::getInst().throwWarning("Uniform " + uniformName + " not found in shader " + p_name);
			}
			p_uniformMap.insert(std::make_pair(uniformName, loc));
			return loc;
		}
		else {
			return it->second; // Return existing location
		}
	}

	// Overloading the upload functions
	inline void p_uploadUniform(const GLint & loc, const GLint & data)     { glUniform1i(loc, data); }
	inline void p_uploadUniform(const GLint & loc, const float & data)     { glUniform1f(loc, data); }
	inline void p_uploadUniform(const GLint & loc, const GLdouble & data)  { glUniform1d(loc, data); }
	inline void p_uploadUniform(const GLint & loc, const GLboolean & data) { glUniform1i(loc, data); }
	inline void p_uploadUniform(const GLint & loc, const vec2 & data)      { glUniform2f(loc, data.x, data.y); }
	inline void p_uploadUniform(const GLint & loc, const vec3 & data)      { glUniform3f(loc, data.x, data.y, data.z); }
	inline void p_uploadUniform(const GLint & loc, const vec4 & data)      { glUniform4f(loc, data.x, data.y, data.z, data.w); }
	inline void p_uploadUniform(const GLint & loc, const mat3 & data)      { glUniformMatrix3fv(loc, 1, GL_FALSE, glm::value_ptr(data)); }
	inline void p_uploadUniform(const GLint & loc, const mat4 & data)      { glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(data)); }
};