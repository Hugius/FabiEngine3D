#include "script_interpreter.hpp"

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dRaycastGetter(const string& functionName, vector<ScriptValue>& args, vector<ScriptValue>& returnValues)
{
	if(functionName == "fe3d:raycast_get_cursor_ray_position_x")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->raycast_getCursorRay().getPosition().x;

			returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:raycast_get_cursor_ray_position_y")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->raycast_getCursorRay().getPosition().y;

			returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:raycast_get_cursor_ray_position_z")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->raycast_getCursorRay().getPosition().z;

			returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:raycast_get_cursor_ray_direction_x")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->raycast_getCursorRay().getDirection().x;

			returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:raycast_get_cursor_ray_direction_y")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->raycast_getCursorRay().getDirection().y;

			returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:raycast_get_cursor_ray_direction_z")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			const auto result = _fe3d->raycast_getCursorRay().getDirection().z;

			returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:raycast_get_point_on_terrain_x")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			if(_validateFe3dTerrain())
			{
				const auto result = _fe3d->raycast_getPointOnTerrain().x;

				returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
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

				returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
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

				returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
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

				returnValues.push_back(ScriptValue(SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:raycast_into_model")
	{
		auto types = {SVT::STRING, SVT::STRING, SVT::BOOLEAN};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			string result = "";
			auto foundAabbID = _fe3d->raycast_checkCursorInEntities(args[0].getString(), args[2].getBoolean()).first;

			if(!foundAabbID.empty())
			{
				if(_fe3d->aabb_hasParent(foundAabbID) && (_fe3d->aabb_getParentEntityType(foundAabbID) == AabbParentEntityType::MODEL))
				{
					if(args[1].getString().empty())
					{
						result = _fe3d->aabb_getParentEntityId(foundAabbID);
					}
					else
					{
						string partId = foundAabbID;
						reverse(partId.begin(), partId.end());
						partId = partId.substr(0, partId.find('@'));
						reverse(partId.begin(), partId.end());

						if(partId == args[1].getString())
						{
							result = _fe3d->aabb_getParentEntityId(foundAabbID);
						}
					}
				}
			}

			returnValues.push_back(ScriptValue(SVT::STRING, result));
		}
	}
	else if(functionName == "fe3d:raycast_into_model_distance")
	{
		auto types = {SVT::STRING, SVT::STRING, SVT::BOOLEAN};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			float result = -1.0f;
			auto intersection = _fe3d->raycast_checkCursorInEntities(args[0].getString(), args[2].getBoolean());
			string foundAabbID = intersection.first;
			float foundDistance = intersection.second;

			if(!foundAabbID.empty())
			{
				if(_fe3d->aabb_hasParent(foundAabbID) && (_fe3d->aabb_getParentEntityType(foundAabbID) == AabbParentEntityType::MODEL))
				{
					if(args[1].getString().empty())
					{
						result = foundDistance;
					}
					else
					{
						string partId = foundAabbID;
						reverse(partId.begin(), partId.end());
						partId = partId.substr(0, partId.find('@'));
						reverse(partId.begin(), partId.end());

						if(partId == args[1].getString())
						{
							result = foundDistance;
						}
					}
				}
			}

			returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:raycast_into_models")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			string result = "";
			auto foundAabbID = _fe3d->raycast_checkCursorInAny().first;

			if(!foundAabbID.empty())
			{
				if(_fe3d->aabb_hasParent(foundAabbID) && (_fe3d->aabb_getParentEntityType(foundAabbID) == AabbParentEntityType::MODEL))
				{
					result = _fe3d->aabb_getParentEntityId(foundAabbID);
				}
			}

			returnValues.push_back(ScriptValue(SVT::STRING, result));
		}
	}
	else if(functionName == "fe3d:raycast_into_models_distance")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			float result = -1.0f;
			auto intersection = _fe3d->raycast_checkCursorInAny();

			if(!intersection.first.empty())
			{
				if(_fe3d->aabb_hasParent(intersection.first) && (_fe3d->aabb_getParentEntityType(intersection.first) == AabbParentEntityType::MODEL))
				{
					result = intersection.second;
				}
			}

			returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:raycast_into_quad3d")
	{
		auto types = {SVT::STRING, SVT::BOOLEAN};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			string result = "";
			auto foundAabbID = _fe3d->raycast_checkCursorInEntities(args[0].getString(), args[1].getBoolean()).first;

			if(!foundAabbID.empty())
			{
				if(_fe3d->aabb_hasParent(foundAabbID) && (_fe3d->aabb_getParentEntityType(foundAabbID) == AabbParentEntityType::QUAD3D))
				{
					result = _fe3d->aabb_getParentEntityId(foundAabbID);
				}
			}

			returnValues.push_back(ScriptValue(SVT::STRING, result));
		}
	}
	else if(functionName == "fe3d:raycast_into_quad3ds")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			string result = "";
			auto foundAabbID = _fe3d->raycast_checkCursorInAny().first;

			if(!foundAabbID.empty())
			{
				if(_fe3d->aabb_hasParent(foundAabbID) && (_fe3d->aabb_getParentEntityType(foundAabbID) == AabbParentEntityType::QUAD3D))
				{
					result = _fe3d->aabb_getParentEntityId(foundAabbID);
				}
			}

			returnValues.push_back(ScriptValue(SVT::STRING, result));
		}
	}
	else if(functionName == "fe3d:raycast_into_quad3d_distance")
	{
		auto types = {SVT::STRING, SVT::BOOLEAN};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			float result = -1.0f;
			auto intersection = _fe3d->raycast_checkCursorInEntities(args[0].getString(), args[1].getBoolean());

			if(!intersection.first.empty())
			{
				if(_fe3d->aabb_hasParent(intersection.first) && (_fe3d->aabb_getParentEntityType(intersection.first) == AabbParentEntityType::QUAD3D))
				{
					result = intersection.second;
				}
			}

			returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:raycast_into_quad3ds_distance")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			float result = -1.0f;
			auto intersection = _fe3d->raycast_checkCursorInAny();

			if(!intersection.first.empty())
			{
				if(_fe3d->aabb_hasParent(intersection.first) && (_fe3d->aabb_getParentEntityType(intersection.first) == AabbParentEntityType::QUAD3D))
				{
					result = intersection.second;
				}
			}

			returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:raycast_into_text3d")
	{
		auto types = {SVT::STRING, SVT::BOOLEAN};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			string result = "";
			auto foundAabbID = _fe3d->raycast_checkCursorInEntities(args[0].getString(), args[1].getBoolean()).first;

			if(!foundAabbID.empty())
			{
				if(_fe3d->aabb_hasParent(foundAabbID) && (_fe3d->aabb_getParentEntityType(foundAabbID) == AabbParentEntityType::TEXT3D))
				{
					result = _fe3d->aabb_getParentEntityId(foundAabbID);
				}
			}

			returnValues.push_back(ScriptValue(SVT::STRING, result));
		}
	}
	else if(functionName == "fe3d:raycast_into_text3ds")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			string result = "";
			auto foundAabbID = _fe3d->raycast_checkCursorInAny().first;

			if(!foundAabbID.empty())
			{
				if(_fe3d->aabb_hasParent(foundAabbID) && (_fe3d->aabb_getParentEntityType(foundAabbID) == AabbParentEntityType::TEXT3D))
				{
					result = _fe3d->aabb_getParentEntityId(foundAabbID);
				}
			}

			returnValues.push_back(ScriptValue(SVT::STRING, result));
		}
	}
	else if(functionName == "fe3d:raycast_into_text3d_distance")
	{
		auto types = {SVT::STRING, SVT::BOOLEAN};

		if(_validateArgumentCount(args, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(args, types))
		{
			float result = -1.0f;
			auto intersection = _fe3d->raycast_checkCursorInEntities(args[0].getString(), args[1].getBoolean());

			if(!intersection.first.empty())
			{
				if(_fe3d->aabb_hasParent(intersection.first) && (_fe3d->aabb_getParentEntityType(intersection.first) == AabbParentEntityType::TEXT3D))
				{
					result = intersection.second;
				}
			}

			returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:raycast_into_text3ds_distance")
	{
		if(_validateArgumentCount(args, 0) && _validateArgumentTypes(args, {}))
		{
			float result = -1.0f;
			auto intersection = _fe3d->raycast_checkCursorInAny();

			if(!intersection.first.empty())
			{
				if(_fe3d->aabb_hasParent(intersection.first) && (_fe3d->aabb_getParentEntityType(intersection.first) == AabbParentEntityType::TEXT3D))
				{
					result = intersection.second;
				}
			}

			returnValues.push_back(ScriptValue(SVT::DECIMAL, result));
		}
	}

	else
	{
		return false;
	}

	if(_fe3d->server_isRunning())
	{
		_throwScriptError("cannot access `fe3d:raycast` functionality as networking server!");
	}

	return true;
}