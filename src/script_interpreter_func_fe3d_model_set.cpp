#include "script_interpreter.hpp"
#include "logger.hpp"

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dModelSetter(const string& functionName, vector<ScriptValue>& args, vector<ScriptValue>& returnValues)
{
	if(functionName == "fe3d:model_place")
	{
		auto types = {SVT::STRING, SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(!_validateFe3dID(args[0].getString()))
			{
				return true;
			}

			if(_fe3d->model_isExisting(args[0].getString()))
			{
				_throwScriptError("model already exists!");
				return true;
			}

			if(_validateFe3dModel(args[1].getString(), true))
			{
				_worldEditor->copyTemplateModel(args[0].getString(), ("@" + args[1].getString()),
												fvec3(args[2].getDecimal(), args[3].getDecimal(), args[4].getDecimal()));
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:model_delete")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0].getString(), false))
			{
				_fe3d->model_delete(args[0].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:model_delete_all")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			for(const auto& ID : _fe3d->model_getIDs())
			{
				if(ID[0] != '@')
				{
					_fe3d->model_delete(ID);
				}
			}

			returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:model_set_visible")
	{
		auto types = {SVT::STRING, SVT::BOOLEAN};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0].getString(), false))
			{
				_fe3d->model_setVisible(args[0].getString(), args[1].getBoolean());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:model_set_position")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0].getString(), false))
			{
				_fe3d->model_setBasePosition(args[0].getString(),
											 fvec3(args[1].getDecimal(), args[2].getDecimal(), args[3].getDecimal()));
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:model_set_rotation")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0].getString(), false))
			{
				_fe3d->model_setBaseRotation(args[0].getString(),
											 fvec3(args[1].getDecimal(), args[2].getDecimal(), args[3].getDecimal()));
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:model_set_rotation_origin")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0].getString(), false))
			{
				_fe3d->model_setBaseRotationOrigin(args[0].getString(),
												   fvec3(args[1].getDecimal(), args[2].getDecimal(), args[3].getDecimal()));
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:model_set_size")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0].getString(), false))
			{
				_fe3d->model_setBaseSize(args[0].getString(),
										 fvec3(args[1].getDecimal(), args[2].getDecimal(), args[3].getDecimal()));
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:model_move")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0].getString(), false))
			{
				_fe3d->model_moveBase(args[0].getString(),
									  fvec3(args[1].getDecimal(), args[2].getDecimal(), args[3].getDecimal()));
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:model_rotate")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0].getString(), false))
			{
				_fe3d->model_rotateBase(args[0].getString(),
										fvec3(args[1].getDecimal(), args[2].getDecimal(), args[3].getDecimal()));
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:model_scale")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0].getString(), false))
			{
				_fe3d->model_scaleBase(args[0].getString(),
									   fvec3(args[1].getDecimal(), args[2].getDecimal(), args[3].getDecimal()));
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:model_move_to")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0].getString(), false))
			{
				_fe3d->model_moveBaseTo(args[0].getString(),
										fvec3(args[1].getDecimal(), args[2].getDecimal(), args[3].getDecimal()), args[4].getDecimal());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:model_rotate_to")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0].getString(), false))
			{
				_fe3d->model_rotateBaseTo(args[0].getString(),
										  fvec3(args[1].getDecimal(), args[2].getDecimal(), args[3].getDecimal()), args[4].getDecimal());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:model_scale_to")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0].getString(), false))
			{
				_fe3d->model_scaleBaseTo(args[0].getString(),
										 fvec3(args[1].getDecimal(), args[2].getDecimal(), args[3].getDecimal()), args[4].getDecimal());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:model_set_min_height")
	{
		auto types = {SVT::STRING, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0].getString(), false))
			{
				_fe3d->model_setMinHeight(args[0].getString(), args[1].getDecimal());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:model_set_max_height")
	{
		auto types = {SVT::STRING, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0].getString(), false))
			{
				_fe3d->model_setMaxHeight(args[0].getString(), args[1].getDecimal());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:model_set_aabb_raycast_responsive")
	{
		auto types = {SVT::STRING, SVT::BOOLEAN};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0].getString(), false))
			{
				auto aabbIDs = _fe3d->aabb_getChildIDs(args[0].getString(), AabbParentEntityType::MODEL);

				if(aabbIDs.empty())
				{
					_throwScriptError("model with ID \"" + args[0].getString() + "\" has no bound AABBs!");
					return true;
				}

				for(const auto& ID : aabbIDs)
				{
					_fe3d->aabb_setRaycastResponsive(ID, args[1].getBoolean());
				}

				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:model_set_aabb_collision_responsive")
	{
		auto types = {SVT::STRING, SVT::BOOLEAN};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0].getString(), false))
			{
				auto aabbIDs = _fe3d->aabb_getChildIDs(args[0].getString(), AabbParentEntityType::MODEL);

				if(aabbIDs.empty())
				{
					_throwScriptError("model with ID \"" + args[0].getString() + "\" has no bound AABBs!");
					return true;
				}

				for(const auto& ID : aabbIDs)
				{
					_fe3d->aabb_setCollisionResponsive(ID, args[1].getBoolean());
				}

				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:model_set_color")
	{
		auto types = {SVT::STRING, SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0].getString(), false))
			{
				if(_validateFe3dModelPart(args[0].getString(), args[1].getString()))
				{
					_fe3d->model_setColor(args[0].getString(), args[1].getString(),
										  fvec3(args[2].getDecimal(), args[3].getDecimal(), args[4].getDecimal()));
					returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
				}
			}
		}
	}
	else if(functionName == "fe3d:model_set_wireframe_color")
	{
		auto types = {SVT::STRING, SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0].getString(), false))
			{
				if(_validateFe3dModelPart(args[0].getString(), args[1].getString()))
				{
					_fe3d->model_setWireframeColor(args[0].getString(), args[1].getString(),
												   fvec3(args[2].getDecimal(), args[3].getDecimal(), args[4].getDecimal()));
					returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
				}
			}
		}
	}
	else if(functionName == "fe3d:model_set_lod_entity_id")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0].getString(), false))
			{
				_fe3d->model_setLevelOfDetailEntityID(args[0].getString(), args[1].getString());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:model_set_lightness")
	{
		auto types = {SVT::STRING, SVT::STRING, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0].getString(), false))
			{
				if(_validateFe3dModelPart(args[0].getString(), args[1].getString()))
				{
					_fe3d->model_setLightness(args[0].getString(), args[1].getString(), args[2].getDecimal());
					returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
				}
			}
		}
	}
	else if(functionName == "fe3d:model_set_specular_shininess")
	{
		auto types = {SVT::STRING, SVT::STRING, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0].getString(), false))
			{
				if(_validateFe3dModelPart(args[0].getString(), args[1].getString()))
				{
					_fe3d->model_setSpecularShininess(args[0].getString(), args[1].getString(), args[2].getDecimal());
					returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
				}
			}
		}
	}
	else if(functionName == "fe3d:model_set_specular_intensity")
	{
		auto types = {SVT::STRING, SVT::STRING, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0].getString(), false))
			{
				if(_validateFe3dModelPart(args[0].getString(), args[1].getString()))
				{
					_fe3d->model_setSpecularIntensity(args[0].getString(), args[1].getString(), args[2].getDecimal());
					returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
				}
			}
		}
	}
	else if(functionName == "fe3d:model_set_reflectivity")
	{
		auto types = {SVT::STRING, SVT::STRING, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0].getString(), false))
			{
				if(_validateFe3dModelPart(args[0].getString(), args[1].getString()))
				{
					_fe3d->model_setReflectivity(args[0].getString(), args[1].getString(), args[2].getDecimal());
					returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
				}
			}
		}
	}
	else if(functionName == "fe3d:model_set_lod_distance")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0].getString(), false))
			{
				_fe3d->model_setLevelOfDetailDistance(args[0].getString(), args[1].getDecimal());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:model_set_transparency")
	{
		auto types = {SVT::STRING, SVT::STRING, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0].getString(), false))
			{
				if(_validateFe3dModelPart(args[0].getString(), args[1].getString()))
				{
					_fe3d->model_setTransparency(args[0].getString(), args[1].getString(), args[2].getDecimal());
					returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
				}
			}
		}
	}
	else if(functionName == "fe3d:model_set_specular")
	{
		auto types = {SVT::STRING, SVT::STRING, SVT::BOOLEAN};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0].getString(), false))
			{
				if(_validateFe3dModelPart(args[0].getString(), args[1].getString()))
				{
					_fe3d->model_setSpecular(args[0].getString(), args[1].getString(), args[2].getBoolean());
					returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
				}
			}
		}
	}
	else if(functionName == "fe3d:model_set_reflected")
	{
		auto types = {SVT::STRING, SVT::BOOLEAN};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0].getString(), false))
			{
				_fe3d->model_setReflected(args[0].getString(), args[1].getBoolean());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:model_set_reflective")
	{
		auto types = {SVT::STRING, SVT::STRING, SVT::BOOLEAN};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0].getString(), false))
			{
				if(_validateFe3dModelPart(args[0].getString(), args[1].getString()))
				{
					_fe3d->model_setReflective(args[0].getString(), args[1].getString(), args[2].getBoolean());
					returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
				}
			}
		}
	}
	else if(functionName == "fe3d:model_set_shadowed")
	{
		auto types = {SVT::STRING, SVT::BOOLEAN};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0].getString(), false))
			{
				_fe3d->model_setShadowed(args[0].getString(), args[1].getBoolean());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:model_set_frozen")
	{
		auto types = {SVT::STRING, SVT::BOOLEAN};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0].getString(), false))
			{
				_fe3d->model_setFrozen(args[0].getString(), args[1].getBoolean());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:model_set_wireframed")
	{
		auto types = {SVT::STRING, SVT::STRING, SVT::BOOLEAN};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0].getString(), false))
			{
				if(_validateFe3dModelPart(args[0].getString(), args[1].getString()))
				{
					_fe3d->model_setWireframed(args[0].getString(), args[1].getString(), args[2].getBoolean());
					returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
				}
			}
		}
	}
	else if(functionName == "fe3d:model_set_bright")
	{
		auto types = {SVT::STRING, SVT::BOOLEAN};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0].getString(), false))
			{
				_fe3d->model_setBright(args[0].getString(), args[1].getBoolean());
				returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:model_set_emission_intensity")
	{
		auto types = {SVT::STRING, SVT::STRING, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0].getString(), false))
			{
				if(_validateFe3dModelPart(args[0].getString(), args[1].getString()))
				{
					_fe3d->model_setEmissionIntensity(args[0].getString(), args[1].getString(), args[2].getDecimal());
					returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
				}
			}
		}
	}
	else if(functionName == "fe3d:model_set_reflection_type")
	{
		auto types = {SVT::STRING, SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0].getString(), false))
			{
				if(_validateFe3dModelPart(args[0].getString(), args[1].getString()))
				{
					if(args[2].getString() == "CUBE")
					{
						_fe3d->model_setReflectionType(args[0].getString(), args[1].getString(), ReflectionType::CUBE);
						returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
					}
					else if(args[2].getString() == "PLANAR")
					{
						_fe3d->model_setReflectionType(args[0].getString(), args[1].getString(), ReflectionType::PLANAR);
						returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
					}
					else
					{
						Logger::throwWarning("invalid reflection type!");
						returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
					}
				}
			}
		}
	}
	else if(functionName == "fe3d:model_set_rotation_order")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0].getString(), false))
			{
				if(args[1].getString() == "XYZ")
				{
					_fe3d->model_setRotationOrder(args[0].getString(), DirectionOrder::XYZ);
					returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
				}
				else if(args[1].getString() == "XZY")
				{
					_fe3d->model_setRotationOrder(args[0].getString(), DirectionOrder::XZY);
					returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
				}
				else if(args[1].getString() == "YXZ")
				{
					_fe3d->model_setRotationOrder(args[0].getString(), DirectionOrder::YXZ);
					returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
				}
				else if(args[1].getString() == "YZX")
				{
					_fe3d->model_setRotationOrder(args[0].getString(), DirectionOrder::YZX);
					returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
				}
				else if(args[1].getString() == "ZXY")
				{
					_fe3d->model_setRotationOrder(args[0].getString(), DirectionOrder::ZXY);
					returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
				}
				else if(args[1].getString() == "ZYX")
				{
					_fe3d->model_setRotationOrder(args[0].getString(), DirectionOrder::ZYX);
					returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
				}
				else
				{
					Logger::throwWarning("invalid rotation order!");
					returnValues.push_back(ScriptValue(_fe3d, SVT::EMPTY));
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
		_throwScriptError("cannot access `fe3d:model` functionality as networking server!");
	}

	return true;
}