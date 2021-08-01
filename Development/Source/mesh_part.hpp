#pragma once

#include "mathematics.hpp"

#include <vector>
#include <string>

using std::vector;
using std::string;

struct MeshPart final
{
	string ID;
	string diffuseMapPath;
	string emissionMapPath;
	string reflectionMapPath;
	string normalMapPath;

	vector<Vec3> vertices;
	vector<Vec2> uvCoords;
	vector<Vec3> normals;
	vector<Vec3> tangents;
};