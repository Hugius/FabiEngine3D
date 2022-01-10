#include "script_interpreter.hpp"
#include "configuration.hpp"
#include "tools.hpp"
#include "logger.hpp"

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dQuadSetter(const string& functionName, vector<ScriptValue>& args, vector<ScriptValue>& returnValues)
{
	if(functionName == "fe3d:quad_place")
	{
		auto types = {SVT::STRING, SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

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

				if(_currentProjectID.empty())
				{
					Logger::throwError("ScriptInterpreter::_executeFe3dQuadSetter");
				}

				const auto isExported = Config::getInst().isApplicationExported();
				const auto rootPath = Tools::getRootDirectoryPath();
				const auto targetDirectoryPath = string(rootPath + (isExported ? "" : ("projects\\" + _currentProjectID + "\\")) + "assets\\image\\entity\\quad\\diffuse_map\\");
				const auto filePath = (targetDirectoryPath + args[1].getString());
				_fe3d->quad_setDiffuseMap(args[0].getString(), filePath);

				_fe3d->quad_setPosition(args[0].getString(), _convertGuiPositionToViewport(fvec2(args[2].getDecimal(), args[3].getDecimal())));
				_fe3d->quad_setRotation(args[0].getString(), args[4].getDecimal());
				_fe3d->quad_setSize(args[0].getString(), _convertGuiSizeToViewport(fvec2(args[5].getDecimal(), args[6].getDecimal())));

				if(!Config::getInst().isApplicationExported())
				{
					auto minPosition = Math::convertToNdc(Tools::convertFromScreenCoords(Config::getInst().getViewportPosition()));
					auto maxPosition = Math::convertToNdc(Tools::convertFromScreenCoords(Config::getInst().getViewportPosition() + Config::getInst().getViewportSize()));
					_fe3d->quad_setMinPosition(args[0].getString(), minPosition);
					_fe3d->quad_setMaxPosition(args[0].getString(), maxPosition);
				}

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
	else if(functionName == "fe3d:quad_set_position")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad(args[0].getString(), false))
			{
				auto position = _convertGuiPositionToViewport(fvec2(args[1].getDecimal(), args[2].getDecimal()));
				_fe3d->quad_setPosition(args[0].getString(), position);
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
				fvec2 change = _convertGuiSizeToViewport(fvec2(args[1].getDecimal(), args[2].getDecimal()));
				_fe3d->quad_move(args[0].getString(), change);
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
				fvec2 target = _convertGuiSizeToViewport(fvec2(args[1].getDecimal(), args[2].getDecimal()));
				fvec2 speed = _convertGuiSizeToViewport(fvec2(args[3].getDecimal(), args[3].getDecimal()));
				_fe3d->quad_moveTo(args[0].getString(), target, speed.x);
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
				fvec2 size = _convertGuiSizeToViewport(fvec2(args[1].getDecimal(), args[2].getDecimal()));
				_fe3d->quad_setSize(args[0].getString(), size);
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
				fvec2 change = _convertGuiSizeToViewport(fvec2(args[1].getDecimal(), args[2].getDecimal()));
				_fe3d->quad_scale(args[0].getString(), change);
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
				fvec2 target = _convertGuiSizeToViewport(fvec2(args[1].getDecimal(), args[2].getDecimal()));
				fvec2 speed = _convertGuiSizeToViewport(fvec2(args[3].getDecimal(), args[3].getDecimal()));
				_fe3d->quad_scaleTo(args[0].getString(), target, speed.x);
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
				_fe3d->quad_setColor(args[0].getString(),
									 fvec3(args[1].getDecimal(), args[2].getDecimal(), args[3].getDecimal()));
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
				_fe3d->quad_setWireframeColor(args[0].getString(),
											  fvec3(args[1].getDecimal(), args[2].getDecimal(), args[3].getDecimal()));
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
	else if(functionName == "fe3d:quad_set_mirrored_horizontally")
	{
		auto types = {SVT::STRING, SVT::BOOLEAN};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad(args[0].getString(), false))
			{
				_fe3d->quad_setMirroredHorizontally(args[0].getString(), args[1].getBoolean());
				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:quad_set_mirrored_vertically")
	{
		auto types = {SVT::STRING, SVT::BOOLEAN};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad(args[0].getString(), false))
			{
				_fe3d->quad_setMirroredVertically(args[0].getString(), args[1].getBoolean());
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