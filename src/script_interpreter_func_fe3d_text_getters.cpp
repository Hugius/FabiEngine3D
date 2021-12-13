#include "script_interpreter.hpp"

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dTextGetter(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues)
{
	if(functionName == "fe3d:text_is_existing")
	{
		auto types = {SVT::STRING};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// @ sign is reserved
			if(arguments[0].getString()[0] == '@')
			{
				_throwScriptError("ID of requested text with ID \"" + arguments[0].getString() + "\" cannot start with '@'");
				return true;
			}

			// Check if existing
			auto result = _fe3d.text_isExisting(arguments[0].getString());
			returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
		}
	}
	else if(functionName == "fe3d:text_find_ids")
	{
		auto types = {SVT::STRING};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// @ sign is reserved
			if(arguments[0].getString()[0] == '@')
			{
				_throwScriptError("ID of requested text with ID \"" + arguments[0].getString() + "\" cannot start with '@'");
				return true;
			}

			// Find full entity IDs based on sub ID
			for(const auto& ID : _fe3d.text_getAllIDs())
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
	else if(functionName == "fe3d:text_get_all_ids")
	{
		// Validate arguments
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			auto result = _fe3d.text_getAllIDs();

			// Iterate through texts
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
	else if(functionName == "fe3d:text_is_visible")
	{
		auto types = {SVT::STRING};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dText(arguments[0].getString()))
			{
				auto result = _fe3d.text_isVisible(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:text_get_position_x")
	{
		auto types = {SVT::STRING};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dText(arguments[0].getString()))
			{
				auto result = _fe3d.text_getPosition(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, _convertGuiPositionFromViewport(result).x));
			}
		}
	}
	else if(functionName == "fe3d:text_get_position_y")
	{
		auto types = {SVT::STRING};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dText(arguments[0].getString()))
			{
				auto result = _fe3d.text_getPosition(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, _convertGuiPositionFromViewport(result).y));
			}
		}
	}
	else if(functionName == "fe3d:text_get_rotation")
	{
		auto types = {SVT::STRING};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dText(arguments[0].getString()))
			{
				auto result = _fe3d.text_getRotation(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:text_get_width")
	{
		auto types = {SVT::STRING};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dText(arguments[0].getString()))
			{
				auto result = _fe3d.text_getSize(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, _convertGuiSizeFromViewport(result).x));
			}
		}
	}
	else if(functionName == "fe3d:text_get_height")
	{
		auto types = {SVT::STRING};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dText(arguments[0].getString()))
			{
				auto result = _fe3d.text_getSize(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, _convertGuiSizeFromViewport(result).y));
			}
		}
	}
	else if(functionName == "fe3d:text_get_color_r")
	{
		auto types = {SVT::STRING};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dText(arguments[0].getString()))
			{
				auto result = _fe3d.text_getColor(arguments[0].getString()).r;
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:text_get_color_g")
	{
		auto types = {SVT::STRING};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dText(arguments[0].getString()))
			{
				auto result = _fe3d.text_getColor(arguments[0].getString()).g;
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:text_get_color_b")
	{
		auto types = {SVT::STRING};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dText(arguments[0].getString()))
			{
				auto result = _fe3d.text_getColor(arguments[0].getString()).b;
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:text_get_content")
	{
		auto types = {SVT::STRING};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dText(arguments[0].getString()))
			{
				auto result = _fe3d.text_getContent(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::STRING, result));
			}
		}
	}
	else if(functionName == "fe3d:text_get_transparency")
	{
		auto types = {SVT::STRING};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dText(arguments[0].getString()))
			{
				auto result = _fe3d.text_getTransparency(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else
	{
		return false;
	}

	// Cannot execute text functionality when server is running
	if(_fe3d.server_isRunning())
	{
		_throwScriptError("cannot access `fe3d:text` functionality as networking server!");
	}

	// Return
	return true;
}