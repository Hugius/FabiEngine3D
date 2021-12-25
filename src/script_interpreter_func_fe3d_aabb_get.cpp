#include "script_interpreter.hpp"

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dAabbGetter(const string& functionName, vector<ScriptValue>& args, vector<ScriptValue>& returnValues)
{
	if(functionName == "fe3d:aabb_find_ids")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			// Validate ID
			if(!_validateFe3dID(args[0].getString()))
			{
				return true;
			}

			// Find full entity IDs based on sub ID
			for(const auto& ID : _fe3d.aabb_getIDs())
			{
				// If substring matches
				if(args[0].getString() == ID.substr(0, args[0].getString().size()))
				{
					// Cannot be template
					if(ID[0] != '@')
					{
						// Only non-bound AABBs
						if(!_fe3d.aabb_hasParent(ID))
						{
							returnValues.push_back(ScriptValue(_fe3d, SVT::STRING, ID));
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
			// Validate ID
			if(!_validateFe3dID(args[0].getString()))
			{
				return true;
			}

			// Cannot access a bound entity
			if(!_fe3d.aabb_getParentEntityID(args[0].getString()).empty())
			{
				_throwScriptError("cannot access AABB with ID \"" + args[0].getString() + "\": bound to model or billboard!");
				return true;
			}

			// Check if existing
			auto result = _fe3d.aabb_isExisting(args[0].getString());
			returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
		}
	}
	else if(functionName == "fe3d:aabb_is_visible")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAabb(args[0].getString()))
			{
				// Cannot access a bound entity
				if(!_fe3d.aabb_getParentEntityID(args[0].getString()).empty())
				{
					_throwScriptError("cannot access AABB with ID \"" + args[0].getString() + "\": bound to model or billboard!");
					return true;
				}

				// Get visibility
				auto result = _fe3d.aabb_isVisible(args[0].getString());

				// Return
				returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:aabb_get_position_x")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAabb(args[0].getString()))
			{
				// Cannot access a bound entity
				if(!_fe3d.aabb_getParentEntityID(args[0].getString()).empty())
				{
					_throwScriptError("cannot access AABB with ID \"" + args[0].getString() + "\": bound to model or billboard!");
					return true;
				}

				// Return
				auto result = _fe3d.aabb_getPosition(args[0].getString()).x;
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:aabb_get_position_y")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAabb(args[0].getString()))
			{
				// Cannot access a bound entity
				if(!_fe3d.aabb_getParentEntityID(args[0].getString()).empty())
				{
					_throwScriptError("cannot access AABB with ID \"" + args[0].getString() + "\": bound to model or billboard!");
					return true;
				}

				// Return
				auto result = _fe3d.aabb_getPosition(args[0].getString()).y;
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:aabb_get_position_z")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAabb(args[0].getString()))
			{
				// Cannot access a bound entity
				if(!_fe3d.aabb_getParentEntityID(args[0].getString()).empty())
				{
					_throwScriptError("cannot access AABB with ID \"" + args[0].getString() + "\": bound to model or billboard!");
					return true;
				}

				// Return
				auto result = _fe3d.aabb_getPosition(args[0].getString()).z;
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:aabb_get_size_x")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAabb(args[0].getString()))
			{
				// Cannot access a bound entity
				if(!_fe3d.aabb_getParentEntityID(args[0].getString()).empty())
				{
					_throwScriptError("cannot access AABB with ID \"" + args[0].getString() + "\": bound to model or billboard!");
					return true;
				}

				// Return
				auto result = _fe3d.aabb_getSize(args[0].getString()).x;
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:aabb_get_size_y")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAabb(args[0].getString()))
			{
				// Cannot access a bound entity
				if(!_fe3d.aabb_getParentEntityID(args[0].getString()).empty())
				{
					_throwScriptError("cannot access AABB with ID \"" + args[0].getString() + "\": bound to model or billboard!");
					return true;
				}

				// Return
				auto result = _fe3d.aabb_getSize(args[0].getString()).y;
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:aabb_get_size_z")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAabb(args[0].getString()))
			{
				// Cannot access a bound entity
				if(!_fe3d.aabb_getParentEntityID(args[0].getString()).empty())
				{
					_throwScriptError("cannot access AABB with ID \"" + args[0].getString() + "\": bound to model or billboard!");
					return true;
				}

				// Return
				auto result = _fe3d.aabb_getSize(args[0].getString()).z;
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:aabb_get_ids")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			auto result = _fe3d.aabb_getIDs();

			// Iterate through AABBs
			for(const auto& ID : result)
			{
				// Cannot be template
				if(ID[0] != '@')
				{
					// Only non-bound AABBs
					if(!_fe3d.aabb_hasParent(ID))
					{
						returnValues.push_back(ScriptValue(_fe3d, SVT::STRING, ID));
					}
				}
			}
		}
	}
	else if(functionName == "fe3d:aabb_is_raycast_responsive")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAabb(args[0].getString()))
			{
				// Cannot access a bound entity
				if(!_fe3d.aabb_getParentEntityID(args[0].getString()).empty())
				{
					_throwScriptError("cannot access AABB with ID \"" + args[0].getString() + "\": bound to model or billboard!");
					return true;
				}

				// Return
				auto result = _fe3d.aabb_getSize(args[0].getString()).z;
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:aabb_get_color_r")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAabb(args[0].getString()))
			{
				// Cannot access a bound entity
				if(!_fe3d.aabb_getParentEntityID(args[0].getString()).empty())
				{
					_throwScriptError("cannot access AABB with ID \"" + args[0].getString() + "\": bound to model or billboard!");
					return true;
				}

				// Return
				auto result = _fe3d.aabb_getColor(args[0].getString()).r;
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:aabb_get_color_g")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAabb(args[0].getString()))
			{
				// Cannot access a bound entity
				if(!_fe3d.aabb_getParentEntityID(args[0].getString()).empty())
				{
					_throwScriptError("cannot access AABB with ID \"" + args[0].getString() + "\": bound to model or billboard!");
					return true;
				}

				// Return
				auto result = _fe3d.aabb_getColor(args[0].getString()).g;
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:aabb_get_color_b")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAabb(args[0].getString()))
			{
				// Cannot access a bound entity
				if(!_fe3d.aabb_getParentEntityID(args[0].getString()).empty())
				{
					_throwScriptError("cannot access AABB with ID \"" + args[0].getString() + "\": bound to model or billboard!");
					return true;
				}

				// Return
				auto result = _fe3d.aabb_getColor(args[0].getString()).b;
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else
	{
		return false;
	}

	if(_fe3d.server_isRunning())
	{
		_throwScriptError("cannot access `fe3d:aabb` functionality as networking server!");
	}

	return true;
}