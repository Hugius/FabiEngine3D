#include "script_interpreter.hpp"

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dWaterSetter(const string & functionName, const vector<shared_ptr<ScriptValue>> & args, vector<shared_ptr<ScriptValue>> & returnValues)
{
	if(functionName == "fe3d:water_place")
	{
		const auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(!_validateFe3dId(args[0]->getString()))
			{
				return true;
			}

			if(_fe3d->water_isExisting(args[0]->getString()))
			{
				_throwRuntimeError("water already exists");

				return true;
			}

			if(_validateFe3dWater(args[0]->getString(), true))
			{
				_duplicator->copyTemplateWater(args[0]->getString(), ("@" + args[1]->getString()));

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:water_select")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dWater(args[0]->getString(), false))
			{
				_fe3d->water_select(args[0]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:water_delete")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dWater(args[0]->getString(), false))
			{
				_duplicator->deleteCopiedWater(args[0]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:water_delete_all")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			for(const auto & waterId : _fe3d->water_getIds())
			{
				if(waterId[0] != '@')
				{
					_duplicator->deleteCopiedWater(waterId);
				}
			}

			returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:water_set_min_clip_position")
	{
		const auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dWater(args[0]->getString(), false))
			{
				_fe3d->water_setMinClipPosition(args[0]->getString(), fvec3(args[1]->getDecimal(), args[2]->getDecimal(), args[3]->getDecimal()));

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:water_set_max_clip_position")
	{
		const auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dWater(args[0]->getString(), false))
			{
				_fe3d->water_setMaxClipPosition(args[0]->getString(), fvec3(args[1]->getDecimal(), args[2]->getDecimal(), args[3]->getDecimal()));

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:water_set_ripple_speed")
	{
		const auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dWater(args[0]->getString(), false))
			{
				_fe3d->water_setRippleSpeed(_fe3d->water_getSelectedId(), fvec2((args[10]->getDecimal() / 100000.0f), (args[2]->getDecimal() / 100000.0f)));

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:water_set_wave_speed")
	{
		const auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dWater(args[0]->getString(), false))
			{
				_fe3d->water_setWaveSpeed(_fe3d->water_getSelectedId(), fvec2((args[1]->getDecimal() / 100000.0f), (args[2]->getDecimal() / 100000.0f)));

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:water_set_distortion_size")
	{
		const auto types = {SVT::STRING, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dWater(args[0]->getString(), false))
			{
				_fe3d->water_setDistortionSize(_fe3d->water_getSelectedId(), args[1]->getDecimal());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:water_set_distortion_factor")
	{
		const auto types = {SVT::STRING, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dWater(args[0]->getString(), false))
			{
				_fe3d->water_setDistortionFactor(_fe3d->water_getSelectedId(), args[1]->getDecimal());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:water_set_capture_offset")
	{
		const auto types = {SVT::STRING, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dWater(args[0]->getString(), false))
			{
				_fe3d->water_setCaptureOffset(_fe3d->water_getSelectedId(), args[1]->getDecimal());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:water_set_max_depth")
	{
		const auto types = {SVT::STRING, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dWater(args[0]->getString(), false))
			{
				_fe3d->water_setMaxDepth(_fe3d->water_getSelectedId(), args[1]->getDecimal());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:water_set_size")
	{
		const auto types = {SVT::STRING, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dWater(args[0]->getString(), false))
			{
				_fe3d->water_setSize(_fe3d->water_getSelectedId(), args[1]->getDecimal());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:water_set_dudv_map")
	{
		const auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dWater(args[0]->getString(), false))
			{
				_fe3d->water_setDudvMap(_fe3d->water_getSelectedId(), args[1]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:water_set_normal_map")
	{
		const auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dWater(args[0]->getString(), false))
			{
				_fe3d->water_setNormalMap(_fe3d->water_getSelectedId(), args[1]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:water_set_height_map")
	{
		const auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dWater(args[0]->getString(), false))
			{
				_fe3d->water_setHeightMap(_fe3d->water_getSelectedId(), args[1]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:water_set_color")
	{
		const auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dWater(args[0]->getString(), false))
			{
				_fe3d->water_setColor(_fe3d->water_getSelectedId(), fvec3(args[1]->getDecimal(), args[2]->getDecimal(), args[3]->getDecimal()));

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:water_set_lightness")
	{
		const auto types = {SVT::STRING, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dWater(args[0]->getString(), false))
			{
				_fe3d->water_setLightness(_fe3d->water_getSelectedId(), args[1]->getDecimal());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:water_set_wireframe_color")
	{
		const auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dWater(args[0]->getString(), false))
			{
				_fe3d->water_setWireframeColor(_fe3d->water_getSelectedId(), fvec3(args[1]->getDecimal(), args[2]->getDecimal(), args[3]->getDecimal()));

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:water_set_height")
	{
		const auto types = {SVT::STRING, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dWater(args[0]->getString(), false))
			{
				_fe3d->water_setHeight(_fe3d->water_getSelectedId(), args[1]->getDecimal());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:water_set_wave_height")
	{
		const auto types = {SVT::STRING, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dWater(args[0]->getString(), false))
			{
				_fe3d->water_setWaveHeight(_fe3d->water_getSelectedId(), args[1]->getDecimal());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:water_set_texture_repeat")
	{
		const auto types = {SVT::STRING, SVT::INTEGER};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dWater(args[0]->getString(), false))
			{
				_fe3d->water_setTextureRepeat(_fe3d->water_getSelectedId(), args[1]->getInteger());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:water_set_specular_shininess")
	{
		const auto types = {SVT::STRING, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dWater(args[0]->getString(), false))
			{
				_fe3d->water_setSpecularShininess(_fe3d->water_getSelectedId(), args[1]->getDecimal());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:water_set_specular_intensity")
	{
		const auto types = {SVT::STRING, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dWater(args[0]->getString(), false))
			{
				_fe3d->water_setSpecularIntensity(_fe3d->water_getSelectedId(), args[1]->getDecimal());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:water_set_reflective")
	{
		const auto types = {SVT::STRING, SVT::BOOLEAN};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dWater(args[0]->getString(), false))
			{
				_fe3d->water_setReflective(_fe3d->water_getSelectedId(), args[1]->getBoolean());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:water_set_refractive")
	{
		const auto types = {SVT::STRING, SVT::BOOLEAN};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dWater(args[0]->getString(), false))
			{
				_fe3d->water_setRefractive(_fe3d->water_getSelectedId(), args[1]->getBoolean());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:water_set_specular")
	{
		const auto types = {SVT::STRING, SVT::BOOLEAN};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dWater(args[0]->getString(), false))
			{
				_fe3d->water_setSpecular(_fe3d->water_getSelectedId(), args[1]->getBoolean());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:water_set_wireframed")
	{
		const auto types = {SVT::STRING, SVT::BOOLEAN};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dWater(args[0]->getString(), false))
			{
				_fe3d->water_setWireframed(_fe3d->water_getSelectedId(), args[1]->getBoolean());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:water_set_edged")
	{
		const auto types = {SVT::STRING, SVT::BOOLEAN};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dWater(args[0]->getString(), false))
			{
				_fe3d->water_setEdged(_fe3d->water_getSelectedId(), args[1]->getBoolean());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:water_set_capturing_sky")
	{
		const auto types = {SVT::STRING, SVT::BOOLEAN};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dWater(args[0]->getString(), false))
			{
				_fe3d->water_setCaptureSky(_fe3d->water_getSelectedId(), args[1]->getBoolean());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:water_set_capturing_terrain")
	{
		const auto types = {SVT::STRING, SVT::BOOLEAN};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dWater(args[0]->getString(), false))
			{
				_fe3d->water_setCaptureTerrain(_fe3d->water_getSelectedId(), args[1]->getBoolean());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:water_set_capturing_models")
	{
		const auto types = {SVT::STRING, SVT::BOOLEAN};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dWater(args[0]->getString(), false))
			{
				_fe3d->water_setCaptureModels(_fe3d->water_getSelectedId(), args[1]->getBoolean());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:water_set_capturing_quad3ds")
	{
		const auto types = {SVT::STRING, SVT::BOOLEAN};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dWater(args[0]->getString(), false))
			{
				_fe3d->water_setCaptureQuad3ds(_fe3d->water_getSelectedId(), args[1]->getBoolean());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:water_set_capturing_text3ds")
	{
		const auto types = {SVT::STRING, SVT::BOOLEAN};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dWater(args[0]->getString(), false))
			{
				_fe3d->water_setCaptureText3ds(_fe3d->water_getSelectedId(), args[1]->getBoolean());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:water_set_capturing_aabbs")
	{
		const auto types = {SVT::STRING, SVT::BOOLEAN};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dWater(args[0]->getString(), false))
			{
				_fe3d->water_setCaptureAabbs(_fe3d->water_getSelectedId(), args[1]->getBoolean());

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
		_throwRuntimeError("cannot access `fe3d:water` functionality as a networking server");

		return true;
	}

	return true;
}