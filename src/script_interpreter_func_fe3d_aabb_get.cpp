#include "script_interpreter.hpp"

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dAabbGetter(const string& functionName, const vector<shared_ptr<ScriptValue>>& args, vector<shared_ptr<ScriptValue>>& returnValues)
{
	if(functionName == "fe3d:aabb_find_ids")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(!_validateFe3dId(args[0]->getString()))
			{
				return true;
			}

			for(const auto& result : _fe3d->aabb_getIds())
			{
				if(result[0] != '@')
				{
					if(args[0]->getString() == result.substr(0, args[0]->getString().size()))
					{
						if(!_fe3d->aabb_hasParent(result))
						{
							returnValues.push_back(make_shared<ScriptValue>(SVT::STRING, result));
						}
					}
				}
			}
		}
	}
	else if(functionName == "fe3d:aabb_is_existing")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(!_validateFe3dId(args[0]->getString()))
			{
				return true;
			}

			if(!_fe3d->aabb_getParentId(args[0]->getString()).empty())
			{
				_throwRuntimeError("cannot access a bound AABB");
				return true;
			}

			const auto result = _fe3d->aabb_isExisting(args[0]->getString());

			returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
		}
	}
	else if(functionName == "fe3d:aabb_is_visible")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAabb(args[0]->getString()))
			{
				if(!_fe3d->aabb_getParentId(args[0]->getString()).empty())
				{
					_throwRuntimeError("cannot access a bound AABB");
					return true;
				}

				const auto result = _fe3d->aabb_isVisible(args[0]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:aabb_get_position_x")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAabb(args[0]->getString()))
			{
				if(!_fe3d->aabb_getParentId(args[0]->getString()).empty())
				{
					_throwRuntimeError("cannot access a bound AABB");
					return true;
				}

				const auto result = _fe3d->aabb_getBasePosition(args[0]->getString()).x;

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:aabb_get_position_y")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAabb(args[0]->getString()))
			{
				if(!_fe3d->aabb_getParentId(args[0]->getString()).empty())
				{
					_throwRuntimeError("cannot access a bound AABB");
					return true;
				}

				const auto result = _fe3d->aabb_getBasePosition(args[0]->getString()).y;

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:aabb_get_position_z")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAabb(args[0]->getString()))
			{
				if(!_fe3d->aabb_getParentId(args[0]->getString()).empty())
				{
					_throwRuntimeError("cannot access a bound AABB");
					return true;
				}

				const auto result = _fe3d->aabb_getBasePosition(args[0]->getString()).z;

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:aabb_get_size_x")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAabb(args[0]->getString()))
			{
				if(!_fe3d->aabb_getParentId(args[0]->getString()).empty())
				{
					_throwRuntimeError("cannot access a bound AABB");
					return true;
				}

				const auto result = _fe3d->aabb_getBaseSize(args[0]->getString()).x;

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:aabb_get_size_y")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAabb(args[0]->getString()))
			{
				if(!_fe3d->aabb_getParentId(args[0]->getString()).empty())
				{
					_throwRuntimeError("cannot access a bound AABB");
					return true;
				}

				const auto result = _fe3d->aabb_getBaseSize(args[0]->getString()).y;

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:aabb_get_size_z")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAabb(args[0]->getString()))
			{
				if(!_fe3d->aabb_getParentId(args[0]->getString()).empty())
				{
					_throwRuntimeError("cannot access a bound AABB");
					return true;
				}

				const auto result = _fe3d->aabb_getBaseSize(args[0]->getString()).z;

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:aabb_get_ids")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			for(const auto& result : _fe3d->aabb_getIds())
			{
				if(result[0] != '@')
				{
					if(!_fe3d->aabb_hasParent(result))
					{
						returnValues.push_back(make_shared<ScriptValue>(SVT::STRING, result));
					}
				}
			}
		}
	}
	else if(functionName == "fe3d:aabb_is_collision_responsive")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAabb(args[0]->getString()))
			{
				if(!_fe3d->aabb_getParentId(args[0]->getString()).empty())
				{
					_throwRuntimeError("cannot access a bound AABB");
					return true;
				}

				const auto result = _fe3d->aabb_isCollisionResponsive(args[0]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:aabb_is_raycast_responsive")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAabb(args[0]->getString()))
			{
				if(!_fe3d->aabb_getParentId(args[0]->getString()).empty())
				{
					_throwRuntimeError("cannot access a bound AABB");
					return true;
				}

				const auto result = _fe3d->aabb_isRaycastResponsive(args[0]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:aabb_get_color_r")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAabb(args[0]->getString()))
			{
				if(!_fe3d->aabb_getParentId(args[0]->getString()).empty())
				{
					_throwRuntimeError("cannot access a bound AABB");
					return true;
				}

				const auto result = _fe3d->aabb_getColor(args[0]->getString()).r;

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:aabb_get_color_g")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAabb(args[0]->getString()))
			{
				if(!_fe3d->aabb_getParentId(args[0]->getString()).empty())
				{
					_throwRuntimeError("cannot access a bound AABB");
					return true;
				}

				const auto result = _fe3d->aabb_getColor(args[0]->getString()).g;

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:aabb_get_color_b")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAabb(args[0]->getString()))
			{
				if(!_fe3d->aabb_getParentId(args[0]->getString()).empty())
				{
					_throwRuntimeError("cannot access a bound AABB");
					return true;
				}

				const auto result = _fe3d->aabb_getColor(args[0]->getString()).b;

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else
	{
		return false;
	}

	if(_fe3d->server_isRunning())
	{
		_throwRuntimeError("cannot access `fe3d:aabb` functionality as a networking server");
		return true;
	}

	return true;
}