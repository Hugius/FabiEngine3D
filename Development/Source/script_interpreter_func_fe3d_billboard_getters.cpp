#include "script_interpreter.hpp"

using SVT = ScriptValueType;

bool ScriptInterpreter::_executeFe3dBillboardGetterFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues)
{
	// Determine type of function
	if(functionName == "fe3d:billboard_is_visible")
	{
		auto types = { SVT::STRING };

		// Validate arguments
		if(_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dBillboard(arguments[0].getString()))
			{
				auto result = _fe3d.billboardEntity_isVisible(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:billboard_get_position")
	{
		auto types = { SVT::STRING };

		// Validate arguments
		if(_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dBillboard(arguments[0].getString()))
			{
				auto result = _fe3d.billboardEntity_getPosition(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::VEC3, result));
			}
		}
	}
	else if(functionName == "fe3d:billboard_get_rotation")
	{
		auto types = { SVT::STRING };

		// Validate arguments
		if(_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dBillboard(arguments[0].getString()))
			{
				auto result = _fe3d.billboardEntity_getRotation(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::VEC3, result));
			}
		}
	}
	else if(functionName == "fe3d:billboard_get_width")
	{
		auto types = { SVT::STRING };

		// Validate arguments
		if(_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dBillboard(arguments[0].getString()))
			{
				auto result = _fe3d.billboardEntity_getSize(arguments[0].getString()).x;
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:billboard_get_height")
	{
		auto types = { SVT::STRING };

		// Validate arguments
		if(_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dBillboard(arguments[0].getString()))
			{
				auto result = _fe3d.billboardEntity_getSize(arguments[0].getString()).y;
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:billboard_get_color")
	{
		auto types = { SVT::STRING };

		// Validate arguments
		if(_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dBillboard(arguments[0].getString()))
			{
				auto result = _fe3d.billboardEntity_getColor(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::VEC3, result));
			}
		}
	}
	else if(functionName == "fe3d:billboard_get_min_height")
	{
		auto types = { SVT::STRING };

		// Validate arguments
		if(_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dBillboard(arguments[0].getString()))
			{
				auto result = _fe3d.billboardEntity_getMinHeight(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:billboard_get_max_height")
	{
		auto types = { SVT::STRING };

		// Validate arguments
		if(_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dBillboard(arguments[0].getString()))
			{
				auto result = _fe3d.billboardEntity_getMaxHeight(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:billboard_get_alpha")
	{
		auto types = { SVT::STRING };

		// Validate arguments
		if(_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dBillboard(arguments[0].getString()))
			{
				auto result = _fe3d.billboardEntity_getAlpha(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:billboard_get_lightness")
	{
		auto types = { SVT::STRING };

		// Validate arguments
		if(_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dBillboard(arguments[0].getString()))
			{
				auto result = _fe3d.billboardEntity_getLightness(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:billboard_is_facing_camera_x")
	{
		auto types = { SVT::STRING };

		// Validate arguments
		if(_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dBillboard(arguments[0].getString()))
			{
				auto result = _fe3d.billboardEntity_isFacingCameraX(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:billboard_is_facing_camera_y")
	{
		auto types = { SVT::STRING };

		// Validate arguments
		if(_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dBillboard(arguments[0].getString()))
			{
				auto result = _fe3d.billboardEntity_isFacingCameraY(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:billboard_is_animation_started")
	{
		auto types = { SVT::STRING };

		// Validate arguments
		if(_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dBillboard(arguments[0].getString()))
			{
				auto result = _fe3d.billboardEntity_isSpriteAnimationStarted(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:billboard_is_animation_playing")
	{
		auto types = { SVT::STRING };

		// Validate arguments
		if(_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dBillboard(arguments[0].getString()))
			{
				auto result = _fe3d.billboardEntity_isSpriteAnimationPlaying(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:billboard_is_animation_paused")
	{
		auto types = { SVT::STRING };

		// Validate arguments
		if(_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dBillboard(arguments[0].getString()))
			{
				auto result = _fe3d.billboardEntity_isSpriteAnimationPaused(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:billboard_is_existing")
	{
		auto types = { SVT::STRING };

		// Validate arguments
		if(_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// @ sign is reserved
			if(arguments[0].getString().front() == '@')
			{
				_throwScriptError("ID of requested billboard with ID \"" + arguments[0].getString() + "\" cannot start with '@'");
				return true;
			}

			// Check if existing
			auto result = _fe3d.billboardEntity_isExisting(arguments[0].getString());
			returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
		}
	}
	else if(functionName == "fe3d:billboard_find_ids")
	{
		auto types = { SVT::STRING };

		// Validate arguments
		if(_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// @ sign is reserved
			if(arguments[0].getString().front() == '@')
			{
				_throwScriptError("ID of requested billboard with ID \"" + arguments[0].getString() + "\" cannot start with '@'");
				return true;
			}

			// Find full entity IDs based on part ID
			for(const auto& ID : _fe3d.billboardEntity_getAllIDs())
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
	else if(functionName == "fe3d:billboard_get_all_ids")
	{
		// Validate arguments
		if(_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto result = _fe3d.billboardEntity_getAllIDs();

			// For every billboard
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
	else if(functionName == "fe3d:billboard_get_text")
	{
		auto types = { SVT::STRING };

		// Validate arguments
		if(_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dBillboard(arguments[0].getString()))
			{
				// Check if billboard is not of type text
				if(!_fe3d.billboardEntity_isText(arguments[0].getString()))
				{
					_throwScriptError("billboard with ID \"" + arguments[0].getString() + "\" is not of type text!");
					return true;
				}
				else
				{
					auto result = _fe3d.billboardEntity_getTextContent(arguments[0].getString());
					returnValues.push_back(ScriptValue(_fe3d, SVT::STRING, result));
				}
			}
		}
	}
	else
	{
		return false;
	}

	// Cannot execute billboard functionality when server is running
	if(_fe3d.networkServer_isRunning())
	{
		_throwScriptError("cannot access `fe3d:billboard` functionality as a networking server!");
	}

	// Return
	return true;
}