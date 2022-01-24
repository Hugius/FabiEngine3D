#include "script_interpreter.hpp"

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dAabbSetter(const string& functionName, vector<ScriptValue>& args, vector<ScriptValue>& returnValues)
{
	if(functionName == "fe3d:aabb_place")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(!_validateFe3dID(args[0].getString()))
			{
				return true;
			}

			if(_fe3d->aabb_isExisting(args[0].getString()))
			{
				_throwScriptError("AABB already exists!");
				return true;
			}

			_fe3d->aabb_create(args[0].getString(), false);
			_fe3d->aabb_setBasePosition(args[0].getString(), fvec3(args[1].getDecimal(), args[2].getDecimal(), args[3].getDecimal()));
			_fe3d->aabb_setBaseSize(args[0].getString(), fvec3(args[4].getDecimal(), args[5].getDecimal(), args[6].getDecimal()));

			returnValues.push_back(ScriptValue(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:aabb_delete")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAabb(args[0].getString()))
			{
				if(!_fe3d->aabb_getParentEntityID(args[0].getString()).empty())
				{
					_throwScriptError("cannot delete AABB with id \"" + args[0].getString() + "\": bound to model or quad3d!");
					return true;
				}

				_fe3d->aabb_delete(args[0].getString());

				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:aabb_delete_all")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			for(const auto& id : _fe3d->aabb_getIDs())
			{
				if(id[0] != '@')
				{
					if(_fe3d->aabb_getParentEntityID(args[0].getString()).empty())
					{
						_fe3d->aabb_delete(id);
					}
				}
			}

			returnValues.push_back(ScriptValue(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:aabb_set_visible")
	{
		auto types = {SVT::STRING, SVT::BOOLEAN};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAabb(args[0].getString()))
			{
				if(!_fe3d->aabb_getParentEntityID(args[0].getString()).empty())
				{
					_throwScriptError("cannot access AABB with id \"" + args[0].getString() + "\": bound to model or quad3d!");
					return true;
				}

				_fe3d->aabb_setVisible(args[0].getString(), args[1].getBoolean());

				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:aabb_set_position")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAabb(args[0].getString()))
			{
				if(!_fe3d->aabb_getParentEntityID(args[0].getString()).empty())
				{
					_throwScriptError("cannot access AABB with id \"" + args[0].getString() + "\": bound to model or quad3d!");
					return true;
				}

				_fe3d->aabb_setBasePosition(args[0].getString(), fvec3(args[1].getDecimal(), args[2].getDecimal(), args[3].getDecimal()));

				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:aabb_set_size")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAabb(args[0].getString()))
			{
				if(!_fe3d->aabb_getParentEntityID(args[0].getString()).empty())
				{
					_throwScriptError("cannot access AABB with id \"" + args[0].getString() + "\": bound to model or quad3d!");
					return true;
				}

				_fe3d->aabb_setBaseSize(args[0].getString(), fvec3(args[1].getDecimal(), args[2].getDecimal(), args[3].getDecimal()));

				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:aabb_move")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAabb(args[0].getString()))
			{
				if(!_fe3d->aabb_getParentEntityID(args[0].getString()).empty())
				{
					_throwScriptError("cannot access AABB with id \"" + args[0].getString() + "\": bound to model or quad3d!");
					return true;
				}

				_fe3d->aabb_move(args[0].getString(), fvec3(args[1].getDecimal(), args[2].getDecimal(), args[3].getDecimal()));

				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:aabb_scale")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAabb(args[0].getString()))
			{
				if(!_fe3d->aabb_getParentEntityID(args[0].getString()).empty())
				{
					_throwScriptError("cannot access AABB with id \"" + args[0].getString() + "\": bound to model or quad3d!");
					return true;
				}

				_fe3d->aabb_scale(args[0].getString(), fvec3(args[1].getDecimal(), args[2].getDecimal(), args[3].getDecimal()));

				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:aabb_move_to")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAabb(args[0].getString()))
			{
				if(!_fe3d->aabb_getParentEntityID(args[0].getString()).empty())
				{
					_throwScriptError("cannot access AABB with id \"" + args[0].getString() + "\": bound to model or quad3d!");
					return true;
				}

				_fe3d->aabb_moveTo(args[0].getString(), fvec3(args[1].getDecimal(), args[2].getDecimal(), args[3].getDecimal()), args[4].getDecimal());

				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:aabb_scale_to")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAabb(args[0].getString()))
			{
				if(!_fe3d->aabb_getParentEntityID(args[0].getString()).empty())
				{
					_throwScriptError("cannot access AABB with id \"" + args[0].getString() + "\": bound to model or quad3d!");
					return true;
				}

				_fe3d->aabb_scaleTo(args[0].getString(), fvec3(args[1].getDecimal(), args[2].getDecimal(), args[3].getDecimal()), args[4].getDecimal());

				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:aabb_set_color")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAabb(args[0].getString()))
			{
				if(!_fe3d->aabb_getParentEntityID(args[0].getString()).empty())
				{
					_throwScriptError("cannot access AABB with id \"" + args[0].getString() + "\": bound to model or quad3d!");
					return true;
				}

				_fe3d->aabb_setColor(args[0].getString(), fvec3(args[1].getDecimal(), args[2].getDecimal(), args[3].getDecimal()));

				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:aabb_set_raycast_responsive")
	{
		auto types = {SVT::STRING, SVT::BOOLEAN};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAabb(args[0].getString()))
			{
				if(!_fe3d->aabb_getParentEntityID(args[0].getString()).empty())
				{
					_throwScriptError("cannot access AABB with id \"" + args[0].getString() + "\": bound to model or quad3d!");
					return true;
				}

				_fe3d->aabb_setRaycastResponsive(args[0].getString(), args[1].getBoolean());

				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:aabb_set_collision_responsive")
	{
		auto types = {SVT::STRING, SVT::BOOLEAN};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAabb(args[0].getString()))
			{
				if(!_fe3d->aabb_getParentEntityID(args[0].getString()).empty())
				{
					_throwScriptError("cannot access AABB with id \"" + args[0].getString() + "\": bound to model or quad3d!");
					return true;
				}

				_fe3d->aabb_setCollisionResponsive(args[0].getString(), args[1].getBoolean());

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
		_throwScriptError("cannot access `fe3d:aabb` functionality as networking server!");
	}

	return true;
}