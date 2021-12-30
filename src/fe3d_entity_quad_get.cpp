#include "fe3d.hpp"
#include "core.hpp"

const bool FabiEngine3D::quad_isExisting(const string& ID) const
{
	return _core->_quadEntityManager.isEntityExisting(ID);
}

const fvec2 FabiEngine3D::quad_getPosition(const string& ID) const
{
	return _core->_quadEntityManager.getEntity(ID)->getPosition();
}

const float FabiEngine3D::quad_getRotation(const string& ID) const
{
	return _core->_quadEntityManager.getEntity(ID)->getRotation();
}

const float FabiEngine3D::quad_getTransparency(const string& ID) const
{
	return _core->_quadEntityManager.getEntity(ID)->getTransparency();
}

const vector<string> FabiEngine3D::quad_getIDs() const
{
	vector<string> result;

	for(const auto& [key, entity] : _core->_quadEntityManager.getEntities())
	{
		result.push_back(entity->getID());
	}

	return result;
}

const string& FabiEngine3D::quad_getDiffuseMapPath(const string& ID) const
{
	return _core->_quadEntityManager.getEntity(ID)->getDiffuseMapPath();
}

const fvec3 FabiEngine3D::quad_getWireframeColor(const string& ID) const
{
	return _core->_quadEntityManager.getEntity(ID)->getWireframeColor();
}

const fvec2 FabiEngine3D::quad_getSize(const string& ID) const
{
	return _core->_quadEntityManager.getEntity(ID)->getSize();
}

const fvec2 FabiEngine3D::quad_getMinPosition(const string& ID) const
{
	return _core->_quadEntityManager.getEntity(ID)->getMinPosition();
}

const fvec2 FabiEngine3D::quad_getMaxPosition(const string& ID) const
{
	return _core->_quadEntityManager.getEntity(ID)->getMaxPosition();
}

const fvec2 FabiEngine3D::quad_getMultiplierUV(const string& ID) const
{
	return _core->_quadEntityManager.getEntity(ID)->getMultiplierUV();
}

const fvec2 FabiEngine3D::quad_getAdderUV(const string& ID) const
{
	return _core->_quadEntityManager.getEntity(ID)->getAdderUV();
}

const fvec3 FabiEngine3D::quad_getColor(const string& ID) const
{
	return _core->_quadEntityManager.getEntity(ID)->getColor();
}

const bool FabiEngine3D::quad_isVisible(const string& ID) const
{
	return _core->_quadEntityManager.getEntity(ID)->isVisible();
}

const bool FabiEngine3D::quad_isCentered(const string& ID) const
{
	return _core->_quadEntityManager.getEntity(ID)->isCentered();
}

const bool FabiEngine3D::quad_hasDiffuseMap(const string& ID) const
{
	return _core->_quadEntityManager.getEntity(ID)->hasDiffuseMap();
}

const bool FabiEngine3D::quad_isWireframed(const string& ID) const
{
	return _core->_quadEntityManager.getEntity(ID)->isWireframed();
}

const bool FabiEngine3D::quad_isMirroredHorizontally(const string& ID) const
{
	return _core->_quadEntityManager.getEntity(ID)->isMirroredHorizonally();
}

const bool FabiEngine3D::quad_isMirroredVertically(const string& ID) const
{
	return _core->_quadEntityManager.getEntity(ID)->isMirroredVertically();
}