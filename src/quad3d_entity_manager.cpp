#include "quad3d_entity_manager.hpp"
#include "render_storage.hpp"

using std::make_shared;

constexpr float centeredBufferData[] =
{
	-0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
	-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
	0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
	0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
	0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
	-0.5f, 0.5f, 0.0f, 0.0f, 1.0f
};

constexpr float standingBufferData[] =
{
	-0.5f, 1.0f, 0.0f, 0.0f, 1.0f,
	-0.5f, 0.0f, 0.0f, 0.0f, 0.0f,
	0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
	0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
	0.5f, 1.0f, 0.0f, 1.0f, 1.0f,
	-0.5f, 1.0f, 0.0f, 0.0f, 1.0f
};

constexpr int centeredBufferDataCount = static_cast<int>(sizeof(centeredBufferData) / sizeof(float));
constexpr int standingBufferDataCount = static_cast<int>(sizeof(standingBufferData) / sizeof(float));

Quad3dManager::Quad3dManager()
	:
	_centeredVertexBuffer(make_shared<VertexBuffer>(VertexBufferType::POS_UV, centeredBufferData, centeredBufferDataCount)),
	_standingVertexBuffer(make_shared<VertexBuffer>(VertexBufferType::POS_UV, standingBufferData, standingBufferDataCount))
{

}

void Quad3dManager::inject(shared_ptr<RenderStorage> renderStorage)
{
	_renderStorage = renderStorage;
}

void Quad3dManager::inject(shared_ptr<Camera> camera)
{
	_camera = camera;
}

const shared_ptr<Quad3d> Quad3dManager::getQuad3d(const string & quad3dId) const
{
	auto iterator = _quad3ds.find(quad3dId);

	if(iterator == _quad3ds.end())
	{
		abort();
	}

	return iterator->second;
}

const unordered_map<string, shared_ptr<Quad3d>> & Quad3dManager::getQuad3ds() const
{
	return _quad3ds;
}

void Quad3dManager::createQuad3d(const string & quad3dId, bool isCentered)
{
	if(isQuad3dExisting(quad3dId))
	{
		abort();
	}

	auto entity = make_shared<Quad3d>(quad3dId);

	entity->setVertexBuffer(isCentered ? _centeredVertexBuffer : _standingVertexBuffer);
	entity->setCentered(isCentered);

	_quad3ds.insert({quad3dId, entity});
}

void Quad3dManager::update()
{
	for(const auto & [entityId, entity] : _quad3ds)
	{
		entity->updateTarget();

		if(entity->isFacingCameraHorizontally() || entity->isFacingCameraVertically())
		{
			auto position = (entity->getPosition() + fvec3(0.0f, (entity->getSize().y * 0.5f), 0.0f));
			auto direction = (position - _camera->getPosition());

			auto degreesX = Mathematics::convertToDegrees(atan2f(direction.y, fabsf(direction.x) + fabsf(direction.z)));
			auto degreesY = Mathematics::convertToDegrees(atan2f(direction.z, direction.x));

			auto rotation = entity->getRotation();
			rotation.x = (degreesX * static_cast<float>(entity->isFacingCameraHorizontally()));
			rotation.y = ((-degreesY - 90.0f) * static_cast<float>(entity->isFacingCameraVertically()));

			entity->setRotation(rotation);
		}

		if(entity->isVisible())
		{
			entity->updateTransformation();
		}
	}
}

void Quad3dManager::deleteQuad3d(const string & quad3dId)
{
	if(!isQuad3dExisting(quad3dId))
	{
		abort();
	}

	_quad3ds.erase(quad3dId);
}

void Quad3dManager::deleteQuad3ds()
{
	_quad3ds.clear();
}

const bool Quad3dManager::isQuad3dExisting(const string & quad3dId) const
{
	return (_quad3ds.find(quad3dId) != _quad3ds.end());
}

const bool Quad3dManager::isQuad3dsExisting() const
{
	return !_quad3ds.empty();
}