#include "script_interpreter.hpp"

bool ScriptInterpreter::_executeFe3dCameraFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues)
{
	// Determine type of function
	if (functionName == "fe3d:camera_move") // Move camera
	{
		auto types = { ScriptValueType::DECIMAL, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL };

		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			_fe3d.camera_translate(Vec3(arguments[0].getDecimal(), arguments[1].getDecimal(), arguments[2].getDecimal()));
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			return true;
		}
	}
	else if (functionName == "fe3d:camera_position_set") // Set camera position
	{
		auto types = { ScriptValueType::DECIMAL, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL };

		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			_fe3d.camera_setPosition(Vec3(arguments[0].getDecimal(), arguments[1].getDecimal(), arguments[2].getDecimal()));
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			return true;
		}
	}
	else if (functionName == "fe3d:camera_position_get") // Get camera position
	{
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto result = _fe3d.camera_getPosition();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::VEC3, result));
			return true;
		}
	}
	else if (functionName == "fe3d:camera_follow_x") // Follow X direction
	{
		auto types = { ScriptValueType::DECIMAL };

		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			_fe3d.camera_translateFollowX(arguments[0].getDecimal());
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			return true;
		}
	}
	else if (functionName == "fe3d:camera_follow_z") // Follow Z direction
	{
		auto types = { ScriptValueType::DECIMAL };

		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			_fe3d.camera_translateFollowZ(arguments[0].getDecimal());
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			return true;
		}
	}
	else if (functionName == "fe3d:camera_follow_zy") // Follow ZY direction
	{
		auto types = { ScriptValueType::DECIMAL };

		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			_fe3d.camera_translateFollowZY(arguments[0].getDecimal());
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			return true;
		}
	}
	else if (functionName == "fe3d:camera_yaw_set") // Set yaw angle
	{
		auto types = { ScriptValueType::DECIMAL };

		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			_fe3d.camera_setYaw(arguments[0].getDecimal());
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			return true;
		}
	}
	else if (functionName == "fe3d:camera_yaw_get") // Get yaw angle
	{
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto result = _fe3d.camera_getYaw();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, result));
			return true;
		}
	}
	else if (functionName == "fe3d:camera_pitch_set") // Set pitch angle
	{
		auto types = { ScriptValueType::DECIMAL };

		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			_fe3d.camera_setPitch(arguments[0].getDecimal());
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			return true;
		}
	}
	else if (functionName == "fe3d:camera_pitch_get") // Get pitch angle
	{
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto result = _fe3d.camera_getPitch();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, result));
			return true;
		}
	}
	else if (functionName == "fe3d:camera_fov_set") // Set FOV angle
	{
		auto types = { ScriptValueType::DECIMAL };

		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			_fe3d.camera_setFOV(arguments[0].getDecimal());
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			return true;
		}
	}
	else if (functionName == "fe3d:camera_fov_get") // Get FOV angle
	{
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			auto result = _fe3d.camera_getFOV();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, result));
			return true;
		}
	}
	else if (functionName == "fe3d:camera_lookat_enable") // Enable lookat view
	{
		auto types = { ScriptValueType::DECIMAL, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL };

		if (_validateListValueAmount(arguments, types.size()) && _validateListValueTypes(arguments, types))
		{
			_fe3d.camera_enableLookat(Vec3(arguments[0].getDecimal(), arguments[1].getDecimal(), arguments[2].getDecimal()));
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			return true;
		}
	}
	else if (functionName == "fe3d:camera_lookat_disable") // Disable lookat view
	{
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			_fe3d.camera_disableLookat();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			return true;
		}
	}
	else if (functionName == "fe3d:camera_firstperson_enable") // Enable first person view
	{
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			_fe3d.camera_center();
			_fe3d.camera_enableFirstPersonView();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			return true;
		}
	}
	else if (functionName == "fe3d:camera_firstperson_disable") // Disable first person view
	{
		if (_validateListValueAmount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			_fe3d.camera_disableFirstPersonView();
			returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
			return true;
		}
	}
	else
	{
		return false;
	}

	return false;
}