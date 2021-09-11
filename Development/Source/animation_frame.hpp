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
	void setTargetTransformations(const map<string, Vec3>& value);
	void setTargetTransformation(const string& partID, Vec3 value);
	void addTargetTransformation(const string& partID, Vec3 value);
	void setRotationOrigins(const map<string, Vec3>& value);
	void setRotationOrigin(const string& partID, Vec3 value);
	void addRotationOrigin(const string& partID, Vec3 value);
	void setSpeeds(const map<string, Vec3>& value);
	void setSpeed(const string& partID, Vec3 value);
	void addSpeed(const string& partID, Vec3 value);
	void setSpeedTypes(const map<string, AnimationSpeedType>& value);
	void setSpeedType(const string& partID, AnimationSpeedType value);
	void addSpeedType(const string& partID, AnimationSpeedType value);
	void setTransformationTypes(const map<string, TransformationType>& value);
	void setTransformationType(const string& partID, TransformationType value);
	void addTransformationType(const string& partID, TransformationType value);

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