#include "mesh_part.hpp"

MeshPart::MeshPart(const string& ID)
	:
	_ID(ID)
{

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