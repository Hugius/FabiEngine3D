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
	AabbManager();

	void inject(shared_ptr<ModelManager> modelManager);
	void inject(shared_ptr<Quad3dManager> quad3dManager);
	void inject(shared_ptr<Text3dManager> text3dManager);
	void createAabb(const string & aabbId, bool isCentered);
	void update();
	void deleteAabb(const string & aabbId);
	void deleteAabbs();

	const unordered_map<string, shared_ptr<Aabb>> & getAabbs() const;

	const shared_ptr<Aabb> getAabb(const string & aabbId) const;

	const bool isAabbExisting(const string & aabbId) const;
	const bool isAabbsExisting() const;

private:
	static inline constexpr float MIN_SIZE = 0.1f;

	const shared_ptr<VertexBuffer> _centeredVertexBuffer;
	const shared_ptr<VertexBuffer> _standingVertexBuffer;

	unordered_map<string, shared_ptr<Aabb>> _aabbEntities = {};

	shared_ptr<ModelManager> _modelManager = nullptr;
	shared_ptr<Quad3dManager> _quad3dManager = nullptr;
	shared_ptr<Text3dManager> _text3dManager = nullptr;
};