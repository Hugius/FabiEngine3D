#pragma once

#include "aabb.hpp"

class AabbCollisionHandler final
{
public:
	const bool hasAabbsCollided(shared_ptr<Aabb> firstAabb, shared_ptr<Aabb> secondAabb) const;
};