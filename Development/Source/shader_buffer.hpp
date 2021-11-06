#pragma once

#include "logger.hpp"
#include "mathematics.hpp" 
#include "render_utils.hpp"

#include <map>

using std::map;

class ShaderBuffer final
{
public:
	ShaderBuffer(const string& vertexFilename, const string& fragmentFilename);

	// Voids
	void bind();
	void unbind();
	template<typename T> void uploadUniform(const string& ID, const T& data)
	{
		auto uniform = _getUniformID(ID);
		_uploadUniform(uniform, data);
	}

private:
	// Voids
	void _createProgram(const char* vertexShaderCode, const char* fragmentShaderCode);
	void _uploadUniform(const UniformID& uniformID, const bool& data);
	void _uploadUniform(const UniformID& uniformID, const int& data);
	void _uploadUniform(const UniformID& uniformID, const float& data);
	void _uploadUniform(const UniformID& uniformID, const double& data);
	void _uploadUniform(const UniformID& uniformID, const Vec2& data);
	void _uploadUniform(const UniformID& uniformID, const Vec3& data);
	void _uploadUniform(const UniformID& uniformID, const Vec4& data);
	void _uploadUniform(const UniformID& uniformID, const Matrix33& data);
	void _uploadUniform(const UniformID& uniformID, const Matrix44& data);

	// Miscellaneous
	const UniformID _getUniformID(const string& uniformID);
	 
	// Strings
	string _vertexFilename = "";
	string _fragmentFilename = "";
	string _name = "";

	// Miscellaneous
	map<string, UniformID> _uniformCache;
	ShaderID _program = 0;
};