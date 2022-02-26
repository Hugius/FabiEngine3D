#pragma once

#include "logger.hpp"
#include "mathematics.hpp" 

#include <unordered_map>
#include <glew.h>

using std::unordered_map;

class ShaderBuffer final
{
public:
	ShaderBuffer(const string& vertexFileName, const string& fragmentFileName);
	~ShaderBuffer();

	void bind();
	void unbind();
	template<typename T> void uploadUniform(const string& name, const T& data)
	{
		auto uniformId = getUniformId(name);
		_uploadUniform(uniformId, data);
	}

	const unsigned int getProgramId() const;
	const unsigned int getUniformId(const string& name);

private:
	void _uploadUniform(const unsigned int& uniformId, const bool& data);
	void _uploadUniform(const unsigned int& uniformId, const int& data);
	void _uploadUniform(const unsigned int& uniformId, const float& data);
	void _uploadUniform(const unsigned int& uniformId, const double& data);
	void _uploadUniform(const unsigned int& uniformId, const fvec2& data);
	void _uploadUniform(const unsigned int& uniformId, const fvec3& data);
	void _uploadUniform(const unsigned int& uniformId, const fvec4& data);
	void _uploadUniform(const unsigned int& uniformId, const mat22& data);
	void _uploadUniform(const unsigned int& uniformId, const mat33& data);
	void _uploadUniform(const unsigned int& uniformId, const mat44& data);

	unordered_map<string, unsigned int> _uniformCache;

	unsigned int _programId = 0;
};