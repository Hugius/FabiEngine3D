#include "mesh_part.hpp"

MeshPart::MeshPart(const string& ID)
	:
	_ID(ID)
{

}

void MeshPart::addVertex(fvec3 value)
{
	_vertices.push_back(value);
}

void MeshPart::addNormal(fvec3 value)
{
	_normals.push_back(value);
}

void MeshPart::addTangent(fvec3 value)
{
	_tangents.push_back(value);
}

void MeshPart::addUV(fvec2 value)
{
	_uvs.push_back(value);
}

const string& MeshPart::getID() const
{
	return _ID;
}

const vector<fvec3>& MeshPart::getVertices() const
{
	return _vertices;
}

const vector<fvec3>& MeshPart::getNormals() const
{
	return _normals;
}

const vector<fvec3>& MeshPart::getTangents() const
{
	return _tangents;
}

const vector<fvec2>& MeshPart::getUVs() const
{
	return _uvs;
}