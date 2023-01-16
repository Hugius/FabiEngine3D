#pragma once

#include "render_storage.hpp"
#include "quad2d.hpp"

#include <unordered_map>

using std::unordered_map;

class Quad2dManager final
{
public:
	void construct();
	void inject(shared_ptr<RenderStorage> renderStorage);
	void update();
	void createQuad2d(const string & quad2dId, bool isCentered);
	void deleteQuad2d(const string & quad2dId);
	void deleteQuad2ds();

	const unordered_map<string, shared_ptr<Quad2d>> & getQuad2ds() const;

	const shared_ptr<Quad2d> getQuad2d(const string & quad2dId) const;

	const bool isQuad2dExisting(const string & quad2dId) const;
	const bool isQuad2dsExisting() const;

private:
	unordered_map<string, shared_ptr<Quad2d>> _quad2ds = {};

	shared_ptr<VertexBuffer> _centeredVertexBuffer = nullptr;
	shared_ptr<VertexBuffer> _corneredVertexBuffer = nullptr;
	shared_ptr<RenderStorage> _renderStorage = nullptr;
};