#include "engine_interface.hpp"
#include "engine_core.hpp"

const bool EngineInterface::input_isKeyboardHeld(KeyboardKeyType key) const
{
	return _core->getInputHandler()->isKeyboardHeld(key);
}

const bool EngineInterface::input_isKeyboardPressed(KeyboardKeyType key) const
{
	return _core->getInputHandler()->isKeyboardPressed(key);
}

const bool EngineInterface::input_isKeyboardToggled(KeyboardKeyType key) const
{
	return _core->getInputHandler()->isKeyboardToggled(key);
}

const bool EngineInterface::input_isMouseScrolled(MouseWheelType wheel) const
{
	return _core->getInputHandler()->isMouseScrolled(wheel);
}

const bool EngineInterface::input_isMouseHeld(MouseButtonType button) const
{
	return _core->getInputHandler()->isMouseHeld(button);
}

const bool EngineInterface::input_isMousePressed(MouseButtonType button) const
{
	return _core->getInputHandler()->isMousePressed(button);
}

const bool EngineInterface::input_isMouseToggled(MouseButtonType button) const
{
	return _core->getInputHandler()->isMouseToggled(button);
}