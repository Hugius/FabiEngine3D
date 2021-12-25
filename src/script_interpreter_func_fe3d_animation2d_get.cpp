#include "script_interpreter.hpp"

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dAnimation2dGetter(const string& functionName, vector<ScriptValue>& args, vector<ScriptValue>& returnValues)
{
	if(functionName == "fe3d:animation2d_is_billboard_started")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation2d(args[0].getString()) && _validateFe3dBillboard(args[1].getString(), false))
			{
				auto result = _animation2dEditor.isBillboardAnimationStarted(args[0].getString(), args[1].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:animation2d_is_billboard_playing")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation2d(args[0].getString()) && _validateFe3dBillboard(args[1].getString(), false))
			{
				auto result = _animation2dEditor.isBillboardAnimationPlaying(args[0].getString(), args[1].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:animation2d_is_billboard_paused")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation2d(args[0].getString()) && _validateFe3dBillboard(args[1].getString(), false))
			{
				auto result = _animation2dEditor.isBillboardAnimationPaused(args[0].getString(), args[1].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:animation2d_get_billboard_row_count")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation2d(args[0].getString()) && _validateFe3dBillboard(args[1].getString(), false))
			{
				auto result = _animation2dEditor.getBillboardAnimationRowCount(args[0].getString(), args[1].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::INTEGER, static_cast<int>(result)));
			}
		}
	}
	else if(functionName == "fe3d:animation2d_get_billboard_column_count")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation2d(args[0].getString()) && _validateFe3dBillboard(args[1].getString(), false))
			{
				auto result = _animation2dEditor.getBillboardAnimationColumnCount(args[0].getString(), args[1].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::INTEGER, static_cast<int>(result)));
			}
		}
	}
	else if(functionName == "fe3d:animation2d_get_billboard_row_index")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation2d(args[0].getString()) && _validateFe3dBillboard(args[1].getString(), false))
			{
				auto result = _animation2dEditor.getBillboardAnimationRowIndex(args[0].getString(), args[1].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::INTEGER, static_cast<int>(result)));
			}
		}
	}
	else if(functionName == "fe3d:animation2d_get_billboard_column_index")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation2d(args[0].getString()) && _validateFe3dBillboard(args[1].getString(), false))
			{
				auto result = _animation2dEditor.getBillboardAnimationColumnIndex(args[0].getString(), args[1].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::INTEGER, static_cast<int>(result)));
			}
		}
	}
	else if(functionName == "fe3d:animation2d_get_billboard_play_count")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation2d(args[0].getString()) && _validateFe3dBillboard(args[1].getString(), false))
			{
				auto result = _animation2dEditor.getBillboardAnimationPlayCount(args[0].getString(), args[1].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::INTEGER, result));
			}
		}
	}
	else if(functionName == "fe3d:animation2d_get_billboard_framestep")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation2d(args[0].getString()) && _validateFe3dBillboard(args[1].getString(), false))
			{
				auto result = _animation2dEditor.getBillboardAnimationFramestep(args[0].getString(), args[1].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::INTEGER, static_cast<int>(result)));
			}
		}
	}
	else if(functionName == "fe3d:animation2d_is_image_started")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation2d(args[0].getString()) && _validateFe3dImage(args[1].getString()))
			{
				auto result = _animation2dEditor.isImageAnimationStarted(args[0].getString(), args[1].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:animation2d_is_image_playing")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation2d(args[0].getString()) && _validateFe3dImage(args[1].getString()))
			{
				auto result = _animation2dEditor.isImageAnimationPlaying(args[0].getString(), args[1].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:animation2d_is_image_paused")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation2d(args[0].getString()) && _validateFe3dImage(args[1].getString()))
			{
				auto result = _animation2dEditor.isImageAnimationPaused(args[0].getString(), args[1].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:animation2d_get_image_row_count")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation2d(args[0].getString()) && _validateFe3dImage(args[1].getString()))
			{
				auto result = _animation2dEditor.getImageAnimationRowCount(args[0].getString(), args[1].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::INTEGER, static_cast<int>(result)));
			}
		}
	}
	else if(functionName == "fe3d:animation2d_get_image_column_count")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation2d(args[0].getString()) && _validateFe3dImage(args[1].getString()))
			{
				auto result = _animation2dEditor.getImageAnimationColumnCount(args[0].getString(), args[1].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::INTEGER, static_cast<int>(result)));
			}
		}
	}
	else if(functionName == "fe3d:animation2d_get_image_row_index")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation2d(args[0].getString()) && _validateFe3dImage(args[1].getString()))
			{
				auto result = _animation2dEditor.getImageAnimationRowIndex(args[0].getString(), args[1].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::INTEGER, static_cast<int>(result)));
			}
		}
	}
	else if(functionName == "fe3d:animation2d_get_image_column_index")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation2d(args[0].getString()) && _validateFe3dImage(args[1].getString()))
			{
				auto result = _animation2dEditor.getImageAnimationColumnIndex(args[0].getString(), args[1].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::INTEGER, static_cast<int>(result)));
			}
		}
	}
	else if(functionName == "fe3d:animation2d_get_image_play_count")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation2d(args[0].getString()) && _validateFe3dImage(args[1].getString()))
			{
				auto result = _animation2dEditor.getImageAnimationPlayCount(args[0].getString(), args[1].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::INTEGER, result));
			}
		}
	}
	else if(functionName == "fe3d:animation2d_get_image_framestep")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation2d(args[0].getString()) && _validateFe3dImage(args[1].getString()))
			{
				auto result = _animation2dEditor.getImageAnimationFramestep(args[0].getString(), args[1].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::INTEGER, static_cast<int>(result)));
			}
		}
	}
	else
	{
		return false;
	}

	if(_fe3d.server_isRunning())
	{
		_throwScriptError("cannot access `fe3d:animation2d` functionality as networking server!");
	}

	return true;
}