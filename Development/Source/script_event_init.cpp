#include "script_event_init.hpp"

bool ScriptEventInit::isTriggered()
{
    if (!_isAlreadyTriggered)
    {
        _isAlreadyTriggered = true;
        return true;
    }

    return false;
}

void ScriptEventInit::reset()
{
    _isAlreadyTriggered = false;
}