#pragma once

#include "mathematics.hpp"

#include <vector>
#include <string>

using std::vector;
using std::string;

struct MeshPart
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