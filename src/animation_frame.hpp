#pragma once

#include "mathematics.hpp"
#include "animation_speed_type.hpp"
#include "transformation_type.hpp"

#include <map>
#include <string>

using std::map;
using std::string;

class AnimationFrame final
{
public:
	// VOID
	void clearParts();
	void addPart(const string& partID, fvec3 targetTransformation, fvec3 rotationOrigin, fvec3 speed, AnimationSpeedType animationSpeedType, TransformationType transformationType);
	void setTargetTransformation(const string& partID, fvec3 value);
	void setRotationOrigin(const string& partID, fvec3 value);
	void setSpeed(const string& partID, fvec3 value);
	void setSpeedType(const string& partID, AnimationSpeedType value);
	void setTransformationType(const string& partID, TransformationType value);

	// FVEC3
	const map<string, fvec3>& getTargetTransformations() const;
	const map<string, fvec3>& getRotationOrigins() const;
	const map<string, fvec3>& getSpeeds() const;

	// Miscellaneous
	const map<string, AnimationSpeedType>& getSpeedTypes() const;
	const map<string, TransformationType>& getTransformationTypes() const;

private:
	// FVEC3
	map<string, fvec3> _targetTransformations;
	map<string, fvec3> _rotationOrigins;
	map<string, fvec3> _speeds;

	// Miscellaneous
	map<string, AnimationSpeedType> _speedTypes;
	map<string, TransformationType> _transformationTypes;
};