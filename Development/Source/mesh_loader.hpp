#pragma once

#include "mathematics.hpp"
#include "mesh_part.hpp"

#include <map>

class MeshLoader final
{
public:
	MeshLoader() = default;
	~MeshLoader() = default;

	const vector<MeshPart>& loadMesh(const string& filePath, bool calculateTangents);

	void cacheMeshesMultiThreaded(const vector<string>& meshPaths, vector<string>& resultingTexturePaths);

	void clearMeshCache(const string& filePath);

private:
	vector<MeshPart> _loadMesh(const string& filePath, bool calculateTangents);
	void _calculateTangents(vector<MeshPart>& meshParts);

	std::map<string, vector<MeshPart>> _meshCache;
};