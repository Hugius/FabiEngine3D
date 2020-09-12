#include "script_action.hpp"

ScriptAction::ScriptAction(FabiEngine3D& fe3d, ScriptActionType actionType) :
	_fe3d(fe3d),
	_actionType(actionType)
{

}

const ScriptActionType ScriptAction::getType()
{
	return _actionType;
}