#pragma once

#include "animation2d.hpp"

#include <memory>
#include <unordered_map>

using std::shared_ptr;
using std::unordered_map;

class Animation2dManager final
{
public:
	void createAnimation(const string & animation2dId);
	void deleteAnimation(const string & animation2dId);
	void deleteAnimations();

	const unordered_map<string, shared_ptr<Animation2d>> & getAnimations() const;

	const shared_ptr<Animation2d> getAnimation(const string & animation2dId) const;

	const bool isAnimationExisting(const string & animation2dId) const;
	const bool isAnimationsExisting() const;

private:
	unordered_map<string, shared_ptr<Animation2d>> _animations = {};
};