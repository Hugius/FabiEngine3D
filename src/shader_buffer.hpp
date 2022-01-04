#pragma once

#include "logger.hpp"
#include "mathematics.hpp" 
#include "render_utils.hpp"

#include <map>

using std::map;

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

	const BufferID getProgramID() const;
	const BufferID getUniformID(const string& name);

private:
	void _uploadUniform(const BufferID& uniformID, const bool& data);
	void _uploadUniform(const BufferID& uniformID, const int& data);
	void _uploadUniform(const BufferID& uniformID, const float& data);
	void _uploadUniform(const BufferID& uniformID, const double& data);
	void _uploadUniform(const BufferID& uniformID, const fvec2& data);
	void _uploadUniform(const BufferID& uniformID, const fvec3& data);
	void _uploadUniform(const BufferID& uniformID, const fvec4& data);
	void _uploadUniform(const BufferID& uniformID, const mat33& data);
	void _uploadUniform(const BufferID& uniformID, const mat44& data);

	map<string, BufferID> _uniformCache;

	BufferID _programID = 0;
};