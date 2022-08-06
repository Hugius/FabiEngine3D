#include "script_interpreter.hpp"

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dText3dSetter(const string & functionName, const vector<shared_ptr<ScriptValue>> & args, vector<shared_ptr<ScriptValue>> & returnValues)
{
	if(functionName == "fe3d:text3d_place")
	{
		const auto types = {SVT::STRING, SVT::STRING, SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(!_validateFe3dId(args[0]->getString()))
			{
				return true;
			}

			if(_fe3d->text3d_isExisting(args[0]->getString()))
			{
				_throwRuntimeError("text3D already exists");

				return true;
			}

			if(_validateFe3dText3d(args[1]->getString(), true))
			{
				_duplicator->copyEditorText3d(args[0]->getString(), ("@" + args[1]->getString()));

				_fe3d->text3d_setPosition(args[0]->getString(), fvec3(args[3]->getDecimal(), args[4]->getDecimal(), args[5]->getDecimal()));
				_fe3d->text3d_setContent(args[0]->getString(), args[2]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:text3d_set_content")
	{
		const auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dText3d(args[0]->getString(), false))
			{
				_fe3d->text3d_setContent(args[0]->getString(), args[1]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:text3d_delete")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dText3d(args[0]->getString(), false))
			{
				_duplicator->deleteCopiedText3d(args[0]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:text3d_delete_all")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			for(const auto & text3dId : _fe3d->text3d_getIds())
			{
				if(text3dId[0] != '@')
				{
					_duplicator->deleteCopiedText3d(text3dId);
				}
			}

			returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:text3d_set_visible")
	{
		const auto types = {SVT::STRING, SVT::BOOLEAN};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dText3d(args[0]->getString(), false))
			{
				_fe3d->text3d_setVisible(args[0]->getString(), args[1]->getBoolean());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:text3d_set_position")
	{
		const auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dText3d(args[0]->getString(), false))
			{
				_fe3d->text3d_setPosition(args[0]->getString(), fvec3(args[1]->getDecimal(), args[2]->getDecimal(), args[3]->getDecimal()));

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:text3d_set_rotation")
	{
		const auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dText3d(args[0]->getString(), false))
			{
				_fe3d->text3d_setRotation(args[0]->getString(), fvec3(args[1]->getDecimal(), args[2]->getDecimal(), args[3]->getDecimal()));

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:text3d_set_size")
	{
		const auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dText3d(args[0]->getString(), false))
			{
				_fe3d->text3d_setSize(args[0]->getString(), fvec2(args[1]->getDecimal(), args[2]->getDecimal()));

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:text3d_set_horizontally_flipped")
	{
		const auto types = {SVT::STRING, SVT::BOOLEAN};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dText3d(args[0]->getString(), false))
			{
				_fe3d->text3d_setHorizontallyFlipped(args[0]->getString(), args[1]->getBoolean());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:text3d_set_vertically_flipped")
	{
		const auto types = {SVT::STRING, SVT::BOOLEAN};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dText3d(args[0]->getString(), false))
			{
				_fe3d->text3d_setVerticallyFlipped(args[0]->getString(), args[1]->getBoolean());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:text3d_move")
	{
		const auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dText3d(args[0]->getString(), false))
			{
				_fe3d->text3d_move(args[0]->getString(), fvec3(args[1]->getDecimal(), args[2]->getDecimal(), args[3]->getDecimal()));

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:text3d_rotate")
	{
		const auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dText3d(args[0]->getString(), false))
			{
				_fe3d->text3d_rotate(args[0]->getString(), fvec3(args[1]->getDecimal(), args[2]->getDecimal(), args[3]->getDecimal()));

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:text3d_scale")
	{
		const auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dText3d(args[0]->getString(), false))
			{
				_fe3d->text3d_scale(args[0]->getString(), fvec2(args[1]->getDecimal(), args[2]->getDecimal()));

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:text3d_move_to")
	{
		const auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dText3d(args[0]->getString(), false))
			{
				_fe3d->text3d_moveTo(args[0]->getString(), fvec3(args[1]->getDecimal(), args[2]->getDecimal(), args[3]->getDecimal()), args[4]->getDecimal());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:text3d_rotate_to")
	{
		const auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dText3d(args[0]->getString(), false))
			{
				_fe3d->text3d_rotateTo(args[0]->getString(), fvec3(args[1]->getDecimal(), args[2]->getDecimal(), args[3]->getDecimal()), args[4]->getDecimal());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:text3d_scale_to")
	{
		const auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dText3d(args[0]->getString(), false))
			{
				_fe3d->text3d_scaleTo(args[0]->getString(), fvec2(args[1]->getDecimal(), args[2]->getDecimal()), args[3]->getDecimal());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:text3d_set_color")
	{
		const auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dText3d(args[0]->getString(), false))
			{
				_fe3d->text3d_setColor(args[0]->getString(), fvec3(args[1]->getDecimal(), args[2]->getDecimal(), args[3]->getDecimal()));

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:text3d_set_wireframe_color")
	{
		const auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dText3d(args[0]->getString(), false))
			{
				_fe3d->text3d_setWireframeColor(args[0]->getString(), fvec3(args[1]->getDecimal(), args[2]->getDecimal(), args[3]->getDecimal()));

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:text3d_set_min_clip_position")
	{
		const auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dText3d(args[0]->getString(), false))
			{
				_fe3d->text3d_setMinClipPosition(args[0]->getString(), fvec3(args[1]->getDecimal(), args[2]->getDecimal(), args[3]->getDecimal()));

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:text3d_set_max_clip_position")
	{
		const auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dText3d(args[0]->getString(), false))
			{
				_fe3d->text3d_setMaxClipPosition(args[0]->getString(), fvec3(args[1]->getDecimal(), args[2]->getDecimal(), args[3]->getDecimal()));

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:text3d_set_opacity")
	{
		const auto types = {SVT::STRING, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dText3d(args[0]->getString(), false))
			{
				_fe3d->text3d_setOpacity(args[0]->getString(), args[1]->getDecimal());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:text3d_set_lightness")
	{
		const auto types = {SVT::STRING, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dText3d(args[0]->getString(), false))
			{
				_fe3d->text3d_setLightness(args[0]->getString(), args[1]->getDecimal());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:text3d_set_aabb_visible")
	{
		const auto types = {SVT::STRING, SVT::BOOLEAN};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dText3d(args[0]->getString(), false))
			{
				auto aabbIds = _fe3d->text3d_getChildAabbIds(args[0]->getString());

				if(aabbIds.empty())
				{
					_throwRuntimeError("text3D has no bound AABBs");

					return true;
				}

				for(const auto & aabbId : aabbIds)
				{
					_fe3d->aabb_setVisible(aabbId, args[1]->getBoolean());
				}

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:text3d_set_shadowed")
	{
		const auto types = {SVT::STRING, SVT::BOOLEAN};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dText3d(args[0]->getString(), false))
			{
				_fe3d->text3d_setShadowed(args[0]->getString(), args[1]->getBoolean());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:text3d_set_reflected")
	{
		const auto types = {SVT::STRING, SVT::BOOLEAN};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dText3d(args[0]->getString(), false))
			{
				_fe3d->text3d_setReflected(args[0]->getString(), args[1]->getBoolean());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:text3d_set_refracted")
	{
		const auto types = {SVT::STRING, SVT::BOOLEAN};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dText3d(args[0]->getString(), false))
			{
				_fe3d->text3d_setRefracted(args[0]->getString(), args[1]->getBoolean());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:text3d_set_bright")
	{
		const auto types = {SVT::STRING, SVT::BOOLEAN};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dText3d(args[0]->getString(), false))
			{
				_fe3d->text3d_setBright(args[0]->getString(), args[1]->getBoolean());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:text3d_set_wireframed")
	{
		const auto types = {SVT::STRING, SVT::BOOLEAN};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dText3d(args[0]->getString(), false))
			{
				_fe3d->text3d_setWireframed(args[0]->getString(), args[1]->getBoolean());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:text3d_set_facing_camera_horizontally")
	{
		const auto types = {SVT::STRING, SVT::BOOLEAN};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dText3d(args[0]->getString(), false))
			{
				_fe3d->text3d_setFacingCameraHorizontally(args[0]->getString(), args[1]->getBoolean());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:text3d_set_facing_camera_vertically")
	{
		const auto types = {SVT::STRING, SVT::BOOLEAN};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dText3d(args[0]->getString(), false))
			{
				_fe3d->text3d_setFacingCameraVertically(args[0]->getString(), args[1]->getBoolean());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:text3d_set_min_alpha")
	{
		const auto types = {SVT::STRING, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dText3d(args[0]->getString(), false))
			{
				_fe3d->text3d_setMinAlpha(args[0]->getString(), args[1]->getDecimal());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:text3d_set_rotation_order")
	{
		const auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dText3d(args[0]->getString(), false))
			{
				if(args[1]->getString() == "XYZ")
				{
					_fe3d->text3d_setRotationOrder(args[0]->getString(), DirectionOrderType::XYZ);

					returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
				}
				else if(args[1]->getString() == "XZY")
				{
					_fe3d->text3d_setRotationOrder(args[0]->getString(), DirectionOrderType::XZY);

					returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
				}
				else if(args[1]->getString() == "YXZ")
				{
					_fe3d->text3d_setRotationOrder(args[0]->getString(), DirectionOrderType::YXZ);

					returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
				}
				else if(args[1]->getString() == "YZX")
				{
					_fe3d->text3d_setRotationOrder(args[0]->getString(), DirectionOrderType::YZX);

					returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
				}
				else if(args[1]->getString() == "ZXY")
				{
					_fe3d->text3d_setRotationOrder(args[0]->getString(), DirectionOrderType::ZXY);

					returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
				}
				else if(args[1]->getString() == "ZYX")
				{
					_fe3d->text3d_setRotationOrder(args[0]->getString(), DirectionOrderType::ZYX);

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
	else
	{
		return false;
	}

	if(_fe3d->server_isRunning())
	{
		_throwRuntimeError("cannot access `fe3d:text3d` functionality as a networking server");

		return true;
	}

	return true;
}