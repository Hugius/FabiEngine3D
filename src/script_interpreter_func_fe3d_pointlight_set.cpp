#include "script_interpreter.hpp"
#include "logger.hpp"

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dPointlightSetter(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues)
{
	if(functionName == "fe3d:pointlight_place")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Temporary values
			const auto ID = arguments[0].getString();

			// @ sign is reserved
			if(ID[0] == '@')
			{
				_throwScriptError("new pointlight ID (\"" + ID + "\") cannot start with '@'");
				return true;
			}

			// Check if pointlight entity already exists
			if(_fe3d.pointlight_isExisting(ID))
			{
				_throwScriptError("pointlight with ID \"" + ID + "\" already exists!");
				return true;
			}

			// Create pointlight
			_fe3d.pointlight_create(ID);
			_fe3d.pointlight_setPosition(ID, fvec3(arguments[1].getDecimal(), arguments[2].getDecimal(), arguments[3].getDecimal()));
			_fe3d.pointlight_setRadius(ID, fvec3(arguments[4].getDecimal(), arguments[5].getDecimal(), arguments[6].getDecimal()));
			_fe3d.pointlight_setColor(ID, fvec3(arguments[7].getDecimal(), arguments[8].getDecimal(), arguments[9].getDecimal()));
			_fe3d.pointlight_setIntensity(ID, arguments[10].getDecimal());

			// Return
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:pointlight_delete")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dPointlight(arguments[0].getString()))
			{
				_fe3d.pointlight_delete(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:pointlight_delete_all")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			// Iterate through pointlights
			for(const auto& ID : _fe3d.pointlight_getIDs())
			{
				// @ sign is reserved
				if(ID[0] != '@')
				{
					_fe3d.pointlight_delete(ID);
				}
			}

			// Return
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:pointlight_set_visible")
	{
		auto types = {SVT::STRING, SVT::BOOLEAN};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dPointlight(arguments[0].getString()))
			{
				_fe3d.pointlight_setVisible(arguments[0].getString(), arguments[1].getBoolean());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:pointlight_set_position")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dPointlight(arguments[0].getString()))
			{
				_fe3d.pointlight_setPosition(arguments[0].getString(),
											 fvec3(arguments[1].getDecimal(), arguments[2].getDecimal(), arguments[3].getDecimal()));
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:pointlight_move")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dPointlight(arguments[0].getString()))
			{
				_fe3d.pointlight_move(arguments[0].getString(),
									  fvec3(arguments[1].getDecimal(), arguments[2].getDecimal(), arguments[3].getDecimal()));
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:pointlight_move_to")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dPointlight(arguments[0].getString()))
			{
				_fe3d.pointlight_moveTo(arguments[0].getString(),
										fvec3(arguments[1].getDecimal(), arguments[2].getDecimal(), arguments[3].getDecimal()), arguments[4].getDecimal());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:pointlight_set_radius")
	{
		auto types = {SVT::STRING, SVT::DECIMAL};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dPointlight(arguments[0].getString()))
			{
				_fe3d.pointlight_setRadius(arguments[0].getString(), arguments[1].getDecimal());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:pointlight_set_color")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dPointlight(arguments[0].getString()))
			{
				_fe3d.pointlight_setColor(arguments[0].getString(),
										  fvec3(arguments[1].getDecimal(), arguments[2].getDecimal(), arguments[3].getDecimal()));
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:pointlight_set_intensity")
	{
		auto types = {SVT::STRING, SVT::DECIMAL};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dPointlight(arguments[0].getString()))
			{
				_fe3d.pointlight_setIntensity(arguments[0].getString(), arguments[1].getDecimal());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:pointlight_set_shape")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dPointlight(arguments[0].getString()))
			{
				if(arguments[1].getString() == "CIRCLE")
				{
					_fe3d.pointlight_setShape(arguments[0].getString(), PointlightShape::CIRCLE);
					returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
				}
				else if(arguments[1].getString() == "SQUARE")
				{
					_fe3d.pointlight_setShape(arguments[0].getString(), PointlightShape::SQUARE);
					returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
				}
				else
				{
					Logger::throwWarning("invalid shape!");
					returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
				}
			}
		}
	}
	else
	{
		return false;
	}

	// Cannot execute when server is running
	if(_fe3d.server_isRunning())
	{
		_throwScriptError("cannot access `fe3d:pointlight` functionality as networking server!");
	}

	// Return
	return true;
}