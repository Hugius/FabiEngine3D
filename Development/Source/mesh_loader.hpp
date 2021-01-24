#pragma once

#include "mathematics.hpp"
#include "mesh_part.hpp"

#include <map>

class MeshLoader final
{
public:
	MeshLoader() = default;
	~MeshLoader() = default;

	const vector<MeshPart>& loadOBJ(const string& filePath, bool calculateTangents);

	void cacheOBJsMultiThreaded(const vector<string>& filePaths, vector<string>& resultingTexturePaths);

	void clearOBJCache(const string& filePath);

private:
	vector<MeshPart> _loadOBJ(const string& filePath, bool calculateTangents);
	void _calculateTangents(vector<MeshPart>& objParts);

	std::map<string, vector<MeshPart>> _objCache;
};