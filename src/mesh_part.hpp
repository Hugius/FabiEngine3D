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

	// VOID
	void addVertex(fvec3 value);
	void addNormal(fvec3 value);
	void addTangent(fvec3 value);
	void addUV(fvec2 value);

	// STRING
	const string& getID() const;

	// FVEC3
	const vector<fvec3>& getVertices() const;
	const vector<fvec3>& getNormals() const;
	const vector<fvec3>& getTangents() const;

	// FVEC2
	const vector<fvec2>& getUVs() const;

private:
	// STRING
	const string _ID;

	// FVEC3
	vector<fvec3> _vertices;
	vector<fvec3> _normals;
	vector<fvec3> _tangents;

	// FVEC2
	vector<fvec2> _uvs;
};