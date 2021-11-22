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

	// VOID
	void bind();
	void unbind();
	template<typename T> void uploadUniform(const string& ID, const T& data)
	{
		auto uniform = _getUniformID(ID);
		_uploadUniform(uniform, data);
	}

private:
	// VOID
	void _createProgram(const char* vertexShaderCode, const char* fragmentShaderCode);
	void _uploadUniform(const UniformID& uniformID, const bool& data);
	void _uploadUniform(const UniformID& uniformID, const int& data);
	void _uploadUniform(const UniformID& uniformID, const float& data);
	void _uploadUniform(const UniformID& uniformID, const double& data);
	void _uploadUniform(const UniformID& uniformID, const fvec2& data);
	void _uploadUniform(const UniformID& uniformID, const fvec3& data);
	void _uploadUniform(const UniformID& uniformID, const fvec4& data);
	void _uploadUniform(const UniformID& uniformID, const mat33& data);
	void _uploadUniform(const UniformID& uniformID, const mat44& data);

	// Miscellaneous
	const UniformID _getUniformID(const string& uniformID);
	 
	// STRING
	string _vertexFileName = "";
	string _fragmentFileName = "";
	string _name = "";

	// Miscellaneous
	map<string, UniformID> _uniformCache;
	ShaderID _program = 0;
};