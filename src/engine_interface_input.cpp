#include "engine_interface.hpp"
#include "engine_core.hpp"

const bool EngineInterface::input_isKeyboardHeld(KeyType key) const
{
	return _core->getInputHandler()->isKeyboardHeld(key);
}

const bool EngineInterface::input_isKeyboardPressed(KeyType key) const
{
	return _core->getInputHandler()->isKeyboardPressed(key);
}

const bool EngineInterface::input_isKeyboardToggled(KeyType key) const
{
	return _core->getInputHandler()->isKeyboardToggled(key);
}

const bool EngineInterface::input_isMouseHeld(ButtonType button) const
{
	return _core->getInputHandler()->isMouseHeld(button);
}

const bool EngineInterface::input_isMousePressed(ButtonType button) const
{
	return _core->getInputHandler()->isMousePressed(button);
}

const bool EngineInterface::input_isMouseToggled(ButtonType button) const
{
	return _core->getInputHandler()->isMouseToggled(button);
}

const int EngineInterface::input_getMouseWheelX() const
{
	return _core->getInputHandler()->getHorizontalMouseWheel();
}

const int EngineInterface::input_getMouseWheelY() const
{
	return _core->getInputHandler()->getVerticalMouseWheel();
}