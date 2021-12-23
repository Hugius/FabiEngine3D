#include "script_interpreter.hpp"

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dAabbSetter(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues)
{
	if(functionName == "fe3d:aabb_place")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// @ signs not allowed
			if(arguments[0].getString().find('@') != string::npos)
			{
				_throwScriptError("new AABB ID (\"" + arguments[0].getString() + "\") cannot contain '@'");
				return true;
			}

			// Check if AABB entity already exists
			if(_fe3d.aabb_isExisting(arguments[0].getString()))
			{
				_throwScriptError("AABB with ID \"" + arguments[0].getString() + "\" already exists!");
				return true;
			}

			// Place AABB
			_fe3d.aabb_create(arguments[0].getString());
			_fe3d.aabb_setBasePosition(arguments[0].getString(), fvec3(arguments[1].getDecimal(), arguments[2].getDecimal(), arguments[3].getDecimal()));
			_fe3d.aabb_setBaseSize(arguments[0].getString(), fvec3(arguments[4].getDecimal(), arguments[5].getDecimal(), arguments[6].getDecimal()));

			// Return
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:aabb_delete")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dAabb(arguments[0].getString()))
			{
				// Cannot delete a bound entity
				if(!_fe3d.aabb_getParentEntityID(arguments[0].getString()).empty())
				{
					_throwScriptError("cannot delete AABB with ID \"" + arguments[0].getString() + "\": bound to model or billboard!");
					return true;
				}

				// Delete AABB
				_fe3d.aabb_delete(arguments[0].getString());

				// Return
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:aabb_delete_all")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			// Iterate through AABBs
			for(const auto& ID : _fe3d.aabb_getIDs())
			{
				// @ signs not allowed
				if(ID[0] != '@')
				{
					// Only non-bound AABBs
					if(_fe3d.aabb_getParentEntityID(arguments[0].getString()).empty())
					{
						_fe3d.aabb_delete(ID);
					}
				}
			}

			// Return
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:aabb_set_visible")
	{
		auto types = {SVT::STRING, SVT::BOOLEAN};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dAabb(arguments[0].getString()))
			{
				// Cannot access a bound entity
				if(!_fe3d.aabb_getParentEntityID(arguments[0].getString()).empty())
				{
					_throwScriptError("cannot access AABB with ID \"" + arguments[0].getString() + "\": bound to model or billboard!");
					return true;
				}

				// Set visibility
				_fe3d.aabb_setVisible(arguments[0].getString(), arguments[1].getBoolean());

				// Return
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:aabb_set_position")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dAabb(arguments[0].getString()))
			{
				// Cannot access a bound entity
				if(!_fe3d.aabb_getParentEntityID(arguments[0].getString()).empty())
				{
					_throwScriptError("cannot access AABB with ID \"" + arguments[0].getString() + "\": bound to model or billboard!");
					return true;
				}

				// Set position
				_fe3d.aabb_setBasePosition(arguments[0].getString(),
										   fvec3(arguments[1].getDecimal(), arguments[2].getDecimal(), arguments[3].getDecimal()));

				// Return
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:aabb_set_size")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dAabb(arguments[0].getString()))
			{
				// Cannot access a bound entity
				if(!_fe3d.aabb_getParentEntityID(arguments[0].getString()).empty())
				{
					_throwScriptError("cannot access AABB with ID \"" + arguments[0].getString() + "\": bound to model or billboard!");
					return true;
				}

				// Set size
				_fe3d.aabb_setBaseSize(arguments[0].getString(),
									   fvec3(arguments[1].getDecimal(), arguments[2].getDecimal(), arguments[3].getDecimal()));

				// Return
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:aabb_move")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dAabb(arguments[0].getString()))
			{
				// Cannot access a bound entity
				if(!_fe3d.aabb_getParentEntityID(arguments[0].getString()).empty())
				{
					_throwScriptError("cannot access AABB with ID \"" + arguments[0].getString() + "\": bound to model or billboard!");
					return true;
				}

				// Move position
				_fe3d.aabb_move(arguments[0].getString(),
								fvec3(arguments[1].getDecimal(), arguments[2].getDecimal(), arguments[3].getDecimal()));

				// Return
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:aabb_scale")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dAabb(arguments[0].getString()))
			{
				// Cannot access a bound entity
				if(!_fe3d.aabb_getParentEntityID(arguments[0].getString()).empty())
				{
					_throwScriptError("cannot access AABB with ID \"" + arguments[0].getString() + "\": bound to model or billboard!");
					return true;
				}

				// Scale size
				_fe3d.aabb_scale(arguments[0].getString(),
								 fvec3(arguments[1].getDecimal(), arguments[2].getDecimal(), arguments[3].getDecimal()));

				// Return
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:aabb_move_to")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dAabb(arguments[0].getString()))
			{
				// Cannot access a bound entity
				if(!_fe3d.aabb_getParentEntityID(arguments[0].getString()).empty())
				{
					_throwScriptError("cannot access AABB with ID \"" + arguments[0].getString() + "\": bound to model or billboard!");
					return true;
				}

				// Move position
				_fe3d.aabb_moveTo(arguments[0].getString(),
								  fvec3(arguments[1].getDecimal(), arguments[2].getDecimal(), arguments[3].getDecimal()), arguments[4].getDecimal());

				// Return
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:aabb_scale_to")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dAabb(arguments[0].getString()))
			{
				// Cannot access a bound entity
				if(!_fe3d.aabb_getParentEntityID(arguments[0].getString()).empty())
				{
					_throwScriptError("cannot access AABB with ID \"" + arguments[0].getString() + "\": bound to model or billboard!");
					return true;
				}

				// Scale size
				_fe3d.aabb_scaleTo(arguments[0].getString(),
								   fvec3(arguments[1].getDecimal(), arguments[2].getDecimal(), arguments[3].getDecimal()), arguments[4].getDecimal());

				// Return
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:aabb_set_color")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dAabb(arguments[0].getString()))
			{
				// Cannot access a bound entity
				if(!_fe3d.aabb_getParentEntityID(arguments[0].getString()).empty())
				{
					_throwScriptError("cannot access AABB with ID \"" + arguments[0].getString() + "\": bound to model or billboard!");
					return true;
				}

				// Set color
				_fe3d.aabb_setColor(arguments[0].getString(),
									fvec3(arguments[1].getDecimal(), arguments[2].getDecimal(), arguments[3].getDecimal()));

				// Return
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:aabb_set_raycast_responsive")
	{
		auto types = {SVT::STRING, SVT::BOOLEAN};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dAabb(arguments[0].getString()))
			{
				// Cannot access a bound entity
				if(!_fe3d.aabb_getParentEntityID(arguments[0].getString()).empty())
				{
					_throwScriptError("cannot access AABB with ID \"" + arguments[0].getString() + "\": bound to model or billboard!");
					return true;
				}

				// Set responsiveness
				_fe3d.aabb_setRaycastResponsive(arguments[0].getString(), arguments[1].getBoolean());

				// Return
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:aabb_set_collision_responsive")
	{
		auto types = {SVT::STRING, SVT::BOOLEAN};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dAabb(arguments[0].getString()))
			{
				// Cannot access a bound entity
				if(!_fe3d.aabb_getParentEntityID(arguments[0].getString()).empty())
				{
					_throwScriptError("cannot access AABB with ID \"" + arguments[0].getString() + "\": bound to model or billboard!");
					return true;
				}

				// Set responsiveness
				_fe3d.aabb_setCollisionResponsive(arguments[0].getString(), arguments[1].getBoolean());

				// Return
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
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
		_throwScriptError("cannot access `fe3d:aabb` functionality as networking server!");
	}

	// Return
	return true;
}