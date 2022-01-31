#include "script_interpreter.hpp"

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dRaycastSetter(const string& functionName, const vector<shared_ptr<ScriptValue>>& args, vector<shared_ptr<ScriptValue>>& returnValues)
{
	if(functionName == "fe3d:raycast_enable_terrain_pointing")
	{
		auto types = {SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_fe3d->raycast_isTerrainPointingEnabled())
			{
				_throwScriptError("Tried to enable terrain raycast pointing: already enabled!");
				return true;
			}

			_fe3d->raycast_enableTerrainPointing(args[0]->getDecimal(), args[1]->getDecimal());

			returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:raycast_disable_terrain_pointing")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(!_fe3d->raycast_isTerrainPointingEnabled())
			{
				_throwScriptError("Tried to disable terrain raycast pointing: not enabled!");
				return true;
			}

			_fe3d->raycast_disableTerrainPointing();

			returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
		}
	}
	else
	{
		return false;
	}

	if(_fe3d->server_isRunning())
	{
		_throwScriptError("cannot access `fe3d:raycast` functionality as networking server!");
	}

	return true;
}