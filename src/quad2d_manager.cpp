#include "quad2d_manager.hpp"

using std::make_shared;

const shared_ptr<Quad2d> Quad2dManager::getQuad2d(const string & quad2dId) const
{
	const auto iterator = _quad2ds.find(quad2dId);

	if(iterator == _quad2ds.end())
	{
		abort();
	}

	return iterator->second;
}

const unordered_map<string, shared_ptr<Quad2d>> & Quad2dManager::getQuad2ds() const
{
	return _quad2ds;
}

void Quad2dManager::createQuad2d(const string & quad2dId, bool isCentered)
{
	if(isQuad2dExisting(quad2dId))
	{
		abort();
	}

	const auto quad2d = make_shared<Quad2d>(quad2dId);

	quad2d->setVertexBuffer(isCentered ? _centeredVertexBuffer : _corneredVertexBuffer);
	quad2d->setCentered(isCentered);
	quad2d->setDepth(_renderStorage->getGuiDepth());

	_quad2ds.insert({quad2dId, quad2d});

	_renderStorage->setGuiDepth(_renderStorage->getGuiDepth() + 1);
}

void Quad2dManager::deleteQuad2d(const string & quad2dId)
{
	if(!isQuad2dExisting(quad2dId))
	{
		abort();
	}

	_quad2ds.erase(quad2dId);
}

void Quad2dManager::deleteQuad2ds()
{
	_quad2ds.clear();
}

const bool Quad2dManager::isQuad2dExisting(const string & quad2dId) const
{
	return (_quad2ds.find(quad2dId) != _quad2ds.end());
}

const bool Quad2dManager::isQuad2dsExisting() const
{
	return !_quad2ds.empty();
}

void Quad2dManager::initialize()
{
	_centeredVertexBuffer = make_shared<VertexBuffer>(0.0f, 0.0f, 1.0f, 1.0f, true);
	_corneredVertexBuffer = make_shared<VertexBuffer>(0.0f, 0.0f, 1.0f, 1.0f, false);
}

void Quad2dManager::inject(shared_ptr<RenderStorage> renderStorage)
{
	_renderStorage = renderStorage;
}

void Quad2dManager::update()
{
	for(const auto & [quad2dId, quad2d] : _quad2ds)
	{
		quad2d->updateTarget();

		if(quad2d->isVisible())
		{
			quad2d->updateTransformation();
		}
	}
}