#include "fe3d.hpp"
#include "core.hpp"

const bool FabiEngine3D::image_isExisting(const string& ID) const
{
	return _core->_imageEntityManager.isEntityExisting(ID);
}

const fvec2 FabiEngine3D::image_getPosition(const string& ID) const
{
	return _core->_imageEntityManager.getEntity(ID)->getPosition();
}

const float FabiEngine3D::image_getRotation(const string& ID) const
{
	return _core->_imageEntityManager.getEntity(ID)->getRotation();
}

const float FabiEngine3D::image_getTransparency(const string& ID) const
{
	return _core->_imageEntityManager.getEntity(ID)->getTransparency();
}

const vector<string> FabiEngine3D::image_getIDs() const
{
	vector<string> result;

	for (const auto& [key, entity] : _core->_imageEntityManager.getEntities())
	{
		result.push_back(entity->getID());
	}

	return result;
}

const string& FabiEngine3D::image_getDiffuseMapPath(const string& ID) const
{
	return _core->_imageEntityManager.getEntity(ID)->getDiffuseMapPath();
}

const fvec3 FabiEngine3D::image_getWireframeColor(const string& ID) const
{
	return _core->_imageEntityManager.getEntity(ID)->getWireframeColor();
}

const fvec2 FabiEngine3D::image_getSize(const string& ID) const
{
	return _core->_imageEntityManager.getEntity(ID)->getSize();
}

const fvec2 FabiEngine3D::image_getMinPosition(const string& ID) const
{
	return _core->_imageEntityManager.getEntity(ID)->getMinPosition();
}

const fvec2 FabiEngine3D::image_getMaxPosition(const string& ID) const
{
	return _core->_imageEntityManager.getEntity(ID)->getMaxPosition();
}

const fvec2 FabiEngine3D::image_getMultiplierUV(const string& ID) const
{
	return _core->_imageEntityManager.getEntity(ID)->getMultiplierUV();
}

const fvec2 FabiEngine3D::image_getAdderUV(const string& ID) const
{
	return _core->_imageEntityManager.getEntity(ID)->getAdderUV();
}

const fvec3 FabiEngine3D::image_getColor(const string& ID) const
{
	return _core->_imageEntityManager.getEntity(ID)->getColor();
}

const bool FabiEngine3D::image_isVisible(const string& ID) const
{
	return _core->_imageEntityManager.getEntity(ID)->isVisible();
}

const bool FabiEngine3D::image_isCentered(const string& ID) const
{
	return _core->_imageEntityManager.getEntity(ID)->isCentered();
}

const bool FabiEngine3D::image_hasDiffuseMap(const string& ID) const
{
	return _core->_imageEntityManager.getEntity(ID)->hasDiffuseMap();
}

const bool FabiEngine3D::image_isWireframed(const string& ID) const
{
	return _core->_imageEntityManager.getEntity(ID)->isWireframed();
}

const bool FabiEngine3D::image_isMirroredHorizontally(const string& ID) const
{
	return _core->_imageEntityManager.getEntity(ID)->isMirroredHorizonally();
}

const bool FabiEngine3D::image_isMirroredVertically(const string& ID) const
{
	return _core->_imageEntityManager.getEntity(ID)->isMirroredVertically();
}