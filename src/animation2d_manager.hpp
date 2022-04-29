#pragma once

#include "animation2d.hpp"

#include <memory>
#include <unordered_map>

using std::shared_ptr;
using std::unordered_map;

class Animation2dManager final
{
public:
	void createAnimation2d(const string & animation2dId);
	void deleteAnimation2d(const string & animation2dId);
	void deleteAnimation2ds();

	const unordered_map<string, shared_ptr<Animation2d>> & getAnimation2ds() const;

	const shared_ptr<Animation2d> getAnimation2d(const string & animation2dId) const;

	const bool isAnimation2dExisting(const string & animation2dId) const;
	const bool isAnimation2dsExisting() const;

private:
	unordered_map<string, shared_ptr<Animation2d>> _animation2ds = {};
};