#include "script_interpreter.hpp"

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dCameraGetterFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues)
{
	// Determine type of function
	if(functionName == "fe3d:camera_get_position")
	{
		// Validate arguments
		if(_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto result = _fe3d.camera_getPosition();
			returnValues.push_back(ScriptValue(_fe3d, SVT::VEC3, result));
		}
	}
	else if(functionName == "fe3d:camera_get_up_vector")
	{
		// Validate arguments
		if(_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto result = _fe3d.camera_getUpVector();
			returnValues.push_back(ScriptValue(_fe3d, SVT::VEC3, result));
		}
	}
	else if(functionName == "fe3d:camera_get_front_vector")
	{
		// Validate arguments
		if(_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto result = _fe3d.camera_getFrontVector();
			returnValues.push_back(ScriptValue(_fe3d, SVT::VEC3, result));
		}
	}
	else if(functionName == "fe3d:camera_get_right_vector")
	{
		// Validate arguments
		if(_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto result = _fe3d.camera_getRightVector();
			returnValues.push_back(ScriptValue(_fe3d, SVT::VEC3, result));
		}
	}
	else if(functionName == "fe3d:camera_get_yaw")
	{
		// Validate arguments
		if(_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto result = _fe3d.camera_getYaw();
			returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:camera_get_pitch")
	{
		// Validate arguments
		if(_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto result = _fe3d.camera_getPitch();
			returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:camera_get_fov")
	{
		// Validate arguments
		if(_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto result = _fe3d.camera_getFOV();
			returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:camera_is_first_person_view_enabled")
	{
		// Validate arguments
		if(_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto result = _fe3d.camera_isFirstPersonViewEnabled();
			returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
		}
	}
	else if(functionName == "fe3d:camera_get_first_person_yaw")
	{
		// Validate arguments
		if(_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto result = _fe3d.camera_getFirstPersonYaw();
			returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:camera_get_first_person_pitch")
	{
		// Validate arguments
		if(_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto result = _fe3d.camera_getFirstPersonPitch();
			returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:camera_is_third_person_view_enabled")
	{
		// Validate arguments
		if(_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto result = _fe3d.camera_isThirdPersonViewEnabled();
			returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
		}
	}
	else if(functionName == "fe3d:camera_get_third_person_yaw")
	{
		// Validate arguments
		if(_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto result = _fe3d.camera_getThirdPersonYaw();
			returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:camera_get_third_person_pitch")
	{
		// Validate arguments
		if(_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto result = _fe3d.camera_getThirdPersonPitch();
			returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:camera_get_third_person_distance")
	{
		// Validate arguments
		if(_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto result = _fe3d.camera_getThirdPersonDistance();
			returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:camera_get_third_person_lookat")
	{
		// Validate arguments
		if(_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto result = _fe3d.camera_getThirdPersonLookat();
			returnValues.push_back(ScriptValue(_fe3d, SVT::VEC3, result));
		}
	}
	else if(functionName == "fe3d:camera_get_aspect_ratio")
	{
		// Validate arguments
		if(_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto result = _fe3d.camera_getAspectRatio();
			returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:camera_get_cursor_sensitivity")
	{
		// Validate arguments
		if(_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto result = _fe3d.camera_getCursorSensitivity();
			returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:camera_get_near_distance")
	{
		// Validate arguments
		if(_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto result = _fe3d.camera_getNearDistance();
			returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:camera_get_far_distance")
	{
		// Validate arguments
		if(_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto result = _fe3d.camera_getFarDistance();
			returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
		}
	}
	else
	{
		return false;
	}

	// Cannot execute camera functionality when server is running
	if(_fe3d.server_isRunning())
	{
		_throwScriptError("cannot access `fe3d:camera` functionality as a networking server!");
	}

	return true;
}