#include "fabi_engine_3d.hpp"
#include "core_engine.hpp"

void FabiEngine3D::input_setLocked(bool locked)
{
	return _core->_inputHandler.setLocked(locked);
}

void FabiEngine3D::input_clearKeyToggles()
{
	_core->_inputHandler.clearKeyToggles();
}

void FabiEngine3D::input_clearMouseToggles()
{
	_core->_inputHandler.clearMouseToggles();
}

void FabiEngine3D::input_setKeyTogglingLocked(bool locked)
{
	return _core->_inputHandler.setKeyTogglingLocked(locked);
}

void FabiEngine3D::input_setMouseTogglingLocked(bool locked)
{
	return _core->_inputHandler.setMouseTogglingLocked(locked);
}

bool FabiEngine3D::input_getKeyDown(InputType keyName)
{
	return _core->_inputHandler.getKeyDown(keyName);
}

bool FabiEngine3D::input_getKeyPressed(InputType keyName)
{
	return _core->_inputHandler.getKeyPressed(keyName);
}

bool FabiEngine3D::input_getKeyToggled(InputType keyName)
{
	return _core->_inputHandler.getKeyToggled(keyName);
}

bool FabiEngine3D::input_getMouseDown(InputType mouseButton)
{
	return _core->_inputHandler.getMouseDown(mouseButton);
}

bool FabiEngine3D::input_getMousePressed(InputType mouseButton)
{
	return _core->_inputHandler.getMousePressed(mouseButton);
}

bool FabiEngine3D::input_getMouseToggled(InputType mouseButton)
{
	return _core->_inputHandler.getMouseToggled(mouseButton);
}

int FabiEngine3D::input_getMouseWheelX()
{
	return _core->_inputHandler.getMouseWheelX();
}

int FabiEngine3D::input_getMouseWheelY()
{
	return _core->_inputHandler.getMouseWheelY();
}