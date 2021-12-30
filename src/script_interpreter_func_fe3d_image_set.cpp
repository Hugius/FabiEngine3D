#include "script_interpreter.hpp"
#include "configuration.hpp"
#include "tools.hpp"
#include "logger.hpp"

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dImageSetter(const string& functionName, vector<ScriptValue>& args, vector<ScriptValue>& returnValues)
{
	if (functionName == "fe3d:image_place")
	{
		auto types = { SVT::STRING, SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL };

		if (_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if (!_validateFe3dID(args[0].getString()))
			{
				return true;
			}

			if (_fe3d.image_isExisting(args[0].getString()))
			{
				_throwScriptError("image already exists!");
				return true;
			}

			_fe3d.image_create(args[0].getString(), true);

			if (_currentProjectID.empty())
			{
				Logger::throwError("ScriptInterpreter::_executeFe3dImageSetter");
			}

			const auto isExported = Config::getInst().isApplicationExported();
			const auto rootPath = Tools::getRootDirectoryPath();
			const string targetDirectoryPath = string(rootPath + (isExported ? "" : ("projects\\" + _currentProjectID + "\\")) + "assets\\image\\diffuse_map\\");
			const string filePath = (targetDirectoryPath + args[1].getString());
			_fe3d.image_setDiffuseMap(args[0].getString(), filePath);

			_fe3d.image_setPosition(args[0].getString(), _convertGuiPositionToViewport(fvec2(args[2].getDecimal(), args[3].getDecimal())));
			_fe3d.image_setRotation(args[0].getString(), args[4].getDecimal());
			_fe3d.image_setSize(args[0].getString(), _convertGuiSizeToViewport(fvec2(args[5].getDecimal(), args[6].getDecimal())));

			if (!Config::getInst().isApplicationExported())
			{
				auto minPosition = Math::convertToNDC(Tools::convertFromScreenCoords(Config::getInst().getViewportPosition()));
				auto maxPosition = Math::convertToNDC(Tools::convertFromScreenCoords(Config::getInst().getViewportPosition() + Config::getInst().getViewportSize()));
				_fe3d.image_setMinPosition(args[0].getString(), minPosition);
				_fe3d.image_setMaxPosition(args[0].getString(), maxPosition);
			}

			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if (functionName == "fe3d:image_delete")
	{
		auto types = { SVT::STRING };

		if (_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if (_validateFe3dImage(args[0].getString()))
			{
				_fe3d.image_delete(args[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:image_delete_all")
	{
		if (_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			for (const auto& ID : _fe3d.image_getIDs())
			{
				if (ID[0] != '@')
				{
					_fe3d.image_delete(ID);
				}
			}

			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if (functionName == "fe3d:image_set_visible")
	{
		auto types = { SVT::STRING, SVT::BOOLEAN };

		if (_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if (_validateFe3dImage(args[0].getString()))
			{
				_fe3d.image_setVisible(args[0].getString(), args[1].getBoolean());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:image_set_position")
	{
		auto types = { SVT::STRING, SVT::DECIMAL, SVT::DECIMAL };

		if (_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if (_validateFe3dImage(args[0].getString()))
			{
				auto position = _convertGuiPositionToViewport(fvec2(args[1].getDecimal(), args[2].getDecimal()));
				_fe3d.image_setPosition(args[0].getString(), position);
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:image_move")
	{
		auto types = { SVT::STRING, SVT::DECIMAL, SVT::DECIMAL };

		if (_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if (_validateFe3dImage(args[0].getString()))
			{
				fvec2 change = _convertGuiSizeToViewport(fvec2(args[1].getDecimal(), args[2].getDecimal()));
				_fe3d.image_move(args[0].getString(), change);
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:image_move_to")
	{
		auto types = { SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL };

		if (_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if (_validateFe3dImage(args[0].getString()))
			{
				fvec2 target = _convertGuiSizeToViewport(fvec2(args[1].getDecimal(), args[2].getDecimal()));
				fvec2 speed = _convertGuiSizeToViewport(fvec2(args[3].getDecimal(), args[3].getDecimal()));
				_fe3d.image_moveTo(args[0].getString(), target, speed.x);
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:image_set_rotation")
	{
		auto types = { SVT::STRING, SVT::DECIMAL };

		if (_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if (_validateFe3dImage(args[0].getString()))
			{
				_fe3d.image_setRotation(args[0].getString(), args[1].getDecimal());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:image_rotate")
	{
		auto types = { SVT::STRING, SVT::DECIMAL };

		if (_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if (_validateFe3dImage(args[0].getString()))
			{
				_fe3d.image_rotate(args[0].getString(), args[1].getDecimal());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:image_rotate_to")
	{
		auto types = { SVT::STRING, SVT::DECIMAL, SVT::DECIMAL };

		if (_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if (_validateFe3dImage(args[0].getString()))
			{
				_fe3d.image_rotateTo(args[0].getString(), args[1].getDecimal(), args[2].getDecimal());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:image_set_size")
	{
		auto types = { SVT::STRING, SVT::DECIMAL, SVT::DECIMAL };

		if (_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if (_validateFe3dImage(args[0].getString()))
			{
				fvec2 size = _convertGuiSizeToViewport(fvec2(args[1].getDecimal(), args[2].getDecimal()));
				_fe3d.image_setSize(args[0].getString(), size);
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:image_scale")
	{
		auto types = { SVT::STRING, SVT::DECIMAL, SVT::DECIMAL };

		if (_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if (_validateFe3dImage(args[0].getString()))
			{
				fvec2 change = _convertGuiSizeToViewport(fvec2(args[1].getDecimal(), args[2].getDecimal()));
				_fe3d.image_scale(args[0].getString(), change);
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:image_scale_to")
	{
		auto types = { SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL };

		if (_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if (_validateFe3dImage(args[0].getString()))
			{
				fvec2 target = _convertGuiSizeToViewport(fvec2(args[1].getDecimal(), args[2].getDecimal()));
				fvec2 speed = _convertGuiSizeToViewport(fvec2(args[3].getDecimal(), args[3].getDecimal()));
				_fe3d.image_scaleTo(args[0].getString(), target, speed.x);
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:image_set_color")
	{
		auto types = { SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL };

		if (_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if (_validateFe3dImage(args[0].getString()))
			{
				_fe3d.image_setColor(args[0].getString(),
					fvec3(args[1].getDecimal(), args[2].getDecimal(), args[3].getDecimal()));
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:image_set_wireframe_color")
	{
		auto types = { SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL };

		if (_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if (_validateFe3dImage(args[0].getString()))
			{
				_fe3d.image_setWireframeColor(args[0].getString(),
					fvec3(args[1].getDecimal(), args[2].getDecimal(), args[3].getDecimal()));
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:image_set_transparency")
	{
		auto types = { SVT::STRING, SVT::DECIMAL };

		if (_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if (_validateFe3dImage(args[0].getString()))
			{
				_fe3d.image_setTransparency(args[0].getString(), args[1].getDecimal());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:image_set_wireframed")
	{
		auto types = { SVT::STRING, SVT::BOOLEAN };

		if (_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if (_validateFe3dImage(args[0].getString()))
			{
				_fe3d.image_setWireframed(args[0].getString(), args[1].getBoolean());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:image_set_mirrored_horizontally")
	{
		auto types = { SVT::STRING, SVT::BOOLEAN };

		if (_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if (_validateFe3dImage(args[0].getString()))
			{
				_fe3d.image_setMirroredHorizontally(args[0].getString(), args[1].getBoolean());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if (functionName == "fe3d:image_set_mirrored_vertically")
	{
		auto types = { SVT::STRING, SVT::BOOLEAN };

		if (_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if (_validateFe3dImage(args[0].getString()))
			{
				_fe3d.image_setMirroredVertically(args[0].getString(), args[1].getBoolean());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else
	{
		return false;
	}

	if (_fe3d.server_isRunning())
	{
		_throwScriptError("cannot access `fe3d:image` functionality as networking server!");
	}

	return true;
}