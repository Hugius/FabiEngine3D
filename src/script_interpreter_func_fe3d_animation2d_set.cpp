#include "script_interpreter.hpp"

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dAnimation2dSetter(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues)
{
	if(functionName == "fe3d:animation2d_start_billboard")
	{
		auto types = {SVT::STRING, SVT::STRING, SVT::INTEGER};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dBillboard(arguments[0].getString(), false))
			{
				_animation2dEditor.startBillboardAnimation(arguments[0].getString(), arguments[1].getString(), arguments[2].getInteger());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:animation2d_pause_billboard")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dBillboard(arguments[0].getString(), false))
			{
				_animation2dEditor.pauseBillboardAnimation(arguments[0].getString(), arguments[1].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:animation2d_resume_billboard")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dBillboard(arguments[0].getString(), false))
			{
				_animation2dEditor.resumeBillboardAnimation(arguments[0].getString(), arguments[1].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:animation2d_stop_billboard")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dBillboard(arguments[0].getString(), false))
			{
				_animation2dEditor.stopBillboardAnimation(arguments[0].getString(), arguments[1].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:animation2d_set_billboard_framestep")
	{
		auto types = {SVT::STRING, SVT::STRING, SVT::INTEGER};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dBillboard(arguments[0].getString(), false))
			{
				_animation2dEditor.setBillboardAnimationFramestep(arguments[0].getString(), arguments[1].getString(), arguments[1].getInteger());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:animation2d_start_image")
	{
		auto types = {SVT::STRING, SVT::STRING, SVT::INTEGER};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dImage(arguments[0].getString()))
			{
				_animation2dEditor.startImageAnimation(arguments[0].getString(), arguments[1].getString(), arguments[2].getInteger());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:animation2d_pause_image")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dImage(arguments[0].getString()))
			{
				_animation2dEditor.pauseImageAnimation(arguments[0].getString(), arguments[1].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:animation2d_resume_image")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dImage(arguments[0].getString()))
			{
				_animation2dEditor.resumeImageAnimation(arguments[0].getString(), arguments[1].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:animation2d_stop_image")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dImage(arguments[0].getString()))
			{
				_animation2dEditor.stopImageAnimation(arguments[0].getString(), arguments[1].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:animation2d_set_image_framestep")
	{
		auto types = {SVT::STRING, SVT::STRING, SVT::INTEGER};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dImage(arguments[0].getString()))
			{
				_animation2dEditor.setImageAnimationFramestep(arguments[0].getString(), arguments[1].getString(), arguments[1].getInteger());
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
		_throwScriptError("cannot access `fe3d:animation3d` functionality as networking server!");
	}

	// Return
	return true;
}