#include "script_interpreter.hpp"

using SVT = ScriptValueType;

bool ScriptInterpreter::_executeFe3dLightGetterFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues)
{
	// Determine type of function
	if (functionName == "fe3d:light_is_existing")
	{
		auto types = { SVT::STRING };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Check if existing
			auto result = _fe3d.lightEntity_isExisting(arguments[0].getString());
			returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
		}
	}
	else if (functionName == "fe3d:light_find_ids")
	{
		auto types = { SVT::STRING };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Cannot request a preview entity
			if (arguments[0].getString().front() == '@')
			{
				_throwScriptError("ID of requested light with ID \"" + arguments[0].getString() + "\" cannot start with '@'");
				return true;
			}

			// Find full lightEntity IDs based on part ID
			for (const auto& ID : _fe3d.lightEntity_getAllIDs())
			{
				// If substring matches
				if (arguments[0].getString() == ID.substr(0, arguments[0].getString().size()))
				{
					// Only non-preview lights
					if (ID.front() != '@')
					{
						returnValues.push_back(ScriptValue(_fe3d, SVT::STRING, ID));
					}
				}
			}
		}
	}
	else if (functionName == "fe3d:light_get_all_ids")
	{
		// Validate arguments
		if (_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto result = _fe3d.lightEntity_getAllIDs();

			// For every light
			for (const auto& ID : result)
			{
				// Only non-preview lights
				if (ID.front() != '@')
				{
					returnValues.push_back(ScriptValue(_fe3d, SVT::STRING, ID));
				}
			}
		}
	}
	else if (functionName == "fe3d:light_is_visible")
	{
		auto types = { SVT::STRING };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing light ID
			if (_validateFe3dLight(arguments[0].getString()))
			{
				auto result = _fe3d.lightEntity_isVisible(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
			}
		}
	}
	else if (functionName == "fe3d:light_get_position")
	{
		auto types = { SVT::STRING };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing light ID
			if (_validateFe3dLight(arguments[0].getString()))
			{
				auto result = _fe3d.lightEntity_getPosition(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::VEC3, result));
			}
		}
	}
	else if (functionName == "fe3d:light_get_color")
	{
		auto types = { SVT::STRING };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing light ID
			if (_validateFe3dLight(arguments[0].getString()))
			{
				auto result = _fe3d.lightEntity_getColor(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::VEC3, result));
			}
		}
	}
	else if (functionName == "fe3d:light_get_intensity")
	{
		auto types = { SVT::STRING };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing light ID
			if (_validateFe3dLight(arguments[0].getString()))
			{
				auto result = _fe3d.lightEntity_getIntensity(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if (functionName == "fe3d:light_get_radius")
	{
		auto types = { SVT::STRING };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing light ID
			if (_validateFe3dLight(arguments[0].getString()))
			{
				auto result = _fe3d.lightEntity_getRadius(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if (functionName == "fe3d:light_is_circle_shape")
	{
		auto types = { SVT::STRING };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing light ID
			if (_validateFe3dLight(arguments[0].getString()))
			{
				auto result = (_fe3d.lightEntity_getShape(arguments[0].getString()) == LightShape::CIRCLE);
				returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
			}
		}
	}
	else if (functionName == "fe3d:light_is_square_shape")
	{
		auto types = { SVT::STRING };

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existing light ID
			if (_validateFe3dLight(arguments[0].getString()))
			{
				auto result = (_fe3d.lightEntity_getShape(arguments[0].getString()) == LightShape::SQUARE);
				returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
			}
		}
	}
	else
	{
		return false;
	}

	// Cannot execute light functionality when server is running
	if (_fe3d.networkServer_isRunning())
	{
		_throwScriptError("cannot access `fe3d:light` functionality as a networking server!");
	}

	// Return
	return true;
}