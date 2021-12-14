#include "fe3d.hpp"
#include "core.hpp"

void FabiEngine3D::input_setLocked(bool value)
{
	return _core->_inputHandler.setLocked(value);
}

const bool FabiEngine3D::input_isKeyDown(InputType key) const
{
	return _core->_inputHandler.isKeyDown(key);
}

const bool FabiEngine3D::input_isKeyPressed(InputType key) const
{
	return _core->_inputHandler.isKeyPressed(key);
}

const bool FabiEngine3D::input_isMouseDown(InputType button) const
{
	return _core->_inputHandler.isMouseDown(button);
}

const bool FabiEngine3D::input_isMousePressed(InputType button) const
{
	return _core->_inputHandler.isMousePressed(button);
}

const int FabiEngine3D::input_getMouseWheelX() const
{
	return _core->_inputHandler.getMouseWheelX();
}

const int FabiEngine3D::input_getMouseWheelY() const
{
	return _core->_inputHandler.getMouseWheelY();
}

const bool FabiEngine3D::input_isLocked() const
{
	return _core->_inputHandler.isLocked();
}