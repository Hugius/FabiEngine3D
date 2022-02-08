#include "script_interpreter.hpp"

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dRaycastGetter(const string& functionName, const vector<shared_ptr<ScriptValue>>& args, vector<shared_ptr<ScriptValue>>& returnValues)
{
	if(functionName == "fe3d:raycast_get_cursor_ray_position_x")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->raycast_getCursorRayPosition().x;

			returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:raycast_get_cursor_ray_position_y")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->raycast_getCursorRayPosition().y;

			returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:raycast_get_cursor_ray_position_z")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->raycast_getCursorRayPosition().z;

			returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:raycast_get_cursor_ray_direction_x")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->raycast_getCursorRayDirection().x;

			returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:raycast_get_cursor_ray_direction_y")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->raycast_getCursorRayDirection().y;

			returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:raycast_get_cursor_ray_direction_z")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->raycast_getCursorRayDirection().z;

			returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:raycast_is_terrain_intersection_enabled")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(_validateFe3dTerrain())
			{
				const auto result = _fe3d->raycast_isTerrainIntersectionEnabled();

				returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:raycast_get_terrain_intersection_distance")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(_validateFe3dTerrain())
			{
				const auto result = _fe3d->raycast_getTerrainIntersectionDistance();

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:raycast_get_terrain_intersection_precision")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(_validateFe3dTerrain())
			{
				const auto result = _fe3d->raycast_getTerrainIntersectionPrecision();

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:raycast_is_aabb_intersection_enabled")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(_validateFe3dTerrain())
			{
				const auto result = _fe3d->raycast_isAabbIntersectionEnabled();

				returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:raycast_get_point_on_terrain_x")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(_validateFe3dTerrain())
			{
				const auto result = _fe3d->raycast_getPointOnTerrain().x;

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:raycast_get_point_on_terrain_y")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(_validateFe3dTerrain())
			{
				const auto result = _fe3d->raycast_getPointOnTerrain().y;

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:raycast_get_point_on_terrain_z")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(_validateFe3dTerrain())
			{
				const auto result = _fe3d->raycast_getPointOnTerrain().z;

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:raycast_is_point_on_terrain_valid")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(_validateFe3dTerrain())
			{
				const auto result = _fe3d->raycast_isPointOnTerrainValid();

				returnValues.push_back(make_shared<ScriptValue>(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:raycast_get_closest_model")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			const auto aabbId = _fe3d->raycast_getClosestAabbId();
			string result = "";

			if(!aabbId.empty())
			{
				if(_fe3d->aabb_hasParent(aabbId))
				{
					if(_fe3d->aabb_getParentEntityType(aabbId) == AabbParentEntityType::MODEL)
					{
						if(args[0]->getString().empty())
						{
							result = _fe3d->aabb_getParentEntityId(aabbId);
						}
						else
						{
							auto partId = aabbId;
							reverse(partId.begin(), partId.end());
							partId = partId.substr(0, partId.find('@'));
							reverse(partId.begin(), partId.end());

							if(partId == args[1]->getString())
							{
								result = _fe3d->aabb_getParentEntityId(aabbId);
							}
						}
					}
				}
			}

			returnValues.push_back(make_shared<ScriptValue>(SVT::STRING, result));
		}
	}
	else if(functionName == "fe3d:raycast_get_closest_quad3d")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto aabbId = _fe3d->raycast_getClosestAabbId();
			string result = "";

			if(!aabbId.empty())
			{
				if(_fe3d->aabb_hasParent(aabbId))
				{
					if(_fe3d->aabb_getParentEntityType(aabbId) == AabbParentEntityType::QUAD3D)
					{
						result = _fe3d->aabb_getParentEntityId(aabbId);
					}
				}
			}

			returnValues.push_back(make_shared<ScriptValue>(SVT::STRING, result));
		}
	}
	else if(functionName == "fe3d:raycast_get_closest_text3d")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto aabbId = _fe3d->raycast_getClosestAabbId();
			string result = "";

			if(!aabbId.empty())
			{
				if(_fe3d->aabb_hasParent(aabbId))
				{
					if(_fe3d->aabb_getParentEntityType(aabbId) == AabbParentEntityType::TEXT3D)
					{
						result = _fe3d->aabb_getParentEntityId(aabbId);
					}
				}
			}

			returnValues.push_back(make_shared<ScriptValue>(SVT::STRING, result));
		}
	}
	else if(functionName == "fe3d:raycast_get_distance_to_model")
	{
		auto types = {SVT::STRING, SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dModel(args[0]->getString(), false))
			{
				if(_validateFe3dAabb((args[0]->getString() + "@" + args[1]->getString())))
				{
					const auto result = _fe3d->raycast_getDistanceToAabb((args[0]->getString() + "@" + args[1]->getString()));

					returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
				}
			}
		}
	}
	else if(functionName == "fe3d:raycast_get_distance_to_quad3d")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dQuad3d(args[0]->getString(), false))
			{
				const auto result = _fe3d->raycast_getDistanceToAabb(args[0]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:raycast_get_distance_to_text3d")
	{
		auto types = {SVT::STRING};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			if(_validateFe3dText3d(args[0]->getString(), false))
			{
				const auto result = _fe3d->raycast_getDistanceToAabb(args[0]->getString());

				returnValues.push_back(make_shared<ScriptValue>(SVT::DECIMAL, result));
			}
		}
	}
	else
	{
		return false;
	}

	if(_fe3d->server_isRunning())
	{
		_throwRuntimeError("cannot access `fe3d:raycast` functionality as a networking server");
		return true;
	}

	return true;
}