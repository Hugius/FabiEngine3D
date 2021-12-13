#pragma once

#include "mathematics.hpp"
#include "animation3d_speed_type.hpp"
#include "transformation_type.hpp"

#include <map>
#include <string>

using std::map;
using std::string;

class Animation3dFrame final
{
public:
	// VOID
	void clearParts();
	void addPart(const string& partID, fvec3 targetTransformation, fvec3 rotationOrigin, fvec3 speed, Animation3dSpeedType animationSpeedType, TransformationType transformationType);
	void setTargetTransformation(const string& partID, fvec3 value);
	void setRotationOrigin(const string& partID, fvec3 value);
	void setSpeed(const string& partID, fvec3 value);
	void setSpeedType(const string& partID, Animation3dSpeedType value);
	void setTransformationType(const string& partID, TransformationType value);

	// FVEC3
	const map<string, fvec3>& getTargetTransformations() const;
	const map<string, fvec3>& getRotationOrigins() const;
	const map<string, fvec3>& getSpeeds() const;

	// MISCELLANEOUS
	const map<string, Animation3dSpeedType>& getSpeedTypes() const;
	const map<string, TransformationType>& getTransformationTypes() const;

private:
	// FVEC3
	map<string, fvec3> _targetTransformations;
	map<string, fvec3> _rotationOrigins;
	map<string, fvec3> _speeds;

	// MISCELLANEOUS
	map<string, Animation3dSpeedType> _speedTypes;
	map<string, TransformationType> _transformationTypes;
};