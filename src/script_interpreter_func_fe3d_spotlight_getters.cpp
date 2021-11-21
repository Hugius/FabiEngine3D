#include "script_interpreter.hpp"

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dSpotlightGetterFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues)
{
	// Determine type of function
	if(functionName == "fe3d:spotlight_is_existing")
	{
		auto types = { SVT::STRING };

		// Validate arguments
		if(_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// @ sign is reserved
			if(arguments[0].getString().front() == '@')
			{
				_throwScriptError("ID of requested spotlight with ID \"" + arguments[0].getString() + "\" cannot start with '@'");
				return true;
			}

			// Check if existing
			auto result = _fe3d.spotlight_isExisting(arguments[0].getString());
			returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
		}
	}
	else if(functionName == "fe3d:spotlight_find_ids")
	{
		auto types = { SVT::STRING };

		// Validate arguments
		if(_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// @ sign is reserved
			if(arguments[0].getString().front() == '@')
			{
				_throwScriptError("ID of requested spotlight with ID \"" + arguments[0].getString() + "\" cannot start with '@'");
				return true;
			}

			// Find full entity IDs based on part ID
			for(const auto& ID : _fe3d.spotlight_getAllIDs())
			{
				// If substring matches
				if(arguments[0].getString() == ID.substr(0, arguments[0].getString().size()))
				{
					// @ sign is reserved
					if(ID.front() != '@')
					{
						returnValues.push_back(ScriptValue(_fe3d, SVT::STRING, ID));
					}
				}
			}
		}
	}
	else if(functionName == "fe3d:spotlight_get_all_ids")
	{
		// Validate arguments
		if(_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto result = _fe3d.spotlight_getAllIDs();

			// For every spotlight
			for(const auto& ID : result)
			{
				// @ sign is reserved
				if(ID.front() != '@')
				{
					returnValues.push_back(ScriptValue(_fe3d, SVT::STRING, ID));
				}
			}
		}
	}
	else if(functionName == "fe3d:spotlight_is_visible")
	{
		auto types = { SVT::STRING };

		// Validate arguments
		if(_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dSpotlight(arguments[0].getString()))
			{
				auto result = _fe3d.spotlight_isVisible(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:spotlight_get_position")
	{
		auto types = { SVT::STRING };

		// Validate arguments
		if(_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dSpotlight(arguments[0].getString()))
			{
				auto result = _fe3d.spotlight_getPosition(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::VEC3, result));
			}
		}
	}
	else if(functionName == "fe3d:spotlight_get_color")
	{
		auto types = { SVT::STRING };

		// Validate arguments
		if(_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dSpotlight(arguments[0].getString()))
			{
				auto result = _fe3d.spotlight_getColor(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::VEC3, result));
			}
		}
	}
	else if(functionName == "fe3d:spotlight_get_yaw")
	{
		auto types = { SVT::STRING };

		// Validate arguments
		if(_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dSpotlight(arguments[0].getString()))
			{
				auto result = _fe3d.spotlight_getYaw(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:spotlight_get_pitch")
	{
		auto types = { SVT::STRING };

		// Validate arguments
		if(_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dSpotlight(arguments[0].getString()))
			{
				auto result = _fe3d.spotlight_getPitch(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:spotlight_get_intensity")
	{
		auto types = { SVT::STRING };

		// Validate arguments
		if(_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dSpotlight(arguments[0].getString()))
			{
				auto result = _fe3d.spotlight_getIntensity(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:spotlight_get_angle")
	{
		auto types = { SVT::STRING };

		// Validate arguments
		if(_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dSpotlight(arguments[0].getString()))
			{
				auto result = _fe3d.spotlight_getAngle(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:spotlight_get_distance")
	{
		auto types = { SVT::STRING };

		// Validate arguments
		if(_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dSpotlight(arguments[0].getString()))
			{
				auto result = _fe3d.spotlight_getDistance(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else
	{
		return false;
	}

	// Cannot execute spotlight functionality when server is running
	if(_fe3d.server_isRunning())
	{
		_throwScriptError("cannot access `fe3d:spotlight` functionality as a networking server!");
	}

	// Return
	return true;
}