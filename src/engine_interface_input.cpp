#include "engine_interface.hpp"
#include "engine_core.hpp"

const bool EngineInterface::input_isKeyboardHeld(KeyboardKey key) const
{
	return _core->getInputHandler()->isKeyboardHeld(key);
}

const bool EngineInterface::input_isKeyboardPressed(KeyboardKey key) const
{
	return _core->getInputHandler()->isKeyboardPressed(key);
}

const bool EngineInterface::input_isKeyboardToggled(KeyboardKey key) const
{
	return _core->getInputHandler()->isKeyboardToggled(key);
}

const bool EngineInterface::input_isMouseScrolled(MouseWheel wheel) const
{
	return _core->getInputHandler()->isMouseScrolled(wheel);
}

const bool EngineInterface::input_isMouseHeld(MouseButton button) const
{
	return _core->getInputHandler()->isMouseHeld(button);
}

const bool EngineInterface::input_isMousePressed(MouseButton button) const
{
	return _core->getInputHandler()->isMousePressed(button);
}

const bool EngineInterface::input_isMouseToggled(MouseButton button) const
{
	return _core->getInputHandler()->isMouseToggled(button);
}