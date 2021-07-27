#include "fabi_engine_3d.hpp"
#include "core_engine.hpp"

void FabiEngine3D::input_setLocked(bool locked)
{
	return _core->_inputHandler.setLocked(locked);
}

const bool FabiEngine3D::input_isKeyDown(InputType keyName)
{
	return _core->_inputHandler.isKeyDown(keyName);
}

const bool FabiEngine3D::input_isKeyPressed(InputType keyName)
{
	return _core->_inputHandler.isKeyPressed(keyName);
}

const bool FabiEngine3D::input_isMouseDown(InputType mouseButton)
{
	return _core->_inputHandler.isMouseDown(mouseButton);
}

const bool FabiEngine3D::input_isMousePressed(InputType mouseButton)
{
	return _core->_inputHandler.isMousePressed(mouseButton);
}

const int FabiEngine3D::input_getMouseWheelX()
{
	return _core->_inputHandler.getMouseWheelX();
}

const int FabiEngine3D::input_getMouseWheelY()
{
	return _core->_inputHandler.getMouseWheelY();
}

const bool FabiEngine3D::input_isLocked()
{
	return _core->_inputHandler.isLocked();
}