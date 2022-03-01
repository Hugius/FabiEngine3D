#include "engine_interface.hpp"
#include "engine_core.hpp"

void EngineInterface::text2d_create(const string& id, const string& fontMapPath, bool isCentered)
{
	_core->getText2dEntityManager()->createEntity(id, fontMapPath, isCentered);
}

void EngineInterface::text2d_delete(const string& id)
{
	_core->getText2dEntityManager()->deleteEntity(id);
}

void EngineInterface::text2d_setVisible(const string& id, bool value)
{
	_core->getText2dEntityManager()->getEntity(id)->setVisible(value);
}

void EngineInterface::text2d_setContent(const string& id, const string& value)
{
	_core->getText2dEntityManager()->getEntity(id)->setContent(value);
}

void EngineInterface::text2d_setColor(const string& id, const fvec3& value)
{
	_core->getText2dEntityManager()->getEntity(id)->setColor(value);
}

void EngineInterface::text2d_setOpacity(const string& id, float value)
{
	_core->getText2dEntityManager()->getEntity(id)->setOpacity(value);
}

void EngineInterface::text2d_setPosition(const string& id, const fvec2& value)
{
	_core->getText2dEntityManager()->getEntity(id)->setPosition(value);
}

void EngineInterface::text2d_setRotation(const string& id, float value)
{
	_core->getText2dEntityManager()->getEntity(id)->setRotation(value);
}

void EngineInterface::text2d_setSize(const string& id, const fvec2& value)
{
	_core->getText2dEntityManager()->getEntity(id)->setSize(value);
}

void EngineInterface::text2d_move(const string& id, const fvec2& position)
{
	_core->getText2dEntityManager()->getEntity(id)->move(position);
}

void EngineInterface::text2d_rotate(const string& id, float rotation)
{
	_core->getText2dEntityManager()->getEntity(id)->rotate(rotation);
}

void EngineInterface::text2d_scale(const string& id, const fvec2& size)
{
	_core->getText2dEntityManager()->getEntity(id)->scale(size);
}

void EngineInterface::text2d_moveTo(const string& id, const fvec2& target, float speed)
{
	_core->getText2dEntityManager()->getEntity(id)->moveTo(target, speed);
}

void EngineInterface::text2d_rotateTo(const string& id, float target, float speed)
{
	_core->getText2dEntityManager()->getEntity(id)->rotateTo(target, speed);
}

void EngineInterface::text2d_scaleTo(const string& id, const fvec2& target, float speed)
{
	_core->getText2dEntityManager()->getEntity(id)->scaleTo(target, speed);
}

void EngineInterface::text2d_setHorizontallyFlipped(const string& id, bool value)
{
	_core->getText2dEntityManager()->getEntity(id)->setHorizontallyFlipped(value);
}

void EngineInterface::text2d_setVerticallyFlipped(const string& id, bool value)
{
	_core->getText2dEntityManager()->getEntity(id)->setVerticallyFlipped(value);
}

void EngineInterface::text2d_setWireframed(const string& id, bool value)
{
	_core->getText2dEntityManager()->getEntity(id)->setWireframed(value);
}

void EngineInterface::text2d_setWireframeColor(const string& id, const fvec3& value)
{
	_core->getText2dEntityManager()->getEntity(id)->setWireframeColor(value);
}

void EngineInterface::text2d_setMinPosition(const string& id, const fvec2& value)
{
	_core->getText2dEntityManager()->getEntity(id)->setMinPosition(value);
}

void EngineInterface::text2d_setMaxPosition(const string& id, const fvec2& value)
{
	_core->getText2dEntityManager()->getEntity(id)->setMaxPosition(value);
}

const bool EngineInterface::text2d_isExisting(const string& id) const
{
	return _core->getText2dEntityManager()->isEntityExisting(id);
}

const bool EngineInterface::text2d_isVisible(const string& id) const
{
	return _core->getText2dEntityManager()->getEntity(id)->isVisible();
}

const bool EngineInterface::text2d_isCentered(const string& id) const
{
	return _core->getText2dEntityManager()->getEntity(id)->isCentered();
}

const bool EngineInterface::text2d_isHorizontallyFlipped(const string& id) const
{
	return _core->getText2dEntityManager()->getEntity(id)->isFlippedHorizonally();
}

const bool EngineInterface::text2d_isVerticallyFlipped(const string& id) const
{
	return _core->getText2dEntityManager()->getEntity(id)->isVerticallyFlipped();
}

const bool EngineInterface::text2d_isWireframed(const string& id) const
{
	return _core->getText2dEntityManager()->getEntity(id)->isWireframed();
}

const bool EngineInterface::text2d_hasFontMap(const string& id) const
{
	return (_core->getText2dEntityManager()->getEntity(id)->getFontTextureBuffer() != nullptr);
}

const fvec2& EngineInterface::text2d_getPosition(const string& id) const
{
	return _core->getText2dEntityManager()->getEntity(id)->getPosition();
}

const float EngineInterface::text2d_getRotation(const string& id) const
{
	return _core->getText2dEntityManager()->getEntity(id)->getRotation();
}

const float EngineInterface::text2d_getOpacity(const string& id) const
{
	return _core->getText2dEntityManager()->getEntity(id)->getOpacity();
}

const fvec2& EngineInterface::text2d_getSize(const string& id) const
{
	return _core->getText2dEntityManager()->getEntity(id)->getSize();
}

const fvec2& EngineInterface::text2d_getMinPosition(const string& id) const
{
	return  _core->getText2dEntityManager()->getEntity(id)->getMinPosition();
}

const fvec2& EngineInterface::text2d_getMaxPosition(const string& id) const
{
	return  _core->getText2dEntityManager()->getEntity(id)->getMaxPosition();
}

const fvec3& EngineInterface::text2d_getColor(const string& id) const
{
	return _core->getText2dEntityManager()->getEntity(id)->getColor();
}

const fvec3& EngineInterface::text2d_getWireframeColor(const string& id) const
{
	return _core->getText2dEntityManager()->getEntity(id)->getWireframeColor();
}

const string& EngineInterface::text2d_getContent(const string& id) const
{
	return _core->getText2dEntityManager()->getEntity(id)->getContent();
}

const vector<string> EngineInterface::text2d_getIds() const
{
	vector<string> result;

	for(const auto& [key, entity] : _core->getText2dEntityManager()->getEntities())
	{
		result.push_back(entity->getId());
	}

	return result;
}

const string& EngineInterface::text2d_getFontMapPath(const string& id) const
{
	return _core->getText2dEntityManager()->getEntity(id)->getFontMapPath();
}