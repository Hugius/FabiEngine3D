#pragma once

#include <vector>
#include <map>
#include <string>
#include <GLM\\glm.hpp>

using std::vector;
using std::string;
using glm::vec2;
using glm::vec3;

struct ObjPart 
{
	string partName;
	string diffuseMapName;
	string lightMapName;
	string normalMapName;
	string reflectionMapName;
	
	vector<vec3> vertices;
	vector<vec2> uvCoords;
	vector<vec3> normals;
	vector<vec3> tangents;
};

class OBJLoader final
{
public:
	OBJLoader() = default;
	~OBJLoader() = default;

	vector<ObjPart>& loadOBJ(const string& filePath, bool calculateTangents);

	void clearOBJCache(const string& filePath);

private:
	vector<ObjPart> _loadOBJ(const string& filePath, bool calculateTangents);
	void _calculateTangents(vector<ObjPart>& objParts);

	std::map<string, vector<ObjPart>> _objPartsMap;
};