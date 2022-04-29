#include "engine_interface.hpp"
#include "engine_core.hpp"

void EngineInterface::text2d_create(const string & text2dId, const string & fontMapPath, bool isCentered)
{
	_core->getText2dManager()->createText2d(text2dId, fontMapPath, isCentered);
}

void EngineInterface::text2d_delete(const string & text2dId)
{
	_core->getText2dManager()->deleteText2d(text2dId);
}

void EngineInterface::text2d_setVisible(const string & text2dId, bool value)
{
	_core->getText2dManager()->getText2d(text2dId)->setVisible(value);
}

void EngineInterface::text2d_setContent(const string & text2dId, const string & value)
{
	_core->getText2dManager()->getText2d(text2dId)->setContent(value);
}

void EngineInterface::text2d_setColor(const string & text2dId, const fvec3 & value)
{
	_core->getText2dManager()->getText2d(text2dId)->setColor(value);
}

void EngineInterface::text2d_setOpacity(const string & text2dId, float value)
{
	_core->getText2dManager()->getText2d(text2dId)->setOpacity(value);
}

void EngineInterface::text2d_setPosition(const string & text2dId, const fvec2 & value)
{
	_core->getText2dManager()->getText2d(text2dId)->setPosition(value);
}

void EngineInterface::text2d_setRotation(const string & text2dId, float value)
{
	_core->getText2dManager()->getText2d(text2dId)->setRotation(value);
}

void EngineInterface::text2d_setSize(const string & text2dId, const fvec2 & value)
{
	_core->getText2dManager()->getText2d(text2dId)->setSize(value);
}

void EngineInterface::text2d_move(const string & text2dId, const fvec2 & change)
{
	_core->getText2dManager()->getText2d(text2dId)->move(change);
}

void EngineInterface::text2d_rotate(const string & text2dId, float change)
{
	_core->getText2dManager()->getText2d(text2dId)->rotate(change);
}

void EngineInterface::text2d_scale(const string & text2dId, const fvec2 & change)
{
	_core->getText2dManager()->getText2d(text2dId)->scale(change);
}

void EngineInterface::text2d_moveTo(const string & text2dId, const fvec2 & target, float speed)
{
	_core->getText2dManager()->getText2d(text2dId)->moveTo(target, speed);
}

void EngineInterface::text2d_rotateTo(const string & text2dId, float target, float speed)
{
	_core->getText2dManager()->getText2d(text2dId)->rotateTo(target, speed);
}

void EngineInterface::text2d_scaleTo(const string & text2dId, const fvec2 & target, float speed)
{
	_core->getText2dManager()->getText2d(text2dId)->scaleTo(target, speed);
}

void EngineInterface::text2d_setHorizontallyFlipped(const string & text2dId, bool value)
{
	_core->getText2dManager()->getText2d(text2dId)->setHorizontallyFlipped(value);
}

void EngineInterface::text2d_setVerticallyFlipped(const string & text2dId, bool value)
{
	_core->getText2dManager()->getText2d(text2dId)->setVerticallyFlipped(value);
}

void EngineInterface::text2d_setWireframed(const string & text2dId, bool value)
{
	_core->getText2dManager()->getText2d(text2dId)->setWireframed(value);
}

void EngineInterface::text2d_setWireframeColor(const string & text2dId, const fvec3 & value)
{
	_core->getText2dManager()->getText2d(text2dId)->setWireframeColor(value);
}

void EngineInterface::text2d_setMinClipPosition(const string & text2dId, const fvec2 & value)
{
	_core->getText2dManager()->getText2d(text2dId)->setMinClipPosition(value);
}

void EngineInterface::text2d_setMaxClipPosition(const string & text2dId, const fvec2 & value)
{
	_core->getText2dManager()->getText2d(text2dId)->setMaxClipPosition(value);
}

const bool EngineInterface::text2d_isExisting(const string & text2dId) const
{
	return _core->getText2dManager()->isText2dExisting(text2dId);
}

const bool EngineInterface::text2d_isVisible(const string & text2dId) const
{
	return _core->getText2dManager()->getText2d(text2dId)->isVisible();
}

const bool EngineInterface::text2d_isCentered(const string & text2dId) const
{
	return _core->getText2dManager()->getText2d(text2dId)->isCentered();
}

const bool EngineInterface::text2d_isHorizontallyFlipped(const string & text2dId) const
{
	return _core->getText2dManager()->getText2d(text2dId)->isHorizontallyFlipped();
}

const bool EngineInterface::text2d_isVerticallyFlipped(const string & text2dId) const
{
	return _core->getText2dManager()->getText2d(text2dId)->isVerticallyFlipped();
}

const bool EngineInterface::text2d_isWireframed(const string & text2dId) const
{
	return _core->getText2dManager()->getText2d(text2dId)->isWireframed();
}

const fvec2 & EngineInterface::text2d_getPosition(const string & text2dId) const
{
	return _core->getText2dManager()->getText2d(text2dId)->getPosition();
}

const float EngineInterface::text2d_getRotation(const string & text2dId) const
{
	return _core->getText2dManager()->getText2d(text2dId)->getRotation();
}

const float EngineInterface::text2d_getOpacity(const string & text2dId) const
{
	return _core->getText2dManager()->getText2d(text2dId)->getOpacity();
}

const fvec2 & EngineInterface::text2d_getSize(const string & text2dId) const
{
	return _core->getText2dManager()->getText2d(text2dId)->getSize();
}

const fvec2 & EngineInterface::text2d_getMinClipPosition(const string & text2dId) const
{
	return  _core->getText2dManager()->getText2d(text2dId)->getMinClipPosition();
}

const fvec2 & EngineInterface::text2d_getMaxClipPosition(const string & text2dId) const
{
	return  _core->getText2dManager()->getText2d(text2dId)->getMaxClipPosition();
}

const fvec3 & EngineInterface::text2d_getColor(const string & text2dId) const
{
	return _core->getText2dManager()->getText2d(text2dId)->getColor();
}

const fvec3 & EngineInterface::text2d_getWireframeColor(const string & text2dId) const
{
	return _core->getText2dManager()->getText2d(text2dId)->getWireframeColor();
}

const string & EngineInterface::text2d_getContent(const string & text2dId) const
{
	return _core->getText2dManager()->getText2d(text2dId)->getContent();
}

const vector<string> EngineInterface::text2d_getIds() const
{
	vector<string> result;

	for(const auto & [text2dId, text2d] : _core->getText2dManager()->getText2ds())
	{
		result.push_back(text2d->getId());
	}

	return result;
}

const string & EngineInterface::text2d_getFontMapPath(const string & text2dId) const
{
	return _core->getText2dManager()->getText2d(text2dId)->getFontMapPath();
}