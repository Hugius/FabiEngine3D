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

	void bind();
	void unbind();
	
	template<typename T>
	void uploadUniform(const string& ID, const T & data) 
	{
		auto uniform = _getUniformID(ID);
		_uploadUniform(uniform, data);
	}

private:
	void _createProgram(const char* vShaderCode, const char* fShaderCode);
	void _uploadUniform(const UniformID& uniformID, const bool& data);
	void _uploadUniform(const UniformID& uniformID, const int& data);
	void _uploadUniform(const UniformID& uniformID, const float& data);
	void _uploadUniform(const UniformID& uniformID, const double& data);
	void _uploadUniform(const UniformID& uniformID, const Vec2& data);
	void _uploadUniform(const UniformID& uniformID, const Vec3& data);
	void _uploadUniform(const UniformID& uniformID, const Vec4& data);
	void _uploadUniform(const UniformID& uniformID, const Matrix33& data);
	void _uploadUniform(const UniformID& uniformID, const Matrix44& data);

	UniformID _getUniformID(const string& uniformID);

	ShaderID _program = 0;

	map<string, UniformID> _uniformCache;

	string _vertexFilename = "";
	string _fragmentFilename = "";
	string _name = "";
};