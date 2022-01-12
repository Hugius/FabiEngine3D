#include "script_interpreter.hpp"

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dTextGetter(const string& functionName, vector<ScriptValue>& args, vector<ScriptValue>& returnValues)
{
	if(functionName == "fe3d:text_is_existing")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(!_validateFe3dID(args[0].getString()))
			{
				return true;
			}

			auto result = _fe3d->text_isExisting(args[0].getString());
			returnValues.push_back(ScriptValue(SVT::BOOLEAN, result));
		}
	}
	else if(functionName == "fe3d:text_find_ids")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(!_validateFe3dID(args[0].getString()))
			{
				return true;
			}

			for(const auto& ID : _fe3d->text_getIDs())
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
	else if(functionName == "fe3d:text_get_ids")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			auto result = _fe3d->text_getIDs();

			for(const auto& ID : result)
			{
				if(ID[0] != '@')
				{
					returnValues.push_back(ScriptValue(SVT::STRING, ID));
				}
			}
		}
	}
	else if(functionName == "fe3d:text_is_visible")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dText(args[0].getString(), false))
			{
				auto result = _fe3d->text_isVisible(args[0].getString());
				returnValues.push_back(ScriptValue(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:text_get_position_x")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dText(args[0].getString(), false))
			{
				auto result = _convertPositionFromViewport(_fe3d->text_getPosition(args[0].getString())).x;
				returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:text_get_position_y")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dText(args[0].getString(), false))
			{
				auto result = _convertPositionFromViewport(_fe3d->text_getPosition(args[0].getString())).y;
				returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:text_get_rotation")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dText(args[0].getString(), false))
			{
				auto result = _fe3d->text_getRotation(args[0].getString());
				returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:text_get_size_x")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dText(args[0].getString(), false))
			{
				auto result = _convertSizeFromViewport(_fe3d->text_getSize(args[0].getString())).x;
				returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:text_get_size_y")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dText(args[0].getString(), false))
			{
				auto result = _convertSizeFromViewport(_fe3d->text_getSize(args[0].getString())).y;
				returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:text_get_color_r")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dText(args[0].getString(), false))
			{
				auto result = _fe3d->text_getColor(args[0].getString()).r;
				returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:text_get_color_g")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dText(args[0].getString(), false))
			{
				auto result = _fe3d->text_getColor(args[0].getString()).g;
				returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:text_get_color_b")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dText(args[0].getString(), false))
			{
				auto result = _fe3d->text_getColor(args[0].getString()).b;
				returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:text_get_wireframe_color_r")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dText(args[0].getString(), false))
			{
				auto result = _fe3d->text_getColor(args[0].getString()).r;
				returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:text_get_wireframe_color_g")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dText(args[0].getString(), false))
			{
				auto result = _fe3d->text_getColor(args[0].getString()).g;
				returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:text_get_wireframe_color_b")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dText(args[0].getString(), false))
			{
				auto result = _fe3d->text_getColor(args[0].getString()).b;
				returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:text_get_content")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dText(args[0].getString(), false))
			{
				auto result = _fe3d->text_getContent(args[0].getString());
				returnValues.push_back(ScriptValue(SVT::STRING, result));
			}
		}
	}
	else if(functionName == "fe3d:text_get_transparency")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dText(args[0].getString(), false))
			{
				auto result = _fe3d->text_getTransparency(args[0].getString());
				returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:text_is_wireframed")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dText(args[0].getString(), false))
			{
				auto result = _fe3d->text_isWireframed(args[0].getString());
				returnValues.push_back(ScriptValue(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:text_get_font_path")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dText(args[0].getString(), false))
			{
				auto result = _fe3d->text_getFontMapPath(args[0].getString());
				returnValues.push_back(ScriptValue(SVT::STRING, result));
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