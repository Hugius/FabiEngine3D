#include "script_interpreter.hpp"

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dBillboardGetter(const string& functionName, vector<ScriptValue>& args, vector<ScriptValue>& returnValues)
{
	if(functionName == "fe3d:billboard_is_visible")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dBillboard(args[0].getString(), false))
			{
				auto result = _fe3d->billboard_isVisible(args[0].getString());
				returnValues.push_back(ScriptValue(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:billboard_get_position_x")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dBillboard(args[0].getString(), false))
			{
				auto result = _fe3d->billboard_getPosition(args[0].getString()).x;
				returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:billboard_get_position_y")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dBillboard(args[0].getString(), false))
			{
				auto result = _fe3d->billboard_getPosition(args[0].getString()).y;
				returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:billboard_get_position_z")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dBillboard(args[0].getString(), false))
			{
				auto result = _fe3d->billboard_getPosition(args[0].getString()).z;
				returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:billboard_get_rotation_x")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dBillboard(args[0].getString(), false))
			{
				auto result = _fe3d->billboard_getRotation(args[0].getString()).x;
				returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:billboard_get_rotation_y")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dBillboard(args[0].getString(), false))
			{
				auto result = _fe3d->billboard_getRotation(args[0].getString()).y;
				returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:billboard_get_rotation_z")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dBillboard(args[0].getString(), false))
			{
				auto result = _fe3d->billboard_getRotation(args[0].getString()).z;
				returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:billboard_get_size_x")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dBillboard(args[0].getString(), false))
			{
				auto result = _fe3d->billboard_getSize(args[0].getString()).x;
				returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:billboard_get_size_y")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dBillboard(args[0].getString(), false))
			{
				auto result = _fe3d->billboard_getSize(args[0].getString()).y;
				returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:billboard_get_color_r")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dBillboard(args[0].getString(), false))
			{
				auto result = _fe3d->billboard_getColor(args[0].getString()).r;
				returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:billboard_get_color_g")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dBillboard(args[0].getString(), false))
			{
				auto result = _fe3d->billboard_getColor(args[0].getString()).g;
				returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:billboard_get_color_b")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dBillboard(args[0].getString(), false))
			{
				auto result = _fe3d->billboard_getColor(args[0].getString()).b;
				returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:billboard_get_wireframe_color_r")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dBillboard(args[0].getString(), false))
			{
				auto result = _fe3d->billboard_getWireframeColor(args[0].getString()).r;
				returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:billboard_get_wireframe_color_g")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dBillboard(args[0].getString(), false))
			{
				auto result = _fe3d->billboard_getWireframeColor(args[0].getString()).g;
				returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:billboard_get_wireframe_color_b")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dBillboard(args[0].getString(), false))
			{
				auto result = _fe3d->billboard_getWireframeColor(args[0].getString()).b;
				returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:billboard_get_min_height")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dBillboard(args[0].getString(), false))
			{
				auto result = _fe3d->billboard_getMinHeight(args[0].getString());
				returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:billboard_get_max_height")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dBillboard(args[0].getString(), false))
			{
				auto result = _fe3d->billboard_getMaxHeight(args[0].getString());
				returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:billboard_get_transparency")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dBillboard(args[0].getString(), false))
			{
				auto result = _fe3d->billboard_getTransparency(args[0].getString());
				returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:billboard_get_emission_intensity")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dBillboard(args[0].getString(), false))
			{
				auto result = _fe3d->billboard_getEmissionIntensity(args[0].getString());
				returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:billboard_get_texture_repeat")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dBillboard(args[0].getString(), false))
			{
				auto result = _fe3d->billboard_getTextureRepeat(args[0].getString());
				returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:billboard_get_lightness")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dBillboard(args[0].getString(), false))
			{
				auto result = _fe3d->billboard_getLightness(args[0].getString());
				returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:billboard_is_facing_camera_x")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dBillboard(args[0].getString(), false))
			{
				auto result = _fe3d->billboard_isFacingCameraX(args[0].getString());
				returnValues.push_back(ScriptValue(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:billboard_is_facing_camera_y")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dBillboard(args[0].getString(), false))
			{
				auto result = _fe3d->billboard_isFacingCameraY(args[0].getString());
				returnValues.push_back(ScriptValue(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:billboard_is_shadowed")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dBillboard(args[0].getString(), false))
			{
				auto result = _fe3d->billboard_isShadowed(args[0].getString());
				returnValues.push_back(ScriptValue(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:billboard_is_reflected")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dBillboard(args[0].getString(), false))
			{
				auto result = _fe3d->billboard_isReflected(args[0].getString());
				returnValues.push_back(ScriptValue(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:billboard_is_bright")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dBillboard(args[0].getString(), false))
			{
				auto result = _fe3d->billboard_isBright(args[0].getString());
				returnValues.push_back(ScriptValue(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:billboard_is_wireframed")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dBillboard(args[0].getString(), false))
			{
				auto result = _fe3d->billboard_isWireframed(args[0].getString());
				returnValues.push_back(ScriptValue(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:billboard_is_frozen")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dBillboard(args[0].getString(), false))
			{
				auto result = _fe3d->billboard_isFrozen(args[0].getString());
				returnValues.push_back(ScriptValue(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:billboard_is_textual")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dBillboard(args[0].getString(), false))
			{
				auto result = _fe3d->billboard_isTextual(args[0].getString());
				returnValues.push_back(ScriptValue(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:billboard_is_existing")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(!_validateFe3dID(args[0].getString()))
			{
				return true;
			}

			auto result = _fe3d->billboard_isExisting(args[0].getString());
			returnValues.push_back(ScriptValue(SVT::BOOLEAN, result));
		}
	}
	else if(functionName == "fe3d:billboard_find_ids")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(!_validateFe3dID(args[0].getString()))
			{
				return true;
			}

			for(const auto& ID : _fe3d->billboard_getIDs())
			{
				if(args[0].getString() == ID.substr(0, args[0].getString().size()))
				{
					if(ID[0] != '@')
					{
						returnValues.push_back(ScriptValue(SVT::STRING, ID));
					}
				}
			}
		}
	}
	else if(functionName == "fe3d:billboard_get_ids")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			auto result = _fe3d->billboard_getIDs();

			for(const auto& ID : result)
			{
				if(ID[0] != '@')
				{
					returnValues.push_back(ScriptValue(SVT::STRING, ID));
				}
			}
		}
	}
	else if(functionName == "fe3d:billboard_get_text_content")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dBillboard(args[0].getString(), false))
			{
				if(!_fe3d->billboard_isTextual(args[0].getString()))
				{
					_throwScriptError("billboard with ID \"" + args[0].getString() + "\" is not of type text!");
					return true;
				}

				auto result = _fe3d->billboard_getTextContent(args[0].getString());
				returnValues.push_back(ScriptValue(SVT::STRING, result));
			}
		}
	}
	else if(functionName == "fe3d:billboard_get_diffuse_map_path")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dBillboard(args[0].getString(), false))
			{
				auto result = _fe3d->billboard_getDiffuseMapPath(args[0].getString());
				returnValues.push_back(ScriptValue(SVT::STRING, result));
			}
		}
	}
	else if(functionName == "fe3d:billboard_get_emission_map_path")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dBillboard(args[0].getString(), false))
			{
				auto result = _fe3d->billboard_getEmissionMapPath(args[0].getString());
				returnValues.push_back(ScriptValue(SVT::STRING, result));
			}
		}
	}
	else if(functionName == "fe3d:billboard_get_font_path")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dBillboard(args[0].getString(), false))
			{
				auto result = _fe3d->billboard_getFontPath(args[0].getString());
				returnValues.push_back(ScriptValue(SVT::STRING, result));
			}
		}
	}
	else
	{
		return false;
	}

	if(_fe3d->server_isRunning())
	{
		_throwScriptError("cannot access `fe3d:billboard` functionality as networking server!");
	}

	return true;
}