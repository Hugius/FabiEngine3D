#pragma once

#include "mathematics.hpp"
#include "mesh_part.hpp"

#include <map>

using std::map;

class MeshLoader final
{
public:
	const vector<MeshPart>* loadMesh(const string& filePath);

	void cacheMeshesMultiThreaded(const vector<string>& meshPaths, vector<string>& resultingTexturePaths);

	void clearMeshCache(const string& filePath);

private:
	vector<MeshPart> _loadMesh(const string& filePath);

	map<string, vector<MeshPart>> _meshCache;
};