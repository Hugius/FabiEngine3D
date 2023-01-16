#pragma once

#include "vertex_buffer.hpp"
#include "aabb.hpp"
#include "model_manager.hpp"
#include "quad3d_manager.hpp"
#include "text3d_manager.hpp"

#include <unordered_map>

using std::unordered_map;

class AabbManager final
{
public:
	void construct();
	void inject(shared_ptr<ModelManager> modelManager);
	void inject(shared_ptr<Quad3dManager> quad3dManager);
	void inject(shared_ptr<Text3dManager> text3dManager);
	void createAabb(const string & aabbId, bool isCentered);
	void update();
	void deleteAabb(const string & aabbId);
	void deleteAabbs();
	void registerParent(const string & parentId, AabbParentType parentType);
	void unregisterParent(const string & parentId, AabbParentType parentType);
	void bindAabbToParent(const string & aabbId, const string & parentId, AabbParentType parentType);
	void unbindAabbFromParent(const string & aabbId);

	const unordered_map<string, shared_ptr<Aabb>> & getAabbs() const;

	const vector<string> getChildAabbIds(const string & parentId, AabbParentType parentType) const;

	const shared_ptr<Aabb> getAabb(const string & aabbId) const;

	const bool isAabbExisting(const string & aabbId) const;
	const bool isAabbsExisting() const;

private:
	unordered_map<string, shared_ptr<Aabb>> _aabbs = {};
	unordered_map<string, vector<string>> _modelChildAabbIds = {};
	unordered_map<string, vector<string>> _quad3dChildAabbIds = {};
	unordered_map<string, vector<string>> _text3dChildAabbIds = {};

	shared_ptr<VertexBuffer> _centeredVertexBuffer = nullptr;
	shared_ptr<VertexBuffer> _standingVertexBuffer = nullptr;
	shared_ptr<ModelManager> _modelManager = nullptr;
	shared_ptr<Quad3dManager> _quad3dManager = nullptr;
	shared_ptr<Text3dManager> _text3dManager = nullptr;
};