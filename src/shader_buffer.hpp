#pragma once

#include "logger.hpp"
#include "mathematics.hpp" 

#include <unordered_map>
#include <glew.h>

using std::unordered_map;
using BufferId = GLuint;

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

	const BufferId getProgramId() const;
	const BufferId getUniformId(const string& name);

private:
	void _uploadUniform(const BufferId& uniformId, const bool& data);
	void _uploadUniform(const BufferId& uniformId, const int& data);
	void _uploadUniform(const BufferId& uniformId, const float& data);
	void _uploadUniform(const BufferId& uniformId, const double& data);
	void _uploadUniform(const BufferId& uniformId, const fvec2& data);
	void _uploadUniform(const BufferId& uniformId, const fvec3& data);
	void _uploadUniform(const BufferId& uniformId, const fvec4& data);
	void _uploadUniform(const BufferId& uniformId, const mat22& data);
	void _uploadUniform(const BufferId& uniformId, const mat33& data);
	void _uploadUniform(const BufferId& uniformId, const mat44& data);

	unordered_map<string, BufferId> _uniformCache;

	BufferId _programId = 0;
};