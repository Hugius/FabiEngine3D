#include "script_interpreter.hpp"

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dImageGetter(const string& functionName, vector<ScriptValue>& args, vector<ScriptValue>& returnValues)
{
	if(functionName == "fe3d:image_is_existing")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			// Validate ID
			if(!_validateFe3dID(args[0].getString()))
			{
				return true;
			}

			// Check if existing
			auto result = _fe3d.image_isExisting(args[0].getString());
			returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
		}
	}
	else if(functionName == "fe3d:image_find_ids")
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
			for(const auto& ID : _fe3d.image_getIDs())
			{
				// If substring matches
				if(args[0].getString() == ID.substr(0, args[0].getString().size()))
				{
					// Cannot be template
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
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			auto result = _fe3d.image_getIDs();

			// Iterate through images
			for(const auto& ID : result)
			{
				// Cannot be template
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

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dImage(args[0].getString()))
			{
				auto result = _fe3d.image_isVisible(args[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:image_get_position_x")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dImage(args[0].getString()))
			{
				auto result = _convertGuiPositionFromViewport(_fe3d.image_getPosition(args[0].getString())).x;
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:image_get_position_y")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dImage(args[0].getString()))
			{
				auto result = _convertGuiPositionFromViewport(_fe3d.image_getPosition(args[0].getString())).y;
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:image_get_rotation")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dImage(args[0].getString()))
			{
				auto result = _fe3d.image_getRotation(args[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:image_get_size_x")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dImage(args[0].getString()))
			{
				auto result = _convertGuiSizeFromViewport(_fe3d.image_getSize(args[0].getString())).x;
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:image_get_size_y")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dImage(args[0].getString()))
			{
				auto result = _convertGuiSizeFromViewport(_fe3d.image_getSize(args[0].getString())).y;
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:image_get_color_r")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dImage(args[0].getString()))
			{
				auto result = _fe3d.image_getColor(args[0].getString()).r;
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:image_get_color_g")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dImage(args[0].getString()))
			{
				auto result = _fe3d.image_getColor(args[0].getString()).g;
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:image_get_color_b")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dImage(args[0].getString()))
			{
				auto result = _fe3d.image_getColor(args[0].getString()).b;
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:image_get_transparency")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dImage(args[0].getString()))
			{
				auto result = _fe3d.image_getTransparency(args[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:image_get_diffuse_map_path")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dImage(args[0].getString()))
			{
				auto result = _fe3d.image_getDiffuseMapPath(args[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:image_is_mirrored_horizontally")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dImage(args[0].getString()))
			{
				auto result = _fe3d.image_isMirroredHorizontally(args[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:image_is_mirrored_vertically")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dImage(args[0].getString()))
			{
				auto result = _fe3d.image_isMirroredVertically(args[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:image_get_wireframe_color_r")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dImage(args[0].getString()))
			{
				auto result = _fe3d.image_getWireframeColor(args[0].getString()).r;
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:image_get_wireframe_color_g")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dImage(args[0].getString()))
			{
				auto result = _fe3d.image_getWireframeColor(args[0].getString()).g;
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:image_get_wireframe_color_b")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dImage(args[0].getString()))
			{
				auto result = _fe3d.image_getWireframeColor(args[0].getString()).b;
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:image_is_wireframed")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dImage(args[0].getString()))
			{
				auto result = _fe3d.image_isWireframed(args[0].getString());
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