#include "script_interpreter.hpp"

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dImageGetter(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues)
{
	if(functionName == "fe3d:image_is_existing")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// @ signs not allowed
			if(arguments[0].getString().find('@') != string::npos)
			{
				_throwScriptError("ID of requested image with ID \"" + arguments[0].getString() + "\" cannot contain '@'");
				return true;
			}

			// Check if existing
			auto result = _fe3d.image_isExisting(arguments[0].getString());
			returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
		}
	}
	else if(functionName == "fe3d:image_find_ids")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// @ signs not allowed
			if(arguments[0].getString().find('@') != string::npos)
			{
				_throwScriptError("ID of requested image with ID \"" + arguments[0].getString() + "\" cannot contain '@'");
				return true;
			}

			// Find full entity IDs based on sub ID
			for(const auto& ID : _fe3d.image_getIDs())
			{
				// If substring matches
				if(arguments[0].getString() == ID.substr(0, arguments[0].getString().size()))
				{
					// @ signs not allowed
					if(ID[0] != '@')
					{
						returnValues.push_back(ScriptValue(_fe3d, SVT::STRING, ID));
					}
				}
			}
		}
	}
	else if(functionName == "fe3d:image_get_ids")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			auto result = _fe3d.image_getIDs();

			// Iterate through images
			for(const auto& ID : result)
			{
				// @ signs not allowed
				if(ID[0] != '@')
				{
					returnValues.push_back(ScriptValue(_fe3d, SVT::STRING, ID));
				}
			}
		}
	}
	else if(functionName == "fe3d:image_is_visible")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dImage(arguments[0].getString()))
			{
				auto result = _fe3d.image_isVisible(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:image_get_position_x")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dImage(arguments[0].getString()))
			{
				auto result = _convertGuiPositionFromViewport(_fe3d.image_getPosition(arguments[0].getString())).x;
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:image_get_position_y")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dImage(arguments[0].getString()))
			{
				auto result = _convertGuiPositionFromViewport(_fe3d.image_getPosition(arguments[0].getString())).y;
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:image_get_rotation")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dImage(arguments[0].getString()))
			{
				auto result = _fe3d.image_getRotation(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:image_get_size_x")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dImage(arguments[0].getString()))
			{
				auto result = _convertGuiSizeFromViewport(_fe3d.image_getSize(arguments[0].getString())).x;
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:image_get_size_y")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dImage(arguments[0].getString()))
			{
				auto result = _convertGuiSizeFromViewport(_fe3d.image_getSize(arguments[0].getString())).y;
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:image_get_color_r")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dImage(arguments[0].getString()))
			{
				auto result = _fe3d.image_getColor(arguments[0].getString()).r;
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:image_get_color_g")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dImage(arguments[0].getString()))
			{
				auto result = _fe3d.image_getColor(arguments[0].getString()).g;
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:image_get_color_b")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dImage(arguments[0].getString()))
			{
				auto result = _fe3d.image_getColor(arguments[0].getString()).b;
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:image_get_transparency")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dImage(arguments[0].getString()))
			{
				auto result = _fe3d.image_getTransparency(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:image_get_diffuse_map_path")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dImage(arguments[0].getString()))
			{
				auto result = _fe3d.image_getDiffuseMapPath(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:image_is_mirrored_horizontally")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dImage(arguments[0].getString()))
			{
				auto result = _fe3d.image_isMirroredHorizontally(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:image_is_mirrored_vertically")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dImage(arguments[0].getString()))
			{
				auto result = _fe3d.image_isMirroredVertically(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:image_get_wireframe_color_r")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dImage(arguments[0].getString()))
			{
				auto result = _fe3d.image_getWireframeColor(arguments[0].getString()).r;
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:image_get_wireframe_color_g")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dImage(arguments[0].getString()))
			{
				auto result = _fe3d.image_getWireframeColor(arguments[0].getString()).g;
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:image_get_wireframe_color_b")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dImage(arguments[0].getString()))
			{
				auto result = _fe3d.image_getWireframeColor(arguments[0].getString()).b;
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:image_is_wireframed")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dImage(arguments[0].getString()))
			{
				auto result = _fe3d.image_isWireframed(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
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
		_throwScriptError("cannot access `fe3d:image` functionality as networking server!");
	}

	// Return
	return true;
}