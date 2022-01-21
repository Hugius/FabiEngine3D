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

	void addPosition(const fvec3& value);
	void addUv(fvec2 value);
	void addNormal(const fvec3& value);
	void addTangent(const fvec3& value);

	const string& getID() const;

	const vector<fvec3>& getPositions() const;
	const vector<fvec2>& getUvs() const;
	const vector<fvec3>& getNormals() const;
	const vector<fvec3>& getTangents() const;

private:
	const string _ID;

	vector<fvec3> _positions;
	vector<fvec2> _uvs;
	vector<fvec3> _normals;
	vector<fvec3> _tangents;
};