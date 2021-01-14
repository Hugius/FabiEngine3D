#pragma once

#include "mathematics.hpp"

#include <vector>
#include <map>
#include <string>

using std::vector;
using std::string;

struct ObjPart 
{
	string name;
	string diffuseMapPath;
	string lightMapPath;
	string normalMapPath;
	string reflectionMapPath;
	
	vector<Vec3> vertices;
	vector<Vec2> uvCoords;
	vector<Vec3> normals;
	vector<Vec3> tangents;
};

class OBJLoader final
{
public:
	OBJLoader() = default;
	~OBJLoader() = default;

	const vector<ObjPart>& loadOBJ(const string& filePath, bool calculateTangents);

	void clearOBJCache(const string& filePath);

private:
	vector<ObjPart> _loadOBJ(const string& filePath, bool calculateTangents);
	void _calculateTangents(vector<ObjPart>& objParts);

	std::map<string, vector<ObjPart>> _objPartsMap;
};