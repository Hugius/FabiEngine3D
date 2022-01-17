#include "engine_interface.hpp"
#include "engine_core.hpp"

void EngineInterface::quad2d_deleteAll()
{
	_core->getQuad2dEntityManager()->deleteEntities();
}

void EngineInterface::quad2d_create(const string& ID, bool isCentered)
{
	_core->getQuad2dEntityManager()->createEntity(ID, isCentered);
}

void EngineInterface::quad2d_delete(const string& ID)
{
	_core->getQuad2dEntityManager()->deleteEntity(ID);
}

void EngineInterface::quad2d_setVisible(const string& ID, bool value)
{
	_core->getQuad2dEntityManager()->getEntity(ID)->setVisible(value);
}

void EngineInterface::quad2d_setDiffuseMap(const string& ID, const string& value)
{
	if(value.empty())
	{
		_core->getQuad2dEntityManager()->getEntity(ID)->setDiffuseMap(nullptr);
		_core->getQuad2dEntityManager()->getEntity(ID)->setDiffuseMapPath("");
	}
	else
	{
		auto texture = _core->getTextureBufferCache()->get2dBuffer(value);

		if(texture == nullptr)
		{
			texture = make_shared<TextureBuffer>(_core->getImageLoader()->loadImage(value));

			_core->getTextureBufferCache()->store2dBuffer(value, texture);
		}

		_core->getQuad2dEntityManager()->getEntity(ID)->setDiffuseMap(texture);
		_core->getQuad2dEntityManager()->getEntity(ID)->setDiffuseMapPath(value);
	}
}

void EngineInterface::quad2d_setPosition(const string& ID, fvec2 position)
{
	_core->getQuad2dEntityManager()->getEntity(ID)->setPosition(position);
}

void EngineInterface::quad2d_setRotation(const string& ID, float rotation)
{
	_core->getQuad2dEntityManager()->getEntity(ID)->setRotation(rotation);
}

void EngineInterface::quad2d_setSize(const string& ID, fvec2 size)
{
	_core->getQuad2dEntityManager()->getEntity(ID)->setSize(size);
}

void EngineInterface::quad2d_move(const string& ID, fvec2 position)
{
	_core->getQuad2dEntityManager()->getEntity(ID)->move(position);
}

void EngineInterface::quad2d_rotate(const string& ID, float rotation)
{
	_core->getQuad2dEntityManager()->getEntity(ID)->rotate(rotation);
}

void EngineInterface::quad2d_scale(const string& ID, fvec2 size)
{
	_core->getQuad2dEntityManager()->getEntity(ID)->scale(size);
}

void EngineInterface::quad2d_moveTo(const string& ID, fvec2 target, float speed)
{
	_core->getQuad2dEntityManager()->getEntity(ID)->moveTo(target, speed);
}

void EngineInterface::quad2d_rotateTo(const string& ID, float target, float speed)
{
	_core->getQuad2dEntityManager()->getEntity(ID)->rotateTo(target, speed);
}

void EngineInterface::quad2d_scaleTo(const string& ID, fvec2 target, float speed)
{
	_core->getQuad2dEntityManager()->getEntity(ID)->scaleTo(target, speed);
}

void EngineInterface::quad2d_setColor(const string& ID, fvec3 value)
{
	_core->getQuad2dEntityManager()->getEntity(ID)->setColor(value);
}

void EngineInterface::quad2d_setTransparency(const string& ID, float value)
{
	_core->getQuad2dEntityManager()->getEntity(ID)->setTransparency(value);
}

void EngineInterface::quad2d_setMinPosition(const string& ID, fvec2 value)
{
	_core->getQuad2dEntityManager()->getEntity(ID)->setMinPosition(value);
}

void EngineInterface::quad2d_setMaxPosition(const string& ID, fvec2 value)
{
	_core->getQuad2dEntityManager()->getEntity(ID)->setMaxPosition(value);
}

void EngineInterface::quad2d_setWireframed(const string& ID, bool value)
{
	_core->getQuad2dEntityManager()->getEntity(ID)->setWireframed(value);
}

void EngineInterface::quad2d_setWireframeColor(const string& ID, fvec3 value)
{
	_core->getQuad2dEntityManager()->getEntity(ID)->setWireframeColor(value);
}

void EngineInterface::quad2d_setUvMultiplier(const string& ID, fvec2 value)
{
	_core->getQuad2dEntityManager()->getEntity(ID)->setUvMultiplier(value);
}

void EngineInterface::quad2d_setUvOffset(const string& ID, fvec2 value)
{
	_core->getQuad2dEntityManager()->getEntity(ID)->setUvOffset(value);
}

void EngineInterface::quad2d_setHorizontallyMirrored(const string& ID, bool value)
{
	_core->getQuad2dEntityManager()->getEntity(ID)->setHorizontallyMirrored(value);
}

void EngineInterface::quad2d_setVerticallyMirrored(const string& ID, bool value)
{
	_core->getQuad2dEntityManager()->getEntity(ID)->setVerticallyMirrored(value);
}