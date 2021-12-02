#include "script_interpreter.hpp"
#include "configuration.hpp"
#include "tools.hpp"

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dImageSetter(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues)
{
	// Determine type of function
	if(functionName == "fe3d:image_place")
	{
		auto types = {SVT::STRING, SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Temporary values
			auto ID = arguments[0].getString();

			// @ sign is reserved
			if(ID.front() == '@')
			{
				_throwScriptError("new image ID (\"" + ID + "\") cannot start with '@'");
				return true;
			}

			// Check if imageEntity already exists
			if(_fe3d.image_isExisting(ID))
			{
				_throwScriptError("image with ID \"" + ID + "\" already exists!");
				return true;
			}

			// Create image
			_fe3d.image_create(ID, true);

			// Set diffuse map
			const auto isExported = Config::getInst().isApplicationExported();
			const auto rootPath = Tools::getRootDirectoryPath();
			const string targetDirectoryPath = string(rootPath + (isExported ? "" : ("projects\\" + _currentProjectID + "\\")) + "assets\\textures\\image_maps\\");
			const string filePath = (targetDirectoryPath + arguments[1].getString());
			_fe3d.image_setDiffuseMap(ID, filePath);

			// Set properties
			_fe3d.image_setPosition(ID, _convertGuiPositionToViewport(fvec2(arguments[2].getDecimal(), arguments[3].getDecimal())));
			_fe3d.image_setRotation(ID, arguments[4].getDecimal());
			_fe3d.image_setSize(ID, _convertGuiSizeToViewport(fvec2(arguments[5].getDecimal(), arguments[6].getDecimal())));

			// In-engine viewport boundaries
			if(!Config::getInst().isApplicationExported())
			{
				auto minPosition = Math::convertToNDC(Tools::convertFromScreenCoords(Config::getInst().getViewportPosition()));
				auto maxPosition = Math::convertToNDC(Tools::convertFromScreenCoords(Config::getInst().getViewportPosition() + Config::getInst().getViewportSize()));
				_fe3d.image_setMinPosition(ID, minPosition);
				_fe3d.image_setMaxPosition(ID, maxPosition);
			}

			// Return
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:image_delete")
	{
		auto types = {SVT::STRING};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dImage(arguments[0].getString()))
			{
				_fe3d.image_delete(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:image_set_visible")
	{
		auto types = {SVT::STRING, SVT::BOOLEAN};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dImage(arguments[0].getString()))
			{
				_fe3d.image_setVisible(arguments[0].getString(), arguments[1].getBoolean());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:image_set_position")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dImage(arguments[0].getString()))
			{
				fvec2 position = _convertGuiPositionToViewport(fvec2(arguments[1].getDecimal(), arguments[2].getDecimal()));
				_fe3d.image_setPosition(arguments[0].getString(), position);
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:image_move")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dImage(arguments[0].getString()))
			{
				fvec2 change = _convertGuiSizeToViewport(fvec2(arguments[1].getDecimal(), arguments[2].getDecimal()));
				_fe3d.image_move(arguments[0].getString(), change);
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:image_move_to")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dImage(arguments[0].getString()))
			{
				fvec2 target = _convertGuiSizeToViewport(fvec2(arguments[1].getDecimal(), arguments[2].getDecimal()));
				fvec2 speed = _convertGuiSizeToViewport(fvec2(arguments[3].getDecimal(), arguments[3].getDecimal()));
				_fe3d.image_moveTo(arguments[0].getString(), target, speed.x);
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:image_set_rotation")
	{
		auto types = {SVT::STRING, SVT::DECIMAL};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dImage(arguments[0].getString()))
			{
				_fe3d.image_setRotation(arguments[0].getString(), arguments[1].getDecimal());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:image_rotate")
	{
		auto types = {SVT::STRING, SVT::DECIMAL};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dImage(arguments[0].getString()))
			{
				_fe3d.image_rotate(arguments[0].getString(), arguments[1].getDecimal());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:image_rotate_to")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dImage(arguments[0].getString()))
			{
				_fe3d.image_rotateTo(arguments[0].getString(), arguments[1].getDecimal(), arguments[2].getDecimal());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:image_set_size")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dImage(arguments[0].getString()))
			{
				fvec2 size = _convertGuiSizeToViewport(fvec2(arguments[1].getDecimal(), arguments[2].getDecimal()));
				_fe3d.image_setSize(arguments[0].getString(), size);
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:image_scale")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dImage(arguments[0].getString()))
			{
				fvec2 change = _convertGuiSizeToViewport(fvec2(arguments[1].getDecimal(), arguments[2].getDecimal()));
				_fe3d.image_scale(arguments[0].getString(), change);
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:image_scale_to")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dImage(arguments[0].getString()))
			{
				fvec2 target = _convertGuiSizeToViewport(fvec2(arguments[1].getDecimal(), arguments[2].getDecimal()));
				fvec2 speed = _convertGuiSizeToViewport(fvec2(arguments[3].getDecimal(), arguments[3].getDecimal()));
				_fe3d.image_scaleTo(arguments[0].getString(), target, speed.x);
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:image_set_color")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dImage(arguments[0].getString()))
			{
				_fe3d.image_setColor(arguments[0].getString(),
										   fvec3(arguments[1].getDecimal(), arguments[2].getDecimal(), arguments[3].getDecimal()));
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:image_set_transparency")
	{
		auto types = {SVT::STRING, SVT::DECIMAL};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dImage(arguments[0].getString()))
			{
				_fe3d.image_setTransparency(arguments[0].getString(), arguments[1].getDecimal());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:image_start_animation")
	{
		auto types = {SVT::STRING, SVT::INTEGER, SVT::INTEGER, SVT::INTEGER, SVT::INTEGER};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dImage(arguments[0].getString()))
			{
				_fe3d.image_setSpriteAnimationRowCount(arguments[0].getString(), arguments[1].getInteger());
				_fe3d.image_setSpriteAnimationColumnCount(arguments[0].getString(), arguments[2].getInteger());
				_fe3d.image_setSpriteAnimationFramestep(arguments[0].getString(), arguments[3].getInteger());
				_fe3d.image_startSpriteAnimation(arguments[0].getString(), arguments[4].getInteger());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:image_pause_animation")
	{
		auto types = {SVT::STRING};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dImage(arguments[0].getString()))
			{
				_fe3d.image_pauseSpriteAnimation(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:image_resume_animation")
	{
		auto types = {SVT::STRING};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dImage(arguments[0].getString()))
			{
				_fe3d.image_resumeSpriteAnimation(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:image_stop_animation")
	{
		auto types = {SVT::STRING};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dImage(arguments[0].getString()))
			{
				_fe3d.image_stopSpriteAnimation(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:image_set_mirrored_horizontally")
	{
		auto types = {SVT::STRING, SVT::BOOLEAN};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dImage(arguments[0].getString()))
			{
				_fe3d.image_setMirroredHorizontally(arguments[0].getString(), arguments[1].getBoolean());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:image_set_mirrored_vertically")
	{
		auto types = {SVT::STRING, SVT::BOOLEAN};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dImage(arguments[0].getString()))
			{
				_fe3d.image_setMirroredVertically(arguments[0].getString(), arguments[1].getBoolean());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else
	{
		return false;
	}

	// Cannot execute image functionality when server is running
	if(_fe3d.server_isRunning())
	{
		_throwScriptError("cannot access `fe3d:image` functionality as networking server!");
	}

	// Return
	return true;
}