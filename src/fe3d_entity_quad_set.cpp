#include "fe3d.hpp"
#include "core.hpp"

void FabiEngine3D::quad_deleteAll()
{
	_core->_quadEntityManager->deleteEntities();
}

void FabiEngine3D::quad_create(const string& ID, bool isCentered)
{
	_core->_quadEntityManager->createEntity(ID, isCentered);
}

void FabiEngine3D::quad_delete(const string& ID)
{
	_core->_quadEntityManager->deleteEntity(ID);
}

void FabiEngine3D::quad_setVisible(const string& ID, bool value)
{
	_core->_quadEntityManager->getEntity(ID)->setVisible(value);
}

void FabiEngine3D::quad_setDiffuseMap(const string& ID, const string& value)
{
	if(value.empty())
	{
		_core->_quadEntityManager->getEntity(ID)->setDiffuseMap(0);
		_core->_quadEntityManager->getEntity(ID)->setDiffuseMapPath("");
	}
	else
	{
		auto texture = make_shared<TextureBuffer>(_core->_imageLoader->loadImage(value), false);
		_core->_quadEntityManager->getEntity(ID)->setDiffuseMap(texture);
		_core->_quadEntityManager->getEntity(ID)->setDiffuseMapPath(value);
	}
}

void FabiEngine3D::quad_setPosition(const string& ID, fvec2 position)
{
	_core->_quadEntityManager->getEntity(ID)->setPosition(position);
}

void FabiEngine3D::quad_setRotation(const string& ID, float rotation)
{
	_core->_quadEntityManager->getEntity(ID)->setRotation(rotation);
}

void FabiEngine3D::quad_setSize(const string& ID, fvec2 size)
{
	_core->_quadEntityManager->getEntity(ID)->setSize(size);
}

void FabiEngine3D::quad_move(const string& ID, fvec2 position)
{
	_core->_quadEntityManager->getEntity(ID)->move(position);
}

void FabiEngine3D::quad_rotate(const string& ID, float rotation)
{
	_core->_quadEntityManager->getEntity(ID)->rotate(rotation);
}

void FabiEngine3D::quad_scale(const string& ID, fvec2 size)
{
	_core->_quadEntityManager->getEntity(ID)->scale(size);
}

void FabiEngine3D::quad_moveTo(const string& ID, fvec2 target, float speed)
{
	_core->_quadEntityManager->getEntity(ID)->moveTo(target, speed);
}

void FabiEngine3D::quad_rotateTo(const string& ID, float target, float speed)
{
	_core->_quadEntityManager->getEntity(ID)->rotateTo(target, speed);
}

void FabiEngine3D::quad_scaleTo(const string& ID, fvec2 target, float speed)
{
	_core->_quadEntityManager->getEntity(ID)->scaleTo(target, speed);
}

void FabiEngine3D::quad_setColor(const string& ID, fvec3 value)
{
	_core->_quadEntityManager->getEntity(ID)->setColor(value);
}

void FabiEngine3D::quad_setTransparency(const string& ID, float value)
{
	_core->_quadEntityManager->getEntity(ID)->setTransparency(value);
}

void FabiEngine3D::quad_setMinPosition(const string& ID, fvec2 value)
{
	_core->_quadEntityManager->getEntity(ID)->setMinPosition(value);
}

void FabiEngine3D::quad_setMaxPosition(const string& ID, fvec2 value)
{
	_core->_quadEntityManager->getEntity(ID)->setMaxPosition(value);
}

void FabiEngine3D::quad_setWireframed(const string& ID, bool value)
{
	_core->_quadEntityManager->getEntity(ID)->setWireframed(value);
}

void FabiEngine3D::quad_setWireframeColor(const string& ID, fvec3 value)
{
	_core->_quadEntityManager->getEntity(ID)->setWireframeColor(value);
}

void FabiEngine3D::quad_setUvMultiplier(const string& ID, fvec2 value)
{
	_core->_quadEntityManager->getEntity(ID)->setUvMultiplier(value);
}

void FabiEngine3D::quad_setUvOffset(const string& ID, fvec2 value)
{
	_core->_quadEntityManager->getEntity(ID)->setUvOffset(value);
}

void FabiEngine3D::quad_setMirroredHorizontally(const string& ID, bool value)
{
	_core->_quadEntityManager->getEntity(ID)->setMirroredHorizontally(value);
}

void FabiEngine3D::quad_setMirroredVertically(const string& ID, bool value)
{
	_core->_quadEntityManager->getEntity(ID)->setMirroredVertically(value);
}