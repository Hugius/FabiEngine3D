#include "script_interpreter.hpp"

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dPointlightGetter(const string& functionName, vector<ScriptValue>& args, vector<ScriptValue>& returnValues)
{
	if(functionName == "fe3d:pointlight_is_existing")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(!_validateFe3dID(args[0].getString()))
			{
				return true;
			}

			const auto result = _fe3d->pointlight_isExisting(args[0].getString());
			returnValues.push_back(ScriptValue(SVT::BOOLEAN, result));
		}
	}
	else if(functionName == "fe3d:pointlight_find_ids")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(!_validateFe3dID(args[0].getString()))
			{
				return true;
			}

			for(const auto& ID : _fe3d->pointlight_getIDs())
			{
				if(args[0].getString() == ID.substr(0, args[0].getString().size()))
				{
					if(ID[0] != '@')
					{
						returnValues.push_back(ScriptValue(SVT::STRING, ID));
					}
				}
			}
		}
	}
	else if(functionName == "fe3d:pointlight_get_ids")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->pointlight_getIDs();

			for(const auto& ID : result)
			{
				if(ID[0] != '@')
				{
					returnValues.push_back(ScriptValue(SVT::STRING, ID));
				}
			}
		}
	}
	else if(functionName == "fe3d:pointlight_is_visible")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dPointlight(args[0].getString()))
			{
				const auto result = _fe3d->pointlight_isVisible(args[0].getString());
				returnValues.push_back(ScriptValue(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:pointlight_get_position_x")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dPointlight(args[0].getString()))
			{
				const auto result = _fe3d->pointlight_getPosition(args[0].getString()).x;
				returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:pointlight_get_position_y")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dPointlight(args[0].getString()))
			{
				const auto result = _fe3d->pointlight_getPosition(args[0].getString()).y;
				returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:pointlight_get_position_z")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dPointlight(args[0].getString()))
			{
				const auto result = _fe3d->pointlight_getPosition(args[0].getString()).z;
				returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:pointlight_get_radius_x")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dPointlight(args[0].getString()))
			{
				const auto result = _fe3d->pointlight_getRadius(args[0].getString()).x;
				returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:pointlight_get_radius_y")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dPointlight(args[0].getString()))
			{
				const auto result = _fe3d->pointlight_getRadius(args[0].getString()).y;
				returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:pointlight_get_radius_z")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dPointlight(args[0].getString()))
			{
				const auto result = _fe3d->pointlight_getRadius(args[0].getString()).z;
				returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:pointlight_get_color_r")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dPointlight(args[0].getString()))
			{
				const auto result = _fe3d->pointlight_getColor(args[0].getString()).r;
				returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:pointlight_get_color_g")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dPointlight(args[0].getString()))
			{
				const auto result = _fe3d->pointlight_getColor(args[0].getString()).g;
				returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:pointlight_get_color_b")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dPointlight(args[0].getString()))
			{
				const auto result = _fe3d->pointlight_getColor(args[0].getString()).b;
				returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:pointlight_get_intensity")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dPointlight(args[0].getString()))
			{
				const auto result = _fe3d->pointlight_getIntensity(args[0].getString());
				returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:pointlight_get_shape")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dPointlight(args[0].getString()))
			{
				const auto result = _fe3d->pointlight_getShape(args[0].getString());
				switch(result)
				{
					case PointlightShape::CIRCLE:
					{
						returnValues.push_back(ScriptValue(SVT::STRING, "CIRCLE"));
						break;
					}
					case PointlightShape::SQUARE:
					{
						returnValues.push_back(ScriptValue(SVT::STRING, "SQUARE"));
						break;
					}
				}
			}
		}
	}
	else
	{
		return false;
	}

	if(_fe3d->server_isRunning())
	{
		_throwScriptError("cannot access `fe3d:pointlight` functionality as networking server!");
	}

	return true;
}