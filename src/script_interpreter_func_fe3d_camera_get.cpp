#include "script_interpreter.hpp"

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dCameraGetter(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues)
{
	if(functionName == "fe3d:camera_get_position_x")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			auto result = _fe3d.camera_getPosition().x;
			returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:camera_get_position_y")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			auto result = _fe3d.camera_getPosition().y;
			returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:camera_get_position_z")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			auto result = _fe3d.camera_getPosition().z;
			returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:camera_get_up_vector_x")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			auto result = _fe3d.camera_getUpVector().x;
			returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:camera_get_up_vector_y")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			auto result = _fe3d.camera_getUpVector().y;
			returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:camera_get_up_vector_z")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			auto result = _fe3d.camera_getUpVector().z;
			returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:camera_get_front_vector_x")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			auto result = _fe3d.camera_getFrontVector().x;
			returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:camera_get_front_vector_y")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			auto result = _fe3d.camera_getFrontVector().y;
			returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:camera_get_front_vector_z")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			auto result = _fe3d.camera_getFrontVector().z;
			returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:camera_get_right_vector_x")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			auto result = _fe3d.camera_getRightVector().x;
			returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:camera_get_right_vector_y")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			auto result = _fe3d.camera_getRightVector().y;
			returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:camera_get_right_vector_z")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			auto result = _fe3d.camera_getRightVector().z;
			returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:camera_get_yaw")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			auto result = _fe3d.camera_getYaw();
			returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:camera_get_pitch")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			auto result = _fe3d.camera_getPitch();
			returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:camera_get_fov")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			auto result = _fe3d.camera_getFOV();
			returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:camera_is_first_person_view_enabled")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			auto result = _fe3d.camera_isFirstPersonViewEnabled();
			returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
		}
	}
	else if(functionName == "fe3d:camera_get_first_person_yaw")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			auto result = _fe3d.camera_getFirstPersonYaw();
			returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:camera_get_first_person_pitch")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			auto result = _fe3d.camera_getFirstPersonPitch();
			returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:camera_get_min_first_person_pitch")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			auto result = _fe3d.camera_getMinFirstPersonPitch();
			returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:camera_get_max_first_person_pitch")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			auto result = _fe3d.camera_getMaxFirstPersonPitch();
			returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:camera_is_third_person_view_enabled")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			auto result = _fe3d.camera_isThirdPersonViewEnabled();
			returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
		}
	}
	else if(functionName == "fe3d:camera_get_third_person_yaw")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			auto result = _fe3d.camera_getThirdPersonYaw();
			returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:camera_get_third_person_pitch")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			auto result = _fe3d.camera_getThirdPersonPitch();
			returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:camera_get_min_third_person_pitch")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			auto result = _fe3d.camera_getMinThirdPersonPitch();
			returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:camera_get_max_third_person_pitch")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			auto result = _fe3d.camera_getMaxThirdPersonPitch();
			returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:camera_get_third_person_distance")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			auto result = _fe3d.camera_getThirdPersonDistance();
			returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:camera_get_third_person_lookat_x")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			auto result = _fe3d.camera_getThirdPersonLookat().x;
			returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:camera_get_third_person_lookat_y")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			auto result = _fe3d.camera_getThirdPersonLookat().y;
			returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:camera_get_third_person_lookat_z")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			auto result = _fe3d.camera_getThirdPersonLookat().z;
			returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:camera_get_cursor_sensitivity")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			auto result = _fe3d.camera_getCursorSensitivity();
			returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:camera_get_near_distance")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			auto result = _fe3d.camera_getNearDistance();
			returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:camera_get_far_distance")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			auto result = _fe3d.camera_getFarDistance();
			returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
		}
	}
	else
	{
		return false;
	}

	// Cannot execute when server is running
	if(_fe3d.server_isRunning())
	{
		_throwScriptError("cannot access `fe3d:camera` functionality as networking server!");
	}

	return true;
}