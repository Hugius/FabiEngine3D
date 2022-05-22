#pragma once

#define GLEW_STATIC

#include "mathematics.hpp" 

#include <unordered_map>
#include <glew.h>
#include <string>

using std::unordered_map;
using std::string;

class ShaderBuffer final
{
public:
	ShaderBuffer(const string & vertexFileName, const string & fragmentFileName);
	~ShaderBuffer();

	template<typename T> void uploadUniform(const string & name, const T & data)
	{
		_uploadUniform(getUniformId(name), data);
	}

	void bind();
	void unbind();

	const unsigned int getProgramId() const;
	const unsigned int getUniformId(const string & name);

private:
	void _uploadUniform(const int & uniformId, const bool & data);
	void _uploadUniform(const int & uniformId, const int & data);
	void _uploadUniform(const int & uniformId, const float & data);
	void _uploadUniform(const int & uniformId, const fvec2 & data);
	void _uploadUniform(const int & uniformId, const fvec3 & data);
	void _uploadUniform(const int & uniformId, const fvec4 & data);
	void _uploadUniform(const int & uniformId, const mat22 & data);
	void _uploadUniform(const int & uniformId, const mat33 & data);
	void _uploadUniform(const int & uniformId, const mat44 & data);

	unordered_map<string, unsigned int> _uniformCache = {};

	unsigned int _programId = 0;
};