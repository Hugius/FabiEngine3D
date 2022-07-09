#pragma once

#include "mathematics.hpp"

class AabbCollisionHandler final
{
public:
	const bool hasAabbsCollided(const fvec3 & firstAabbPosition, const fvec3 & firstAabbSize, const fvec3 & secondAabbPosition, const fvec3 & secondAabbSize) const;
};