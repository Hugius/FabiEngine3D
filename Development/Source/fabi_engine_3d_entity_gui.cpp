#include "fabi_engine_3d.hpp"
#include "core_engine.hpp"

void FabiEngine3D::guiEntity_deleteAll()
{
	_core->_guiEntityManager.deleteAllEntities();
}

void FabiEngine3D::guiEntity_hideAll()
{
	for (auto& [keyID, entity] : _core->_guiEntityManager.getEntities())
	{
		entity->setVisible(false);
	}
}

void FabiEngine3D::guiEntity_showAll()
{
	for (auto& [keyID, entity] : _core->_guiEntityManager.getEntities())
	{
		entity->setVisible(true);
	}
}

void FabiEngine3D::guiEntity_add(const string& ID, const string& texturePath, Vec2 translation, float rotation, Vec2 scaling, bool isCentered, bool visible)
{
	_core->_guiEntityManager.addGuiEntity(ID, texturePath, translation, rotation, scaling, false, isCentered);
	_core->_guiEntityManager.getEntity(ID)->setVisible(visible);
}

void FabiEngine3D::guiEntity_add(const string& ID, Vec3 color, Vec2 translation, float rotation, Vec2 scaling, bool isCentered, bool visible)
{
	_core->_guiEntityManager.addGuiEntity(ID, color, translation, rotation, scaling, isCentered);
	_core->_guiEntityManager.getEntity(ID)->setVisible(visible);
}

void FabiEngine3D::guiEntity_hide(const string& ID)
{
	_core->_guiEntityManager.getEntity(ID)->setVisible(false);
}

void FabiEngine3D::guiEntity_show(const string& ID)
{
	_core->_guiEntityManager.getEntity(ID)->setVisible(true);
}

void FabiEngine3D::guiEntity_delete(const string& ID)
{
	_core->_guiEntityManager.deleteEntity(ID);
}

void FabiEngine3D::guiEntity_changeTexture(const string& ID, const string& texturePath)
{
	_core->_guiEntityManager.getEntity(ID)->setDiffuseMap(_core->_texLoader.getTexture(texturePath, true, true));
}

bool FabiEngine3D::guiEntity_isExisting(const string& ID)
{
	return _core->_guiEntityManager.isExisting(ID);
}

void FabiEngine3D::guiEntity_setPosition(const string& ID, Vec2 position)
{
	_core->_guiEntityManager.getEntity(ID)->setTranslation(position);
}

void FabiEngine3D::guiEntity_setRotation(const string& ID, float rotation)
{
	_core->_guiEntityManager.getEntity(ID)->setRotation(rotation);
}

void FabiEngine3D::guiEntity_setSize(const string& ID, Vec2 size)
{
	_core->_guiEntityManager.getEntity(ID)->setScaling(size);
}

void FabiEngine3D::guiEntity_move(const string& ID, Vec2 position)
{
	_core->_guiEntityManager.getEntity(ID)->translate(position);
}

void FabiEngine3D::guiEntity_rotate(const string& ID, float rotation)
{
	_core->_guiEntityManager.getEntity(ID)->rotate(rotation);
}

void FabiEngine3D::guiEntity_scale(const string& ID, Vec2 size)
{
	_core->_guiEntityManager.getEntity(ID)->scale(size);
}

void FabiEngine3D::guiEntity_setColor(const string& ID, Vec3 color)
{
	_core->_guiEntityManager.getEntity(ID)->setColor(color);
}

void FabiEngine3D::guiEntity_setAlpha(const string& ID, float alpha)
{
	_core->_guiEntityManager.getEntity(ID)->setAlpha(alpha);
}

void FabiEngine3D::guiEntity_setMinPosition(const string& ID, Vec2 minPos)
{
	_core->_guiEntityManager.getEntity(ID)->setMinPosition(minPos);
}

void FabiEngine3D::guiEntity_setMaxPosition(const string& ID, Vec2 maxPos)
{
	_core->_guiEntityManager.getEntity(ID)->setMaxPosition(maxPos);
}

Vec2 FabiEngine3D::guiEntity_getPosition(const string& ID)
{
	return _core->_guiEntityManager.getEntity(ID)->getTranslation();
}

float FabiEngine3D::guiEntity_getRotation(const string& ID)
{
	return _core->_guiEntityManager.getEntity(ID)->getRotation();
}

float FabiEngine3D::guiEntity_getAlpha(const string& ID)
{
	return _core->_guiEntityManager.getEntity(ID)->getAlpha();
}

vector<string> FabiEngine3D::guiEntity_getAllIDs()
{
	vector<string> IDs;

	for (auto [keyID, entity] : _core->_guiEntityManager.getEntities())
	{
		IDs.push_back(entity->getID());
	}

	return IDs;
}

Vec2 FabiEngine3D::guiEntity_getSize(const string& ID)
{
	return _core->_guiEntityManager.getEntity(ID)->getScaling();
}

Vec2 FabiEngine3D::guiEntity_getMinPosition(const string& ID)
{
	return _core->_guiEntityManager.getEntity(ID)->getMinPosition();
}

Vec2 FabiEngine3D::guiEntity_getMaxPosition(const string& ID)
{
	return _core->_guiEntityManager.getEntity(ID)->getMaxPosition();
}

Vec3 FabiEngine3D::guiEntity_getColor(const string& ID)
{
	return _core->_guiEntityManager.getEntity(ID)->getColor();
}

bool FabiEngine3D::guiEntity_isVisible(const string& ID)
{
	return _core->_guiEntityManager.getEntity(ID)->isVisible();
}

bool FabiEngine3D::guiEntity_isCentered(const string& ID)
{
	return _core->_guiEntityManager.getEntity(ID)->isCentered();
}
