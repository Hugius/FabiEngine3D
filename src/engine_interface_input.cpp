#include "engine_interface.hpp"
#include "engine_core.hpp"

void EngineInterface::input_setLocked(bool value)
{
	return _core->getInputHandler()->setLocked(value);
}

const bool EngineInterface::input_isKeyDown(InputType key) const
{
	return _core->getInputHandler()->isKeyDown(key);
}

const bool EngineInterface::input_isKeyPressed(InputType key) const
{
	return _core->getInputHandler()->isKeyPressed(key);
}

const bool EngineInterface::input_isMouseDown(InputType button) const
{
	return _core->getInputHandler()->isMouseDown(button);
}

const bool EngineInterface::input_isMousePressed(InputType button) const
{
	return _core->getInputHandler()->isMousePressed(button);
}

const int EngineInterface::input_getMouseWheelX() const
{
	return _core->getInputHandler()->getMouseWheelX();
}

const int EngineInterface::input_getMouseWheelY() const
{
	return _core->getInputHandler()->getMouseWheelY();
}

const bool EngineInterface::input_isLocked() const
{
	return _core->getInputHandler()->isLocked();
}