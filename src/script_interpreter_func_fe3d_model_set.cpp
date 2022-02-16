#include "script_interpreter.hpp"
#include "logger.hpp"

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dModelSetter(const string& functionName, const vector<shared_ptr<ScriptValue>>& args, vector<shared_ptr<ScriptValue>>& returnValues)
{
	if(functionName == "fe3d:model_place")
	{
		auto types = {SVT::STRING, SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(!_validateFe3dId(args[0]->getString()))
			{
				return true;
			}

			if(_fe3d->model_isExisting(args[0]->getString()))
			{
				_throwRuntimeError("model already exists");
				return true;
			}

			if(_validateFe3dModel(args[1]->getString(), true))
			{
				_worldUtilities->copyTemplateModel(args[0]->getString(), ("@" + args[1]->getString()));

				_fe3d->model_setBasePosition(args[0]->getString(), fvec3(args[2]->getDecimal(), args[3]->getDecimal(), args[4]->getDecimal()));

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:model_delete")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				_fe3d->model_delete(args[0]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:model_delete_all")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			for(const auto& id : _fe3d->model_getIds())
			{
				if(id[0] != '@')
				{
					_fe3d->model_delete(id);
				}
			}

			returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:model_set_visible")
	{
		auto types = {SVT::STRING, SVT::BOOLEAN};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				_fe3d->model_setVisible(args[0]->getString(), args[1]->getBoolean());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:model_set_face_culled")
	{
		auto types = {SVT::STRING, SVT::STRING, SVT::BOOLEAN};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				if(_validateFe3dModelPart(args[0]->getString(), args[1]->getString()))
				{
					_fe3d->model_setFaceCulled(args[0]->getString(), args[1]->getString(), args[2]->getBoolean());

					returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
				}
			}
		}
	}
	else if(functionName == "fe3d:model_set_base_position")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				_fe3d->model_setBasePosition(args[0]->getString(), fvec3(args[1]->getDecimal(), args[2]->getDecimal(), args[3]->getDecimal()));

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:model_set_base_rotation")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				_fe3d->model_setBaseRotation(args[0]->getString(), fvec3(args[1]->getDecimal(), args[2]->getDecimal(), args[3]->getDecimal()));

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:model_set_base_rotation_origin")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				_fe3d->model_setBaseRotationOrigin(args[0]->getString(), fvec3(args[1]->getDecimal(), args[2]->getDecimal(), args[3]->getDecimal()));

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:model_set_base_size")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				_fe3d->model_setBaseSize(args[0]->getString(), fvec3(args[1]->getDecimal(), args[2]->getDecimal(), args[3]->getDecimal()));

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:model_set_part_position")
	{
		auto types = {SVT::STRING, SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				if(_validateFe3dModelPart(args[0]->getString(), args[1]->getString()))
				{
					_fe3d->model_setPartPosition(args[0]->getString(), args[1]->getString(), fvec3(args[2]->getDecimal(), args[3]->getDecimal(), args[4]->getDecimal()));

					returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
				}
			}
		}
	}
	else if(functionName == "fe3d:model_set_part_rotation")
	{
		auto types = {SVT::STRING, SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				if(_validateFe3dModelPart(args[0]->getString(), args[1]->getString()))
				{
					_fe3d->model_setPartRotation(args[0]->getString(), args[1]->getString(), fvec3(args[2]->getDecimal(), args[3]->getDecimal(), args[4]->getDecimal()));

					returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
				}
			}
		}
	}
	else if(functionName == "fe3d:model_set_part_rotation_origin")
	{
		auto types = {SVT::STRING, SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				if(_validateFe3dModelPart(args[0]->getString(), args[1]->getString()))
				{
					_fe3d->model_setPartRotationOrigin(args[0]->getString(), args[1]->getString(), fvec3(args[2]->getDecimal(), args[3]->getDecimal(), args[4]->getDecimal()));

					returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
				}
			}
		}
	}
	else if(functionName == "fe3d:model_set_part_size")
	{
		auto types = {SVT::STRING, SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				if(_validateFe3dModelPart(args[0]->getString(), args[1]->getString()))
				{
					_fe3d->model_setPartSize(args[0]->getString(), args[1]->getString(), fvec3(args[2]->getDecimal(), args[3]->getDecimal(), args[4]->getDecimal()));

					returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
				}
			}
		}
	}
	else if(functionName == "fe3d:model_move_base")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				_fe3d->model_moveBase(args[0]->getString(), fvec3(args[1]->getDecimal(), args[2]->getDecimal(), args[3]->getDecimal()));

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:model_rotate_base")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				_fe3d->model_rotateBase(args[0]->getString(), fvec3(args[1]->getDecimal(), args[2]->getDecimal(), args[3]->getDecimal()));
				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:model_scale_base")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				_fe3d->model_scaleBase(args[0]->getString(), fvec3(args[1]->getDecimal(), args[2]->getDecimal(), args[3]->getDecimal()));

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:model_move_part")
	{
		auto types = {SVT::STRING, SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				if(_validateFe3dModelPart(args[0]->getString(), args[1]->getString()))
				{
					_fe3d->model_movePart(args[0]->getString(), args[1]->getString(), fvec3(args[2]->getDecimal(), args[3]->getDecimal(), args[4]->getDecimal()));

					returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
				}
			}
		}
	}
	else if(functionName == "fe3d:model_rotate_part")
	{
		auto types = {SVT::STRING, SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				if(_validateFe3dModelPart(args[0]->getString(), args[1]->getString()))
				{
					_fe3d->model_rotatePart(args[0]->getString(), args[1]->getString(), fvec3(args[2]->getDecimal(), args[3]->getDecimal(), args[4]->getDecimal()));

					returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
				}
			}
		}
	}
	else if(functionName == "fe3d:model_scale_part")
	{
		auto types = {SVT::STRING, SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				if(_validateFe3dModelPart(args[0]->getString(), args[1]->getString()))
				{
					_fe3d->model_scalePart(args[0]->getString(), args[1]->getString(), fvec3(args[2]->getDecimal(), args[3]->getDecimal(), args[4]->getDecimal()));

					returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
				}
			}
		}
	}
	else if(functionName == "fe3d:model_move_base_to")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				_fe3d->model_moveBaseTo(args[0]->getString(), fvec3(args[1]->getDecimal(), args[2]->getDecimal(), args[3]->getDecimal()), args[4]->getDecimal());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:model_rotate_base_to")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				_fe3d->model_rotateBaseTo(args[0]->getString(), fvec3(args[1]->getDecimal(), args[2]->getDecimal(), args[3]->getDecimal()), args[4]->getDecimal());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:model_scale_base_to")
	{
		auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				_fe3d->model_scaleBaseTo(args[0]->getString(), fvec3(args[1]->getDecimal(), args[2]->getDecimal(), args[3]->getDecimal()), args[4]->getDecimal());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:model_move_part_to")
	{
		auto types = {SVT::STRING, SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				if(_validateFe3dModelPart(args[0]->getString(), args[1]->getString()))
				{
					_fe3d->model_movePartTo(args[0]->getString(), args[1]->getString(), fvec3(args[2]->getDecimal(), args[3]->getDecimal(), args[4]->getDecimal()), args[5]->getDecimal());

					returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
				}
			}
		}
	}
	else if(functionName == "fe3d:model_rotate_part_to")
	{
		auto types = {SVT::STRING, SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				if(_validateFe3dModelPart(args[0]->getString(), args[1]->getString()))
				{
					_fe3d->model_rotatePartTo(args[0]->getString(), args[1]->getString(), fvec3(args[2]->getDecimal(), args[3]->getDecimal(), args[4]->getDecimal()), args[5]->getDecimal());

					returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
				}
			}
		}
	}
	else if(functionName == "fe3d:model_scale_part_to")
	{
		auto types = {SVT::STRING, SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				if(_validateFe3dModelPart(args[0]->getString(), args[1]->getString()))
				{
					_fe3d->model_scalePartTo(args[0]->getString(), args[1]->getString(), fvec3(args[2]->getDecimal(), args[3]->getDecimal(), args[4]->getDecimal()), args[5]->getDecimal());

					returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
				}
			}
		}
	}
	else if(functionName == "fe3d:model_set_min_height")
	{
		auto types = {SVT::STRING, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				_fe3d->model_setMinHeight(args[0]->getString(), args[1]->getDecimal());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:model_set_max_height")
	{
		auto types = {SVT::STRING, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				_fe3d->model_setMaxHeight(args[0]->getString(), args[1]->getDecimal());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:model_set_aabb_raycast_responsive")
	{
		auto types = {SVT::STRING, SVT::BOOLEAN};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				auto aabbIds = _fe3d->model_getChildAabbIds(args[0]->getString());

				if(aabbIds.empty())
				{
					_throwRuntimeError("model has no bound AABBs");
					return true;
				}

				for(const auto& id : aabbIds)
				{
					_fe3d->aabb_setRaycastResponsive(id, args[1]->getBoolean());
				}

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:model_set_aabb_collision_responsive")
	{
		auto types = {SVT::STRING, SVT::BOOLEAN};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				auto aabbIds = _fe3d->model_getChildAabbIds(args[0]->getString());

				if(aabbIds.empty())
				{
					_throwRuntimeError("model has no bound AABBs");
					return true;
				}

				for(const auto& id : aabbIds)
				{
					_fe3d->aabb_setCollisionResponsive(id, args[1]->getBoolean());
				}

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:model_set_texture_repeat")
	{
		auto types = {SVT::STRING, SVT::STRING, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				if(_validateFe3dModelPart(args[0]->getString(), args[1]->getString()))
				{
					_fe3d->model_setTextureRepeat(args[0]->getString(), args[1]->getString(), args[2]->getDecimal());

					returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
				}
			}
		}
	}
	else if(functionName == "fe3d:model_set_diffuse_map")
	{
		auto types = {SVT::STRING, SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				if(_validateFe3dModelPart(args[0]->getString(), args[1]->getString()))
				{
					_fe3d->model_setDiffuseMap(args[0]->getString(), args[1]->getString(), args[2]->getString());

					returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
				}
			}
		}
	}
	else if(functionName == "fe3d:model_set_emission_map")
	{
		auto types = {SVT::STRING, SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				if(_validateFe3dModelPart(args[0]->getString(), args[1]->getString()))
				{
					_fe3d->model_setEmissionMap(args[0]->getString(), args[1]->getString(), args[2]->getString());

					returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
				}
			}
		}
	}
	else if(functionName == "fe3d:model_set_specular_map")
	{
		auto types = {SVT::STRING, SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				if(_validateFe3dModelPart(args[0]->getString(), args[1]->getString()))
				{
					_fe3d->model_setSpecularMap(args[0]->getString(), args[1]->getString(), args[2]->getString());

					returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
				}
			}
		}
	}
	else if(functionName == "fe3d:model_set_reflection_map")
	{
		auto types = {SVT::STRING, SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				if(_validateFe3dModelPart(args[0]->getString(), args[1]->getString()))
				{
					_fe3d->model_setReflectionMap(args[0]->getString(), args[1]->getString(), args[2]->getString());

					returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
				}
			}
		}
	}
	else if(functionName == "fe3d:model_set_normal_map")
	{
		auto types = {SVT::STRING, SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				if(_validateFe3dModelPart(args[0]->getString(), args[1]->getString()))
				{
					_fe3d->model_setNormalMap(args[0]->getString(), args[1]->getString(), args[2]->getString());

					returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
				}
			}
		}
	}
	else if(functionName == "fe3d:model_set_color")
	{
		auto types = {SVT::STRING, SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				if(_validateFe3dModelPart(args[0]->getString(), args[1]->getString()))
				{
					_fe3d->model_setColor(args[0]->getString(), args[1]->getString(), fvec3(args[2]->getDecimal(), args[3]->getDecimal(), args[4]->getDecimal()));

					returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
				}
			}
		}
	}
	else if(functionName == "fe3d:model_set_wireframe_color")
	{
		auto types = {SVT::STRING, SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				if(_validateFe3dModelPart(args[0]->getString(), args[1]->getString()))
				{
					_fe3d->model_setWireframeColor(args[0]->getString(), args[1]->getString(), fvec3(args[2]->getDecimal(), args[3]->getDecimal(), args[4]->getDecimal()));

					returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
				}
			}
		}
	}
	else if(functionName == "fe3d:model_set_lod_entity_id")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				_fe3d->model_setLevelOfDetailEntityId(args[0]->getString(), args[1]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:model_set_lightness")
	{
		auto types = {SVT::STRING, SVT::STRING, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				if(_validateFe3dModelPart(args[0]->getString(), args[1]->getString()))
				{
					_fe3d->model_setLightness(args[0]->getString(), args[1]->getString(), args[2]->getDecimal());

					returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
				}
			}
		}
	}
	else if(functionName == "fe3d:model_set_specular_shininess")
	{
		auto types = {SVT::STRING, SVT::STRING, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				if(_validateFe3dModelPart(args[0]->getString(), args[1]->getString()))
				{
					_fe3d->model_setSpecularShininess(args[0]->getString(), args[1]->getString(), args[2]->getDecimal());

					returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
				}
			}
		}
	}
	else if(functionName == "fe3d:model_set_specular_intensity")
	{
		auto types = {SVT::STRING, SVT::STRING, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				if(_validateFe3dModelPart(args[0]->getString(), args[1]->getString()))
				{
					_fe3d->model_setSpecularIntensity(args[0]->getString(), args[1]->getString(), args[2]->getDecimal());

					returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
				}
			}
		}
	}
	else if(functionName == "fe3d:model_set_reflectivity")
	{
		auto types = {SVT::STRING, SVT::STRING, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				if(_validateFe3dModelPart(args[0]->getString(), args[1]->getString()))
				{
					_fe3d->model_setReflectivity(args[0]->getString(), args[1]->getString(), args[2]->getDecimal());

					returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
				}
			}
		}
	}
	else if(functionName == "fe3d:model_set_lod_distance")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				_fe3d->model_setLevelOfDetailDistance(args[0]->getString(), args[1]->getDecimal());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:model_set_opacity")
	{
		auto types = {SVT::STRING, SVT::STRING, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				if(_validateFe3dModelPart(args[0]->getString(), args[1]->getString()))
				{
					_fe3d->model_setOpacity(args[0]->getString(), args[1]->getString(), args[2]->getDecimal());

					returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
				}
			}
		}
	}
	else if(functionName == "fe3d:model_set_specular")
	{
		auto types = {SVT::STRING, SVT::STRING, SVT::BOOLEAN};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				if(_validateFe3dModelPart(args[0]->getString(), args[1]->getString()))
				{
					_fe3d->model_setSpecular(args[0]->getString(), args[1]->getString(), args[2]->getBoolean());

					returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
				}
			}
		}
	}
	else if(functionName == "fe3d:model_set_reflected")
	{
		auto types = {SVT::STRING, SVT::BOOLEAN};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				_fe3d->model_setReflected(args[0]->getString(), args[1]->getBoolean());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:model_set_reflective")
	{
		auto types = {SVT::STRING, SVT::STRING, SVT::BOOLEAN};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				if(_validateFe3dModelPart(args[0]->getString(), args[1]->getString()))
				{
					_fe3d->model_setReflective(args[0]->getString(), args[1]->getString(), args[2]->getBoolean());

					returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
				}
			}
		}
	}
	else if(functionName == "fe3d:model_set_shadowed")
	{
		auto types = {SVT::STRING, SVT::BOOLEAN};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				_fe3d->model_setShadowed(args[0]->getString(), args[1]->getBoolean());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:model_set_frozen")
	{
		auto types = {SVT::STRING, SVT::BOOLEAN};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				_fe3d->model_setFrozen(args[0]->getString(), args[1]->getBoolean());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:model_set_wireframed")
	{
		auto types = {SVT::STRING, SVT::STRING, SVT::BOOLEAN};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				if(_validateFe3dModelPart(args[0]->getString(), args[1]->getString()))
				{
					_fe3d->model_setWireframed(args[0]->getString(), args[1]->getString(), args[2]->getBoolean());

					returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
				}
			}
		}
	}
	else if(functionName == "fe3d:model_set_bright")
	{
		auto types = {SVT::STRING, SVT::STRING, SVT::BOOLEAN};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				if(_validateFe3dModelPart(args[0]->getString(), args[1]->getString()))
				{
					_fe3d->model_setBright(args[0]->getString(), args[1]->getString(), args[2]->getBoolean());

					returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
				}
			}
		}
	}
	else if(functionName == "fe3d:model_set_emission_intensity")
	{
		auto types = {SVT::STRING, SVT::STRING, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				if(_validateFe3dModelPart(args[0]->getString(), args[1]->getString()))
				{
					_fe3d->model_setEmissionIntensity(args[0]->getString(), args[1]->getString(), args[2]->getDecimal());

					returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
				}
			}
		}
	}
	else if(functionName == "fe3d:model_set_reflection_type")
	{
		auto types = {SVT::STRING, SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				if(_validateFe3dModelPart(args[0]->getString(), args[1]->getString()))
				{
					if(args[2]->getString() == "CUBE")
					{
						_fe3d->model_setReflectionType(args[0]->getString(), args[1]->getString(), ReflectionType::CUBE);

						returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
					}
					else if(args[2]->getString() == "PLANAR")
					{
						_fe3d->model_setReflectionType(args[0]->getString(), args[1]->getString(), ReflectionType::PLANAR);

						returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
					}
					else
					{
						_throwRuntimeError("reflection type is invalid");
						return true;
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
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				if(args[1]->getString() == "XYZ")
				{
					_fe3d->model_setRotationOrder(args[0]->getString(), DirectionOrder::XYZ);

					returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
				}
				else if(args[1]->getString() == "XZY")
				{
					_fe3d->model_setRotationOrder(args[0]->getString(), DirectionOrder::XZY);

					returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
				}
				else if(args[1]->getString() == "YXZ")
				{
					_fe3d->model_setRotationOrder(args[0]->getString(), DirectionOrder::YXZ);

					returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
				}
				else if(args[1]->getString() == "YZX")
				{
					_fe3d->model_setRotationOrder(args[0]->getString(), DirectionOrder::YZX);

					returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
				}
				else if(args[1]->getString() == "ZXY")
				{
					_fe3d->model_setRotationOrder(args[0]->getString(), DirectionOrder::ZXY);

					returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
				}
				else if(args[1]->getString() == "ZYX")
				{
					_fe3d->model_setRotationOrder(args[0]->getString(), DirectionOrder::ZYX);

					returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
				}
				else
				{
					_throwRuntimeError("rotation order is invalid");
					return true;
				}
			}
		}
	}
	else if(functionName == "fe3d:model_start_animation")
	{
		auto types = {SVT::STRING, SVT::STRING, SVT::INTEGER};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation3d(args[0]->getString()) && _validateFe3dModel(args[1]->getString(), false))
			{
				if(_fe3d->model_isAnimationStarted(args[0]->getString(), args[1]->getString()))
				{
					_throwRuntimeError("animation is already started");
					return true;
				}
				if((args[2]->getInteger() < -1) || (args[2]->getInteger() == 0))
				{
					_throwRuntimeError("play count is invalid");
					return true;
				}

				for(const auto& partId : _fe3d->animation3d_getPartIds(args[1]->getString()))
				{
					if(!partId.empty())
					{
						if(!_fe3d->model_hasPart(args[0]->getString(), partId))
						{
							_throwRuntimeError("model does not have the required animation parts");
							return true;
						}
					}
				}

				_fe3d->model_startAnimation(args[0]->getString(), args[1]->getString(), args[2]->getInteger());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:model_pause_animation")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation3d(args[0]->getString()) && _validateFe3dModel(args[1]->getString(), false))
			{
				if(!_fe3d->model_isAnimationStarted(args[0]->getString(), args[1]->getString()))
				{
					_throwRuntimeError("animation is not started");
					return true;
				}
				if(_fe3d->model_isAnimationPaused(args[0]->getString(), args[1]->getString()))
				{
					_throwRuntimeError("animation is not playing");
					return true;
				}

				_fe3d->model_pauseAnimation(args[0]->getString(), args[1]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:model_autopause_animation")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation3d(args[0]->getString()) && _validateFe3dModel(args[1]->getString(), false))
			{
				if(!_fe3d->model_isAnimationStarted(args[0]->getString(), args[1]->getString()))
				{
					_throwRuntimeError("animation is not started");
					return true;
				}
				if(_fe3d->model_isAnimationPaused(args[0]->getString(), args[1]->getString()))
				{
					_throwRuntimeError("animation not playing");
					return true;
				}

				_fe3d->model_autopauseAnimation(args[0]->getString(), args[1]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:model_resume_animation")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation3d(args[0]->getString()) && _validateFe3dModel(args[1]->getString(), false))
			{
				if(!_fe3d->model_isAnimationStarted(args[0]->getString(), args[1]->getString()))
				{
					_throwRuntimeError("animation is not started");
					return true;
				}
				if(!_fe3d->model_isAnimationPaused(args[0]->getString(), args[1]->getString()))
				{
					_throwRuntimeError("animation is not paused");
					return true;
				}

				_fe3d->model_resumeAnimation(args[0]->getString(), args[1]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:model_stop_animation")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation3d(args[0]->getString()) && _validateFe3dModel(args[1]->getString(), false))
			{
				if(!_fe3d->model_isAnimationStarted(args[0]->getString(), args[1]->getString()))
				{
					_throwRuntimeError("animation is not started");
					return true;
				}

				_fe3d->model_stopAnimation(args[0]->getString(), args[1]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:model_set_animation_speed_multiplier")
	{
		auto types = {SVT::STRING, SVT::STRING, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation3d(args[0]->getString()) && _validateFe3dModel(args[1]->getString(), false))
			{
				if(!_fe3d->model_isAnimationStarted(args[0]->getString(), args[1]->getString()))
				{
					_throwRuntimeError("animation is not started");
					return true;
				}

				_fe3d->model_setAnimationSpeedMultiplier(args[0]->getString(), args[1]->getString(), args[2]->getDecimal());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:model_set_animation_frame_index")
	{
		auto types = {SVT::STRING, SVT::STRING, SVT::INTEGER};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation3d(args[0]->getString()) && _validateFe3dModel(args[1]->getString(), false))
			{
				if(!_fe3d->model_isAnimationStarted(args[0]->getString(), args[1]->getString()))
				{
					_throwRuntimeError("animation is not started");
					return true;
				}

				_fe3d->model_setAnimationFrameIndex(args[0]->getString(), args[1]->getString(), args[2]->getInteger());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else
	{
		return false;
	}

	if(_fe3d->server_isRunning())
	{
		_throwRuntimeError("cannot access `fe3d:model` functionality as a networking server");
		return true;
	}

	return true;
}