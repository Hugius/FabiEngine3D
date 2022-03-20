#pragma once

#include "mesh_part.hpp"

#include <memory>

using std::shared_ptr;

class Mesh final
{
public:
	void addPart(shared_ptr<MeshPart> value);

	const vector<shared_ptr<MeshPart>>& getParts() const;

private:
	vector<shared_ptr<MeshPart>> _parts = {};
};