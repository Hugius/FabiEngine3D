#include "engine_interface.hpp"
#include "engine_core.hpp"

void EngineInterface::text2d_deleteAll()
{
	_core->getText2dEntityManager()->deleteEntities();
}

void EngineInterface::text2d_create(const string& ID, const string& fontMapPath, bool isCentered)
{
	_core->getText2dEntityManager()->createEntity(ID, fontMapPath, isCentered);
}

void EngineInterface::text2d_delete(const string& ID)
{
	_core->getText2dEntityManager()->deleteEntity(ID);
}

void EngineInterface::text2d_setVisible(const string& ID, bool value)
{
	_core->getText2dEntityManager()->getEntity(ID)->setVisible(value);
}

void EngineInterface::text2d_setContent(const string& ID, const string& value, float charWidth, float charHeight)
{
	auto entity = _core->getText2dEntityManager()->getEntity(ID);

	entity->setContent(value);

	fvec2 newSize = entity->getSize();

	if(charWidth >= 0.0f)
	{
		newSize.x = (charWidth * static_cast<float>(value.size()));
	}
	if(charHeight >= 0.0f)
	{
		newSize.y = charHeight;
	}

	entity->setSize(newSize);
}

void EngineInterface::text2d_setColor(const string& ID, const fvec3& value)
{
	_core->getText2dEntityManager()->getEntity(ID)->setColor(value);
}

void EngineInterface::text2d_setOpacity(const string& ID, float value)
{
	_core->getText2dEntityManager()->getEntity(ID)->setOpacity(value);
}

void EngineInterface::text2d_setPosition(const string& ID, const fvec2& value)
{
	_core->getText2dEntityManager()->getEntity(ID)->setPosition(value);
}

void EngineInterface::text2d_setRotation(const string& ID, float value)
{
	_core->getText2dEntityManager()->getEntity(ID)->setRotation(value);
}

void EngineInterface::text2d_setSize(const string& ID, const fvec2& value)
{
	_core->getText2dEntityManager()->getEntity(ID)->setSize(value);
}

void EngineInterface::text2d_move(const string& ID, const fvec2& position)
{
	_core->getText2dEntityManager()->getEntity(ID)->move(position);
}

void EngineInterface::text2d_rotate(const string& ID, float rotation)
{
	_core->getText2dEntityManager()->getEntity(ID)->rotate(rotation);
}

void EngineInterface::text2d_scale(const string& ID, const fvec2& size)
{
	_core->getText2dEntityManager()->getEntity(ID)->scale(size);
}

void EngineInterface::text2d_moveTo(const string& ID, const fvec2& target, float speed)
{
	_core->getText2dEntityManager()->getEntity(ID)->moveTo(target, speed);
}

void EngineInterface::text2d_rotateTo(const string& ID, float target, float speed)
{
	_core->getText2dEntityManager()->getEntity(ID)->rotateTo(target, speed);
}

void EngineInterface::text2d_scaleTo(const string& ID, const fvec2& target, float speed)
{
	_core->getText2dEntityManager()->getEntity(ID)->scaleTo(target, speed);
}

void EngineInterface::text2d_setHorizontallyMirrored(const string& ID, bool value)
{
	_core->getText2dEntityManager()->getEntity(ID)->setHorizontallyMirrored(value);
}

void EngineInterface::text2d_setVerticallyMirrored(const string& ID, bool value)
{
	_core->getText2dEntityManager()->getEntity(ID)->setVerticallyMirrored(value);
}

void EngineInterface::text2d_setWireframed(const string& ID, bool value)
{
	_core->getText2dEntityManager()->getEntity(ID)->setWireframed(value);
}

void EngineInterface::text2d_setWireframeColor(const string& ID, const fvec3& value)
{
	_core->getText2dEntityManager()->getEntity(ID)->setWireframeColor(value);
}

void EngineInterface::text2d_setMinPosition(const string& ID, const fvec2& value)
{
	_core->getText2dEntityManager()->getEntity(ID)->setMinPosition(value);
}

void EngineInterface::text2d_setMaxPosition(const string& ID, const fvec2& value)
{
	_core->getText2dEntityManager()->getEntity(ID)->setMaxPosition(value);
}

const bool EngineInterface::text2d_isExisting(const string& ID) const
{
	return _core->getText2dEntityManager()->isEntityExisting(ID);
}

const bool EngineInterface::text2d_isVisible(const string& ID) const
{
	return _core->getText2dEntityManager()->getEntity(ID)->isVisible();
}

const bool EngineInterface::text2d_isCentered(const string& ID) const
{
	return _core->getText2dEntityManager()->getEntity(ID)->isCentered();
}

const bool EngineInterface::text2d_isHorizontallyMirrored(const string& ID) const
{
	return _core->getText2dEntityManager()->getEntity(ID)->isMirroredHorizonally();
}

const bool EngineInterface::text2d_isVerticallyMirrored(const string& ID) const
{
	return _core->getText2dEntityManager()->getEntity(ID)->isVerticallyMirrored();
}

const bool EngineInterface::text2d_isWireframed(const string& ID) const
{
	return _core->getText2dEntityManager()->getEntity(ID)->isWireframed();
}

const bool EngineInterface::text2d_hasFontMap(const string& ID) const
{
	return (_core->getText2dEntityManager()->getEntity(ID)->getFontMap() != nullptr);
}

const fvec2& EngineInterface::text2d_getPosition(const string& ID) const
{
	return _core->getText2dEntityManager()->getEntity(ID)->getPosition();
}

const float EngineInterface::text2d_getRotation(const string& ID) const
{
	return _core->getText2dEntityManager()->getEntity(ID)->getRotation();
}

const float EngineInterface::text2d_getOpacity(const string& ID) const
{
	return _core->getText2dEntityManager()->getEntity(ID)->getOpacity();
}

const fvec2& EngineInterface::text2d_getSize(const string& ID) const
{
	return _core->getText2dEntityManager()->getEntity(ID)->getSize();
}

const fvec2& EngineInterface::text2d_getMinPosition(const string& ID) const
{
	return  _core->getText2dEntityManager()->getEntity(ID)->getMinPosition();
}

const fvec2& EngineInterface::text2d_getMaxPosition(const string& ID) const
{
	return  _core->getText2dEntityManager()->getEntity(ID)->getMaxPosition();
}

const fvec3& EngineInterface::text2d_getColor(const string& ID) const
{
	return _core->getText2dEntityManager()->getEntity(ID)->getColor();
}

const fvec3& EngineInterface::text2d_getWireframeColor(const string& ID) const
{
	return _core->getText2dEntityManager()->getEntity(ID)->getWireframeColor();
}

const string& EngineInterface::text2d_getContent(const string& ID) const
{
	return _core->getText2dEntityManager()->getEntity(ID)->getContent();
}

const vector<string> EngineInterface::text2d_getIDs() const
{
	vector<string> result;

	for(const auto& [key, entity] : _core->getText2dEntityManager()->getEntities())
	{
		result.push_back(entity->getID());
	}

	return result;
}

const string& EngineInterface::text2d_getFontMapPath(const string& ID) const
{
	return _core->getText2dEntityManager()->getEntity(ID)->getFontMapPath();
}