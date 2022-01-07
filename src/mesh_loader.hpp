#pragma once

#include "mesh.hpp"

#include <map>

using std::map;
using std::pair;

class MeshLoader final
{
public:
	void cacheMesh(const string& filePath);
	void cacheMeshes(const vector<string>& meshPaths);
	void clearMeshCache(const string& filePath);
	void clearMeshesCache();

	const shared_ptr<Mesh> loadMesh(const string& filePath);

private:
	shared_ptr<Mesh> _loadMesh(const string& filePath);

	map<string, shared_ptr<Mesh>> _cache;
};