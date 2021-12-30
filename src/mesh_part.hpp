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

	void addPosition(fvec3 value);
	void addNormal(fvec3 value);
	void addTangent(fvec3 value);
	void addUV(fvec2 value);

	const string& getID() const;

	const vector<fvec3>& getPositions() const;
	const vector<fvec3>& getNormals() const;
	const vector<fvec3>& getTangents() const;

	const vector<fvec2>& getUVs() const;

private:
	const string _ID;

	vector<fvec3> _positions;
	vector<fvec3> _normals;
	vector<fvec3> _tangents;

	vector<fvec2> _uvs;
};