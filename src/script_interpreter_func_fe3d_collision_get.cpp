#include "script_interpreter.hpp"

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dCollisionGetter(const string & functionName, const vector<shared_ptr<ScriptValue>> & args, vector<shared_ptr<ScriptValue>> & returnValues)
{
	if(functionName == "fe3d:collision_check_camera_terrain")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			bool result = _fe3d->collision_hasCameraCollidedWithTerrain();

			returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
		}
	}
	else if(functionName == "fe3d:collision_check_camera_models")
	{
		const auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			vector<string> aabbIds = {};

			if(args[1]->getString().empty())
			{
				aabbIds = _fe3d->collision_getAabbIdsThatCollidedWithCamera();
			}
			else if(args[1]->getString() == "X")
			{
				aabbIds = _fe3d->collision_getAabbIdsThatCollidedWithCamera(DirectionType::X);
			}
			else if(args[1]->getString() == "Y")
			{
				aabbIds = _fe3d->collision_getAabbIdsThatCollidedWithCamera(DirectionType::Y);
			}
			else if(args[1]->getString() == "Z")
			{
				aabbIds = _fe3d->collision_getAabbIdsThatCollidedWithCamera(DirectionType::Z);
			}
			else
			{
				_throwRuntimeError("direction is invalid");

				return true;
			}

			for(const auto & aabbId : aabbIds)
			{
				if(_fe3d->aabb_hasParent(aabbId))
				{
					if(_fe3d->aabb_getParentType(aabbId) == AabbParentType::MODEL)
					{
						if(args[0]->getString().empty())
						{
							const auto result = _fe3d->aabb_getParentId(aabbId);

							returnValues.push_back(make_shared<ScriptValue>(SVT::STRING, result));
						}
						else
						{
							const auto rawAabbId = aabbId.substr(string("model@").size());
							const auto subAabbId = rawAabbId.substr(rawAabbId.find('@'));

							if(args[0]->getString() == subAabbId)
							{
								const auto result = _fe3d->aabb_getParentId(aabbId);

								returnValues.push_back(make_shared<ScriptValue>(SVT::STRING, result));
							}
						}
					}
				}
			}
		}
	}
	else if(functionName == "fe3d:collision_check_camera_quad3ds")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			vector<string> aabbIds = {};

			if(args[1]->getString().empty())
			{
				aabbIds = _fe3d->collision_getAabbIdsThatCollidedWithCamera();
			}
			else if(args[1]->getString() == "X")
			{
				aabbIds = _fe3d->collision_getAabbIdsThatCollidedWithCamera(DirectionType::X);
			}
			else if(args[1]->getString() == "Y")
			{
				aabbIds = _fe3d->collision_getAabbIdsThatCollidedWithCamera(DirectionType::Y);
			}
			else if(args[1]->getString() == "Z")
			{
				aabbIds = _fe3d->collision_getAabbIdsThatCollidedWithCamera(DirectionType::Z);
			}
			else
			{
				_throwRuntimeError("direction is invalid");

				return true;
			}

			for(const auto & aabbId : aabbIds)
			{
				if(_fe3d->aabb_hasParent(aabbId))
				{
					if(_fe3d->aabb_getParentType(aabbId) == AabbParentType::QUAD3D)
					{
						const auto result = _fe3d->aabb_getParentId(aabbId);

						returnValues.push_back(make_shared<ScriptValue>(SVT::STRING, result));
					}
				}
			}
		}
	}
	else if(functionName == "fe3d:collision_check_camera_text3ds")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			vector<string> aabbIds = {};

			if(args[1]->getString().empty())
			{
				aabbIds = _fe3d->collision_getAabbIdsThatCollidedWithCamera();
			}
			else if(args[1]->getString() == "X")
			{
				aabbIds = _fe3d->collision_getAabbIdsThatCollidedWithCamera(DirectionType::X);
			}
			else if(args[1]->getString() == "Y")
			{
				aabbIds = _fe3d->collision_getAabbIdsThatCollidedWithCamera(DirectionType::Y);
			}
			else if(args[1]->getString() == "Z")
			{
				aabbIds = _fe3d->collision_getAabbIdsThatCollidedWithCamera(DirectionType::Z);
			}
			else
			{
				_throwRuntimeError("direction is invalid");

				return true;
			}

			for(const auto & aabbId : aabbIds)
			{
				if(_fe3d->aabb_hasParent(aabbId))
				{
					if(_fe3d->aabb_getParentType(aabbId) == AabbParentType::TEXT3D)
					{
						const auto result = _fe3d->aabb_getParentId(aabbId);

						returnValues.push_back(make_shared<ScriptValue>(SVT::STRING, result));
					}
				}
			}
		}
	}
	else if(functionName == "fe3d:collision_check_camera_aabbs")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			vector<string> aabbIds = {};

			if(args[1]->getString().empty())
			{
				aabbIds = _fe3d->collision_getAabbIdsThatCollidedWithCamera();
			}
			else if(args[1]->getString() == "X")
			{
				aabbIds = _fe3d->collision_getAabbIdsThatCollidedWithCamera(DirectionType::X);
			}
			else if(args[1]->getString() == "Y")
			{
				aabbIds = _fe3d->collision_getAabbIdsThatCollidedWithCamera(DirectionType::Y);
			}
			else if(args[1]->getString() == "Z")
			{
				aabbIds = _fe3d->collision_getAabbIdsThatCollidedWithCamera(DirectionType::Z);
			}
			else
			{
				_throwRuntimeError("direction is invalid");

				return true;
			}

			for(const auto & aabbId : aabbIds)
			{
				if(!_fe3d->aabb_hasParent(aabbId))
				{
					returnValues.push_back(make_shared<ScriptValue>(SVT::STRING, aabbId));
				}
			}
		}
	}
	else if(functionName == "fe3d:collision_check_camera_model")
	{
		const auto types = {SVT::STRING, SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				if(args[1]->getString().empty())
				{
					bool result = false;

					for(const auto & childAabbId : _fe3d->model_getChildAabbIds(args[0]->getString()))
					{
						if(args[2]->getString().empty())
						{
							if(_fe3d->collision_hasCameraCollidedWithAabb(childAabbId))
							{
								result = true;

								break;
							}
						}
						else if(args[2]->getString() == "X")
						{
							if(_fe3d->collision_hasCameraCollidedWithAabb(childAabbId, DirectionType::X))
							{
								result = true;

								break;
							}
						}
						else if(args[2]->getString() == "Y")
						{
							if(_fe3d->collision_hasCameraCollidedWithAabb(childAabbId, DirectionType::Y))
							{
								result = true;

								break;
							}
						}
						else if(args[2]->getString() == "Z")
						{
							if(_fe3d->collision_hasCameraCollidedWithAabb(childAabbId, DirectionType::Z))
							{
								result = true;

								break;
							}
						}
						else
						{
							_throwRuntimeError("direction is invalid");

							return true;
						}
					}

					returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
				}
				else
				{
					const auto childAabbId = ("model@" + args[0]->getString() + "@" + args[1]->getString());

					if(_validateFe3dAabb(childAabbId, false))
					{
						if(args[2]->getString().empty())
						{
							const auto result = _fe3d->collision_hasCameraCollidedWithAabb(childAabbId);

							returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
						}
						else if(args[2]->getString() == "X")
						{
							const auto result = _fe3d->collision_hasCameraCollidedWithAabb(childAabbId, DirectionType::X);

							returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
						}
						else if(args[2]->getString() == "Y")
						{
							const auto result = _fe3d->collision_hasCameraCollidedWithAabb(childAabbId, DirectionType::Y);

							returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
						}
						else if(args[2]->getString() == "Z")
						{
							const auto result = _fe3d->collision_hasCameraCollidedWithAabb(childAabbId, DirectionType::Z);

							returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
						}
						else
						{
							_throwRuntimeError("direction is invalid");

							return true;
						}
					}
				}
			}
		}
	}
	else if(functionName == "fe3d:collision_check_camera_quad3d")
	{
		const auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad3d(args[0]->getString(), false))
			{
				const auto childAabbId = ("quad3d@" + args[0]->getString());

				if(_validateFe3dAabb(childAabbId, false))
				{
					if(args[1]->getString().empty())
					{
						const auto result = _fe3d->collision_hasCameraCollidedWithAabb(childAabbId);

						returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
					}
					else if(args[1]->getString() == "X")
					{
						const auto result = _fe3d->collision_hasCameraCollidedWithAabb(childAabbId, DirectionType::X);

						returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
					}
					else if(args[1]->getString() == "Y")
					{
						const auto result = _fe3d->collision_hasCameraCollidedWithAabb(childAabbId, DirectionType::Y);

						returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
					}
					else if(args[1]->getString() == "Z")
					{
						const auto result = _fe3d->collision_hasCameraCollidedWithAabb(childAabbId, DirectionType::Z);

						returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
					}
					else
					{
						_throwRuntimeError("direction is invalid");

						return true;
					}
				}
			}
		}
	}
	else if(functionName == "fe3d:collision_check_camera_text3d")
	{
		const auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dText3d(args[0]->getString(), false))
			{
				const auto childAabbId = ("text3d@" + args[0]->getString());

				if(_validateFe3dAabb(childAabbId, false))
				{
					if(args[1]->getString().empty())
					{
						const auto result = _fe3d->collision_hasCameraCollidedWithAabb(childAabbId);

						returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
					}
					else if(args[1]->getString() == "X")
					{
						const auto result = _fe3d->collision_hasCameraCollidedWithAabb(childAabbId, DirectionType::X);

						returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
					}
					else if(args[1]->getString() == "Y")
					{
						const auto result = _fe3d->collision_hasCameraCollidedWithAabb(childAabbId, DirectionType::Y);

						returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
					}
					else if(args[1]->getString() == "Z")
					{
						const auto result = _fe3d->collision_hasCameraCollidedWithAabb(childAabbId, DirectionType::Z);

						returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
					}
					else
					{
						_throwRuntimeError("direction is invalid");

						return true;
					}
				}
			}
		}
	}
	else if(functionName == "fe3d:collision_check_camera_aabb")
	{
		const auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAabb(args[0]->getString(), false))
			{
				if(args[1]->getString().empty())
				{
					const auto result = _fe3d->collision_hasCameraCollidedWithAabb(args[0]->getString());

					returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
				}
				else if(args[1]->getString() == "X")
				{
					const auto result = _fe3d->collision_hasCameraCollidedWithAabb(args[0]->getString(), DirectionType::X);

					returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
				}
				else if(args[1]->getString() == "Y")
				{
					const auto result = _fe3d->collision_hasCameraCollidedWithAabb(args[0]->getString(), DirectionType::Y);

					returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
				}
				else if(args[1]->getString() == "Z")
				{
					const auto result = _fe3d->collision_hasCameraCollidedWithAabb(args[0]->getString(), DirectionType::Z);

					returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
				}
				else
				{
					_throwRuntimeError("direction is invalid");

					return true;
				}
			}
		}
	}
	else if(functionName == "fe3d:collision_check_model_models")
	{
		const auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				set<string> modelIds = {};

				if(args[1]->getString().empty())
				{
					for(const auto & childAabbId : _fe3d->model_getChildAabbIds(args[0]->getString()))
					{
						for(const auto & collidedAabbId : _fe3d->collision_getAabbIdsThatCollidedWithAabb(childAabbId))
						{
							if(_fe3d->aabb_hasParent(collidedAabbId))
							{
								if(_fe3d->aabb_getParentType(collidedAabbId) == AabbParentType::MODEL)
								{
									if(_fe3d->aabb_getParentId(collidedAabbId) != args[0]->getString())
									{
										modelIds.insert(_fe3d->aabb_getParentId(collidedAabbId));
									}
								}
							}
						}
					}
				}
				else
				{
					const auto childAabbId = ("model@" + args[0]->getString() + "@" + args[1]->getString());

					if(_validateFe3dAabb(childAabbId, false))
					{
						for(const auto & collidedAabbId : _fe3d->collision_getAabbIdsThatCollidedWithAabb(childAabbId))
						{
							if(_fe3d->aabb_hasParent(collidedAabbId))
							{
								if(_fe3d->aabb_getParentType(collidedAabbId) == AabbParentType::MODEL)
								{
									modelIds.insert(_fe3d->aabb_getParentId(collidedAabbId));
								}
							}
						}
					}
				}

				for(const auto & modelId : modelIds)
				{
					returnValues.push_back(make_shared<ScriptValue>(SVT::STRING, modelId));
				}
			}
		}
	}
	else if(functionName == "fe3d:collision_check_quad3d_quad3ds")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad3d(args[0]->getString(), false))
			{
				set<string> quad3dIds = {};

				for(const auto & childAabbId : _fe3d->quad3d_getChildAabbIds(args[0]->getString()))
				{
					for(const auto & collidedAabbId : _fe3d->collision_getAabbIdsThatCollidedWithAabb(childAabbId))
					{
						if(_fe3d->aabb_hasParent(collidedAabbId))
						{
							if(_fe3d->aabb_getParentType(collidedAabbId) == AabbParentType::QUAD3D)
							{
								quad3dIds.insert(_fe3d->aabb_getParentId(collidedAabbId));
							}
						}
					}
				}

				for(const auto & quad3dId : quad3dIds)
				{
					returnValues.push_back(make_shared<ScriptValue>(SVT::STRING, quad3dId));
				}
			}
		}
	}
	else if(functionName == "fe3d:collision_check_text3d_text3ds")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dText3d(args[0]->getString(), false))
			{
				set<string> text3dIds = {};

				for(const auto & childAabbId : _fe3d->text3d_getChildAabbIds(args[0]->getString()))
				{
					for(const auto & collidedAabbId : _fe3d->collision_getAabbIdsThatCollidedWithAabb(childAabbId))
					{
						if(_fe3d->aabb_hasParent(collidedAabbId))
						{
							if(_fe3d->aabb_getParentType(collidedAabbId) == AabbParentType::TEXT3D)
							{
								text3dIds.insert(_fe3d->aabb_getParentId(collidedAabbId));
							}
						}
					}
				}

				for(const auto & text3dId : text3dIds)
				{
					returnValues.push_back(make_shared<ScriptValue>(SVT::STRING, text3dId));
				}
			}
		}
	}
	else if(functionName == "fe3d:collision_check_aabb_aabbs")
	{
		const auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAabb(args[0]->getString(), false))
			{
				for(const auto & aabbId : _fe3d->collision_getAabbIdsThatCollidedWithAabb(args[0]->getString()))
				{
					if(!_fe3d->aabb_hasParent(aabbId))
					{
						returnValues.push_back(make_shared<ScriptValue>(SVT::STRING, aabbId));
					}
				}
			}
		}
	}
	else if(functionName == "fe3d:collision_check_model_model")
	{
		const auto types = {SVT::STRING, SVT::STRING, SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false) && _validateFe3dModel(args[2]->getString(), false))
			{
				vector<string> firstAabbIds = {};
				vector<string> secondAabbIds = {};

				if(args[1]->getString().empty())
				{
					for(const auto & childAabbId : _fe3d->model_getChildAabbIds(args[0]->getString()))
					{
						firstAabbIds.push_back(childAabbId);
					}
				}
				else
				{
					const auto childAabbId = ("model@" + args[0]->getString() + "@" + args[1]->getString());

					if(_validateFe3dAabb(childAabbId, false))
					{
						firstAabbIds.push_back(childAabbId);
					}
				}

				if(args[3]->getString().empty())
				{
					for(const auto & childAabbId : _fe3d->model_getChildAabbIds(args[2]->getString()))
					{
						secondAabbIds.push_back(childAabbId);
					}
				}
				else
				{
					const auto childAabbId = ("model@" + args[2]->getString() + "@" + args[3]->getString());

					if(_validateFe3dAabb(childAabbId, false))
					{
						secondAabbIds.push_back(childAabbId);
					}
				}

				bool result = false;

				for(const auto & firstAabbId : firstAabbIds)
				{
					for(const auto & secondAabbId : secondAabbIds)
					{
						if(_fe3d->collision_hasAabbCollidedWithAabb(firstAabbId, secondAabbId))
						{
							result = true;

							break;
						}
					}
				}

				returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:collision_check_quad3d_quad3d")
	{
		const auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad3d(args[0]->getString(), false) && _validateFe3dQuad3d(args[1]->getString(), false))
			{
				const auto firstAabbId = ("quad3d@" + args[0]->getString());
				const auto secondAabbId = ("quad3d@" + args[1]->getString());

				if(_validateFe3dAabb(firstAabbId, false) && _validateFe3dAabb(secondAabbId, false))
				{
					const auto result = _fe3d->collision_hasAabbCollidedWithAabb(args[0]->getString(), args[1]->getString());

					returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
				}
			}
		}
	}
	else if(functionName == "fe3d:collision_check_text3d_text3d")
	{
		const auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dText3d(args[0]->getString(), false) && _validateFe3dText3d(args[1]->getString(), false))
			{
				const auto firstAabbId = ("text3d@" + args[0]->getString());
				const auto secondAabbId = ("text3d@" + args[1]->getString());

				if(_validateFe3dAabb(firstAabbId, false) && _validateFe3dAabb(secondAabbId, false))
				{
					const auto result = _fe3d->collision_hasAabbCollidedWithAabb(args[0]->getString(), args[1]->getString());

					returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
				}
			}
		}
	}
	else if(functionName == "fe3d:collision_check_aabb_aabb")
	{
		const auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dAabb(args[0]->getString(), false) && _validateFe3dAabb(args[1]->getString(), false))
			{
				const auto result = _fe3d->collision_hasAabbCollidedWithAabb(args[0]->getString(), args[1]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
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