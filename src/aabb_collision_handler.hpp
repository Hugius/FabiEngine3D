#pragma once

#include "aabb_manager.hpp"

class AabbCollisionHandler final
{
public:
	void inject(shared_ptr<AabbManager> aabbManager);
	void calculateCollisionWithAabbs(const string & aabbId);
	void clearCollisionWithAabbs();

	const vector<string> getAabbCollisions(const string & aabbId) const;

private:
	unordered_map<string, vector<string>> _aabbCollisions = {};

	shared_ptr<AabbManager> _aabbManager = nullptr;
};