#pragma once

#include "mathematics.hpp"
#include "speed_type.hpp"
#include "transformation_type.hpp"

#include <map>
#include <string>

using std::map;
using std::string;

class Animation3dFrame final
{
	friend class Animation3d;

	map<string, fvec3> targetTransformations;
	map<string, fvec3> rotationOrigins;
	map<string, fvec3> speeds;

	map<string, SpeedType> speedTypes;
	map<string, TransformationType> transformationTypes;
};