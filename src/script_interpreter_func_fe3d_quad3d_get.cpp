#include "script_interpreter.hpp"

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dQuad3dGetter(const string & functionName, const vector<shared_ptr<ScriptValue>> & args, vector<shared_ptr<ScriptValue>> & returnValues)
{
	if(functionName == "fe3d:quad3d_is_visible")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad3d(args[0]->getString(), false))
			{
				const auto result = _fe3d->quad3d_isVisible(args[0]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:quad3d_get_position_x")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad3d(args[0]->getString(), false))
			{
				const auto result = _fe3d->quad3d_getPosition(args[0]->getString()).x;

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:quad3d_get_position_y")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad3d(args[0]->getString(), false))
			{
				const auto result = _fe3d->quad3d_getPosition(args[0]->getString()).y;

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:quad3d_get_position_z")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad3d(args[0]->getString(), false))
			{
				const auto result = _fe3d->quad3d_getPosition(args[0]->getString()).z;

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:quad3d_get_rotation_x")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad3d(args[0]->getString(), false))
			{
				const auto result = _fe3d->quad3d_getRotation(args[0]->getString()).x;

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:quad3d_get_rotation_y")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad3d(args[0]->getString(), false))
			{
				const auto result = _fe3d->quad3d_getRotation(args[0]->getString()).y;

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:quad3d_get_rotation_z")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad3d(args[0]->getString(), false))
			{
				const auto result = _fe3d->quad3d_getRotation(args[0]->getString()).z;

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:quad3d_get_size_x")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad3d(args[0]->getString(), false))
			{
				const auto result = _fe3d->quad3d_getSize(args[0]->getString()).x;

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:quad3d_get_size_y")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad3d(args[0]->getString(), false))
			{
				const auto result = _fe3d->quad3d_getSize(args[0]->getString()).y;

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:quad3d_get_color_r")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad3d(args[0]->getString(), false))
			{
				const auto result = _fe3d->quad3d_getColor(args[0]->getString()).r;

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:quad3d_get_color_g")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad3d(args[0]->getString(), false))
			{
				const auto result = _fe3d->quad3d_getColor(args[0]->getString()).g;

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:quad3d_get_color_b")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad3d(args[0]->getString(), false))
			{
				const auto result = _fe3d->quad3d_getColor(args[0]->getString()).b;

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:quad3d_get_wireframe_color_r")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad3d(args[0]->getString(), false))
			{
				const auto result = _fe3d->quad3d_getWireframeColor(args[0]->getString()).r;

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:quad3d_get_wireframe_color_g")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad3d(args[0]->getString(), false))
			{
				const auto result = _fe3d->quad3d_getWireframeColor(args[0]->getString()).g;

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:quad3d_get_wireframe_color_b")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad3d(args[0]->getString(), false))
			{
				const auto result = _fe3d->quad3d_getWireframeColor(args[0]->getString()).b;

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:quad3d_is_horizontally_flipped")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad3d(args[0]->getString(), false))
			{
				const auto result = _fe3d->quad3d_isHorizontallyFlipped(args[0]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:quad3d_is_vertically_flipped")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad3d(args[0]->getString(), false))
			{
				const auto result = _fe3d->quad3d_isVerticallyFlipped(args[0]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:quad3d_get_min_clip_position_x")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad3d(args[0]->getString(), false))
			{
				const auto result = _fe3d->quad3d_getMinClipPosition(args[0]->getString()).x;

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:quad3d_get_min_clip_position_y")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad3d(args[0]->getString(), false))
			{
				const auto result = _fe3d->quad3d_getMinClipPosition(args[0]->getString()).y;

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:quad3d_get_min_clip_position_z")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad3d(args[0]->getString(), false))
			{
				const auto result = _fe3d->quad3d_getMinClipPosition(args[0]->getString()).z;

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:quad3d_get_max_clip_position_x")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad3d(args[0]->getString(), false))
			{
				const auto result = _fe3d->quad3d_getMaxClipPosition(args[0]->getString()).x;

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:quad3d_get_max_clip_position_y")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad3d(args[0]->getString(), false))
			{
				const auto result = _fe3d->quad3d_getMaxClipPosition(args[0]->getString()).y;

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:quad3d_get_max_clip_position_z")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad3d(args[0]->getString(), false))
			{
				const auto result = _fe3d->quad3d_getMaxClipPosition(args[0]->getString()).z;

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:quad3d_get_opacity")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad3d(args[0]->getString(), false))
			{
				const auto result = _fe3d->quad3d_getOpacity(args[0]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:quad3d_get_emission_intensity")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad3d(args[0]->getString(), false))
			{
				const auto result = _fe3d->quad3d_getEmissionIntensity(args[0]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:quad3d_get_texture_repeat")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad3d(args[0]->getString(), false))
			{
				const auto result = _fe3d->quad3d_getTextureRepeat(args[0]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::INTEGER, result));
			}
		}
	}
	else if(functionName == "fe3d:quad3d_get_lightness")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad3d(args[0]->getString(), false))
			{
				const auto result = _fe3d->quad3d_getLightness(args[0]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:quad3d_is_facing_camera_horizontally")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad3d(args[0]->getString(), false))
			{
				const auto result = _fe3d->quad3d_isFacingCameraHorizontally(args[0]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:quad3d_is_facing_camera_vertically")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad3d(args[0]->getString(), false))
			{
				const auto result = _fe3d->quad3d_isFacingCameraVertically(args[0]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:quad3d_is_shadowed")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad3d(args[0]->getString(), false))
			{
				const auto result = _fe3d->quad3d_isShadowed(args[0]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:quad3d_is_reflected")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad3d(args[0]->getString(), false))
			{
				const auto result = _fe3d->quad3d_isReflected(args[0]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:quad3d_is_refracted")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad3d(args[0]->getString(), false))
			{
				const auto result = _fe3d->quad3d_isRefracted(args[0]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:quad3d_is_bright")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad3d(args[0]->getString(), false))
			{
				const auto result = _fe3d->quad3d_isBright(args[0]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:quad3d_is_wireframed")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad3d(args[0]->getString(), false))
			{
				const auto result = _fe3d->quad3d_isWireframed(args[0]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:quad3d_is_existing")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(!_validateFe3dId(args[0]->getString()))
			{
				return true;
			}

			const auto result = _fe3d->quad3d_isExisting(args[0]->getString());

			returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
		}
	}
	else if(functionName == "fe3d:quad3d_find_ids")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(!_validateFe3dId(args[0]->getString()))
			{
				return true;
			}

			for(const auto & result : _fe3d->quad3d_getIds())
			{
				if(result[0] != '@')
				{
					if(args[0]->getString() == result.substr(0, args[0]->getString().size()))
					{
						returnValues.push_back(make_shared<ScriptValue>(SVT::STRING, result));
					}
				}
			}
		}
	}
	else if(functionName == "fe3d:quad3d_get_ids")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			for(const auto & result : _fe3d->quad3d_getIds())
			{
				if(result[0] != '@')
				{
					returnValues.push_back(make_shared<ScriptValue>(SVT::STRING, result));
				}
			}
		}
	}
	else if(functionName == "fe3d:quad3d_get_diffuse_map_path")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad3d(args[0]->getString(), false))
			{
				const auto result = _fe3d->quad3d_getDiffuseMapPath(args[0]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::STRING, result));
			}
		}
	}
	else if(functionName == "fe3d:quad3d_get_emission_map_path")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad3d(args[0]->getString(), false))
			{
				const auto result = _fe3d->quad3d_getEmissionMapPath(args[0]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::STRING, result));
			}
		}
	}
	else if(functionName == "fe3d:quad3d_has_diffuse_map")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad3d(args[0]->getString(), false))
			{
				const auto result = _fe3d->quad3d_hasDiffuseMap(args[0]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:quad3d_has_emission_map")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad3d(args[0]->getString(), false))
			{
				const auto result = _fe3d->quad3d_hasEmissionMap(args[0]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:quad3d_get_uv_multiplier_x")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad3d(args[0]->getString(), false))
			{
				const auto result = _fe3d->quad3d_getUvMultiplier(args[0]->getString()).x;
				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:quad3d_get_uv_multiplier_y")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad3d(args[0]->getString(), false))
			{
				const auto result = _fe3d->quad3d_getUvMultiplier(args[0]->getString()).y;

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:quad3d_get_uv_offset_x")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad3d(args[0]->getString(), false))
			{
				const auto result = _fe3d->quad3d_getUvOffset(args[0]->getString()).x;

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:quad3d_get_uv_offset_y")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad3d(args[0]->getString(), false))
			{
				const auto result = _fe3d->quad3d_getUvOffset(args[0]->getString()).y;

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:quad3d_get_min_alpha")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad3d(args[0]->getString(), false))
			{
				const auto result = _fe3d->quad3d_getMinAlpha(args[0]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:quad3d_is_animation2d_started")
	{
		const auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation2d(args[0]->getString()) && _validateFe3dQuad3d(args[1]->getString(), false))
			{
				const auto result = _fe3d->quad3d_isAnimation2dStarted(args[0]->getString(), args[1]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:quad3d_is_animation2d_paused")
	{
		const auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation2d(args[0]->getString()) && _validateFe3dQuad3d(args[1]->getString(), false))
			{
				if(!_fe3d->quad3d_isAnimation2dStarted(args[0]->getString(), args[1]->getString()))
				{
					_throwRuntimeError("animation2D is not started");

					return true;
				}

				const auto result = _fe3d->quad3d_isAnimation2dPaused(args[0]->getString(), args[1]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:quad3d_is_animation2d_autopaused")
	{
		const auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation2d(args[0]->getString()) && _validateFe3dQuad3d(args[1]->getString(), false))
			{
				if(!_fe3d->quad3d_isAnimation2dStarted(args[0]->getString(), args[1]->getString()))
				{
					_throwRuntimeError("animation2D is not started");

					return true;
				}

				const auto result = _fe3d->quad3d_isAnimation2dAutopaused(args[0]->getString(), args[1]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:quad3d_get_animation2d_row_index")
	{
		const auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation2d(args[0]->getString()) && _validateFe3dQuad3d(args[1]->getString(), false))
			{
				if(!_fe3d->quad3d_isAnimation2dStarted(args[0]->getString(), args[1]->getString()))
				{
					_throwRuntimeError("animation2D is not started");

					return true;
				}

				const auto result = _fe3d->quad3d_getAnimation2dRowIndex(args[0]->getString(), args[1]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::INTEGER, result));
			}
		}
	}
	else if(functionName == "fe3d:quad3d_get_animation2d_column_index")
	{
		const auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation2d(args[0]->getString()) && _validateFe3dQuad3d(args[1]->getString(), false))
			{
				if(!_fe3d->quad3d_isAnimation2dStarted(args[0]->getString(), args[1]->getString()))
				{
					_throwRuntimeError("animation2D is not started");

					return true;
				}

				const auto result = _fe3d->quad3d_getAnimation2dColumnIndex(args[0]->getString(), args[1]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::INTEGER, result));
			}
		}
	}
	else if(functionName == "fe3d:quad3d_get_animation2d_play_count")
	{
		const auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation2d(args[0]->getString()) && _validateFe3dQuad3d(args[1]->getString(), false))
			{
				if(!_fe3d->quad3d_isAnimation2dStarted(args[0]->getString(), args[1]->getString()))
				{
					_throwRuntimeError("animation2D is not started");

					return true;
				}

				const auto result = _fe3d->quad3d_getAnimation2dPlayCount(args[0]->getString(), args[1]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::INTEGER, result));
			}
		}
	}
	else if(functionName == "fe3d:quad3d_get_animation2d_interval_multiplier")
	{
		const auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation2d(args[0]->getString()) && _validateFe3dQuad3d(args[1]->getString(), false))
			{
				if(!_fe3d->quad3d_isAnimation2dStarted(args[0]->getString(), args[1]->getString()))
				{
					_throwRuntimeError("animation2D is not started");

					return true;
				}

				const auto result = _fe3d->quad3d_getAnimation2dIntervalMultiplier(args[0]->getString(), args[1]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::INTEGER, result));
			}
		}
	}
	else if(functionName == "fe3d:quad3d_get_animation2d_interval_divider")
	{
		const auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation2d(args[0]->getString()) && _validateFe3dQuad3d(args[1]->getString(), false))
			{
				if(!_fe3d->quad3d_isAnimation2dStarted(args[0]->getString(), args[1]->getString()))
				{
					_throwRuntimeError("animation2D is not started");

					return true;
				}

				const auto result = _fe3d->quad3d_getAnimation2dIntervalDivider(args[0]->getString(), args[1]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::INTEGER, result));
			}
		}
	}
	else if(functionName == "fe3d:quad3d_get_rotation_order")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad3d(args[0]->getString(), false))
			{
				const auto rotationOrder = _fe3d->quad3d_getRotationOrder(args[0]->getString());

				switch(rotationOrder)
				{
					case DirectionOrderType::XYZ:
					{
						const auto result = "XYZ";

						returnValues.push_back(make_shared<ScriptValue>(SVT::STRING, result));

						break;
					}
					case DirectionOrderType::XZY:
					{
						const auto result = "XZY";

						returnValues.push_back(make_shared<ScriptValue>(SVT::STRING, result));

						break;
					}
					case DirectionOrderType::YXZ:
					{
						const auto result = "YXZ";

						returnValues.push_back(make_shared<ScriptValue>(SVT::STRING, result));

						break;
					}
					case DirectionOrderType::YZX:
					{
						const auto result = "YZX";

						returnValues.push_back(make_shared<ScriptValue>(SVT::STRING, result));

						break;
					}
					case DirectionOrderType::ZXY:
					{
						const auto result = "ZXY";

						returnValues.push_back(make_shared<ScriptValue>(SVT::STRING, result));

						break;
					}
					case DirectionOrderType::ZYX:
					{
						const auto result = "ZYX";

						returnValues.push_back(make_shared<ScriptValue>(SVT::STRING, result));

						break;
					}
				}
			}
		}
	}
	else if(functionName == "fe3d:quad3d_is_aabb_visible")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAabb(args[0]->getString(), false))
			{
				const auto aabbIds = _fe3d->quad3d_getChildAabbIds(args[0]->getString());

				if(aabbIds.empty())
				{
					_throwRuntimeError("quad3D has no bound AABBs");

					return true;
				}

				const auto result = _fe3d->aabb_isVisible(aabbIds[0]);

				returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:quad3d_is_aabb_collision_responsive")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAabb(args[0]->getString(), false))
			{
				const auto aabbIds = _fe3d->quad3d_getChildAabbIds(args[0]->getString());

				if(aabbIds.empty())
				{
					_throwRuntimeError("quad3D has no bound AABBs");

					return true;
				}

				const auto result = _fe3d->aabb_isCollisionResponsive(aabbIds[0]);

				returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:quad3d_is_aabb_raycast_responsive")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAabb(args[0]->getString(), false))
			{
				const auto aabbIds = _fe3d->quad3d_getChildAabbIds(args[0]->getString());

				if(aabbIds.empty())
				{
					_throwRuntimeError("quad3D has no bound AABBs");

					return true;
				}

				const auto result = _fe3d->aabb_isRaycastResponsive(aabbIds[0]);

				returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
			}
		}
	}
	else
	{
		return false;
	}

	if(_fe3d->server_isRunning())
	{
		_throwRuntimeError("cannot access `fe3d:quad3d` functionality as a networking server");

		return true;
	}

	return true;
}