#include "script_interpreter.hpp"
#include "tools.hpp"

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dQuad2dGetter(const string & functionName, const vector<shared_ptr<ScriptValue>> & args, vector<shared_ptr<ScriptValue>> & returnValues)
{
	if(functionName == "fe3d:quad2d_is_existing")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(!_validateFe3dId(args[0]->getString()))
			{
				return true;
			}

			const auto result = _fe3d->quad2d_isExisting(args[0]->getString());

			returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
		}
	}
	else if(functionName == "fe3d:quad2d_get_editor_id")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad2d(args[0]->getString(), false))
			{
				const auto result = _duplicator->getEditorQuad2dId(args[0]->getString()).substr(1);

				returnValues.push_back(make_shared<ScriptValue>(SVT::STRING, result));
			}
		}
	}
	else if(functionName == "fe3d:quad2d_find_ids")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(!_validateFe3dId(args[0]->getString()))
			{
				return true;
			}

			for(const auto & result : _fe3d->quad2d_getIds())
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
	else if(functionName == "fe3d:quad2d_get_ids")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			for(const auto & result : _fe3d->quad2d_getIds())
			{
				if(result[0] != '@')
				{
					returnValues.push_back(make_shared<ScriptValue>(SVT::STRING, result));
				}
			}
		}
	}
	else if(functionName == "fe3d:quad2d_get_min_clip_position_x")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad2d(args[0]->getString(), false))
			{
				const auto result = Tools::convertPositionRelativeFromDisplay(_fe3d->quad2d_getMinClipPosition(args[0]->getString())).x;

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:quad2d_get_min_clip_position_y")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad2d(args[0]->getString(), false))
			{
				const auto result = Tools::convertPositionRelativeFromDisplay(_fe3d->quad2d_getMinClipPosition(args[0]->getString())).y;

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:quad2d_get_max_clip_position_x")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad2d(args[0]->getString(), false))
			{
				const auto result = Tools::convertPositionRelativeFromDisplay(_fe3d->quad2d_getMaxClipPosition(args[0]->getString())).x;

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:quad2d_get_max_clip_position_y")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad2d(args[0]->getString(), false))
			{
				const auto result = Tools::convertPositionRelativeFromDisplay(_fe3d->quad2d_getMaxClipPosition(args[0]->getString())).y;

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:quad2d_is_visible")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad2d(args[0]->getString(), false))
			{
				const auto result = _fe3d->quad2d_isVisible(args[0]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:quad2d_get_position_x")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad2d(args[0]->getString(), false))
			{
				const auto result = Tools::convertPositionRelativeFromDisplay(_fe3d->quad2d_getPosition(args[0]->getString())).x;

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:quad2d_get_position_y")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad2d(args[0]->getString(), false))
			{
				const auto result = Tools::convertPositionRelativeFromDisplay(_fe3d->quad2d_getPosition(args[0]->getString())).y;

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:quad2d_get_rotation")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad2d(args[0]->getString(), false))
			{
				const auto result = _fe3d->quad2d_getRotation(args[0]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:quad2d_get_size_x")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad2d(args[0]->getString(), false))
			{
				const auto result = Tools::convertSizeRelativeFromDisplay(_fe3d->quad2d_getSize(args[0]->getString())).x;

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:quad2d_get_size_y")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad2d(args[0]->getString(), false))
			{
				const auto result = Tools::convertSizeRelativeFromDisplay(_fe3d->quad2d_getSize(args[0]->getString())).y;

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:quad2d_get_color_r")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad2d(args[0]->getString(), false))
			{
				const auto result = _fe3d->quad2d_getColor(args[0]->getString()).r;

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:quad2d_get_color_g")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad2d(args[0]->getString(), false))
			{
				const auto result = _fe3d->quad2d_getColor(args[0]->getString()).g;

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:quad2d_get_color_b")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad2d(args[0]->getString(), false))
			{
				const auto result = _fe3d->quad2d_getColor(args[0]->getString()).b;

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:quad2d_get_opacity")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad2d(args[0]->getString(), false))
			{
				const auto result = _fe3d->quad2d_getOpacity(args[0]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:quad2d_get_lightness")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad2d(args[0]->getString(), false))
			{
				const auto result = _fe3d->quad2d_getLightness(args[0]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:quad2d_get_texture_repeat")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad2d(args[0]->getString(), false))
			{
				const auto result = _fe3d->quad2d_getTextureRepeat(args[0]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::INTEGER, result));
			}
		}
	}
	else if(functionName == "fe3d:quad2d_get_diffuse_map_path")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad2d(args[0]->getString(), false))
			{
				const auto result = _fe3d->quad2d_getDiffuseMapPath(args[0]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:quad2d_has_diffuse_map")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad2d(args[0]->getString(), false))
			{
				const auto result = _fe3d->quad2d_hasDiffuseMap(args[0]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:quad2d_is_horizontally_flipped")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad2d(args[0]->getString(), false))
			{
				const auto result = _fe3d->quad2d_isHorizontallyFlipped(args[0]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:quad2d_is_vertically_flipped")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad2d(args[0]->getString(), false))
			{
				const auto result = _fe3d->quad2d_isVerticallyFlipped(args[0]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:quad2d_get_wireframe_color_r")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad2d(args[0]->getString(), false))
			{
				const auto result = _fe3d->quad2d_getWireframeColor(args[0]->getString()).r;

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:quad2d_get_wireframe_color_g")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad2d(args[0]->getString(), false))
			{
				const auto result = _fe3d->quad2d_getWireframeColor(args[0]->getString()).g;

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:quad2d_get_wireframe_color_b")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad2d(args[0]->getString(), false))
			{
				const auto result = _fe3d->quad2d_getWireframeColor(args[0]->getString()).b;

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:quad2d_is_wireframed")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad2d(args[0]->getString(), false))
			{
				const auto result = _fe3d->quad2d_isWireframed(args[0]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:quad2d_get_uv_multiplier_x")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad2d(args[0]->getString(), false))
			{
				const auto result = _fe3d->quad2d_getUvMultiplier(args[0]->getString()).x;

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:quad2d_get_uv_multiplier_y")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad2d(args[0]->getString(), false))
			{
				const auto result = _fe3d->quad2d_getUvMultiplier(args[0]->getString()).y;

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:quad2d_get_uv_offset_x")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad2d(args[0]->getString(), false))
			{
				const auto result = _fe3d->quad2d_getUvOffset(args[0]->getString()).x;

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:quad2d_get_uv_offset_y")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad2d(args[0]->getString(), false))
			{
				const auto result = _fe3d->quad2d_getUvOffset(args[0]->getString()).y;

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:quad2d_is_animation2d_started")
	{
		const auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation2d(args[0]->getString()) && _validateFe3dQuad2d(args[1]->getString(), false))
			{
				if(!_fe3d->quad2d_isAnimation2dStarted(args[0]->getString(), args[1]->getString()))
				{
					_throwRuntimeError("animation2D is not started");

					return true;
				}

				const auto result = _fe3d->quad2d_isAnimation2dStarted(args[0]->getString(), args[1]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:quad2d_is_animation2d_paused")
	{
		const auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation2d(args[0]->getString()) && _validateFe3dQuad2d(args[1]->getString(), false))
			{
				if(!_fe3d->quad2d_isAnimation2dStarted(args[0]->getString(), args[1]->getString()))
				{
					_throwRuntimeError("animation2D is not started");

					return true;
				}

				const auto result = _fe3d->quad2d_isAnimation2dPaused(args[0]->getString(), args[1]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:quad2d_is_animation2d_autopaused")
	{
		const auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation2d(args[0]->getString()) && _validateFe3dQuad2d(args[1]->getString(), false))
			{
				if(!_fe3d->quad2d_isAnimation2dStarted(args[0]->getString(), args[1]->getString()))
				{
					_throwRuntimeError("animation2D is not started");

					return true;
				}

				const auto result = _fe3d->quad2d_isAnimation2dAutopaused(args[0]->getString(), args[1]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:quad2d_get_animation2d_row_index")
	{
		const auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation2d(args[0]->getString()) && _validateFe3dQuad2d(args[1]->getString(), false))
			{
				if(!_fe3d->quad2d_isAnimation2dStarted(args[0]->getString(), args[1]->getString()))
				{
					_throwRuntimeError("animation2D is not started");

					return true;
				}

				const auto result = _fe3d->quad2d_getAnimation2dRowIndex(args[0]->getString(), args[1]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::INTEGER, result));
			}
		}
	}
	else if(functionName == "fe3d:quad2d_get_animation2d_column_index")
	{
		const auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation2d(args[0]->getString()) && _validateFe3dQuad2d(args[1]->getString(), false))
			{
				if(!_fe3d->quad2d_isAnimation2dStarted(args[0]->getString(), args[1]->getString()))
				{
					_throwRuntimeError("animation2D is not started");

					return true;
				}

				const auto result = _fe3d->quad2d_getAnimation2dColumnIndex(args[0]->getString(), args[1]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::INTEGER, result));
			}
		}
	}
	else if(functionName == "fe3d:quad2d_get_animation2d_play_count")
	{
		const auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation2d(args[0]->getString()) && _validateFe3dQuad2d(args[1]->getString(), false))
			{
				if(!_fe3d->quad2d_isAnimation2dStarted(args[0]->getString(), args[1]->getString()))
				{
					_throwRuntimeError("animation2D is not started");

					return true;
				}

				const auto result = _fe3d->quad2d_getAnimation2dPlayCount(args[0]->getString(), args[1]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::INTEGER, result));
			}
		}
	}
	else if(functionName == "fe3d:quad2d_get_animation2d_interval_multiplier")
	{
		const auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation2d(args[0]->getString()) && _validateFe3dQuad2d(args[1]->getString(), false))
			{
				if(!_fe3d->quad2d_isAnimation2dStarted(args[0]->getString(), args[1]->getString()))
				{
					_throwRuntimeError("animation2D is not started");

					return true;
				}

				const auto result = _fe3d->quad2d_getAnimation2dIntervalMultiplier(args[0]->getString(), args[1]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::INTEGER, result));
			}
		}
	}
	else if(functionName == "fe3d:quad2d_get_animation2d_interval_divider")
	{
		const auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation2d(args[0]->getString()) && _validateFe3dQuad2d(args[1]->getString(), false))
			{
				if(!_fe3d->quad2d_isAnimation2dStarted(args[0]->getString(), args[1]->getString()))
				{
					_throwRuntimeError("animation2D is not started");

					return true;
				}

				const auto result = _fe3d->quad2d_getAnimation2dIntervalDivider(args[0]->getString(), args[1]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::INTEGER, result));
			}
		}
	}
	else if(functionName == "fe3d:quad2d_is_hovered")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad2d(args[0]->getString(), false))
			{
				const auto cursorPosition = Tools::convertToNdc(Tools::getCursorPosition());
				const auto quad2dPosition = _fe3d->quad2d_getPosition(args[0]->getString());
				const auto quad2dSize = _fe3d->quad2d_getSize(args[0]->getString());

				bool result = false;

				if(cursorPosition.x > (quad2dPosition.x - (quad2dSize.x * 0.5f)))
				{
					if(cursorPosition.x < (quad2dPosition.x + (quad2dSize.x * 0.5f)))
					{
						if(cursorPosition.y > (quad2dPosition.y - (quad2dSize.y * 0.5f)))
						{
							if(cursorPosition.y < (quad2dPosition.y + (quad2dSize.y * 0.5f)))
							{
								result = true;
							}
						}
					}
				}

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
		_throwRuntimeError("cannot access `fe3d:quad2d` functionality as a networking server");

		return true;
	}

	return true;
}