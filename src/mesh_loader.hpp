#pragma once

#include "mesh.hpp"

#include <unordered_map>

using std::unordered_map;
using std::pair;

class MeshLoader final
{
public:
	void cacheMesh(const string& filePath, bool isCrucial);
	void cacheMeshes(const vector<string>& filePaths, bool isCrucial);
	void clearMeshCache(const string& filePath);
	void clearMeshesCache();

	const shared_ptr<Mesh> loadMesh(const string& filePath);

private:
	shared_ptr<Mesh> _loadMesh(const string& filePath) const;

	unordered_map<string, shared_ptr<Mesh>> _cache = {};
};