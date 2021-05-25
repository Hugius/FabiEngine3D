#pragma once

#include "logger.hpp"
#include "mathematics.hpp"

#include <GLEW\\glew.h>
#include <map>

using std::map;

class RenderShader final
{
public:
	RenderShader(const string& vertexFileName, const string& fragmentFileName);

	void bind();
	void unbind();
	
	template<class T> void uploadUniform(const string& name, const T & data) 
	{
		GLint loc = _getUniLoc(name);
		_uploadUniform(loc, data);
	}

private:
	void _createProgram(const GLchar * vShaderCode, const GLchar * fShaderCode);

	GLuint _program;

	map<string, GLint> _uniformMap;

	string _vertexFileName;
	string _fragmentFileName;
	string _name;

	// Get uniform location
	GLint _getUniLoc(const string& uniformName) 
	{
		auto it = _uniformMap.find(uniformName);
		if (it == _uniformMap.end()) // Add location to the map
		{
			GLint loc = glGetUniformLocation(_program, uniformName.c_str());
			if (loc == -1) 
			{
				Logger::throwError("Uniform " + uniformName + " not found in shader " + _name);
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
	inline void _uploadUniform(const GLint & loc, const Vec2 & data)      { glUniform2f(loc, data.x, data.y); }
	inline void _uploadUniform(const GLint & loc, const Vec3 & data)      { glUniform3f(loc, data.x, data.y, data.z); }
	inline void _uploadUniform(const GLint & loc, const Vec4 & data)      { glUniform4f(loc, data.x, data.y, data.z, data.w); }
	inline void _uploadUniform(const GLint & loc, const Matrix33 & data)  { glUniformMatrix3fv(loc, 1, GL_FALSE, data.f); }
	inline void _uploadUniform(const GLint & loc, const Matrix44 & data)  { glUniformMatrix4fv(loc, 1, GL_FALSE, data.f); }
};