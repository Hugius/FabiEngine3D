#include "script_interpreter.hpp"

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dReflectionGetter(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues)
{
	if(functionName == "fe3d:reflection_is_existing")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// @ sign is reserved
			if(arguments[0].getString()[0] == '@')
			{
				_throwScriptError("ID of requested reflection with ID \"" + arguments[0].getString() + "\" cannot start with '@'");
				return true;
			}

			// Check if existing
			auto result = _fe3d.reflection_isExisting(arguments[0].getString());
			returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
		}
	}
	else if(functionName == "fe3d:reflection_find_ids")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// @ sign is reserved
			if(arguments[0].getString()[0] == '@')
			{
				_throwScriptError("ID of requested reflection with ID \"" + arguments[0].getString() + "\" cannot start with '@'");
				return true;
			}

			// Find full entity IDs based on sub ID
			for(const auto& ID : _fe3d.reflection_getIDs())
			{
				// If substring matches
				if(arguments[0].getString() == ID.substr(0, arguments[0].getString().size()))
				{
					// @ sign is reserved
					if(ID[0] != '@')
					{
						returnValues.push_back(ScriptValue(_fe3d, SVT::STRING, ID));
					}
				}
			}
		}
	}
	else if(functionName == "fe3d:reflection_get_ids")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			auto result = _fe3d.reflection_getIDs();

			// Iterate through reflections
			for(const auto& ID : result)
			{
				// @ sign is reserved
				if(ID[0] != '@')
				{
					returnValues.push_back(ScriptValue(_fe3d, SVT::STRING, ID));
				}
			}
		}
	}
	else if(functionName == "fe3d:reflection_is_visible")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dReflection(arguments[0].getString()))
			{
				auto result = _fe3d.reflection_isVisible(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:reflection_get_position_x")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dReflection(arguments[0].getString()))
			{
				auto result = _fe3d.reflection_getPosition(arguments[0].getString()).x;
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:reflection_get_position_y")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dReflection(arguments[0].getString()))
			{
				auto result = _fe3d.reflection_getPosition(arguments[0].getString()).y;
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:reflection_get_position_z")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dReflection(arguments[0].getString()))
			{
				auto result = _fe3d.reflection_getPosition(arguments[0].getString()).z;
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
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