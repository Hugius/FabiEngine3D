#pragma once

#include "logger.hpp"
#include "mathematics.hpp" 
#include "render_utils.hpp"

#include <map>

using std::map;

class RenderShader final
{
public:
	RenderShader(const string& vertexFileName, const string& fragmentFileName);

	void bind();
	void unbind();
	
	template<typename T>
	void uploadUniform(const string& name, const T & data) 
	{
		auto uniform = _getUniformID(name);
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

	UniformID _getUniformID(const string& uniformName);

	ShaderID _program = 0;

	map<string, UniformID> _uniformCache;

	string _vertexFileName = "";
	string _fragmentFileName = "";
	string _name = "";
};