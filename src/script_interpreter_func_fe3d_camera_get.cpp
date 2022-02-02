#include "script_interpreter.hpp"

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dCameraGetter(const string& functionName, const vector<shared_ptr<ScriptValue>>& args, vector<shared_ptr<ScriptValue>>& returnValues)
{
	if(functionName == "fe3d:camera_get_position_x")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->camera_getPosition().x;

			returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:camera_get_position_y")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->camera_getPosition().y;

			returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:camera_get_position_z")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->camera_getPosition().z;

			returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:camera_get_right_x")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->camera_getRight().x;

			returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:camera_get_right_y")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->camera_getRight().y;

			returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:camera_get_right_z")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->camera_getRight().z;

			returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:camera_get_up_x")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->camera_getUp().x;

			returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:camera_get_up_y")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->camera_getUp().y;

			returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:camera_get_up_z")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->camera_getUp().z;

			returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:camera_get_front_x")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->camera_getFront().x;

			returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:camera_get_front_y")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->camera_getFront().y;

			returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:camera_get_front_z")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->camera_getFront().z;

			returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:camera_get_yaw")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->camera_getYaw();

			returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:camera_get_pitch")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->camera_getPitch();

			returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:camera_get_fov")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->camera_getFov();

			returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:camera_is_first_person_enabled")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->camera_isFirstPersonEnabled();

			returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
		}
	}
	else if(functionName == "fe3d:camera_get_first_person_yaw")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->camera_getFirstPersonYaw();

			returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:camera_get_first_person_pitch")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->camera_getFirstPersonPitch();

			returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:camera_get_min_first_person_pitch")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->camera_getMinFirstPersonPitch();

			returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:camera_get_max_first_person_pitch")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->camera_getMaxFirstPersonPitch();

			returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:camera_is_third_person_enabled")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->camera_isThirdPersonEnabled();

			returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
		}
	}
	else if(functionName == "fe3d:camera_get_third_person_yaw")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->camera_getThirdPersonYaw();

			returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:camera_get_third_person_pitch")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->camera_getThirdPersonPitch();

			returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:camera_get_min_third_person_pitch")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->camera_getMinThirdPersonPitch();

			returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:camera_get_max_third_person_pitch")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->camera_getMaxThirdPersonPitch();

			returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:camera_get_third_person_distance")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->camera_getThirdPersonDistance();

			returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:camera_get_third_person_lookat_x")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->camera_getThirdPersonLookat().x;

			returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:camera_get_third_person_lookat_y")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->camera_getThirdPersonLookat().y;

			returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:camera_get_third_person_lookat_z")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->camera_getThirdPersonLookat().z;

			returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:camera_get_cursor_sensitivity")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->camera_getCursorSensitivity();

			returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:camera_get_near")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->camera_getNear();

			returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:camera_get_far")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->camera_getFar();

			returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
		}
	}
	else
	{
		return false;
	}

	if(_fe3d->server_isRunning())
	{
		_throwRuntimeError("cannot access `fe3d:camera` functionality as networking server!");
		return true;
	}

	return true;
}