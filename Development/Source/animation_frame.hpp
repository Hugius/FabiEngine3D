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
	// Voids
	void clearParts();
	void addPart(const string& partID, Vec3 targetTransformation, Vec3 rotationOrigin, Vec3 speed, AnimationSpeedType animationSpeedType, TransformationType transformationType);
	void setTargetTransformation(const string& partID, Vec3 value);
	void setRotationOrigin(const string& partID, Vec3 value);
	void setSpeed(const string& partID, Vec3 value);
	void setSpeedType(const string& partID, AnimationSpeedType value);
	void setTransformationType(const string& partID, TransformationType value);

	// Vectors
	const map<string, Vec3>& getTargetTransformations() const;
	const map<string, Vec3>& getRotationOrigins() const;
	const map<string, Vec3>& getSpeeds() const;

	// Miscellaneous
	const map<string, AnimationSpeedType>& getSpeedTypes() const;
	const map<string, TransformationType>& getTransformationTypes() const;

private:
	// Vectors
	map<string, Vec3> _targetTransformations;
	map<string, Vec3> _rotationOrigins;
	map<string, Vec3> _speeds;

	// Miscellaneous
	map<string, AnimationSpeedType> _speedTypes;
	map<string, TransformationType> _transformationTypes;
};