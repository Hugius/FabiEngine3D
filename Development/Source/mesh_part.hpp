#pragma once

#include "mathematics.hpp"

#include <vector>
#include <string>

using std::vector;
using std::string;

class MeshPart final
{
public:
	// Voids
	void setID(const string& value);
	void setDiffuseMapPath(const string& value);
	void setEmissionMapPath(const string& value);
	void setReflectionMapPath(const string& value);
	void setNormalMapPath(const string& value);
	void addVertex(Vec3 value);
	void addNormal(Vec3 value);
	void addTangent(Vec3 value);
	void addUV(Vec2 value);

	// Strings
	const string& getID() const;
	const string& getDiffuseMapPath() const;
	const string& getEmissionMapPath() const;
	const string& getReflectionMapPath() const;
	const string& getNormalMapPath() const;

	// Vectors
	const vector<Vec3>& getVertices() const;
	const vector<Vec3>& getNormals() const;
	const vector<Vec3>& getTangents() const;
	const vector<Vec2>& getUVs() const;

private:
	// Strings
	string _ID;
	string _diffuseMapPath;
	string _emissionMapPath;
	string _reflectionMapPath;
	string _normalMapPath;

	// Vectors
	vector<Vec3> _vertices;
	vector<Vec3> _normals;
	vector<Vec3> _tangents;
	vector<Vec2> _uvs;
};