#include "script_interpreter.hpp"

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dBillboardSetter(const string& functionName, vector<ScriptValue>& args, vector<ScriptValue>& returnValues)
{
	if(functionName == "fe3d:billboard_place")
	{
		auto types = {SVT::STRING, SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(!_validateFe3dID(args[0].getString()))
			{
				return true;
			}

			if(_fe3d->billboard_isExisting(args[0].getString()))
			{
				_throwScriptError("billboard already exists!");
				return true;
			}

			if(_validateFe3dBillboard(args[1].getString(), true))
			{
				_worldEditor->copyTemplateBillboard(args[0].getString(), ("@" + args[1].getString()),
													fvec3(args[2].getDecimal(), args[3].getDecimal(), args[4].getDecimal()));
				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:billboard_delete")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dBillboard(args[0].getString(), false))
			{
				_fe3d->billboard_delete(args[0].getString());
				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:billboard_delete_all")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			for(const auto& ID : _fe3d->billboard_getIDs())
			{
				if(ID[0] != '@')
				{
					_fe3d->billboard_delete(ID);
				}
			}

			returnValues.push_back(ScriptValue(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:billboard_set_visible")
	{
		auto types = {SVT::STRING, SVT::BOOLEAN};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dBillboard(args[0].getString(), false))
			{
				_fe3d->billboard_setVisible(args[0].getString(), args[1].getBoolean());
				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:billboard_set_position")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dBillboard(args[0].getString(), false))
			{
				_fe3d->billboard_setPosition(args[0].getString(),
											 fvec3(args[1].getDecimal(), args[2].getDecimal(), args[3].getDecimal()));
				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:billboard_set_rotation")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dBillboard(args[0].getString(), false))
			{
				_fe3d->billboard_setRotation(args[0].getString(),
											 fvec3(args[1].getDecimal(), args[2].getDecimal(), args[3].getDecimal()));
				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:billboard_set_size")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dBillboard(args[0].getString(), false))
			{
				_fe3d->billboard_setSize(args[0].getString(), fvec2(args[1].getDecimal(), args[2].getDecimal()));
				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:billboard_move")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dBillboard(args[0].getString(), false))
			{
				_fe3d->billboard_move(args[0].getString(),
									  fvec3(args[1].getDecimal(), args[2].getDecimal(), args[3].getDecimal()));
				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:billboard_rotate")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dBillboard(args[0].getString(), false))
			{
				_fe3d->billboard_rotate(args[0].getString(),
										fvec3(args[1].getDecimal(), args[2].getDecimal(), args[3].getDecimal()));
				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:billboard_scale")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dBillboard(args[0].getString(), false))
			{
				_fe3d->billboard_scale(args[0].getString(), fvec2(args[1].getDecimal(), args[2].getDecimal()));
				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:billboard_move_to")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dBillboard(args[0].getString(), false))
			{
				_fe3d->billboard_moveTo(args[0].getString(),
										fvec3(args[1].getDecimal(), args[2].getDecimal(), args[3].getDecimal()), args[4].getDecimal());
				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:billboard_rotate_to")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dBillboard(args[0].getString(), false))
			{
				_fe3d->billboard_rotateTo(args[0].getString(),
										  fvec3(args[1].getDecimal(), args[2].getDecimal(), args[3].getDecimal()), args[4].getDecimal());
				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:billboard_scale_to")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dBillboard(args[0].getString(), false))
			{
				_fe3d->billboard_scaleTo(args[0].getString(),
										 fvec2(args[1].getDecimal(), args[2].getDecimal()), args[3].getDecimal());
				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:billboard_set_color")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dBillboard(args[0].getString(), false))
			{
				_fe3d->billboard_setColor(args[0].getString(),
										  fvec3(args[1].getDecimal(), args[2].getDecimal(), args[3].getDecimal()));
				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:billboard_set_wireframe_color")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dBillboard(args[0].getString(), false))
			{
				_fe3d->billboard_setWireframeColor(args[0].getString(),
												   fvec3(args[1].getDecimal(), args[2].getDecimal(), args[3].getDecimal()));
				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:billboard_set_min_height")
	{
		auto types = {SVT::STRING, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dBillboard(args[0].getString(), false))
			{
				_fe3d->billboard_setMinHeight(args[0].getString(), args[1].getDecimal());
				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:billboard_set_max_height")
	{
		auto types = {SVT::STRING, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dBillboard(args[0].getString(), false))
			{
				_fe3d->billboard_setMaxHeight(args[0].getString(), args[1].getDecimal());
				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:billboard_set_transparency")
	{
		auto types = {SVT::STRING, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dBillboard(args[0].getString(), false))
			{
				_fe3d->billboard_setTransparency(args[0].getString(), args[1].getDecimal());
				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:billboard_set_emission_intensity")
	{
		auto types = {SVT::STRING, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dBillboard(args[0].getString(), false))
			{
				_fe3d->billboard_setEmissionIntensity(args[0].getString(), args[1].getDecimal());
				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:billboard_set_texture_repeat")
	{
		auto types = {SVT::STRING, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dBillboard(args[0].getString(), false))
			{
				_fe3d->billboard_setTextureRepeat(args[0].getString(), args[1].getDecimal());
				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:billboard_set_lightness")
	{
		auto types = {SVT::STRING, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dBillboard(args[0].getString(), false))
			{
				_fe3d->billboard_setLightness(args[0].getString(), args[1].getDecimal());
				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:billboard_set_aabb_raycast_responsive")
	{
		auto types = {SVT::STRING, SVT::BOOLEAN};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dBillboard(args[0].getString(), false))
			{
				auto aabbIDs = _fe3d->aabb_getChildIDs(args[0].getString(), AabbParentEntityType::BILLBOARD);

				if(aabbIDs.empty())
				{
					_throwScriptError("billboard with ID \"" + args[0].getString() + "\" has no bound AABBs!");
					return true;
				}

				for(const auto& ID : aabbIDs)
				{
					_fe3d->aabb_setRaycastResponsive(ID, args[1].getBoolean());
				}

				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:billboard_set_aabb_collision_responsive")
	{
		auto types = {SVT::STRING, SVT::BOOLEAN};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dBillboard(args[0].getString(), false))
			{
				auto aabbIDs = _fe3d->aabb_getChildIDs(args[0].getString(), AabbParentEntityType::BILLBOARD);

				if(aabbIDs.empty())
				{
					_throwScriptError("billboard with ID \"" + args[0].getString() + "\" has no bound AABBs!");
					return true;
				}

				for(const auto& ID : aabbIDs)
				{
					_fe3d->aabb_setCollisionResponsive(ID, args[1].getBoolean());
				}

				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:billboard_set_shadowed")
	{
		auto types = {SVT::STRING, SVT::BOOLEAN};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dBillboard(args[0].getString(), false))
			{
				_fe3d->billboard_setShadowed(args[0].getString(), args[1].getBoolean());
				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:billboard_set_bright")
	{
		auto types = {SVT::STRING, SVT::BOOLEAN};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dBillboard(args[0].getString(), false))
			{
				_fe3d->billboard_setBright(args[0].getString(), args[1].getBoolean());
				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:billboard_set_wireframed")
	{
		auto types = {SVT::STRING, SVT::BOOLEAN};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dBillboard(args[0].getString(), false))
			{
				_fe3d->billboard_setWireframed(args[0].getString(), args[1].getBoolean());
				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:billboard_set_frozen")
	{
		auto types = {SVT::STRING, SVT::BOOLEAN};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dBillboard(args[0].getString(), false))
			{
				_fe3d->billboard_setFrozen(args[0].getString(), args[1].getBoolean());
				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:billboard_set_facing_camera_x")
	{
		auto types = {SVT::STRING, SVT::BOOLEAN};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dBillboard(args[0].getString(), false))
			{
				_fe3d->billboard_setFacingCameraX(args[0].getString(), args[1].getBoolean());
				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:billboard_set_facing_camera_y")
	{
		auto types = {SVT::STRING, SVT::BOOLEAN};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dBillboard(args[0].getString(), false))
			{
				_fe3d->billboard_setFacingCameraY(args[0].getString(), args[1].getBoolean());
				returnValues.push_back(ScriptValue(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:billboard_set_text")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dBillboard(args[0].getString(), false))
			{
				if(!_fe3d->billboard_isTextual(args[0].getString()))
				{
					_throwScriptError("billboard with ID \"" + args[0].getString() + "\" is not of type text!");
					return true;
				}
				else
				{
					_fe3d->billboard_setTextContent(args[0].getString(), args[1].getString());
					returnValues.push_back(ScriptValue(SVT::EMPTY));
				}
			}
		}
	}
	else
	{
		return false;
	}

	if(_fe3d->server_isRunning())
	{
		_throwScriptError("cannot access `fe3d:billboard` functionality as networking server!");
	}

	return true;
}