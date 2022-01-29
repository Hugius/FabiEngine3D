#include "script_interpreter.hpp"
#include "configuration.hpp"
#include "tools.hpp"
#include "logger.hpp"

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dQuad2dSetter(const string& functionName, vector<ScriptValue>& args, vector<ScriptValue>& returnValues)
{
	if(functionName == "fe3d:quad2d_place")
	{
		auto types = {SVT::STRING, SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(!_validateFe3dId(args[0].getString()))
			{
				return true;
			}

			if(_fe3d->quad2d_isExisting(args[0].getString()))
			{
				_throwScriptError("Quad2D entity already exists!");
				return true;
			}

			if(_validateFe3dQuad2d(args[1].getString(), true))
			{
				_fe3d->quad2d_create(args[0].getString(), true);
				_fe3d->quad2d_setDiffuseMap(args[0].getString(), _fe3d->quad2d_getDiffuseMapPath("@" + args[1].getString()));
				_fe3d->quad2d_setPosition(args[0].getString(), Tools::convertPositionToViewport(fvec2(args[2].getDecimal(), args[3].getDecimal())));
				_fe3d->quad2d_setSize(args[0].getString(), Tools::convertSizeToViewport(fvec2(args[4].getDecimal(), args[5].getDecimal())));
				_fe3d->quad2d_setMinPosition(args[0].getString(), Tools::calculateMinViewportPosition());
				_fe3d->quad2d_setMaxPosition(args[0].getString(), Tools::calculateMaxViewportPosition());

				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:quad2d_delete")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad2d(args[0].getString(), false))
			{
				_fe3d->quad2d_delete(args[0].getString());
				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:quad2d_delete_all")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			for(const auto& id : _fe3d->quad2d_getIds())
			{
				if(id[0] != '@')
				{
					_fe3d->quad2d_delete(id);
				}
			}

			returnValues.push_back(ScriptValue(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:quad2d_set_visible")
	{
		auto types = {SVT::STRING, SVT::BOOLEAN};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad2d(args[0].getString(), false))
			{
				_fe3d->quad2d_setVisible(args[0].getString(), args[1].getBoolean());

				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:quad2d_set_diffuse_map")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad2d(args[0].getString(), false))
			{
				_fe3d->quad2d_setDiffuseMap(args[0].getString(), args[1].getString());

				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:quad2d_set_position")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad2d(args[0].getString(), false))
			{
				_fe3d->quad2d_setPosition(args[0].getString(), Tools::convertPositionToViewport(fvec2(args[1].getDecimal(), args[2].getDecimal())));
				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:quad2d_move")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad2d(args[0].getString(), false))
			{
				_fe3d->quad2d_move(args[0].getString(), Tools::convertSizeToViewport(fvec2(args[1].getDecimal(), args[2].getDecimal())));

				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:quad2d_move_to")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad2d(args[0].getString(), false))
			{
				auto speed = Tools::convertSizeToViewport(fvec2(args[3].getDecimal(), args[3].getDecimal()));
				_fe3d->quad2d_moveTo(args[0].getString(), Tools::convertSizeToViewport(fvec2(args[1].getDecimal(), args[2].getDecimal())), ((speed.x + speed.y) * 0.5f));

				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:quad2d_set_rotation")
	{
		auto types = {SVT::STRING, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad2d(args[0].getString(), false))
			{
				_fe3d->quad2d_setRotation(args[0].getString(), args[1].getDecimal());

				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:quad2d_rotate")
	{
		auto types = {SVT::STRING, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad2d(args[0].getString(), false))
			{
				_fe3d->quad2d_rotate(args[0].getString(), args[1].getDecimal());

				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:quad2d_rotate_to")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad2d(args[0].getString(), false))
			{
				_fe3d->quad2d_rotateTo(args[0].getString(), args[1].getDecimal(), args[2].getDecimal());

				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:quad2d_set_size")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad2d(args[0].getString(), false))
			{
				_fe3d->quad2d_setSize(args[0].getString(), Tools::convertSizeToViewport(fvec2(args[1].getDecimal(), args[2].getDecimal())));

				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:quad2d_scale")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad2d(args[0].getString(), false))
			{
				_fe3d->quad2d_scale(args[0].getString(), Tools::convertSizeToViewport(fvec2(args[1].getDecimal(), args[2].getDecimal())));

				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:quad2d_scale_to")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad2d(args[0].getString(), false))
			{
				auto speed = Tools::convertSizeToViewport(fvec2(args[3].getDecimal(), args[3].getDecimal()));
				_fe3d->quad2d_scaleTo(args[0].getString(), Tools::convertSizeToViewport(fvec2(args[1].getDecimal(), args[2].getDecimal())), ((speed.x + speed.y) * 0.5f));

				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:quad2d_set_color")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad2d(args[0].getString(), false))
			{
				_fe3d->quad2d_setColor(args[0].getString(), fvec3(args[1].getDecimal(), args[2].getDecimal(), args[3].getDecimal()));

				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:quad2d_set_wireframe_color")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad2d(args[0].getString(), false))
			{
				_fe3d->quad2d_setWireframeColor(args[0].getString(), fvec3(args[1].getDecimal(), args[2].getDecimal(), args[3].getDecimal()));

				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:quad2d_set_opacity")
	{
		auto types = {SVT::STRING, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad2d(args[0].getString(), false))
			{
				_fe3d->quad2d_setOpacity(args[0].getString(), args[1].getDecimal());

				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:quad2d_set_wireframed")
	{
		auto types = {SVT::STRING, SVT::BOOLEAN};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad2d(args[0].getString(), false))
			{
				_fe3d->quad2d_setWireframed(args[0].getString(), args[1].getBoolean());

				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:quad2d_set_horizontally_flipped")
	{
		auto types = {SVT::STRING, SVT::BOOLEAN};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad2d(args[0].getString(), false))
			{
				_fe3d->quad2d_setHorizontallyFlipped(args[0].getString(), args[1].getBoolean());

				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:quad2d_set_vertically_flipped")
	{
		auto types = {SVT::STRING, SVT::BOOLEAN};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad2d(args[0].getString(), false))
			{
				_fe3d->quad2d_setVerticallyFlipped(args[0].getString(), args[1].getBoolean());

				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:quad2d_set_uv_multiplier")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad2d(args[0].getString(), false))
			{
				_fe3d->quad2d_setUvMultiplier(args[0].getString(), fvec2(args[1].getDecimal(), args[2].getDecimal()));

				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:quad2d_set_uv_offset")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad2d(args[0].getString(), false))
			{
				_fe3d->quad2d_setUvOffset(args[0].getString(), fvec2(args[1].getDecimal(), args[2].getDecimal()));

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
		_throwScriptError("cannot access `fe3d:quad2d` functionality as networking server!");
	}

	return true;
}