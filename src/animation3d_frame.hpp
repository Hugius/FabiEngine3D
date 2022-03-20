#pragma once

#include "mathematics.hpp"
#include "speed_type.hpp"
#include "transformation_type.hpp"

#include <unordered_map>
#include <string>

using std::unordered_map;
using std::string;

class Animation3dFrame final
{
	friend class Animation3d;

	unordered_map<string, fvec3> targetTransformations;
	unordered_map<string, fvec3> rotationOrigins;
	unordered_map<string, fvec3> speeds;
	unordered_map<string, SpeedType> speedTypes;
	unordered_map<string, TransformationType> transformationTypes;
};