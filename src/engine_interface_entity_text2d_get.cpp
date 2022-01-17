#include "engine_interface.hpp"
#include "engine_core.hpp"

const bool EngineInterface::text_isExisting(const string& ID) const
{
	return _core->getText2dEntityManager()->isEntityExisting(ID);
}

const bool EngineInterface::text_isVisible(const string& ID) const
{
	return _core->getText2dEntityManager()->getEntity(ID)->isVisible();
}

const bool EngineInterface::text_isCentered(const string& ID) const
{
	return _core->getText2dEntityManager()->getEntity(ID)->isCentered();
}

const bool EngineInterface::text_isHorizontallyMirrored(const string& ID) const
{
	return _core->getText2dEntityManager()->getEntity(ID)->isMirroredHorizonally();
}

const bool EngineInterface::text_isVerticallyMirrored(const string& ID) const
{
	return _core->getText2dEntityManager()->getEntity(ID)->isVerticallyMirrored();
}

const bool EngineInterface::text_isWireframed(const string& ID) const
{
	return _core->getText2dEntityManager()->getEntity(ID)->isWireframed();
}

const bool EngineInterface::text_hasFontMap(const string& ID) const
{
	return (_core->getText2dEntityManager()->getEntity(ID)->getFontMap() != nullptr);
}

const fvec2 EngineInterface::text_getPosition(const string& ID) const
{
	return _core->getText2dEntityManager()->getEntity(ID)->getPosition();
}

const float EngineInterface::text_getRotation(const string& ID) const
{
	return _core->getText2dEntityManager()->getEntity(ID)->getRotation();
}

const float EngineInterface::text_getTransparency(const string& ID) const
{
	return _core->getText2dEntityManager()->getEntity(ID)->getTransparency();
}

const fvec2 EngineInterface::text_getSize(const string& ID) const
{
	return _core->getText2dEntityManager()->getEntity(ID)->getSize();
}

const fvec2 EngineInterface::text_getMinPosition(const string& ID) const
{
	return  _core->getText2dEntityManager()->getEntity(ID)->getMinPosition();
}

const fvec2 EngineInterface::text_getMaxPosition(const string& ID) const
{
	return  _core->getText2dEntityManager()->getEntity(ID)->getMaxPosition();
}

const fvec3 EngineInterface::text_getColor(const string& ID) const
{
	return _core->getText2dEntityManager()->getEntity(ID)->getColor();
}

const fvec3 EngineInterface::text_getWireframeColor(const string& ID) const
{
	return _core->getText2dEntityManager()->getEntity(ID)->getWireframeColor();
}

const string& EngineInterface::text_getContent(const string& ID) const
{
	return _core->getText2dEntityManager()->getEntity(ID)->getContent();
}

const vector<string> EngineInterface::text_getIDs() const
{
	vector<string> result;

	for(const auto& [key, entity] : _core->getText2dEntityManager()->getEntities())
	{
		result.push_back(entity->getID());
	}

	return result;
}

const string& EngineInterface::text_getFontMapPath(const string& ID) const
{
	return _core->getText2dEntityManager()->getEntity(ID)->getFontMapPath();
}