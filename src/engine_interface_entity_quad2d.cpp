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

void EngineInterface::quad2d_setPosition(const string& ID, const fvec2& position)
{
	_core->getQuad2dEntityManager()->getEntity(ID)->setPosition(position);
}

void EngineInterface::quad2d_setRotation(const string& ID, float rotation)
{
	_core->getQuad2dEntityManager()->getEntity(ID)->setRotation(rotation);
}

void EngineInterface::quad2d_setSize(const string& ID, const fvec2& size)
{
	_core->getQuad2dEntityManager()->getEntity(ID)->setSize(size);
}

void EngineInterface::quad2d_move(const string& ID, const fvec2& position)
{
	_core->getQuad2dEntityManager()->getEntity(ID)->move(position);
}

void EngineInterface::quad2d_rotate(const string& ID, float rotation)
{
	_core->getQuad2dEntityManager()->getEntity(ID)->rotate(rotation);
}

void EngineInterface::quad2d_scale(const string& ID, const fvec2& size)
{
	_core->getQuad2dEntityManager()->getEntity(ID)->scale(size);
}

void EngineInterface::quad2d_moveTo(const string& ID, const fvec2& target, float speed)
{
	_core->getQuad2dEntityManager()->getEntity(ID)->moveTo(target, speed);
}

void EngineInterface::quad2d_rotateTo(const string& ID, float target, float speed)
{
	_core->getQuad2dEntityManager()->getEntity(ID)->rotateTo(target, speed);
}

void EngineInterface::quad2d_scaleTo(const string& ID, const fvec2& target, float speed)
{
	_core->getQuad2dEntityManager()->getEntity(ID)->scaleTo(target, speed);
}

void EngineInterface::quad2d_setColor(const string& ID, const fvec3& value)
{
	_core->getQuad2dEntityManager()->getEntity(ID)->setColor(value);
}

void EngineInterface::quad2d_setOpacity(const string& ID, float value)
{
	_core->getQuad2dEntityManager()->getEntity(ID)->setOpacity(value);
}

void EngineInterface::quad2d_setMinPosition(const string& ID, const fvec2& value)
{
	_core->getQuad2dEntityManager()->getEntity(ID)->setMinPosition(value);
}

void EngineInterface::quad2d_setMaxPosition(const string& ID, const fvec2& value)
{
	_core->getQuad2dEntityManager()->getEntity(ID)->setMaxPosition(value);
}

void EngineInterface::quad2d_setWireframed(const string& ID, bool value)
{
	_core->getQuad2dEntityManager()->getEntity(ID)->setWireframed(value);
}

void EngineInterface::quad2d_setWireframeColor(const string& ID, const fvec3& value)
{
	_core->getQuad2dEntityManager()->getEntity(ID)->setWireframeColor(value);
}

void EngineInterface::quad2d_setUvMultiplier(const string& ID, const fvec2& value)
{
	_core->getQuad2dEntityManager()->getEntity(ID)->setUvMultiplier(value);
}

void EngineInterface::quad2d_setUvOffset(const string& ID, const fvec2& value)
{
	_core->getQuad2dEntityManager()->getEntity(ID)->setUvOffset(value);
}

void EngineInterface::quad2d_setHorizontallyFlipped(const string& ID, bool value)
{
	_core->getQuad2dEntityManager()->getEntity(ID)->setHorizontallyFlipped(value);
}

void EngineInterface::quad2d_setVerticallyFlipped(const string& ID, bool value)
{
	_core->getQuad2dEntityManager()->getEntity(ID)->setVerticallyFlipped(value);
}

const bool EngineInterface::quad2d_isExisting(const string& ID) const
{
	return _core->getQuad2dEntityManager()->isEntityExisting(ID);
}

const fvec2& EngineInterface::quad2d_getPosition(const string& ID) const
{
	return _core->getQuad2dEntityManager()->getEntity(ID)->getPosition();
}

const float EngineInterface::quad2d_getRotation(const string& ID) const
{
	return _core->getQuad2dEntityManager()->getEntity(ID)->getRotation();
}

const float EngineInterface::quad2d_getOpacity(const string& ID) const
{
	return _core->getQuad2dEntityManager()->getEntity(ID)->getOpacity();
}

const vector<string> EngineInterface::quad2d_getIDs() const
{
	vector<string> result;

	for(const auto& [key, entity] : _core->getQuad2dEntityManager()->getEntities())
	{
		result.push_back(entity->getID());
	}

	return result;
}

const string& EngineInterface::quad2d_getDiffuseMapPath(const string& ID) const
{
	return _core->getQuad2dEntityManager()->getEntity(ID)->getDiffuseMapPath();
}

const fvec3& EngineInterface::quad2d_getWireframeColor(const string& ID) const
{
	return _core->getQuad2dEntityManager()->getEntity(ID)->getWireframeColor();
}

const fvec2& EngineInterface::quad2d_getSize(const string& ID) const
{
	return _core->getQuad2dEntityManager()->getEntity(ID)->getSize();
}

const fvec2& EngineInterface::quad2d_getMinPosition(const string& ID) const
{
	return _core->getQuad2dEntityManager()->getEntity(ID)->getMinPosition();
}

const fvec2& EngineInterface::quad2d_getMaxPosition(const string& ID) const
{
	return _core->getQuad2dEntityManager()->getEntity(ID)->getMaxPosition();
}

const fvec2& EngineInterface::quad2d_getUvMultiplier(const string& ID) const
{
	return _core->getQuad2dEntityManager()->getEntity(ID)->getUvMultiplier();
}

const fvec2& EngineInterface::quad2d_getUvOffset(const string& ID) const
{
	return _core->getQuad2dEntityManager()->getEntity(ID)->getUvOffset();
}

const fvec3& EngineInterface::quad2d_getColor(const string& ID) const
{
	return _core->getQuad2dEntityManager()->getEntity(ID)->getColor();
}

const bool EngineInterface::quad2d_isVisible(const string& ID) const
{
	return _core->getQuad2dEntityManager()->getEntity(ID)->isVisible();
}

const bool EngineInterface::quad2d_isCentered(const string& ID) const
{
	return _core->getQuad2dEntityManager()->getEntity(ID)->isCentered();
}

const bool EngineInterface::quad2d_hasDiffuseMap(const string& ID) const
{
	return _core->getQuad2dEntityManager()->getEntity(ID)->hasDiffuseMap();
}

const bool EngineInterface::quad2d_isWireframed(const string& ID) const
{
	return _core->getQuad2dEntityManager()->getEntity(ID)->isWireframed();
}

const bool EngineInterface::quad2d_isHorizontallyFlipped(const string& ID) const
{
	return _core->getQuad2dEntityManager()->getEntity(ID)->isFlippedHorizonally();
}

const bool EngineInterface::quad2d_isVerticallyFlipped(const string& ID) const
{
	return _core->getQuad2dEntityManager()->getEntity(ID)->isVerticallyFlipped();
}