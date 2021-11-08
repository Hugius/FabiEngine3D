#include "fe3d.hpp"
#include "core_engine.hpp"

const bool FabiEngine3D::textEntity_isExisting(const string& ID) const
{
	return _core->_textEntityManager.isExisting(ID);
}

const bool FabiEngine3D::textEntity_isVisible(const string& ID) const
{
	return _core->_textEntityManager.getEntity(ID)->isVisible();
}

const Vec2 FabiEngine3D::textEntity_getPosition(const string& ID) const
{
	return _core->_textEntityManager.getEntity(ID)->getPosition();
}

const float FabiEngine3D::textEntity_getRotation(const string& ID) const
{
	return _core->_textEntityManager.getEntity(ID)->getRotation();
}

const float FabiEngine3D::textEntity_getAlpha(const string& ID) const
{
	return _core->_textEntityManager.getEntity(ID)->getAlpha();
}

const Vec2 FabiEngine3D::textEntity_getSize(const string& ID) const
{
	return _core->_textEntityManager.getEntity(ID)->getSize();
}

const Vec2 FabiEngine3D::textEntity_getMinPosition(const string& ID) const
{
	return  _core->_textEntityManager.getEntity(ID)->getMinPosition();
}

const Vec2 FabiEngine3D::textEntity_getMaxPosition(const string& ID) const
{
	return  _core->_textEntityManager.getEntity(ID)->getMaxPosition();
}

const Vec3 FabiEngine3D::textEntity_getColor(const string& ID) const
{
	return _core->_textEntityManager.getEntity(ID)->getColor();
}

const string& FabiEngine3D::textEntity_getTextContent(const string& ID) const
{
	return _core->_textEntityManager.getEntity(ID)->getTextContent();
}

const vector<string> FabiEngine3D::textEntity_getAllIDs() const
{
	vector<string> IDs;

	for(const auto& [keyID, entity] : _core->_textEntityManager.getEntities())
	{
		IDs.push_back(entity->getID());
	}

	return IDs;
}

const string& FabiEngine3D::textEntity_getFontPath(const string& ID) const
{
	return _core->_textEntityManager.getEntity(ID)->getFontPath();
}