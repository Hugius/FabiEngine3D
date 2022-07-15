#include "script_interpreter.hpp"
#include "tools.hpp"

using std::clamp;

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dQuad2dSetter(const string & functionName, const vector<shared_ptr<ScriptValue>> & args, vector<shared_ptr<ScriptValue>> & returnValues)
{
	if(functionName == "fe3d:quad2d_place")
	{
		const auto types = {SVT::STRING, SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(!_validateFe3dId(args[0]->getString()))
			{
				return true;
			}

			if(_fe3d->quad2d_isExisting(args[0]->getString()))
			{
				_throwRuntimeError("quad2D already exists");

				return true;
			}

			if(_validateFe3dQuad2d(args[1]->getString(), true))
			{
				_duplicator->copyEditorQuad2d(args[0]->getString(), ("@" + args[1]->getString()));

				_fe3d->quad2d_setPosition(args[0]->getString(), Tools::convertPositionRelativeToDisplay(fvec2(args[2]->getDecimal(), args[3]->getDecimal())));
				_fe3d->quad2d_setSize(args[0]->getString(), Tools::convertSizeRelativeToDisplay(fvec2(args[4]->getDecimal(), args[5]->getDecimal())));
				_fe3d->quad2d_setMinClipPosition(args[0]->getString(), Tools::convertPositionRelativeToDisplay(fvec2(-1.0f)));
				_fe3d->quad2d_setMaxClipPosition(args[0]->getString(), Tools::convertPositionRelativeToDisplay(fvec2(1.0f)));

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:quad2d_delete")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad2d(args[0]->getString(), false))
			{
				_duplicator->deleteCopiedQuad2d(args[0]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:quad2d_delete_all")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			for(const auto & quad2dId : _fe3d->quad2d_getIds())
			{
				if(quad2dId[0] != '@')
				{
					_duplicator->deleteCopiedQuad2d(quad2dId);
				}
			}

			returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:quad2d_set_min_clip_position")
	{
		const auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad2d(args[0]->getString(), false))
			{
				_fe3d->quad2d_setMinClipPosition(args[0]->getString(), Tools::convertPositionRelativeToDisplay(fvec2(clamp(args[1]->getDecimal(), -1.0f, 1.0f), clamp(args[2]->getDecimal(), -1.0f, 1.0f))));

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:quad2d_set_max_clip_position")
	{
		const auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad2d(args[0]->getString(), false))
			{
				_fe3d->quad2d_setMaxClipPosition(args[0]->getString(), Tools::convertPositionRelativeToDisplay(fvec2(clamp(args[1]->getDecimal(), -1.0f, 1.0f), clamp(args[2]->getDecimal(), -1.0f, 1.0f))));

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:quad2d_set_visible")
	{
		const auto types = {SVT::STRING, SVT::BOOLEAN};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad2d(args[0]->getString(), false))
			{
				_fe3d->quad2d_setVisible(args[0]->getString(), args[1]->getBoolean());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:quad2d_set_diffuse_map")
	{
		const auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad2d(args[0]->getString(), false))
			{
				_fe3d->quad2d_setDiffuseMap(args[0]->getString(), args[1]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:quad2d_set_position")
	{
		const auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad2d(args[0]->getString(), false))
			{
				_fe3d->quad2d_setPosition(args[0]->getString(), Tools::convertPositionRelativeToDisplay(fvec2(args[1]->getDecimal(), args[2]->getDecimal())));
				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:quad2d_move")
	{
		const auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad2d(args[0]->getString(), false))
			{
				_fe3d->quad2d_move(args[0]->getString(), Tools::convertSizeRelativeToDisplay(fvec2(args[1]->getDecimal(), args[2]->getDecimal())));

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:quad2d_move_to")
	{
		const auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad2d(args[0]->getString(), false))
			{
				auto speed = Tools::convertSizeRelativeToDisplay(fvec2(args[3]->getDecimal(), args[3]->getDecimal()));

				_fe3d->quad2d_moveTo(args[0]->getString(), Tools::convertPositionRelativeToDisplay(fvec2(args[1]->getDecimal(), args[2]->getDecimal())), ((speed.x + speed.y) * 0.5f));

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:quad2d_set_rotation")
	{
		const auto types = {SVT::STRING, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad2d(args[0]->getString(), false))
			{
				_fe3d->quad2d_setRotation(args[0]->getString(), args[1]->getDecimal());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:quad2d_rotate")
	{
		const auto types = {SVT::STRING, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad2d(args[0]->getString(), false))
			{
				_fe3d->quad2d_rotate(args[0]->getString(), args[1]->getDecimal());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:quad2d_rotate_to")
	{
		const auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad2d(args[0]->getString(), false))
			{
				_fe3d->quad2d_rotateTo(args[0]->getString(), args[1]->getDecimal(), args[2]->getDecimal());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:quad2d_set_size")
	{
		const auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad2d(args[0]->getString(), false))
			{
				_fe3d->quad2d_setSize(args[0]->getString(), Tools::convertSizeRelativeToDisplay(fvec2(args[1]->getDecimal(), args[2]->getDecimal())));

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:quad2d_scale")
	{
		const auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad2d(args[0]->getString(), false))
			{
				_fe3d->quad2d_scale(args[0]->getString(), Tools::convertSizeRelativeToDisplay(fvec2(args[1]->getDecimal(), args[2]->getDecimal())));

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:quad2d_scale_to")
	{
		const auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad2d(args[0]->getString(), false))
			{
				auto speed = Tools::convertSizeRelativeToDisplay(fvec2(args[3]->getDecimal(), args[3]->getDecimal()));

				_fe3d->quad2d_scaleTo(args[0]->getString(), Tools::convertSizeRelativeToDisplay(fvec2(args[1]->getDecimal(), args[2]->getDecimal())), ((speed.x + speed.y) * 0.5f));

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:quad2d_set_color")
	{
		const auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad2d(args[0]->getString(), false))
			{
				_fe3d->quad2d_setColor(args[0]->getString(), fvec3(args[1]->getDecimal(), args[2]->getDecimal(), args[3]->getDecimal()));

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:quad2d_set_wireframe_color")
	{
		const auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad2d(args[0]->getString(), false))
			{
				_fe3d->quad2d_setWireframeColor(args[0]->getString(), fvec3(args[1]->getDecimal(), args[2]->getDecimal(), args[3]->getDecimal()));

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:quad2d_set_opacity")
	{
		const auto types = {SVT::STRING, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad2d(args[0]->getString(), false))
			{
				_fe3d->quad2d_setOpacity(args[0]->getString(), args[1]->getDecimal());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:quad2d_set_lightness")
	{
		const auto types = {SVT::STRING, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad2d(args[0]->getString(), false))
			{
				_fe3d->quad2d_setLightness(args[0]->getString(), args[1]->getDecimal());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:quad2d_set_texture_repeat")
	{
		const auto types = {SVT::STRING, SVT::INTEGER};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad2d(args[0]->getString(), false))
			{
				_fe3d->quad2d_setTextureRepeat(args[0]->getString(), args[1]->getInteger());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:quad2d_set_wireframed")
	{
		const auto types = {SVT::STRING, SVT::BOOLEAN};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad2d(args[0]->getString(), false))
			{
				_fe3d->quad2d_setWireframed(args[0]->getString(), args[1]->getBoolean());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:quad2d_set_horizontally_flipped")
	{
		const auto types = {SVT::STRING, SVT::BOOLEAN};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad2d(args[0]->getString(), false))
			{
				_fe3d->quad2d_setHorizontallyFlipped(args[0]->getString(), args[1]->getBoolean());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:quad2d_set_vertically_flipped")
	{
		const auto types = {SVT::STRING, SVT::BOOLEAN};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad2d(args[0]->getString(), false))
			{
				_fe3d->quad2d_setVerticallyFlipped(args[0]->getString(), args[1]->getBoolean());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:quad2d_set_uv_multiplier")
	{
		const auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad2d(args[0]->getString(), false))
			{
				_fe3d->quad2d_setUvMultiplier(args[0]->getString(), fvec2(args[1]->getDecimal(), args[2]->getDecimal()));

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:quad2d_set_uv_offset")
	{
		const auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad2d(args[0]->getString(), false))
			{
				_fe3d->quad2d_setUvOffset(args[0]->getString(), fvec2(args[1]->getDecimal(), args[2]->getDecimal()));

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:quad2d_start_animation2d")
	{
		const auto types = {SVT::STRING, SVT::STRING, SVT::INTEGER};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation2d(args[0]->getString()) && _validateFe3dQuad2d(args[1]->getString(), false))
			{
				if(_fe3d->quad2d_isAnimation2dStarted(args[0]->getString(), args[1]->getString()))
				{
					_throwRuntimeError("animation2D is already started");

					return true;
				}

				if(args[2]->getInteger() < -1)
				{
					_throwRuntimeError("play count is invalid");

					return true;
				}

				_fe3d->quad2d_startAnimation2d(args[0]->getString(), args[1]->getString(), args[2]->getInteger());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:quad2d_pause_animation2d")
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

				if(_fe3d->quad2d_isAnimation2dPaused(args[0]->getString(), args[1]->getString()))
				{
					_throwRuntimeError("animation2D already paused");

					return true;
				}

				_fe3d->quad2d_pauseAnimation2d(args[0]->getString(), args[1]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:quad2d_autopause_animation2d")
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

				if(_fe3d->quad2d_isAnimation2dPaused(args[0]->getString(), args[1]->getString()))
				{
					_throwRuntimeError("animation2D already paused");

					return true;
				}

				_fe3d->quad2d_autopauseAnimation2d(args[0]->getString(), args[1]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:quad2d_resume_animation2d")
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

				if(!_fe3d->quad2d_isAnimation2dPaused(args[0]->getString(), args[1]->getString()))
				{
					_throwRuntimeError("animation2D not paused");

					return true;
				}

				_fe3d->quad2d_resumeAnimation2d(args[0]->getString(), args[1]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:quad2d_stop_animation2d")
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

				_fe3d->quad2d_stopAnimation2d(args[0]->getString(), args[1]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:quad2d_set_animation2d_row_index")
	{
		const auto types = {SVT::STRING, SVT::STRING, SVT::INTEGER};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation2d(args[0]->getString()) && _validateFe3dQuad2d(args[1]->getString(), false))
			{
				if(!_fe3d->quad2d_isAnimation2dStarted(args[0]->getString(), args[1]->getString()))
				{
					_throwRuntimeError("animation2D is not started");

					return true;
				}

				_fe3d->quad2d_setAnimation2dRowIndex(args[0]->getString(), args[1]->getString(), args[1]->getInteger());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:quad2d_set_animation2d_column_index")
	{
		const auto types = {SVT::STRING, SVT::STRING, SVT::INTEGER};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation2d(args[0]->getString()) && _validateFe3dQuad2d(args[1]->getString(), false))
			{
				if(!_fe3d->quad2d_isAnimation2dStarted(args[0]->getString(), args[1]->getString()))
				{
					_throwRuntimeError("animation2D is not started");

					return true;
				}

				_fe3d->quad2d_setAnimation2dColumnIndex(args[0]->getString(), args[1]->getString(), args[1]->getInteger());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:quad2d_set_animation2d_interval_multiplier")
	{
		const auto types = {SVT::STRING, SVT::STRING, SVT::INTEGER};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation2d(args[0]->getString()) && _validateFe3dQuad2d(args[1]->getString(), false))
			{
				if(!_fe3d->quad2d_isAnimation2dStarted(args[0]->getString(), args[1]->getString()))
				{
					_throwRuntimeError("animation2D is not started");

					return true;
				}

				_fe3d->quad2d_setAnimation2dIntervalMultiplier(args[0]->getString(), args[1]->getString(), args[1]->getInteger());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:quad2d_set_animation2d_interval_divider")
	{
		const auto types = {SVT::STRING, SVT::STRING, SVT::INTEGER};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation2d(args[0]->getString()) && _validateFe3dQuad2d(args[1]->getString(), false))
			{
				if(!_fe3d->quad2d_isAnimation2dStarted(args[0]->getString(), args[1]->getString()))
				{
					_throwRuntimeError("animation2D is not started");

					return true;
				}

				_fe3d->quad2d_setAnimation2dIntervalDivider(args[0]->getString(), args[1]->getString(), args[1]->getInteger());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
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