#include "mesh.hpp"

void Mesh::addPart(shared_ptr<MeshPart> value)
{
	_parts.push_back(value);
}

const vector<shared_ptr<MeshPart>> & Mesh::getParts() const
{
	return _parts;
}