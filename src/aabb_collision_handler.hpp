#pragma once

#include "aabb_manager.hpp"

class AabbCollisionHandler final
{
public:
	AabbCollisionHandler();

	void inject(shared_ptr<AabbManager> aabbManager);
	void calculateCollisionWithAabbs(const string & aabbId);
	void clearCollisionWithAabbs();

	const vector<string> getAabbCollisions(const string & aabbId) const;

private:
	void _clearCollisionWithAabbs(const string & aabbId);

	const bool _haveAabbsCollided(shared_ptr<Aabb> firstAabb, shared_ptr<Aabb> secondAabb) const;

	unordered_map<string, vector<string>> _aabbCollisions = {};

	shared_ptr<AabbManager> _aabbManager = nullptr;
};