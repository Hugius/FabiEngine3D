#include "mesh_part.hpp"

void MeshPart::setID(const string& value)
{
	_ID = value;
}

void MeshPart::setDiffuseMapPath(const string& value)
{
	_diffuseMapPath = value;
}

void MeshPart::setEmissionMapPath(const string& value)
{
	_emissionMapPath = value;
}

void MeshPart::setReflectionMapPath(const string& value)
{
	_reflectionMapPath = value;
}

void MeshPart::setNormalMapPath(const string& value)
{
	_normalMapPath = value;
}

void MeshPart::addVertex(Vec3 value)
{
	_vertices.push_back(value);
}

void MeshPart::addNormal(Vec3 value)
{
	_normals.push_back(value);
}

void MeshPart::addTangent(Vec3 value)
{
	_tangents.push_back(value);
}

void MeshPart::addUV(Vec2 value)
{
	_uvs.push_back(value);
}

const string& MeshPart::getID() const
{
	return _ID;
}

const string& MeshPart::getDiffuseMapPath() const
{
	return _diffuseMapPath;
}

const string& MeshPart::getEmissionMapPath() const
{
	return _emissionMapPath;
}

const string& MeshPart::getReflectionMapPath() const
{
	return _reflectionMapPath;
}

const string& MeshPart::getNormalMapPath() const
{
	return _normalMapPath;
}

const vector<Vec3>& MeshPart::getVertices() const
{
	return _vertices;
}

const vector<Vec3>& MeshPart::getNormals() const
{
	return _normals;
}

const vector<Vec3>& MeshPart::getTangents() const
{
	return _tangents;
}

const vector<Vec2>& MeshPart::getUVs() const
{
	return _uvs;
}