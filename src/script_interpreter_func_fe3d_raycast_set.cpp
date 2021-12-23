#include "script_interpreter.hpp"

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dRaycastSetter(const string& functionName, vector<ScriptValue>& args, vector<ScriptValue>& returnValues)
{
	if(functionName == "fe3d:raycast_enable_terrain_pointing")
	{
		auto types = {SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			_fe3d.raycast_enableTerrainPointing(args[0].getDecimal(), args[1].getDecimal());
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:raycast_disable_terrain_pointing")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			_fe3d.raycast_disableTerrainPointing();
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else
	{
		return false;
	}

	// Cannot execute when server is running
	if(_fe3d.server_isRunning())
	{
		_throwScriptError("cannot access `fe3d:raycast` functionality as networking server!");
	}

	return true;
}