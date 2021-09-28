#include "script_interpreter.hpp"

bool ScriptInterpreter::_executeFe3dReflectionSetterFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues)
{
	// Determine type of function
	if (functionName == "fe3d:reflection_place")
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Temporary values
			auto ID = arguments[0].getString();

			// New reflection ID cannot start with '@'
			if (ID.front() == '@')
			{
				_throwScriptError("new reflection ID (\"" + ID + "\") cannot start with '@'");
				return true;
			}

			// Check if reflection already exists
			if (_fe3d.reflectionEntity_isExisting(ID))
			{
				_throwScriptError("reflection with ID \"" + ID + "\" already exists!");
				return true;
			}

			// Create reflection
			_fe3d.reflectionEntity_create(ID);
			_fe3d.reflectionEntity_setPosition(ID, Vec3(arguments[1].getDecimal(), arguments[2].getDecimal(), arguments[3].getDecimal()));

			// Return
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
		}
	}
	else if (functionName == "fe3d:reflection_delete")
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing reflection ID
			if (_validateFe3dReflectionEntity(arguments[0].getString()))
			{
				_fe3d.reflectionEntity_delete(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:reflection_set_visible")
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::BOOLEAN };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing reflection ID
			if (_validateFe3dReflectionEntity(arguments[0].getString()))
			{
				_fe3d.reflectionEntity_setVisible(arguments[0].getString(), arguments[1].getBoolean());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:reflection_set_position")
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing reflection ID
			if (_validateFe3dReflectionEntity(arguments[0].getString()))
			{
				_fe3d.reflectionEntity_setPosition(arguments[0].getString(),
					Vec3(arguments[1].getDecimal(), arguments[2].getDecimal(), arguments[3].getDecimal()));
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:reflection_move")
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing reflection ID
			if (_validateFe3dReflectionEntity(arguments[0].getString()))
			{
				_fe3d.reflectionEntity_move(arguments[0].getString(),
					Vec3(arguments[1].getDecimal(), arguments[2].getDecimal(), arguments[3].getDecimal()));
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:reflection_move_to")
	{
		auto types = { ScriptValueType::STRING, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing reflection ID
			if (_validateFe3dReflectionEntity(arguments[0].getString()))
			{
				_fe3d.reflectionEntity_moveTo(arguments[0].getString(),
					Vec3(arguments[1].getDecimal(), arguments[2].getDecimal(), arguments[3].getDecimal()), arguments[4].getDecimal());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:reflection_capture")
	{
		auto types = { ScriptValueType::STRING };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing reflection ID
			if (_validateFe3dReflectionEntity(arguments[0].getString()))
			{
				_fe3d.reflectionEntity_capture(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			}
		}
	}
	else
	{
		return false;
	}

	// Cannot execute reflection functionality when server is running
	if (_fe3d.networkServer_isRunning())
	{
		_throwScriptError("cannot access `fe3d:reflection` functionality as a networking server!");
	}

	// Return
	return true;
}