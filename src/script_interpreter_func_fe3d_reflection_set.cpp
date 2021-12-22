#include "script_interpreter.hpp"

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dReflectionSetter(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues)
{

	if(functionName == "fe3d:reflection_place")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Temporary values
			auto ID = arguments[0].getString();

			// @ sign not allowed
			if(ID[0] == '@')
			{
				_throwScriptError("new reflection ID (\"" + ID + "\") cannot contain '@'");
				return true;
			}

			// Check if reflection already exists
			if(_fe3d.reflection_isExisting(ID))
			{
				_throwScriptError("reflection with ID \"" + ID + "\" already exists!");
				return true;
			}

			// Create reflection
			_fe3d.reflection_create(ID);
			_fe3d.reflection_setPosition(ID, fvec3(arguments[1].getDecimal(), arguments[2].getDecimal(), arguments[3].getDecimal()));

			// Return
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:reflection_delete")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dReflection(arguments[0].getString()))
			{
				_fe3d.reflection_delete(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:reflection_delete_all")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			// Iterate through reflections
			for(const auto& ID : _fe3d.reflection_getIDs())
			{
				// @ sign not allowed
				if(ID[0] != '@')
				{
					_fe3d.reflection_delete(ID);
				}
			}

			// Return
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:reflection_set_visible")
	{
		auto types = {SVT::STRING, SVT::BOOLEAN};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dReflection(arguments[0].getString()))
			{
				_fe3d.reflection_setVisible(arguments[0].getString(), arguments[1].getBoolean());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:reflection_set_position")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dReflection(arguments[0].getString()))
			{
				_fe3d.reflection_setPosition(arguments[0].getString(),
											 fvec3(arguments[1].getDecimal(), arguments[2].getDecimal(), arguments[3].getDecimal()));
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:reflection_move")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dReflection(arguments[0].getString()))
			{
				_fe3d.reflection_move(arguments[0].getString(),
									  fvec3(arguments[1].getDecimal(), arguments[2].getDecimal(), arguments[3].getDecimal()));
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:reflection_move_to")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dReflection(arguments[0].getString()))
			{
				_fe3d.reflection_moveTo(arguments[0].getString(),
										fvec3(arguments[1].getDecimal(), arguments[2].getDecimal(), arguments[3].getDecimal()), arguments[4].getDecimal());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:reflection_capture")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dReflection(arguments[0].getString()))
			{
				_fe3d.reflection_capture(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else
	{
		return false;
	}

	// Cannot execute when server is running
	if(_fe3d.server_isRunning())
	{
		_throwScriptError("cannot access `fe3d:reflection` functionality as networking server!");
	}

	// Return
	return true;
}