#pragma once

#include "animation3d.hpp"

#include <memory>
#include <unordered_map>

using std::shared_ptr;
using std::unordered_map;

class Animation3dManager final
{
public:
	void createAnimation(const string & animation3dId);
	void deleteAnimation(const string & animation3dId);
	void deleteAnimations();

	const unordered_map<string, shared_ptr<Animation3d>> & getAnimations() const;

	const shared_ptr<Animation3d> getAnimation(const string & animation3dId) const;

	const bool isAnimationExisting(const string & animation3dId) const;
	const bool isAnimationsExisting() const;

private:
	unordered_map<string, shared_ptr<Animation3d>> _animations = {};
};