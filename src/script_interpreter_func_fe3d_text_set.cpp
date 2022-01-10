#include "script_interpreter.hpp"
#include "configuration.hpp"
#include "tools.hpp"

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dTextSetter(const string& functionName, vector<ScriptValue>& args, vector<ScriptValue>& returnValues)
{
	if(functionName == "fe3d:text_place")
	{
		auto types = {SVT::STRING, SVT::STRING, SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(!_validateFe3dID(args[0].getString()))
			{
				return true;
			}

			if(_fe3d->text_isExisting(args[0].getString()))
			{
				_throwScriptError("text already exists!");
				return true;
			}

			_fe3d->text_create(args[0].getString(), true);

			const auto isExported = Config::getInst().isApplicationExported();
			const auto rootPath = Tools::getRootDirectoryPath();
			const auto filePath = string(rootPath + (isExported ? "" : ("projects\\" + _currentProjectID + "\\")) + "assets\\image\\entity\\text\\font_map\\" + args[1].getString());
			_fe3d->text_setFontMap(args[0].getString(), filePath);

			_fe3d->text_setPosition(args[0].getString(), _convertGuiPositionToViewport(fvec2(args[3].getDecimal(), args[4].getDecimal())));
			_fe3d->text_setSize(args[0].getString(), _convertGuiSizeToViewport(fvec2(args[5].getDecimal(), args[6].getDecimal())));
			_fe3d->text_setContent(args[0].getString(), args[2].getString());

			if(!Config::getInst().isApplicationExported())
			{
				auto minPosition = Math::convertToNdc(Tools::convertFromScreenCoords(Config::getInst().getViewportPosition()));
				auto maxPosition = Math::convertToNdc(Tools::convertFromScreenCoords(Config::getInst().getViewportPosition() + Config::getInst().getViewportSize()));
				_fe3d->text_setMinPosition(args[0].getString(), minPosition);
				_fe3d->text_setMaxPosition(args[0].getString(), maxPosition);
			}

			returnValues.push_back(ScriptValue(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:text_delete")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dText(args[0].getString(), false))
			{
				_fe3d->text_delete(args[0].getString());
				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:text_delete_all")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			for(const auto& ID : _fe3d->text_getIDs())
			{
				if(ID[0] != '@')
				{
					_fe3d->text_delete(ID);
				}
			}

			returnValues.push_back(ScriptValue(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:text_set_visible")
	{
		auto types = {SVT::STRING, SVT::BOOLEAN};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dText(args[0].getString(), false))
			{
				_fe3d->text_setVisible(args[0].getString(), args[1].getBoolean());
				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:text_set_position")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dText(args[0].getString(), false))
			{
				fvec2 position = _convertGuiPositionToViewport(fvec2(args[1].getDecimal(), args[2].getDecimal()));
				_fe3d->text_setPosition(args[0].getString(), position);
				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:text_move")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dText(args[0].getString(), false))
			{
				fvec2 change = _convertGuiSizeToViewport(fvec2(args[1].getDecimal(), args[2].getDecimal()));
				_fe3d->text_move(args[0].getString(), change);
				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:text_move_to")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dText(args[0].getString(), false))
			{
				fvec2 target = _convertGuiSizeToViewport(fvec2(args[1].getDecimal(), args[2].getDecimal()));
				fvec2 speed = _convertGuiSizeToViewport(fvec2(args[3].getDecimal(), args[3].getDecimal()));
				_fe3d->text_moveTo(args[0].getString(), target, speed.x);
				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:text_rotate_to")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dText(args[0].getString(), false))
			{
				_fe3d->text_rotateTo(args[0].getString(), args[1].getDecimal(), args[2].getDecimal());
				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:text_scale_to")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dText(args[0].getString(), false))
			{
				fvec2 target = _convertGuiSizeToViewport(fvec2(args[1].getDecimal(), args[2].getDecimal()));
				fvec2 speed = _convertGuiSizeToViewport(fvec2(args[3].getDecimal(), args[3].getDecimal()));
				_fe3d->text_scaleTo(args[0].getString(), target, speed.x);
				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:text_set_rotation")
	{
		auto types = {SVT::STRING, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dText(args[0].getString(), false))
			{
				_fe3d->text_setRotation(args[0].getString(), args[1].getDecimal());
				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:text_rotate")
	{
		auto types = {SVT::STRING, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dText(args[0].getString(), false))
			{
				_fe3d->text_rotate(args[0].getString(), args[1].getDecimal());
				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:text_set_size")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dText(args[0].getString(), false))
			{
				fvec2 size = _convertGuiSizeToViewport(fvec2(args[1].getDecimal(), args[2].getDecimal()));
				_fe3d->text_setSize(args[0].getString(), size);
				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:text_scale")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dText(args[0].getString(), false))
			{
				fvec2 change = _convertGuiSizeToViewport(fvec2(args[1].getDecimal(), args[2].getDecimal()));
				_fe3d->text_scale(args[0].getString(), change);
				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:text_set_color")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dText(args[0].getString(), false))
			{
				_fe3d->text_setColor(args[0].getString(),
									 fvec3(args[1].getDecimal(), args[2].getDecimal(), args[3].getDecimal()));
				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:text_set_content")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dText(args[0].getString(), false))
			{
				_fe3d->text_setContent(args[0].getString(), args[1].getString());
				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:text_set_transparency")
	{
		auto types = {SVT::STRING, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dText(args[0].getString(), false))
			{
				_fe3d->text_setTransparency(args[0].getString(), args[1].getDecimal());
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
		_throwScriptError("cannot access `fe3d:text` functionality as networking server!");
	}

	return true;
}