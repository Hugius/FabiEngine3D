#include "script_interpreter.hpp"
#include "configuration.hpp"
#include "tools.hpp"
#include "logger.hpp"

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dQuadSetter(const string& functionName, vector<ScriptValue>& args, vector<ScriptValue>& returnValues)
{
	if(functionName == "fe3d:quad_place")
	{
		auto types = {SVT::STRING, SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(!_validateFe3dID(args[0].getString()))
			{
				return true;
			}

			if(_fe3d->quad_isExisting(args[0].getString()))
			{
				_throwScriptError("quad already exists!");
				return true;
			}

			if(_validateFe3dQuad(args[1].getString(), true))
			{
				_fe3d->quad_create(args[0].getString(), true);
				_fe3d->quad_setDiffuseMap(args[0].getString(), _fe3d->quad_getDiffuseMapPath("@" + args[1].getString()));
				_fe3d->quad_setPosition(args[0].getString(), Tools::_convertPositionToViewport(fvec2(args[2].getDecimal(), args[3].getDecimal())));
				_fe3d->quad_setSize(args[0].getString(), Tools::_convertSizeToViewport(fvec2(args[4].getDecimal(), args[5].getDecimal())));
				_fe3d->quad_setMinPosition(args[0].getString(), Tools::_calculateMinViewportPosition());
				_fe3d->quad_setMaxPosition(args[0].getString(), Tools::_calculateMaxViewportPosition());

				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:quad_delete")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad(args[0].getString(), false))
			{
				_fe3d->quad_delete(args[0].getString());
				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:quad_delete_all")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			for(const auto& ID : _fe3d->quad_getIDs())
			{
				if(ID[0] != '@')
				{
					_fe3d->quad_delete(ID);
				}
			}

			returnValues.push_back(ScriptValue(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:quad_set_visible")
	{
		auto types = {SVT::STRING, SVT::BOOLEAN};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad(args[0].getString(), false))
			{
				_fe3d->quad_setVisible(args[0].getString(), args[1].getBoolean());

				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:quad_set_diffuse_map")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad(args[0].getString(), false))
			{
				_fe3d->quad_setDiffuseMap(args[0].getString(), args[1].getString());

				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:quad_set_position")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad(args[0].getString(), false))
			{
				_fe3d->quad_setPosition(args[0].getString(), Tools::_convertPositionToViewport(fvec2(args[1].getDecimal(), args[2].getDecimal())));
				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:quad_move")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad(args[0].getString(), false))
			{
				_fe3d->quad_move(args[0].getString(), Tools::_convertSizeToViewport(fvec2(args[1].getDecimal(), args[2].getDecimal())));

				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:quad_move_to")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad(args[0].getString(), false))
			{
				auto speed = Tools::_convertSizeToViewport(fvec2(args[3].getDecimal(), args[3].getDecimal()));
				_fe3d->quad_moveTo(args[0].getString(), Tools::_convertSizeToViewport(fvec2(args[1].getDecimal(), args[2].getDecimal())), ((speed.x + speed.y) / 2.0f));

				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:quad_set_rotation")
	{
		auto types = {SVT::STRING, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad(args[0].getString(), false))
			{
				_fe3d->quad_setRotation(args[0].getString(), args[1].getDecimal());

				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:quad_rotate")
	{
		auto types = {SVT::STRING, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad(args[0].getString(), false))
			{
				_fe3d->quad_rotate(args[0].getString(), args[1].getDecimal());

				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:quad_rotate_to")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad(args[0].getString(), false))
			{
				_fe3d->quad_rotateTo(args[0].getString(), args[1].getDecimal(), args[2].getDecimal());

				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:quad_set_size")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad(args[0].getString(), false))
			{
				_fe3d->quad_setSize(args[0].getString(), Tools::_convertSizeToViewport(fvec2(args[1].getDecimal(), args[2].getDecimal())));

				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:quad_scale")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad(args[0].getString(), false))
			{
				_fe3d->quad_scale(args[0].getString(), Tools::_convertSizeToViewport(fvec2(args[1].getDecimal(), args[2].getDecimal())));

				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:quad_scale_to")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad(args[0].getString(), false))
			{
				auto speed = Tools::_convertSizeToViewport(fvec2(args[3].getDecimal(), args[3].getDecimal()));
				_fe3d->quad_scaleTo(args[0].getString(), Tools::_convertSizeToViewport(fvec2(args[1].getDecimal(), args[2].getDecimal())), ((speed.x + speed.y) / 2.0f));

				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:quad_set_color")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad(args[0].getString(), false))
			{
				_fe3d->quad_setColor(args[0].getString(), fvec3(args[1].getDecimal(), args[2].getDecimal(), args[3].getDecimal()));

				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:quad_set_wireframe_color")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad(args[0].getString(), false))
			{
				_fe3d->quad_setWireframeColor(args[0].getString(), fvec3(args[1].getDecimal(), args[2].getDecimal(), args[3].getDecimal()));

				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:quad_set_transparency")
	{
		auto types = {SVT::STRING, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad(args[0].getString(), false))
			{
				_fe3d->quad_setTransparency(args[0].getString(), args[1].getDecimal());

				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:quad_set_wireframed")
	{
		auto types = {SVT::STRING, SVT::BOOLEAN};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad(args[0].getString(), false))
			{
				_fe3d->quad_setWireframed(args[0].getString(), args[1].getBoolean());

				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:quad_set_horizontally_mirrored")
	{
		auto types = {SVT::STRING, SVT::BOOLEAN};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad(args[0].getString(), false))
			{
				_fe3d->quad_setHorizontallyMirrored(args[0].getString(), args[1].getBoolean());

				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:quad_set_vertically_mirrored")
	{
		auto types = {SVT::STRING, SVT::BOOLEAN};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad(args[0].getString(), false))
			{
				_fe3d->quad_setVerticallyMirrored(args[0].getString(), args[1].getBoolean());

				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:quad_set_uv_multiplier")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad(args[0].getString(), false))
			{
				_fe3d->quad_setUvMultiplier(args[0].getString(), fvec2(args[1].getDecimal(), args[2].getDecimal()));

				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:quad_set_uv_offset")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad(args[0].getString(), false))
			{
				_fe3d->quad_setUvOffset(args[0].getString(), fvec2(args[1].getDecimal(), args[2].getDecimal()));

				returnValues.push_back(ScriptValue(SVT::EMPTY));
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