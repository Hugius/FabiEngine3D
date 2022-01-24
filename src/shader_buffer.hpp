#pragma once

#include "logger.hpp"
#include "mathematics.hpp" 

#include <map>
#include <glew.h>

using std::map;
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
		auto uniformID = getUniformID(name);
		_uploadUniform(uniformID, data);
	}

	const BufferId getProgramID() const;
	const BufferId getUniformID(const string& name);

private:
	void _uploadUniform(const BufferId& uniformID, const bool& data);
	void _uploadUniform(const BufferId& uniformID, const int& data);
	void _uploadUniform(const BufferId& uniformID, const float& data);
	void _uploadUniform(const BufferId& uniformID, const double& data);
	void _uploadUniform(const BufferId& uniformID, const fvec2& data);
	void _uploadUniform(const BufferId& uniformID, const fvec3& data);
	void _uploadUniform(const BufferId& uniformID, const fvec4& data);
	void _uploadUniform(const BufferId& uniformID, const mat22& data);
	void _uploadUniform(const BufferId& uniformID, const mat33& data);
	void _uploadUniform(const BufferId& uniformID, const mat44& data);

	map<string, BufferId> _uniformCache;

	BufferId _programID = 0;
};