#pragma once

#include "camera.hpp"
#include "quad3d.hpp"
#include "render_storage.hpp"

#include <unordered_map>

using std::unordered_map;

class Quad3dManager final
{
public:
	void construct();
	void inject(shared_ptr<RenderStorage> renderStorage);
	void inject(shared_ptr<Camera> camera);
	void update();
	void createQuad3d(const string & quad3dId, bool isCentered);
	void deleteQuad3d(const string & quad3dId);
	void deleteQuad3ds();

	const unordered_map<string, shared_ptr<Quad3d>> & getQuad3ds() const;

	const shared_ptr<Quad3d> getQuad3d(const string & quad3dId) const;

	const bool isQuad3dExisting(const string & quad3dId) const;
	const bool isQuad3dsExisting() const;

private:
	unordered_map<string, shared_ptr<Quad3d>> _quad3ds = {};

	shared_ptr<VertexBuffer> _centeredVertexBuffer = nullptr;
	shared_ptr<VertexBuffer> _standingVertexBuffer = nullptr;
	shared_ptr<RenderStorage> _renderStorage = nullptr;
	shared_ptr<Camera> _camera = nullptr;
};