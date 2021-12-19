#include "script_interpreter.hpp"

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dAnimation2dGetter(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues)
{
	if(functionName == "fe3d:animation2d_is_billboard_started")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dBillboard(arguments[0].getString(), false))
			{
				auto result = _animation2dEditor.isBillboardAnimationStarted(arguments[0].getString(), arguments[1].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:animation2d_is_billboard_playing")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dBillboard(arguments[0].getString(), false))
			{
				auto result = _animation2dEditor.isBillboardAnimationPlaying(arguments[0].getString(), arguments[1].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:animation2d_is_billboard_paused")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dBillboard(arguments[0].getString(), false))
			{
				auto result = _animation2dEditor.isBillboardAnimationPaused(arguments[0].getString(), arguments[1].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:animation2d_get_billboard_row_count")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dBillboard(arguments[0].getString(), false))
			{
				auto result = _animation2dEditor.getBillboardAnimationRowCount(arguments[0].getString(), arguments[1].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::INTEGER, static_cast<int>(result)));
			}
		}
	}
	else if(functionName == "fe3d:animation2d_get_billboard_column_count")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dBillboard(arguments[0].getString(), false))
			{
				auto result = _animation2dEditor.getBillboardAnimationColumnCount(arguments[0].getString(), arguments[1].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::INTEGER, static_cast<int>(result)));
			}
		}
	}
	else if(functionName == "fe3d:animation2d_get_billboard_row_index")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dBillboard(arguments[0].getString(), false))
			{
				auto result = _animation2dEditor.getBillboardAnimationRowIndex(arguments[0].getString(), arguments[1].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::INTEGER, static_cast<int>(result)));
			}
		}
	}
	else if(functionName == "fe3d:animation2d_get_billboard_column_index")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dBillboard(arguments[0].getString(), false))
			{
				auto result = _animation2dEditor.getBillboardAnimationColumnIndex(arguments[0].getString(), arguments[1].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::INTEGER, static_cast<int>(result)));
			}
		}
	}
	else if(functionName == "fe3d:animation2d_get_billboard_play_count")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dBillboard(arguments[0].getString(), false))
			{
				auto result = _animation2dEditor.getBillboardAnimationPlayCount(arguments[0].getString(), arguments[1].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::INTEGER, result));
			}
		}
	}
	else if(functionName == "fe3d:animation2d_get_billboard_framestep")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dBillboard(arguments[0].getString(), false))
			{
				auto result = _animation2dEditor.getBillboardAnimationFramestep(arguments[0].getString(), arguments[1].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::INTEGER, static_cast<int>(result)));
			}
		}
	}
	else if(functionName == "fe3d:animation2d_is_image_started")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dImage(arguments[0].getString()))
			{
				auto result = _animation2dEditor.isImageAnimationStarted(arguments[0].getString(), arguments[1].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:animation2d_is_image_playing")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dImage(arguments[0].getString()))
			{
				auto result = _animation2dEditor.isImageAnimationPlaying(arguments[0].getString(), arguments[1].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:animation2d_is_image_paused")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dImage(arguments[0].getString()))
			{
				auto result = _animation2dEditor.isImageAnimationPaused(arguments[0].getString(), arguments[1].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:animation2d_get_image_row_count")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dImage(arguments[0].getString()))
			{
				auto result = _animation2dEditor.getImageAnimationRowCount(arguments[0].getString(), arguments[1].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::INTEGER, static_cast<int>(result)));
			}
		}
	}
	else if(functionName == "fe3d:animation2d_get_image_column_count")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dImage(arguments[0].getString()))
			{
				auto result = _animation2dEditor.getImageAnimationColumnCount(arguments[0].getString(), arguments[1].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::INTEGER, static_cast<int>(result)));
			}
		}
	}
	else if(functionName == "fe3d:animation2d_get_image_row_index")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dImage(arguments[0].getString()))
			{
				auto result = _animation2dEditor.getImageAnimationRowIndex(arguments[0].getString(), arguments[1].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::INTEGER, static_cast<int>(result)));
			}
		}
	}
	else if(functionName == "fe3d:animation2d_get_image_column_index")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dImage(arguments[0].getString()))
			{
				auto result = _animation2dEditor.getImageAnimationColumnIndex(arguments[0].getString(), arguments[1].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::INTEGER, static_cast<int>(result)));
			}
		}
	}
	else if(functionName == "fe3d:animation2d_get_image_play_count")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dImage(arguments[0].getString()))
			{
				auto result = _animation2dEditor.getImageAnimationPlayCount(arguments[0].getString(), arguments[1].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::INTEGER, result));
			}
		}
	}
	else if(functionName == "fe3d:animation2d_get_image_framestep")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dImage(arguments[0].getString()))
			{
				auto result = _animation2dEditor.getImageAnimationFramestep(arguments[0].getString(), arguments[1].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::INTEGER, static_cast<int>(result)));
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
		_throwScriptError("cannot access `fe3d:animation2d` functionality as networking server!");
	}

	// Return
	return true;
}