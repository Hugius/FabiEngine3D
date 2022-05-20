#include "script_interpreter.hpp"

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dSkySetter(const string & functionName, const vector<shared_ptr<ScriptValue>> & args, vector<shared_ptr<ScriptValue>> & returnValues)
{
	if(functionName == "fe3d:sky_place")
	{
		const auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(!_validateFe3dId(args[0]->getString()))
			{
				return true;
			}

			if(_fe3d->sky_isExisting(args[0]->getString()))
			{
				_throwRuntimeError("sky already exists");

				return true;
			}

			if(_validateFe3dSky(args[0]->getString(), true))
			{
				_duplicator->copyTemplateSky(args[0]->getString(), ("@" + args[1]->getString()));

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:sky_select")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dSky(args[0]->getString(), false))
			{
				_fe3d->sky_select(args[0]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:sky_delete")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dSky(args[0]->getString(), false))
			{
				_duplicator->deleteCopiedSky(args[0]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:sky_delete_all")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			for(const auto & skyId : _fe3d->sky_getIds())
			{
				if(skyId[0] != '@')
				{
					_duplicator->deleteCopiedSky(skyId);
				}
			}

			returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:sky_set_lightness")
	{
		const auto types = {SVT::STRING, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dSky(args[0]->getString(), false))
			{
				_fe3d->sky_setLightness(_fe3d->sky_getSelectedId(), args[1]->getDecimal());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:sky_set_color")
	{
		const auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dSky(args[0]->getString(), false))
			{
				_fe3d->sky_setColor(_fe3d->sky_getSelectedId(), fvec3(args[1]->getDecimal(), args[2]->getDecimal(), args[3]->getDecimal()));

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:sky_set_wireframe_color")
	{
		const auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dSky(args[0]->getString(), false))
			{
				_fe3d->sky_setWireframeColor(_fe3d->sky_getSelectedId(), fvec3(args[1]->getDecimal(), args[2]->getDecimal(), args[3]->getDecimal()));

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:sky_set_rotation")
	{
		const auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dSky(args[0]->getString(), false))
			{
				_fe3d->sky_setRotation(_fe3d->sky_getSelectedId(), fvec3(args[1]->getDecimal(), args[2]->getDecimal(), args[3]->getDecimal()));

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:sky_rotate")
	{
		const auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dSky(args[0]->getString(), false))
			{
				_fe3d->sky_rotate(_fe3d->sky_getSelectedId(), fvec3(args[1]->getDecimal(), args[2]->getDecimal(), args[3]->getDecimal()));

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:sky_rotate_to")
	{
		const auto types = {SVT::STRING, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dSky(args[0]->getString(), false))
			{
				_fe3d->sky_rotateTo(_fe3d->sky_getSelectedId(), fvec3(args[1]->getDecimal(), args[2]->getDecimal(), args[3]->getDecimal()), args[4]->getDecimal());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:sky_set_wireframed")
	{
		const auto types = {SVT::STRING, SVT::BOOLEAN};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dSky(args[0]->getString(), false))
			{
				_fe3d->sky_setWireframed(_fe3d->sky_getSelectedId(), args[1]->getBoolean());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:sky_set_left_cube_map")
	{
		const auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dSky(args[0]->getString(), false))
			{
				_fe3d->sky_setLeftCubeMap(_fe3d->sky_getSelectedId(), args[1]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:sky_set_right_cube_map")
	{
		const auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dSky(args[0]->getString(), false))
			{
				_fe3d->sky_setRightCubeMap(_fe3d->sky_getSelectedId(), args[1]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:sky_set_bottom_cube_map")
	{
		const auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dSky(args[0]->getString(), false))
			{
				_fe3d->sky_setBottomCubeMap(_fe3d->sky_getSelectedId(), args[1]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:sky_set_top_cube_map")
	{
		const auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dSky(args[0]->getString(), false))
			{
				_fe3d->sky_setTopCubeMap(_fe3d->sky_getSelectedId(), args[1]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:sky_set_back_cube_map")
	{
		const auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dSky(args[0]->getString(), false))
			{
				_fe3d->sky_setBackCubeMap(_fe3d->sky_getSelectedId(), args[1]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:sky_set_front_cube_map")
	{
		const auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dSky(args[0]->getString(), false))
			{
				_fe3d->sky_setFrontCubeMap(_fe3d->sky_getSelectedId(), args[1]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:sky_set_rotation_order")
	{
		const auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dSky(args[0]->getString(), false))
			{
				if(args[1]->getString() == "XYZ")
				{
					_fe3d->sky_setRotationOrder(args[0]->getString(), DirectionOrderType::XYZ);

					returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
				}
				else if(args[1]->getString() == "XZY")
				{
					_fe3d->sky_setRotationOrder(args[0]->getString(), DirectionOrderType::XZY);

					returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
				}
				else if(args[1]->getString() == "YXZ")
				{
					_fe3d->sky_setRotationOrder(args[0]->getString(), DirectionOrderType::YXZ);

					returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
				}
				else if(args[1]->getString() == "YZX")
				{
					_fe3d->sky_setRotationOrder(args[0]->getString(), DirectionOrderType::YZX);

					returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
				}
				else if(args[1]->getString() == "ZXY")
				{
					_fe3d->sky_setRotationOrder(args[0]->getString(), DirectionOrderType::ZXY);

					returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
				}
				else if(args[1]->getString() == "ZYX")
				{
					_fe3d->sky_setRotationOrder(args[0]->getString(), DirectionOrderType::ZYX);

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
		_throwRuntimeError("cannot access `fe3d:sky` functionality as a networking server");

		return true;
	}

	return true;
}