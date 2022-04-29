#pragma once

#include "animation3d.hpp"

#include <memory>
#include <unordered_map>

using std::shared_ptr;
using std::unordered_map;

class Animation3dManager final
{
public:
	void createAnimation3d(const string & animation3dId);
	void deleteAnimation3d(const string & animation3dId);
	void deleteAnimation3ds();

	const unordered_map<string, shared_ptr<Animation3d>> & getAnimation3ds() const;

	const shared_ptr<Animation3d> getAnimation3d(const string & animation3dId) const;

	const bool isAnimation3dExisting(const string & animation3dId) const;
	const bool isAnimation3dsExisting() const;

private:
	unordered_map<string, shared_ptr<Animation3d>> _animation3ds = {};
};