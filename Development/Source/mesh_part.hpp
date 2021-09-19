#pragma once

#include "mathematics.hpp"

#include <vector>
#include <string>

using std::vector;
using std::string;

class MeshPart final
{
public:
	MeshPart(const string& ID);

	// Voids
	void addVertex(Vec3 value);
	void addNormal(Vec3 value);
	void addTangent(Vec3 value);
	void addUV(Vec2 value);

	// Strings
	const string& getID() const;

	// Vectors
	const vector<Vec3>& getVertices() const;
	const vector<Vec3>& getNormals() const;
	const vector<Vec3>& getTangents() const;
	const vector<Vec2>& getUVs() const;

private:
	// Strings
	const string _ID;

	// Vectors
	vector<Vec3> _vertices;
	vector<Vec3> _normals;
	vector<Vec3> _tangents;
	vector<Vec2> _uvs;
};