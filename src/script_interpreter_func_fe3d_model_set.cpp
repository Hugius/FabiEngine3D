#include "script_interpreter.hpp"

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dModelSetter(const string & functionName, const vector<shared_ptr<ScriptValue>> & args, vector<shared_ptr<ScriptValue>> & returnValues)
{
	if(functionName == "fe3d:model_place")
	{
		const auto types = {SVT::STRING, SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
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
				_duplicator->copyTemplateModel(args[0]->getString(), ("@" + args[1]->getString()));

				_fe3d->model_setBasePosition(args[0]->getString(), fvec3(args[2]->getDecimal(), args[3]->getDecimal(), args[4]->getDecimal()));

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:model_delete")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
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
			for(const auto & modelId : _fe3d->model_getIds())
			{
				if(modelId[0] != '@')
				{
					_fe3d->model_delete(modelId);
				}
			}

			returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:model_set_visible")
	{
		const auto types = {SVT::STRING, SVT::BOOLEAN};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
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
		const auto types = {SVT::STRING, SVT::STRING, SVT::BOOLEAN};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
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
		const auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
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
		const auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
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
		const auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
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
		const auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
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
		const auto types = {SVT::STRING, SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
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
		const auto types = {SVT::STRING, SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
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
		const auto types = {SVT::STRING, SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
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
		const auto types = {SVT::STRING, SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
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
		const auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
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
		const auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
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
		const auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
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
		const auto types = {SVT::STRING, SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
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
		const auto types = {SVT::STRING, SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
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
		const auto types = {SVT::STRING, SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
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
		const auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
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
		const auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
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
		const auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
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
		const auto types = {SVT::STRING, SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
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
		const auto types = {SVT::STRING, SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
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
		const auto types = {SVT::STRING, SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
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
	else if(functionName == "fe3d:model_set_min_clip_position")
	{
		const auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				_fe3d->model_setMinClipPosition(args[0]->getString(), fvec3(args[1]->getDecimal(), args[2]->getDecimal(), args[3]->getDecimal()));

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:model_set_max_clip_position")
	{
		const auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				_fe3d->model_setMaxClipPosition(args[0]->getString(), fvec3(args[1]->getDecimal(), args[2]->getDecimal(), args[3]->getDecimal()));

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:model_set_aabb_raycast_responsive")
	{
		const auto types = {SVT::STRING, SVT::BOOLEAN};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				auto aabbIds = _fe3d->model_getChildAabbIds(args[0]->getString());

				if(aabbIds.empty())
				{
					_throwRuntimeError("model has no bound AABBs");

					return true;
				}

				for(const auto & aabbId : aabbIds)
				{
					_fe3d->aabb_setRaycastResponsive(aabbId, args[1]->getBoolean());
				}

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:model_set_aabb_collision_responsive")
	{
		const auto types = {SVT::STRING, SVT::BOOLEAN};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				auto aabbIds = _fe3d->model_getChildAabbIds(args[0]->getString());

				if(aabbIds.empty())
				{
					_throwRuntimeError("model has no bound AABBs");

					return true;
				}

				for(const auto & aabbId : aabbIds)
				{
					_fe3d->aabb_setCollisionResponsive(aabbId, args[1]->getBoolean());
				}

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:model_set_texture_repeat")
	{
		const auto types = {SVT::STRING, SVT::STRING, SVT::INTEGER};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				if(_validateFe3dModelPart(args[0]->getString(), args[1]->getString()))
				{
					_fe3d->model_setTextureRepeat(args[0]->getString(), args[1]->getString(), args[2]->getInteger());

					returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
				}
			}
		}
	}
	else if(functionName == "fe3d:model_set_diffuse_map")
	{
		const auto types = {SVT::STRING, SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
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
		const auto types = {SVT::STRING, SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
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
		const auto types = {SVT::STRING, SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
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
		const auto types = {SVT::STRING, SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
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
	else if(functionName == "fe3d:model_set_refraction_map")
	{
		const auto types = {SVT::STRING, SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				if(_validateFe3dModelPart(args[0]->getString(), args[1]->getString()))
				{
					_fe3d->model_setRefractionMap(args[0]->getString(), args[1]->getString(), args[2]->getString());

					returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
				}
			}
		}
	}
	else if(functionName == "fe3d:model_set_normal_map")
	{
		const auto types = {SVT::STRING, SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
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
		const auto types = {SVT::STRING, SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
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
		const auto types = {SVT::STRING, SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
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
	else if(functionName == "fe3d:model_set_lod_id")
	{
		const auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				_fe3d->model_setLevelOfDetailId(args[0]->getString(), args[1]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:model_set_lightness")
	{
		const auto types = {SVT::STRING, SVT::STRING, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
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
		const auto types = {SVT::STRING, SVT::STRING, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
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
		const auto types = {SVT::STRING, SVT::STRING, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
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
		const auto types = {SVT::STRING, SVT::STRING, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
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
	else if(functionName == "fe3d:model_set_refractivity")
	{
		const auto types = {SVT::STRING, SVT::STRING, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				if(_validateFe3dModelPart(args[0]->getString(), args[1]->getString()))
				{
					_fe3d->model_setRefractivity(args[0]->getString(), args[1]->getString(), args[2]->getDecimal());

					returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
				}
			}
		}
	}
	else if(functionName == "fe3d:model_set_lod_distance")
	{
		const auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
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
		const auto types = {SVT::STRING, SVT::STRING, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
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
		const auto types = {SVT::STRING, SVT::STRING, SVT::BOOLEAN};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
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
		const auto types = {SVT::STRING, SVT::BOOLEAN};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				_fe3d->model_setReflected(args[0]->getString(), args[1]->getBoolean());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:model_set_refracted")
	{
		const auto types = {SVT::STRING, SVT::BOOLEAN};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				_fe3d->model_setRefracted(args[0]->getString(), args[1]->getBoolean());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:model_set_reflective")
	{
		const auto types = {SVT::STRING, SVT::STRING, SVT::BOOLEAN};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
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
	else if(functionName == "fe3d:model_set_refractive")
	{
		const auto types = {SVT::STRING, SVT::STRING, SVT::BOOLEAN};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				if(_validateFe3dModelPart(args[0]->getString(), args[1]->getString()))
				{
					_fe3d->model_setRefractive(args[0]->getString(), args[1]->getString(), args[2]->getBoolean());

					returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
				}
			}
		}
	}
	else if(functionName == "fe3d:model_set_shadowed")
	{
		const auto types = {SVT::STRING, SVT::BOOLEAN};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
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
		const auto types = {SVT::STRING, SVT::BOOLEAN};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
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
		const auto types = {SVT::STRING, SVT::STRING, SVT::BOOLEAN};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
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
		const auto types = {SVT::STRING, SVT::STRING, SVT::BOOLEAN};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
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
		const auto types = {SVT::STRING, SVT::STRING, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
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
	else if(functionName == "fe3d:model_set_min_alpha")
	{
		const auto types = {SVT::STRING, SVT::STRING, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				if(_validateFe3dModelPart(args[0]->getString(), args[1]->getString()))
				{
					_fe3d->model_setMinAlpha(args[0]->getString(), args[1]->getString(), args[2]->getDecimal());

					returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
				}
			}
		}
	}
	else if(functionName == "fe3d:model_set_reflection_type")
	{
		const auto types = {SVT::STRING, SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
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
	else if(functionName == "fe3d:model_set_refraction_type")
	{
		const auto types = {SVT::STRING, SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				if(_validateFe3dModelPart(args[0]->getString(), args[1]->getString()))
				{
					if(args[2]->getString() == "CUBE")
					{
						_fe3d->model_setRefractionType(args[0]->getString(), args[1]->getString(), RefractionType::CUBE);

						returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
					}
					else if(args[2]->getString() == "PLANAR")
					{
						_fe3d->model_setRefractionType(args[0]->getString(), args[1]->getString(), RefractionType::PLANAR);

						returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
					}
					else
					{
						_throwRuntimeError("refraction type is invalid");

						return true;
					}
				}
			}
		}
	}
	else if(functionName == "fe3d:model_set_rotation_order")
	{
		const auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				if(args[1]->getString() == "XYZ")
				{
					_fe3d->model_setRotationOrder(args[0]->getString(), DirectionOrderType::XYZ);

					returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
				}
				else if(args[1]->getString() == "XZY")
				{
					_fe3d->model_setRotationOrder(args[0]->getString(), DirectionOrderType::XZY);

					returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
				}
				else if(args[1]->getString() == "YXZ")
				{
					_fe3d->model_setRotationOrder(args[0]->getString(), DirectionOrderType::YXZ);

					returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
				}
				else if(args[1]->getString() == "YZX")
				{
					_fe3d->model_setRotationOrder(args[0]->getString(), DirectionOrderType::YZX);

					returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
				}
				else if(args[1]->getString() == "ZXY")
				{
					_fe3d->model_setRotationOrder(args[0]->getString(), DirectionOrderType::ZXY);

					returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
				}
				else if(args[1]->getString() == "ZYX")
				{
					_fe3d->model_setRotationOrder(args[0]->getString(), DirectionOrderType::ZYX);

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
		const auto types = {SVT::STRING, SVT::STRING, SVT::INTEGER};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation3d(args[0]->getString()) && _validateFe3dModel(args[1]->getString(), false))
			{
				if(_fe3d->model_isAnimationStarted(args[0]->getString(), args[1]->getString()))
				{
					_throwRuntimeError("animation3D is already started");

					return true;
				}

				if((args[2]->getInteger() == 0) || (args[2]->getInteger() < -1))
				{
					_throwRuntimeError("play count is invalid");

					return true;
				}

				for(const auto & partId : _fe3d->animation3d_getPartIds(args[1]->getString()))
				{
					if(!partId.empty())
					{
						if(!_fe3d->model_hasPart(args[0]->getString(), partId))
						{
							_throwRuntimeError("model does not have the required animation3D parts");

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
		const auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation3d(args[0]->getString()) && _validateFe3dModel(args[1]->getString(), false))
			{
				if(!_fe3d->model_isAnimationStarted(args[0]->getString(), args[1]->getString()))
				{
					_throwRuntimeError("animation3D is not started");

					return true;
				}

				if(_fe3d->model_isAnimationPaused(args[0]->getString(), args[1]->getString()))
				{
					_throwRuntimeError("animation3D is already paused");

					return true;
				}

				_fe3d->model_pauseAnimation(args[0]->getString(), args[1]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:model_autopause_animation")
	{
		const auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation3d(args[0]->getString()) && _validateFe3dModel(args[1]->getString(), false))
			{
				if(!_fe3d->model_isAnimationStarted(args[0]->getString(), args[1]->getString()))
				{
					_throwRuntimeError("animation3D is not started");

					return true;
				}

				if(_fe3d->model_isAnimationPaused(args[0]->getString(), args[1]->getString()))
				{
					_throwRuntimeError("animation3D is already paused");

					return true;
				}

				_fe3d->model_autopauseAnimation(args[0]->getString(), args[1]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:model_resume_animation")
	{
		const auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation3d(args[0]->getString()) && _validateFe3dModel(args[1]->getString(), false))
			{
				if(!_fe3d->model_isAnimationStarted(args[0]->getString(), args[1]->getString()))
				{
					_throwRuntimeError("animation3D is not started");

					return true;
				}

				if(!_fe3d->model_isAnimationPaused(args[0]->getString(), args[1]->getString()))
				{
					_throwRuntimeError("animation3D is not paused");

					return true;
				}

				_fe3d->model_resumeAnimation(args[0]->getString(), args[1]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:model_stop_animation")
	{
		const auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation3d(args[0]->getString()) && _validateFe3dModel(args[1]->getString(), false))
			{
				if(!_fe3d->model_isAnimationStarted(args[0]->getString(), args[1]->getString()))
				{
					_throwRuntimeError("animation3D is not started");

					return true;
				}

				_fe3d->model_stopAnimation(args[0]->getString(), args[1]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:model_set_animation_speed_multiplier")
	{
		const auto types = {SVT::STRING, SVT::STRING, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation3d(args[0]->getString()) && _validateFe3dModel(args[1]->getString(), false))
			{
				if(!_fe3d->model_isAnimationStarted(args[0]->getString(), args[1]->getString()))
				{
					_throwRuntimeError("animation3D is not started");

					return true;
				}

				_fe3d->model_setAnimationSpeedMultiplier(args[0]->getString(), args[1]->getString(), args[2]->getDecimal());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:model_set_animation_frame_index")
	{
		const auto types = {SVT::STRING, SVT::STRING, SVT::INTEGER};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAnimation3d(args[0]->getString()) && _validateFe3dModel(args[1]->getString(), false))
			{
				if(!_fe3d->model_isAnimationStarted(args[0]->getString(), args[1]->getString()))
				{
					_throwRuntimeError("animation3D is not started");

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