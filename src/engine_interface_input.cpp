#include "engine_interface.hpp"
#include "engine_core.hpp"

const bool EngineInterface::input_isKeyDown(InputType key) const
{
	return _core->getInputHandler()->isKeyboardKeyHeld(key);
}

const bool EngineInterface::input_isKeyPressed(InputType key) const
{
	return _core->getInputHandler()->isKeyboardKeyPressed(key);
}

const bool EngineInterface::input_isMouseDown(InputType button) const
{
	return _core->getInputHandler()->isMouseButtonHeld(button);
}

const bool EngineInterface::input_isMousePressed(InputType button) const
{
	return _core->getInputHandler()->isMouseButtonPressed(button);
}

const int EngineInterface::input_getMouseWheelX() const
{
	return _core->getInputHandler()->getHorizontalMouseWheel();
}

const int EngineInterface::input_getMouseWheelY() const
{
	return _core->getInputHandler()->getVerticalMouseWheel();
}