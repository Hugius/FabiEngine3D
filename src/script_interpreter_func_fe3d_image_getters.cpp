#include "script_interpreter.hpp"

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dImageGetterFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues)
{
	// Determine type of function
	if(functionName == "fe3d:image_is_existing")
	{
		auto types = { SVT::STRING };

		// Validate arguments
		if(_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// @ sign is reserved
			if(arguments[0].getString().front() == '@')
			{
				_throwScriptError("ID of requested image with ID \"" + arguments[0].getString() + "\" cannot start with '@'");
				return true;
			}

			// Check if existing
			auto result = _fe3d.image_isExisting(arguments[0].getString());
			returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
		}
	}
	else if(functionName == "fe3d:image_find_ids")
	{
		auto types = { SVT::STRING };

		// Validate arguments
		if(_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// @ sign is reserved
			if(arguments[0].getString().front() == '@')
			{
				_throwScriptError("ID of requested image with ID \"" + arguments[0].getString() + "\" cannot start with '@'");
				return true;
			}

			// Find full entity IDs based on part ID
			for(const auto& ID : _fe3d.image_getAllIDs())
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
	else if(functionName == "fe3d:image_get_all_ids")
	{
		// Validate arguments
		if(_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto result = _fe3d.image_getAllIDs();

			// For every image
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
	else if(functionName == "fe3d:image_is_visible")
	{
		auto types = { SVT::STRING };

		// Validate arguments
		if(_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dImage(arguments[0].getString()))
			{
				auto result = _fe3d.image_isVisible(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:image_get_position_x")
	{
		auto types = { SVT::STRING };

		// Validate arguments
		if(_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dImage(arguments[0].getString()))
			{
				auto result = _fe3d.image_getPosition(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, _convertGuiPositionFromViewport(result).x));
			}
		}
	}
	else if(functionName == "fe3d:image_get_position_y")
	{
		auto types = { SVT::STRING };

		// Validate arguments
		if(_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dImage(arguments[0].getString()))
			{
				auto result = _fe3d.image_getPosition(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, _convertGuiPositionFromViewport(result).y));
			}
		}
	}
	else if(functionName == "fe3d:image_get_rotation")
	{
		auto types = { SVT::STRING };

		// Validate arguments
		if(_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dImage(arguments[0].getString()))
			{
				auto result = _fe3d.image_getRotation(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:image_get_width")
	{
		auto types = { SVT::STRING };

		// Validate arguments
		if(_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dImage(arguments[0].getString()))
			{
				auto result = _fe3d.image_getSize(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, _convertGuiSizeFromViewport(result).x));
			}
		}
	}
	else if(functionName == "fe3d:image_get_height")
	{
		auto types = { SVT::STRING };

		// Validate arguments
		if(_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dImage(arguments[0].getString()))
			{
				auto result = _fe3d.image_getSize(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, _convertGuiSizeFromViewport(result).y));
			}
		}
	}
	else if(functionName == "fe3d:image_get_color")
	{
		auto types = { SVT::STRING };

		// Validate arguments
		if(_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dImage(arguments[0].getString()))
			{
				auto result = _fe3d.image_getColor(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::VEC3, result));
			}
		}
	}
	else if(functionName == "fe3d:image_get_transparency")
	{
		auto types = { SVT::STRING };

		// Validate arguments
		if(_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dImage(arguments[0].getString()))
			{
				auto result = _fe3d.image_getTransparency(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:image_is_animation_started")
	{
		auto types = { SVT::STRING };

		// Validate arguments
		if(_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dImage(arguments[0].getString()))
			{
				auto result = _fe3d.image_isSpriteAnimationStarted(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:image_is_animation_playing")
	{
		auto types = { SVT::STRING };

		// Validate arguments
		if(_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dImage(arguments[0].getString()))
			{
				auto result = _fe3d.image_isSpriteAnimationPlaying(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:image_is_animation_paused")
	{
		auto types = { SVT::STRING };

		// Validate arguments
		if(_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dImage(arguments[0].getString()))
			{
				auto result = _fe3d.image_isSpriteAnimationPaused(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:image_is_mirrored_horizontally")
	{
		auto types = { SVT::STRING };

		// Validate arguments
		if(_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dImage(arguments[0].getString()))
			{
				auto result = _fe3d.image_isMirroredHorizontally(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:image_is_mirrored_vertically")
	{
		auto types = { SVT::STRING };

		// Validate arguments
		if(_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dImage(arguments[0].getString()))
			{
				auto result = _fe3d.image_isMirroredVertically(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
			}
		}
	}
	else
	{
		return false;
	}

	// Cannot execute image functionality when server is running
	if(_fe3d.server_isRunning())
	{
		_throwScriptError("cannot access `fe3d:image` functionality as a networking server!");
	}

	// Return
	return true;
}