#include "script_interpreter.hpp"
#include "configuration.hpp"
#include "tools.hpp"

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dTextSetterFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues)
{
	// Determine type of function
	if(functionName == "fe3d:text_place")
	{
		auto types = {SVT::STRING, SVT::STRING, SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Temporary values 
			const auto ID = arguments[0].getString();

			// @ sign is reserved
			if(ID.front() == '@')
			{
				_throwScriptError("new text ID \"" + ID + "\" cannot start with '@'");
				return true;
			}

			// Check if text entity already exists
			if(_fe3d.text_isExisting(ID))
			{
				_throwScriptError("text with ID \"" + ID + "\" already exists!");
				return true;
			}

			// Create text
			_fe3d.text_create(ID, true, true);

			// Set font
			const auto isExported = Config::getInst().isApplicationExported();
			const auto rootPath = Tools::getRootDirectoryPath();
			const string filePath = string(rootPath + (isExported ? "" : ("projects\\" + _currentProjectID + "\\")) + "assets\\fonts\\" + arguments[1].getString());
			_fe3d.text_setFont(ID, filePath);

			// Set properties
			_fe3d.text_setPosition(ID, _convertGuiPositionToViewport(fvec2(arguments[3].getDecimal(), arguments[4].getDecimal())));
			_fe3d.text_setRotation(ID, arguments[5].getDecimal());
			_fe3d.text_setSize(ID, _convertGuiSizeToViewport(fvec2(arguments[6].getDecimal(), arguments[7].getDecimal())));
			_fe3d.text_setTextContent(ID, arguments[2].getString());

			// In-engine viewport boundaries
			if(!Config::getInst().isApplicationExported())
			{
				auto minPosition = Math::convertToNDC(Tools::convertFromScreenCoords(Config::getInst().getViewportPosition()));
				auto maxPosition = Math::convertToNDC(Tools::convertFromScreenCoords(Config::getInst().getViewportPosition() + Config::getInst().getViewportSize()));
				_fe3d.text_setMinPosition(arguments[0].getString(), minPosition);
				_fe3d.text_setMaxPosition(arguments[0].getString(), maxPosition);
			}

			// Return
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:text_delete")
	{
		auto types = {SVT::STRING};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dText(arguments[0].getString()))
			{
				_fe3d.text_delete(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:text_set_visible")
	{
		auto types = {SVT::STRING, SVT::BOOLEAN};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dText(arguments[0].getString()))
			{
				_fe3d.text_setVisible(arguments[0].getString(), arguments[1].getBoolean());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:text_set_position")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dText(arguments[0].getString()))
			{
				fvec2 position = _convertGuiPositionToViewport(fvec2(arguments[1].getDecimal(), arguments[2].getDecimal()));
				_fe3d.text_setPosition(arguments[0].getString(), position);
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:text_move")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dText(arguments[0].getString()))
			{
				fvec2 change = _convertGuiSizeToViewport(fvec2(arguments[1].getDecimal(), arguments[2].getDecimal()));
				_fe3d.text_move(arguments[0].getString(), change);
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:text_move_to")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dText(arguments[0].getString()))
			{
				fvec2 target = _convertGuiSizeToViewport(fvec2(arguments[1].getDecimal(), arguments[2].getDecimal()));
				fvec2 speed = _convertGuiSizeToViewport(fvec2(arguments[3].getDecimal(), arguments[3].getDecimal()));
				_fe3d.text_moveTo(arguments[0].getString(), target, speed.x);
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:text_rotate_to")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dText(arguments[0].getString()))
			{
				_fe3d.text_rotateTo(arguments[0].getString(), arguments[1].getDecimal(), arguments[2].getDecimal());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:text_scale_to")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dText(arguments[0].getString()))
			{
				fvec2 target = _convertGuiSizeToViewport(fvec2(arguments[1].getDecimal(), arguments[2].getDecimal()));
				fvec2 speed = _convertGuiSizeToViewport(fvec2(arguments[3].getDecimal(), arguments[3].getDecimal()));
				_fe3d.text_scaleTo(arguments[0].getString(), target, speed.x);
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:text_set_rotation")
	{
		auto types = {SVT::STRING, SVT::DECIMAL};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dText(arguments[0].getString()))
			{
				_fe3d.text_setRotation(arguments[0].getString(), arguments[1].getDecimal());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:text_rotate")
	{
		auto types = {SVT::STRING, SVT::DECIMAL};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dText(arguments[0].getString()))
			{
				_fe3d.text_rotate(arguments[0].getString(), arguments[1].getDecimal());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:text_set_size")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dText(arguments[0].getString()))
			{
				fvec2 size = _convertGuiSizeToViewport(fvec2(arguments[1].getDecimal(), arguments[2].getDecimal()));
				_fe3d.text_setSize(arguments[0].getString(), size);
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:text_scale")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dText(arguments[0].getString()))
			{
				fvec2 change = _convertGuiSizeToViewport(fvec2(arguments[1].getDecimal(), arguments[2].getDecimal()));
				_fe3d.text_scale(arguments[0].getString(), change);
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:text_set_color")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dText(arguments[0].getString()))
			{
				_fe3d.text_setColor(arguments[0].getString(),
										  fvec3(arguments[1].getDecimal(), arguments[2].getDecimal(), arguments[3].getDecimal()));
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:text_set_content")
	{
		auto types = {SVT::STRING, SVT::STRING};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dText(arguments[0].getString()))
			{
				_fe3d.text_setTextContent(arguments[0].getString(), arguments[1].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:text_set_transparency")
	{
		auto types = {SVT::STRING, SVT::DECIMAL};

		// Validate arguments
		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Validate existence
			if(_validateFe3dText(arguments[0].getString()))
			{
				_fe3d.text_setTransparency(arguments[0].getString(), arguments[1].getDecimal());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else
	{
		return false;
	}

	// Cannot execute text functionality when server is running
	if(_fe3d.server_isRunning())
	{
		_throwScriptError("cannot access `fe3d:text` functionality as a networking server!");
	}

	// Return
	return true;
}