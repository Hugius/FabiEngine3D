#include "script_interpreter.hpp"

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dQuadGetter(const string& functionName, vector<ScriptValue>& args, vector<ScriptValue>& returnValues)
{
	if(functionName == "fe3d:quad_is_existing")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(!_validateFe3dID(args[0].getString()))
			{
				return true;
			}

			const auto result = _fe3d->quad_isExisting(args[0].getString());
			returnValues.push_back(ScriptValue(SVT::BOOLEAN, result));
		}
	}
	else if(functionName == "fe3d:quad_find_ids")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(!_validateFe3dID(args[0].getString()))
			{
				return true;
			}

			for(const auto& ID : _fe3d->quad_getIDs())
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
	else if(functionName == "fe3d:quad_get_ids")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->quad_getIDs();

			for(const auto& ID : result)
			{
				if(ID[0] != '@')
				{
					returnValues.push_back(ScriptValue(SVT::STRING, ID));
				}
			}
		}
	}
	else if(functionName == "fe3d:quad_is_visible")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad(args[0].getString(), false))
			{
				const auto result = _fe3d->quad_isVisible(args[0].getString());
				returnValues.push_back(ScriptValue(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:quad_get_position_x")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad(args[0].getString(), false))
			{
				const auto result = _convertPositionFromViewport(_fe3d->quad_getPosition(args[0].getString())).x;
				returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:quad_get_position_y")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad(args[0].getString(), false))
			{
				const auto result = _convertPositionFromViewport(_fe3d->quad_getPosition(args[0].getString())).y;
				returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:quad_get_rotation")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad(args[0].getString(), false))
			{
				const auto result = _fe3d->quad_getRotation(args[0].getString());
				returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:quad_get_size_x")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad(args[0].getString(), false))
			{
				const auto result = _convertSizeFromViewport(_fe3d->quad_getSize(args[0].getString())).x;
				returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:quad_get_size_y")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad(args[0].getString(), false))
			{
				const auto result = _convertSizeFromViewport(_fe3d->quad_getSize(args[0].getString())).y;
				returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:quad_get_color_r")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad(args[0].getString(), false))
			{
				const auto result = _fe3d->quad_getColor(args[0].getString()).r;
				returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:quad_get_color_g")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad(args[0].getString(), false))
			{
				const auto result = _fe3d->quad_getColor(args[0].getString()).g;
				returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:quad_get_color_b")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad(args[0].getString(), false))
			{
				const auto result = _fe3d->quad_getColor(args[0].getString()).b;
				returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:quad_get_transparency")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad(args[0].getString(), false))
			{
				const auto result = _fe3d->quad_getTransparency(args[0].getString());
				returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:quad_get_diffuse_map_path")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad(args[0].getString(), false))
			{
				const auto result = _fe3d->quad_getDiffuseMapPath(args[0].getString());
				returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:quad_has_diffuse_map")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad(args[0].getString(), false))
			{
				const auto result = _fe3d->quad_hasDiffuseMap(args[0].getString());
				returnValues.push_back(ScriptValue(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:quad_is_horizontally_mirrored")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad(args[0].getString(), false))
			{
				const auto result = _fe3d->quad_isHorizontallyMirrored(args[0].getString());
				returnValues.push_back(ScriptValue(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:quad_is_vertically_mirrored")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad(args[0].getString(), false))
			{
				const auto result = _fe3d->quad_isVerticallyMirrored(args[0].getString());
				returnValues.push_back(ScriptValue(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:quad_get_wireframe_color_r")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad(args[0].getString(), false))
			{
				const auto result = _fe3d->quad_getWireframeColor(args[0].getString()).r;
				returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:quad_get_wireframe_color_g")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad(args[0].getString(), false))
			{
				const auto result = _fe3d->quad_getWireframeColor(args[0].getString()).g;
				returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:quad_get_wireframe_color_b")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad(args[0].getString(), false))
			{
				const auto result = _fe3d->quad_getWireframeColor(args[0].getString()).b;
				returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:quad_is_wireframed")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad(args[0].getString(), false))
			{
				const auto result = _fe3d->quad_isWireframed(args[0].getString());
				returnValues.push_back(ScriptValue(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:quad_get_uv_multiplier_x")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad(args[0].getString(), false))
			{
				const auto result = _fe3d->quad_getUvMultiplier(args[0].getString()).x;
				returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:quad_get_uv_multiplier_y")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad(args[0].getString(), false))
			{
				const auto result = _fe3d->quad_getUvMultiplier(args[0].getString()).y;
				returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:quad_get_uv_offset_x")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad(args[0].getString(), false))
			{
				const auto result = _fe3d->quad_getUvOffset(args[0].getString()).x;
				returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:quad_get_uv_offset_y")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad(args[0].getString(), false))
			{
				const auto result = _fe3d->quad_getUvOffset(args[0].getString()).y;
				returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
			}
		}
	}
	else
	{
		return false;
	}

	if(_fe3d->server_isRunning())
	{
		_throwScriptError("cannot access `fe3d:quad` functionality as networking server!");
	}

	return true;
}