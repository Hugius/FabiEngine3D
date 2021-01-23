#pragma once

#include "mathematics.hpp"
#include "obj_part.hpp"

#include <map>

class OBJLoader final
{
public:
	OBJLoader() = default;
	~OBJLoader() = default;

	const vector<ObjPart>& loadOBJ(const string& filePath, bool calculateTangents);

	void cacheOBJsMultiThreaded(const vector<string>& filePaths, vector<string>& resultingTexturePaths);

	void clearOBJCache(const string& filePath);

private:
	vector<ObjPart> _loadOBJ(const string& filePath, bool calculateTangents);
	void _calculateTangents(vector<ObjPart>& objParts);

	std::map<string, vector<ObjPart>> _objCache;
};