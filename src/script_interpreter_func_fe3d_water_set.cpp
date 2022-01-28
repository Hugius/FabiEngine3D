#include "script_interpreter.hpp"
#include "logger.hpp"

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dWaterSetter(const string& functionName, vector<ScriptValue>& args, vector<ScriptValue>& returnValues)
{
	if(functionName == "fe3d:water_set_ripple_speed")
	{
		auto types = {SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dWater())
			{
				_fe3d->water_setRippleSpeed(_fe3d->water_getSelectedId(), fvec2((args[0].getDecimal() / 100000.0f), (args[1].getDecimal() / 100000.0f)));

				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:water_set_wave_speed")
	{
		auto types = {SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dWater())
			{
				_fe3d->water_setWaveSpeed(_fe3d->water_getSelectedId(), fvec2((args[0].getDecimal() / 100000.0f), (args[1].getDecimal() / 100000.0f)));

				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:water_max_depth")
	{
		auto types = {SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dWater())
			{
				_fe3d->water_setMaxDepth(_fe3d->water_getSelectedId(), args[0].getDecimal());

				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:water_set_size")
	{
		auto types = {SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dWater())
			{
				_fe3d->water_setSize(_fe3d->water_getSelectedId(), args[0].getDecimal());

				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:water_set_dudv_map")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dWater())
			{
				_fe3d->water_setDudvMap(_fe3d->water_getSelectedId(), args[0].getString());

				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:water_set_normal_map")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dWater())
			{
				_fe3d->water_setNormalMap(_fe3d->water_getSelectedId(), args[0].getString());

				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:water_set_displacement_map")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dWater())
			{
				_fe3d->water_setDisplacementMap(_fe3d->water_getSelectedId(), args[0].getString());

				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:water_set_color")
	{
		auto types = {SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dWater())
			{
				_fe3d->water_setColor(_fe3d->water_getSelectedId(), fvec3(args[0].getDecimal(), args[1].getDecimal(), args[2].getDecimal()));

				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:water_set_wireframe_color")
	{
		auto types = {SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dWater())
			{
				_fe3d->water_setWireframeColor(_fe3d->water_getSelectedId(), fvec3(args[0].getDecimal(), args[1].getDecimal(), args[2].getDecimal()));

				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:water_set_edged")
	{
		auto types = {SVT::BOOLEAN};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dWater())
			{
				_fe3d->water_setEdged(_fe3d->water_getSelectedId(), args[0].getBoolean());

				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:water_set_height")
	{
		auto types = {SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dWater())
			{
				_fe3d->water_setHeight(_fe3d->water_getSelectedId(), args[0].getDecimal());

				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:water_set_wave_height")
	{
		auto types = {SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dWater())
			{
				_fe3d->water_setWaveHeight(_fe3d->water_getSelectedId(), args[0].getDecimal());

				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:water_set_texture_repeat")
	{
		auto types = {SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dWater())
			{
				_fe3d->water_setTextureRepeat(_fe3d->water_getSelectedId(), args[0].getDecimal());

				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:water_set_specular_shininess")
	{
		auto types = {SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dWater())
			{
				_fe3d->water_setSpecularShininess(_fe3d->water_getSelectedId(), args[0].getDecimal());

				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:water_set_specular_intensity")
	{
		auto types = {SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dWater())
			{
				_fe3d->water_setSpecularIntensity(_fe3d->water_getSelectedId(), args[0].getDecimal());

				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:water_set_reflective")
	{
		auto types = {SVT::BOOLEAN};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dWater())
			{
				_fe3d->water_setReflective(_fe3d->water_getSelectedId(), args[0].getBoolean());

				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:water_set_refractive")
	{
		auto types = {SVT::BOOLEAN};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dWater())
			{
				_fe3d->water_setRefractive(_fe3d->water_getSelectedId(), args[0].getBoolean());

				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:water_set_specular")
	{
		auto types = {SVT::BOOLEAN};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dWater())
			{
				_fe3d->water_setSpecular(_fe3d->water_getSelectedId(), args[0].getBoolean());

				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:water_set_wireframed")
	{
		auto types = {SVT::BOOLEAN};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dWater())
			{
				_fe3d->water_setWireframed(_fe3d->water_getSelectedId(), args[0].getBoolean());

				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:water_set_quality")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dWater())
			{
				if(args[0].getString() == "SKY")
				{
					_fe3d->water_setQuality(_fe3d->water_getSelectedId(), WaterQuality::SKY);

					returnValues.push_back(ScriptValue(SVT::EMPTY));
				}
				else if(args[0].getString() == "SKY_TERRAIN")
				{
					_fe3d->water_setQuality(_fe3d->water_getSelectedId(), WaterQuality::SKY_TERRAIN);

					returnValues.push_back(ScriptValue(SVT::EMPTY));
				}
				else if(args[0].getString() == "SKY_TERRAIN_MODELS")
				{
					_fe3d->water_setQuality(_fe3d->water_getSelectedId(), WaterQuality::SKY_TERRAIN_MODEL);

					returnValues.push_back(ScriptValue(SVT::EMPTY));
				}
				else if(args[0].getString() == "SKY_TERRAIN_MODELS_QUAD3DS")
				{
					_fe3d->water_setQuality(_fe3d->water_getSelectedId(), WaterQuality::SKY_TERRAIN_MODEL_QUAD3D);

					returnValues.push_back(ScriptValue(SVT::EMPTY));
				}
				else
				{
					Logger::throwWarning("invalid quality!");

					returnValues.push_back(ScriptValue(SVT::EMPTY));
				}
			}
		}
	}
	else
	{
		return false;
	}

	if(_fe3d->server_isRunning())
	{
		_throwScriptError("cannot access `fe3d:water` functionality as networking server!");
	}

	return true;
}