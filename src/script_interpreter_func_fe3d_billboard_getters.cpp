#include "script_interpreter.hpp"

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dBillboardGetter(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues)
{
	// Determine type of function
	if(functionName == "fe3d:billboard_is_visible")
	{
		auto types = {SVT::STRING};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dBillboard(arguments[0].getString(), false))
			{
				auto result = _fe3d.billboard_isVisible(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:billboard_get_position_x")
	{
		auto types = {SVT::STRING};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dBillboard(arguments[0].getString(), false))
			{
				auto result = _fe3d.billboard_getPosition(arguments[0].getString()).x;
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:billboard_get_position_y")
	{
		auto types = {SVT::STRING};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dBillboard(arguments[0].getString(), false))
			{
				auto result = _fe3d.billboard_getPosition(arguments[0].getString()).y;
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:billboard_get_position_z")
	{
		auto types = {SVT::STRING};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dBillboard(arguments[0].getString(), false))
			{
				auto result = _fe3d.billboard_getPosition(arguments[0].getString()).z;
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:billboard_get_rotation_x")
	{
		auto types = {SVT::STRING};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dBillboard(arguments[0].getString(), false))
			{
				auto result = _fe3d.billboard_getRotation(arguments[0].getString()).x;
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:billboard_get_rotation_y")
	{
		auto types = {SVT::STRING};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dBillboard(arguments[0].getString(), false))
			{
				auto result = _fe3d.billboard_getRotation(arguments[0].getString()).y;
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:billboard_get_rotation_z")
	{
		auto types = {SVT::STRING};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dBillboard(arguments[0].getString(), false))
			{
				auto result = _fe3d.billboard_getRotation(arguments[0].getString()).z;
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:billboard_get_size_x")
	{
		auto types = {SVT::STRING};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dBillboard(arguments[0].getString(), false))
			{
				auto result = _fe3d.billboard_getSize(arguments[0].getString()).x;
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:billboard_get_size_y")
	{
		auto types = {SVT::STRING};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dBillboard(arguments[0].getString(), false))
			{
				auto result = _fe3d.billboard_getSize(arguments[0].getString()).y;
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:billboard_get_color_r")
	{
		auto types = {SVT::STRING};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dBillboard(arguments[0].getString(), false))
			{
				auto result = _fe3d.billboard_getColor(arguments[0].getString()).r;
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:billboard_get_color_g")
	{
		auto types = {SVT::STRING};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dBillboard(arguments[0].getString(), false))
			{
				auto result = _fe3d.billboard_getColor(arguments[0].getString()).g;
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:billboard_get_color_b")
	{
		auto types = {SVT::STRING};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dBillboard(arguments[0].getString(), false))
			{
				auto result = _fe3d.billboard_getColor(arguments[0].getString()).b;
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:billboard_get_wireframe_color_r")
	{
		auto types = {SVT::STRING};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dBillboard(arguments[0].getString(), false))
			{
				auto result = _fe3d.billboard_getWireframeColor(arguments[0].getString()).r;
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:billboard_get_wireframe_color_g")
	{
		auto types = {SVT::STRING};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dBillboard(arguments[0].getString(), false))
			{
				auto result = _fe3d.billboard_getWireframeColor(arguments[0].getString()).g;
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:billboard_get_wireframe_color_b")
	{
		auto types = {SVT::STRING};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dBillboard(arguments[0].getString(), false))
			{
				auto result = _fe3d.billboard_getWireframeColor(arguments[0].getString()).b;
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:billboard_get_min_height")
	{
		auto types = {SVT::STRING};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dBillboard(arguments[0].getString(), false))
			{
				auto result = _fe3d.billboard_getMinHeight(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:billboard_get_max_height")
	{
		auto types = {SVT::STRING};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dBillboard(arguments[0].getString(), false))
			{
				auto result = _fe3d.billboard_getMaxHeight(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:billboard_get_transparency")
	{
		auto types = {SVT::STRING};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dBillboard(arguments[0].getString(), false))
			{
				auto result = _fe3d.billboard_getTransparency(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:billboard_get_emission_intensity")
	{
		auto types = {SVT::STRING};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dBillboard(arguments[0].getString(), false))
			{
				auto result = _fe3d.billboard_getEmissionIntensity(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:billboard_get_texture_repeat")
	{
		auto types = {SVT::STRING};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dBillboard(arguments[0].getString(), false))
			{
				auto result = _fe3d.billboard_getTextureRepeat(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:billboard_get_lightness")
	{
		auto types = {SVT::STRING};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dBillboard(arguments[0].getString(), false))
			{
				auto result = _fe3d.billboard_getLightness(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:billboard_is_facing_camera_x")
	{
		auto types = {SVT::STRING};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dBillboard(arguments[0].getString(), false))
			{
				auto result = _fe3d.billboard_isFacingCameraX(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:billboard_is_facing_camera_y")
	{
		auto types = {SVT::STRING};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dBillboard(arguments[0].getString(), false))
			{
				auto result = _fe3d.billboard_isFacingCameraY(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:billboard_is_animation_started")
	{
		auto types = {SVT::STRING};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dBillboard(arguments[0].getString(), false))
			{
				auto result = _fe3d.billboard_isSpriteAnimationStarted(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:billboard_is_animation_playing")
	{
		auto types = {SVT::STRING};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dBillboard(arguments[0].getString(), false))
			{
				auto result = _fe3d.billboard_isSpriteAnimationPlaying(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:billboard_is_animation_paused")
	{
		auto types = {SVT::STRING};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dBillboard(arguments[0].getString(), false))
			{
				auto result = _fe3d.billboard_isSpriteAnimationPaused(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:billboard_is_shadowed")
	{
		auto types = {SVT::STRING};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dBillboard(arguments[0].getString(), false))
			{
				auto result = _fe3d.billboard_isShadowed(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:billboard_is_reflected")
	{
		auto types = {SVT::STRING};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dBillboard(arguments[0].getString(), false))
			{
				auto result = _fe3d.billboard_isReflected(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:billboard_is_bright")
	{
		auto types = {SVT::STRING};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dBillboard(arguments[0].getString(), false))
			{
				auto result = _fe3d.billboard_isBright(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:billboard_is_wireframed")
	{
		auto types = {SVT::STRING};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dBillboard(arguments[0].getString(), false))
			{
				auto result = _fe3d.billboard_isWireframed(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:billboard_is_frozen")
	{
		auto types = {SVT::STRING};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dBillboard(arguments[0].getString(), false))
			{
				auto result = _fe3d.billboard_isFrozen(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:billboard_is_textual")
	{
		auto types = {SVT::STRING};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dBillboard(arguments[0].getString(), false))
			{
				auto result = _fe3d.billboard_isTextual(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:billboard_is_existing")
	{
		auto types = {SVT::STRING};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// @ sign is reserved
			if(arguments[0].getString()[0] == '@')
			{
				_throwScriptError("ID of requested billboard with ID \"" + arguments[0].getString() + "\" cannot start with '@'");
				return true;
			}

			// Check if existing
			auto result = _fe3d.billboard_isExisting(arguments[0].getString());
			returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
		}
	}
	else if(functionName == "fe3d:billboard_find_ids")
	{
		auto types = {SVT::STRING};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// @ sign is reserved
			if(arguments[0].getString()[0] == '@')
			{
				_throwScriptError("ID of requested billboard with ID \"" + arguments[0].getString() + "\" cannot start with '@'");
				return true;
			}

			// Find full entity IDs based on part ID
			for(const auto& ID : _fe3d.billboard_getAllIDs())
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
	else if(functionName == "fe3d:billboard_get_all_ids")
	{
		// Validate arguments
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			auto result = _fe3d.billboard_getAllIDs();

			// Iterate through billboards
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
	else if(functionName == "fe3d:billboard_get_text_content")
	{
		auto types = {SVT::STRING};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dBillboard(arguments[0].getString(), false))
			{
				// Check if billboard is not of type text
				if(!_fe3d.billboard_isTextual(arguments[0].getString()))
				{
					_throwScriptError("billboard with ID \"" + arguments[0].getString() + "\" is not of type text!");
					return true;
				}

				// Return text content
				auto result = _fe3d.billboard_getTextContent(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::STRING, result));
			}
		}
	}
	else
	{
		return false;
	}

	// Cannot execute billboard functionality when server is running
	if(_fe3d.server_isRunning())
	{
		_throwScriptError("cannot access `fe3d:billboard` functionality as networking server!");
	}

	// Return
	return true;
}