#include "engine_interface.hpp"
#include "engine_core.hpp"

void EngineInterface::quad_deleteAll()
{
	_core->getQuadEntityManager()->deleteEntities();
}

void EngineInterface::quad_create(const string& ID, bool isCentered)
{
	_core->getQuadEntityManager()->createEntity(ID, isCentered);
}

void EngineInterface::quad_delete(const string& ID)
{
	_core->getQuadEntityManager()->deleteEntity(ID);
}

void EngineInterface::quad_setVisible(const string& ID, bool value)
{
	_core->getQuadEntityManager()->getEntity(ID)->setVisible(value);
}

void EngineInterface::quad_setDiffuseMap(const string& ID, const string& value)
{
	if(value.empty())
	{
		_core->getQuadEntityManager()->getEntity(ID)->setDiffuseMap(nullptr);
		_core->getQuadEntityManager()->getEntity(ID)->setDiffuseMapPath("");
	}
	else
	{
		auto texture = _core->getTextureBufferCache()->get2dBuffer(value);

		if(texture == nullptr)
		{
			texture = make_shared<TextureBuffer>(_core->getImageLoader()->loadImage(value));

			_core->getTextureBufferCache()->store2dBuffer(value, texture);
		}

		_core->getQuadEntityManager()->getEntity(ID)->setDiffuseMap(texture);
		_core->getQuadEntityManager()->getEntity(ID)->setDiffuseMapPath(value);
	}
}

void EngineInterface::quad_setPosition(const string& ID, fvec2 position)
{
	_core->getQuadEntityManager()->getEntity(ID)->setPosition(position);
}

void EngineInterface::quad_setRotation(const string& ID, float rotation)
{
	_core->getQuadEntityManager()->getEntity(ID)->setRotation(rotation);
}

void EngineInterface::quad_setSize(const string& ID, fvec2 size)
{
	_core->getQuadEntityManager()->getEntity(ID)->setSize(size);
}

void EngineInterface::quad_move(const string& ID, fvec2 position)
{
	_core->getQuadEntityManager()->getEntity(ID)->move(position);
}

void EngineInterface::quad_rotate(const string& ID, float rotation)
{
	_core->getQuadEntityManager()->getEntity(ID)->rotate(rotation);
}

void EngineInterface::quad_scale(const string& ID, fvec2 size)
{
	_core->getQuadEntityManager()->getEntity(ID)->scale(size);
}

void EngineInterface::quad_moveTo(const string& ID, fvec2 target, float speed)
{
	_core->getQuadEntityManager()->getEntity(ID)->moveTo(target, speed);
}

void EngineInterface::quad_rotateTo(const string& ID, float target, float speed)
{
	_core->getQuadEntityManager()->getEntity(ID)->rotateTo(target, speed);
}

void EngineInterface::quad_scaleTo(const string& ID, fvec2 target, float speed)
{
	_core->getQuadEntityManager()->getEntity(ID)->scaleTo(target, speed);
}

void EngineInterface::quad_setColor(const string& ID, fvec3 value)
{
	_core->getQuadEntityManager()->getEntity(ID)->setColor(value);
}

void EngineInterface::quad_setTransparency(const string& ID, float value)
{
	_core->getQuadEntityManager()->getEntity(ID)->setTransparency(value);
}

void EngineInterface::quad_setMinPosition(const string& ID, fvec2 value)
{
	_core->getQuadEntityManager()->getEntity(ID)->setMinPosition(value);
}

void EngineInterface::quad_setMaxPosition(const string& ID, fvec2 value)
{
	_core->getQuadEntityManager()->getEntity(ID)->setMaxPosition(value);
}

void EngineInterface::quad_setWireframed(const string& ID, bool value)
{
	_core->getQuadEntityManager()->getEntity(ID)->setWireframed(value);
}

void EngineInterface::quad_setWireframeColor(const string& ID, fvec3 value)
{
	_core->getQuadEntityManager()->getEntity(ID)->setWireframeColor(value);
}

void EngineInterface::quad_setUvMultiplier(const string& ID, fvec2 value)
{
	_core->getQuadEntityManager()->getEntity(ID)->setUvMultiplier(value);
}

void EngineInterface::quad_setUvOffset(const string& ID, fvec2 value)
{
	_core->getQuadEntityManager()->getEntity(ID)->setUvOffset(value);
}

void EngineInterface::quad_setMirroredHorizontally(const string& ID, bool value)
{
	_core->getQuadEntityManager()->getEntity(ID)->setMirroredHorizontally(value);
}

void EngineInterface::quad_setMirroredVertically(const string& ID, bool value)
{
	_core->getQuadEntityManager()->getEntity(ID)->setMirroredVertically(value);
}