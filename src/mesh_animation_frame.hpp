#pragma once

#include "mathematics.hpp"
#include "mesh_animation_speed_type.hpp"
#include "transformation_type.hpp"

#include <map>
#include <string>

using std::map;
using std::string;

class MeshAnimationFrame final
{
public:
	// VOID
	void clearParts();
	void addPart(const string& partID, fvec3 targetTransformation, fvec3 rotationOrigin, fvec3 speed, MeshAnimationSpeedType animationSpeedType, TransformationType transformationType);
	void setTargetTransformation(const string& partID, fvec3 value);
	void setRotationOrigin(const string& partID, fvec3 value);
	void setSpeed(const string& partID, fvec3 value);
	void setSpeedType(const string& partID, MeshAnimationSpeedType value);
	void setTransformationType(const string& partID, TransformationType value);

	// FVEC3
	const map<string, fvec3>& getTargetTransformations() const;
	const map<string, fvec3>& getRotationOrigins() const;
	const map<string, fvec3>& getSpeeds() const;

	// MISCELLANEOUS
	const map<string, MeshAnimationSpeedType>& getSpeedTypes() const;
	const map<string, TransformationType>& getTransformationTypes() const;

private:
	// FVEC3
	map<string, fvec3> _targetTransformations;
	map<string, fvec3> _rotationOrigins;
	map<string, fvec3> _speeds;

	// MISCELLANEOUS
	map<string, MeshAnimationSpeedType> _speedTypes;
	map<string, TransformationType> _transformationTypes;
};