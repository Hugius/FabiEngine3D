#include "script_interpreter.hpp"

using SVT = ScriptValueType;

const bool ScriptInterpreter::_executeFe3dRaycastGetter(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues)
{
	if(functionName == "fe3d:raycast_get_cursor_ray_position_x")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			auto result = _fe3d.raycast_getCursorRay().getPosition().x;
			returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:raycast_get_cursor_ray_position_y")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			auto result = _fe3d.raycast_getCursorRay().getPosition().y;
			returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:raycast_get_cursor_ray_position_z")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			auto result = _fe3d.raycast_getCursorRay().getPosition().z;
			returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:raycast_get_cursor_ray_direction_x")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			auto result = _fe3d.raycast_getCursorRay().getDirection().x;
			returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:raycast_get_cursor_ray_direction_y")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			auto result = _fe3d.raycast_getCursorRay().getDirection().y;
			returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:raycast_get_cursor_ray_direction_z")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			auto result = _fe3d.raycast_getCursorRay().getDirection().z;
			returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:raycast_get_point_on_terrain_x")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			if(_validateFe3dTerrain())
			{
				auto result = _fe3d.raycast_getPointOnTerrain().x;
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:raycast_get_point_on_terrain_y")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			if(_validateFe3dTerrain())
			{
				auto result = _fe3d.raycast_getPointOnTerrain().y;
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:raycast_get_point_on_terrain_z")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			if(_validateFe3dTerrain())
			{
				auto result = _fe3d.raycast_getPointOnTerrain().z;
				returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
			}
		}
	}
	else if(functionName == "fe3d:raycast_is_point_on_terrain_valid")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			if(_validateFe3dTerrain())
			{
				auto result = _fe3d.raycast_isPointOnTerrainValid();
				returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
			}
		}
	}
	else if(functionName == "fe3d:raycast_into_model")
	{
		auto types = {SVT::STRING, SVT::STRING, SVT::BOOLEAN};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Find aabbEntity ID
			string result = "";
			auto foundAabbID = _fe3d.raycast_checkCursorInEntities(arguments[0].getString(), arguments[2].getBoolean()).first;

			// Check if AABB found
			if(!foundAabbID.empty())
			{
				// Check if AABB has modelEntity parent
				if(_fe3d.aabb_hasParent(foundAabbID) &&
				   (_fe3d.aabb_getParentEntityType(foundAabbID) == AabbParentEntityType::MODEL))
				{
					if(arguments[1].getString().empty()) // No specific AABB part
					{
						result = _fe3d.aabb_getParentEntityID(foundAabbID);
					}
					else // Specific AABB part
					{
						// Extract AABB part ID
						string partID = foundAabbID;
						reverse(partID.begin(), partID.end());
						partID = partID.substr(0, partID.find('@'));
						reverse(partID.begin(), partID.end());

						// Check if AABB part IDs match
						if(partID == arguments[1].getString())
						{
							result = _fe3d.aabb_getParentEntityID(foundAabbID);
						}
					}
				}
			}

			// Return
			returnValues.push_back(ScriptValue(_fe3d, SVT::STRING, result));
		}
	}
	else if(functionName == "fe3d:raycast_into_model_distance")
	{
		auto types = {SVT::STRING, SVT::STRING, SVT::BOOLEAN};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Find aabbEntity ID
			float result = -1.0f;
			auto intersection = _fe3d.raycast_checkCursorInEntities(arguments[0].getString(), arguments[2].getBoolean());
			string foundAabbID = intersection.first;
			float foundDistance = intersection.second;

			// Check if AABB found
			if(!foundAabbID.empty())
			{
				// Check if AABB has modelEntity parent
				if(_fe3d.aabb_hasParent(foundAabbID) &&
				   (_fe3d.aabb_getParentEntityType(foundAabbID) == AabbParentEntityType::MODEL))
				{
					if(arguments[1].getString().empty()) // No specific AABB part
					{
						result = foundDistance;
					}
					else // Specific AABB part
					{
						// Extract AABB part ID
						string partID = foundAabbID;
						reverse(partID.begin(), partID.end());
						partID = partID.substr(0, partID.find('@'));
						reverse(partID.begin(), partID.end());

						// Check if AABB part IDs match
						if(partID == arguments[1].getString())
						{
							result = foundDistance;
						}
					}
				}
			}

			// Return
			returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:raycast_into_models")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			// Find aabbEntity ID
			string result = "";
			auto foundAabbID = _fe3d.raycast_checkCursorInAny().first;

			// Check if AABB found
			if(!foundAabbID.empty())
			{
				// Check if AABB has modelEntity parent
				if(_fe3d.aabb_hasParent(foundAabbID) &&
				   (_fe3d.aabb_getParentEntityType(foundAabbID) == AabbParentEntityType::MODEL))
				{
					result = _fe3d.aabb_getParentEntityID(foundAabbID);
				}
			}

			// Return
			returnValues.push_back(ScriptValue(_fe3d, SVT::STRING, result));
		}
	}
	else if(functionName == "fe3d:raycast_into_models_distance")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			// Find aabbEntity ID
			float result = -1.0f;
			auto intersection = _fe3d.raycast_checkCursorInAny();

			// Check if AABB found
			if(!intersection.first.empty())
			{
				// Check if AABB has modelEntity parent
				if(_fe3d.aabb_hasParent(intersection.first) &&
				   (_fe3d.aabb_getParentEntityType(intersection.first) == AabbParentEntityType::MODEL))
				{
					result = intersection.second;
				}
			}

			// Return
			returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:raycast_into_billboard")
	{
		auto types = {SVT::STRING, SVT::BOOLEAN};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Find aabbEntity ID
			string result = "";
			auto foundAabbID = _fe3d.raycast_checkCursorInEntities(arguments[0].getString(), arguments[1].getBoolean()).first;

			// Check if AABB found
			if(!foundAabbID.empty())
			{
				// Check if AABB has billboardEntity parent
				if(_fe3d.aabb_hasParent(foundAabbID) &&
				   (_fe3d.aabb_getParentEntityType(foundAabbID) == AabbParentEntityType::BILLBOARD))
				{
					result = _fe3d.aabb_getParentEntityID(foundAabbID);
				}
			}

			// Return
			returnValues.push_back(ScriptValue(_fe3d, SVT::STRING, result));
		}
	}
	else if(functionName == "fe3d:raycast_into_billboards")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			// Find aabbEntity ID
			string result = "";
			auto foundAabbID = _fe3d.raycast_checkCursorInAny().first;

			// Check if AABB found
			if(!foundAabbID.empty())
			{
				// Check if AABB has billboardEntity parent
				if(_fe3d.aabb_hasParent(foundAabbID) &&
				   (_fe3d.aabb_getParentEntityType(foundAabbID) == AabbParentEntityType::BILLBOARD))
				{
					result = _fe3d.aabb_getParentEntityID(foundAabbID);
				}
			}

			// Return
			returnValues.push_back(ScriptValue(_fe3d, SVT::STRING, result));
		}
	}
	else if(functionName == "fe3d:raycast_into_billboard_distance")
	{
		auto types = {SVT::STRING, SVT::BOOLEAN};

		if(_validateArgumentCount(arguments, static_cast<unsigned int>(types.size())) && _validateArgumentTypes(arguments, types))
		{
			// Find aabbEntity ID
			float result = -1.0f;
			auto intersection = _fe3d.raycast_checkCursorInEntities(arguments[0].getString(), arguments[1].getBoolean());

			// Check if AABB found
			if(!intersection.first.empty())
			{
				// Check if AABB has billboardEntity parent
				if(_fe3d.aabb_hasParent(intersection.first) &&
				   (_fe3d.aabb_getParentEntityType(intersection.first) == AabbParentEntityType::BILLBOARD))
				{
					result = intersection.second;
				}
			}

			// Return
			returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
		}
	}
	else if(functionName == "fe3d:raycast_into_billboards_distance")
	{
		if(_validateArgumentCount(arguments, 0) && _validateArgumentTypes(arguments, {}))
		{
			// Find aabbEntity ID
			float result = -1.0f;
			auto intersection = _fe3d.raycast_checkCursorInAny();

			// Check if AABB found
			if(!intersection.first.empty())
			{
				// Check if AABB has billboardEntity parent
				if(_fe3d.aabb_hasParent(intersection.first) &&
				   (_fe3d.aabb_getParentEntityType(intersection.first) == AabbParentEntityType::BILLBOARD))
				{
					result = intersection.second;
				}
			}

			// Return
			returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
		}
	}
	else
	{
		return false;
	}

	// Cannot execute raycast functionality when server is running
	if(_fe3d.server_isRunning())
	{
		_throwScriptError("cannot access `fe3d:raycast` functionality as networking server!");
	}

	return true;
}