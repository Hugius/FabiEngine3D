#include "fe3d.hpp"
#include "core_engine.hpp"

void FabiEngine3D::input_setLocked(bool locked)
{
	return _core->_inputHandler.setLocked(locked);
}

const bool FabiEngine3D::input_isKeyDown(InputType key)
{
	return _core->_inputHandler.isKeyDown(key);
}

const bool FabiEngine3D::input_isKeyPressed(InputType key)
{
	return _core->_inputHandler.isKeyPressed(key);
}

const bool FabiEngine3D::input_isMouseDown(InputType button)
{
	return _core->_inputHandler.isMouseDown(button);
}

const bool FabiEngine3D::input_isMousePressed(InputType button)
{
	return _core->_inputHandler.isMousePressed(button);
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