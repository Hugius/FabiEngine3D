#include "script_interpreter.hpp"

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dCollisionSetter(const string & functionName, const vector<shared_ptr<ScriptValue>> & args, vector<shared_ptr<ScriptValue>> & returnValues)
{
	if(functionName == "fe3d:collision_set_camera_box")
	{
		const auto types = {SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			_fe3d->collision_setCameraBox(args[0]->getDecimal(), args[1]->getDecimal(), args[2]->getDecimal(), args[3]->getDecimal(), args[4]->getDecimal(), args[5]->getDecimal());

			returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:collision_calculate_camera_terrain")
	{
		const auto types = {SVT::BOOLEAN, SVT::DECIMAL};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			_fe3d->collision_calculateCameraWithTerrain(args[0]->getBoolean(), args[1]->getDecimal());

			returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:collision_calculate_camera_aabbs")
	{
		const auto types = {SVT::BOOLEAN, SVT::BOOLEAN, SVT::BOOLEAN};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			_fe3d->collision_calculateCameraWithAabbs(args[0]->getBoolean(), args[1]->getBoolean(), args[2]->getBoolean());

			returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
		}
	}
	else if(functionName == "fe3d:collision_calculate_model_aabbs")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				for(const auto & aabbId : _fe3d->model_getChildAabbIds(args[0]->getString()))
				{
					_fe3d->collision_calculateAabbWithAabbs(aabbId);
				}

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:collision_calculate_quad3d_aabbs")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad3d(args[0]->getString(), false))
			{
				for(const auto & childAabbId : _fe3d->quad3d_getChildAabbIds(args[0]->getString()))
				{
					_fe3d->collision_calculateAabbWithAabbs(childAabbId);
				}

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:collision_calculate_text3d_aabbs")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dText3d(args[0]->getString(), false))
			{
				for(const auto & childAabbId : _fe3d->text3d_getChildAabbIds(args[0]->getString()))
				{
					_fe3d->collision_calculateAabbWithAabbs(childAabbId);
				}

				returnValues.push_back(make_shared<ScriptValue>(SVT::EMPTY));
			}
		}
	}
	else if(functionName == "fe3d:collision_calculate_aabb_aabbs")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAabb(args[0]->getString(), false))
			{
				_fe3d->collision_calculateAabbWithAabbs(args[0]->getString());

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
		_throwRuntimeError("cannot access `fe3d:collision` functionality as a networking server");

		return true;
	}

	return true;
}