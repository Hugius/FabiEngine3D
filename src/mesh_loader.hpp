#pragma once

#include "mathematics.hpp"
#include "mesh_part.hpp"

#include <memory>
#include <map>

using std::map;
using std::pair;
using std::shared_ptr;

class MeshLoader final
{
public:
	// VOID
	void cacheMesh(const string& filePath);
	void cacheMeshes(const vector<string>& meshPaths);
	void clearMeshCache(const string& filePath);
	void clearMeshesCache();

	// MISCELLANEOUS
	const vector<shared_ptr<MeshPart>>* loadMesh(const string& filePath);

private:
	// MISCELLANEOUS
	pair<string, vector<shared_ptr<MeshPart>>> _loadMesh(const string& filePath);

	// MISCELLANEOUS
	map<string, vector<shared_ptr<MeshPart>>> _meshCache;
};