#include "script_interpreter.hpp"

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dBillboardSetter(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues)
{
	if(functionName == "fe3d:billboard_place")
	{
		auto types = {SVT::STRING, SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// @ signs not allowed
			if(arguments[0].getString().find('@') != string::npos)
			{
				_throwScriptError("new billboard ID (\"" + arguments[0].getString() + "\") cannot contain '@'");
				return true;
			}

			// Check if billboard entity already exists
			if(_fe3d.billboard_isExisting(arguments[0].getString()))
			{
				_throwScriptError("billboard with ID \"" + arguments[0].getString() + "\" already exists!");
				return true;
			}

			// Validate template billboard ID
			if(_validateFe3dBillboard("@" + arguments[1].getString(), true))
			{
				// Copy template billboard
				_worldEditor.copyTemplateBillboard(arguments[0].getString(), ("@" + arguments[1].getString()),
												   fvec3(arguments[2].getDecimal(), arguments[3].getDecimal(), arguments[4].getDecimal()));

				// Return
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:billboard_delete")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dBillboard(arguments[0].getString(), false))
			{
				_fe3d.billboard_delete(arguments[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:billboard_delete_all")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			// Iterate through billboards
			for(const auto& ID : _fe3d.billboard_getIDs())
			{
				// @ signs not allowed
				if(ID[0] != '@')
				{
					_fe3d.billboard_delete(ID);
				}
			}

			// Return
			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:billboard_set_visible")
	{
		auto types = {SVT::STRING, SVT::BOOLEAN};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dBillboard(arguments[0].getString(), false))
			{
				_fe3d.billboard_setVisible(arguments[0].getString(), arguments[1].getBoolean());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:billboard_set_position")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dBillboard(arguments[0].getString(), false))
			{
				_fe3d.billboard_setPosition(arguments[0].getString(),
											fvec3(arguments[1].getDecimal(), arguments[2].getDecimal(), arguments[3].getDecimal()));
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:billboard_set_rotation")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dBillboard(arguments[0].getString(), false))
			{
				_fe3d.billboard_setRotation(arguments[0].getString(),
											fvec3(arguments[1].getDecimal(), arguments[2].getDecimal(), arguments[3].getDecimal()));
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:billboard_set_size")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dBillboard(arguments[0].getString(), false))
			{
				_fe3d.billboard_setSize(arguments[0].getString(), fvec2(arguments[1].getDecimal(), arguments[2].getDecimal()));
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:billboard_move")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dBillboard(arguments[0].getString(), false))
			{
				_fe3d.billboard_move(arguments[0].getString(),
									 fvec3(arguments[1].getDecimal(), arguments[2].getDecimal(), arguments[3].getDecimal()));
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:billboard_rotate")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dBillboard(arguments[0].getString(), false))
			{
				_fe3d.billboard_rotate(arguments[0].getString(),
									   fvec3(arguments[1].getDecimal(), arguments[2].getDecimal(), arguments[3].getDecimal()));
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:billboard_scale")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dBillboard(arguments[0].getString(), false))
			{
				_fe3d.billboard_scale(arguments[0].getString(), fvec2(arguments[1].getDecimal(), arguments[2].getDecimal()));
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:billboard_move_to")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dBillboard(arguments[0].getString(), false))
			{
				_fe3d.billboard_moveTo(arguments[0].getString(),
									   fvec3(arguments[1].getDecimal(), arguments[2].getDecimal(), arguments[3].getDecimal()), arguments[4].getDecimal());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:billboard_rotate_to")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dBillboard(arguments[0].getString(), false))
			{
				_fe3d.billboard_rotateTo(arguments[0].getString(),
										 fvec3(arguments[1].getDecimal(), arguments[2].getDecimal(), arguments[3].getDecimal()), arguments[4].getDecimal());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:billboard_scale_to")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dBillboard(arguments[0].getString(), false))
			{
				_fe3d.billboard_scaleTo(arguments[0].getString(),
										fvec2(arguments[1].getDecimal(), arguments[2].getDecimal()), arguments[3].getDecimal());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:billboard_set_color")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dBillboard(arguments[0].getString(), false))
			{
				_fe3d.billboard_setColor(arguments[0].getString(),
										 fvec3(arguments[1].getDecimal(), arguments[2].getDecimal(), arguments[3].getDecimal()));
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:billboard_set_wireframe_color")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dBillboard(arguments[0].getString(), false))
			{
				_fe3d.billboard_setWireframeColor(arguments[0].getString(),
												  fvec3(arguments[1].getDecimal(), arguments[2].getDecimal(), arguments[3].getDecimal()));
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:billboard_set_min_height")
	{
		auto types = {SVT::STRING, SVT::DECIMAL};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dBillboard(arguments[0].getString(), false))
			{
				_fe3d.billboard_setMinHeight(arguments[0].getString(), arguments[1].getDecimal());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:billboard_set_max_height")
	{
		auto types = {SVT::STRING, SVT::DECIMAL};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dBillboard(arguments[0].getString(), false))
			{
				_fe3d.billboard_setMaxHeight(arguments[0].getString(), arguments[1].getDecimal());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:billboard_set_transparency")
	{
		auto types = {SVT::STRING, SVT::DECIMAL};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dBillboard(arguments[0].getString(), false))
			{
				_fe3d.billboard_setTransparency(arguments[0].getString(), arguments[1].getDecimal());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:billboard_set_emission_intensity")
	{
		auto types = {SVT::STRING, SVT::DECIMAL};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dBillboard(arguments[0].getString(), false))
			{
				_fe3d.billboard_setEmissionIntensity(arguments[0].getString(), arguments[1].getDecimal());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:billboard_set_texture_repeat")
	{
		auto types = {SVT::STRING, SVT::DECIMAL};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dBillboard(arguments[0].getString(), false))
			{
				_fe3d.billboard_setTextureRepeat(arguments[0].getString(), arguments[1].getDecimal());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:billboard_set_lightness")
	{
		auto types = {SVT::STRING, SVT::DECIMAL};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dBillboard(arguments[0].getString(), false))
			{
				_fe3d.billboard_setLightness(arguments[0].getString(), arguments[1].getDecimal());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:billboard_set_aabb_raycast_responsive")
	{
		auto types = {SVT::STRING, SVT::BOOLEAN};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dBillboard(arguments[0].getString(), false))
			{
				// Retrieve all bound AABB IDs
				auto aabbIDs = _fe3d.aabb_getChildIDs(arguments[0].getString(), AabbParentEntityType::BILLBOARD);

				// Check if billboardEntity has no AABBs
				if(aabbIDs.empty())
				{
					_throwScriptError("billboard with ID \"" + arguments[0].getString() + "\" has no bound AABBs!");
					return true;
				}

				// Set responsiveness
				for(const auto& ID : aabbIDs)
				{
					_fe3d.aabb_setRaycastResponsive(ID, arguments[1].getBoolean());
				}

				// Return
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:billboard_set_aabb_collision_responsive")
	{
		auto types = {SVT::STRING, SVT::BOOLEAN};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dBillboard(arguments[0].getString(), false))
			{
				// Retrieve all bound AABB IDs
				auto aabbIDs = _fe3d.aabb_getChildIDs(arguments[0].getString(), AabbParentEntityType::BILLBOARD);

				// Check if billboardEntity has no AABBs
				if(aabbIDs.empty())
				{
					_throwScriptError("billboard with ID \"" + arguments[0].getString() + "\" has no bound AABBs!");
					return true;
				}

				// Set responsiveness
				for(const auto& ID : aabbIDs)
				{
					_fe3d.aabb_setCollisionResponsive(ID, arguments[1].getBoolean());
				}

				// Return
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:billboard_set_shadowed")
	{
		auto types = {SVT::STRING, SVT::BOOLEAN};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dBillboard(arguments[0].getString(), false))
			{
				_fe3d.billboard_setShadowed(arguments[0].getString(), arguments[1].getBoolean());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:billboard_set_bright")
	{
		auto types = {SVT::STRING, SVT::BOOLEAN};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dBillboard(arguments[0].getString(), false))
			{
				_fe3d.billboard_setBright(arguments[0].getString(), arguments[1].getBoolean());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:billboard_set_wireframed")
	{
		auto types = {SVT::STRING, SVT::BOOLEAN};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dBillboard(arguments[0].getString(), false))
			{
				_fe3d.billboard_setWireframed(arguments[0].getString(), arguments[1].getBoolean());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:billboard_set_frozen")
	{
		auto types = {SVT::STRING, SVT::BOOLEAN};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dBillboard(arguments[0].getString(), false))
			{
				_fe3d.billboard_setFrozen(arguments[0].getString(), arguments[1].getBoolean());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:billboard_set_facing_camera_x")
	{
		auto types = {SVT::STRING, SVT::BOOLEAN};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dBillboard(arguments[0].getString(), false))
			{
				_fe3d.billboard_setFacingCameraX(arguments[0].getString(), arguments[1].getBoolean());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:billboard_set_facing_camera_y")
	{
		auto types = {SVT::STRING, SVT::BOOLEAN};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dBillboard(arguments[0].getString(), false))
			{
				_fe3d.billboard_setFacingCameraY(arguments[0].getString(), arguments[1].getBoolean());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:billboard_start_animation")
	{
		auto types = {SVT::STRING, SVT::INTEGER};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dBillboard(arguments[0].getString(), false))
			{

				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:billboard_pause_animation")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dBillboard(arguments[0].getString(), false))
			{

				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:billboard_resume_animation")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dBillboard(arguments[0].getString(), false))
			{

				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:billboard_stop_animation")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dBillboard(arguments[0].getString(), false))
			{

				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:billboard_set_text")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			if(_validateFe3dBillboard(arguments[0].getString(), false))
			{
				// Check if billboard is not of type text
				if(!_fe3d.billboard_isTextual(arguments[0].getString()))
				{
					_throwScriptError("billboard with ID \"" + arguments[0].getString() + "\" is not of type text!");
					return true;
				}
				else
				{
					_fe3d.billboard_setTextContent(arguments[0].getString(), arguments[1].getString());
					returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
				}
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
		_throwScriptError("cannot access `fe3d:billboard` functionality as networking server!");
	}

	// Return
	return true;
}