#include "script_event_initialization.hpp"

bool ScriptEventInitialization::isTriggered()
{
    if (!_isAlreadyTriggered)
    {
        _isAlreadyTriggered = true;
        return true;
    }

    return false;
}

void ScriptEventInitialization::reset()
{
    _isAlreadyTriggered = false;
}