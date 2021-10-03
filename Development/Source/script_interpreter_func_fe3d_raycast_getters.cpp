#include "script_interpreter.hpp"

using SVT = ScriptValueType;

bool ScriptInterpreter::_executeFe3dRaycastGetterFunction(const string& functionName, vector<ScriptValue>& arguments, vector<ScriptValue>& returnValues)
{
	// Determine type of function
	if (functionName == "fe3d:raycast_get_vector")
	{
		// Validate arguments
		if (_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			// Validate terrain existence
			if (_validateFe3dTerrain())
			{
				auto result = _fe3d.raycast_getVector();
				returnValues.push_back(ScriptValue(_fe3d, SVT::VEC3, result));
			}
		}
	}
	else if (functionName == "fe3d:raycast_get_point_on_terrain")
	{
		// Validate arguments
		if (_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			// Validate terrain existence
			if (_validateFe3dTerrain())
			{
				auto result = _fe3d.raycast_getPointOnTerrain();
				returnValues.push_back(ScriptValue(_fe3d, SVT::VEC3, result));
			}
		}
	}
	else if (functionName == "fe3d:raycast_is_point_on_terrain_valid")
	{
		// Validate arguments
		if (_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			// Validate terrain existence
			if (_validateFe3dTerrain())
			{
				auto result = _fe3d.raycast_isPointOnTerrainValid();
				returnValues.push_back(ScriptValue(_fe3d, SVT::BOOLEAN, result));
			}
		}
	}
	else if (functionName == "fe3d:raycast_into_model")
	{
		auto types = { SVT::STRING, SVT::STRING, SVT::BOOLEAN }; // ModelEntityID + aabbPartID + canBeOccluded

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Find aabbEntity ID
			string result = "";
			auto foundAabbID = _fe3d.raycast_checkCursorInEntities(arguments[0].getString(), arguments[2].getBoolean()).first;

			// Check if AABB found
			if (!foundAabbID.empty())
			{
				// Check if AABB has modelEntity parent
				if (_fe3d.aabbEntity_hasParent(foundAabbID) && 
					(_fe3d.aabbEntity_getParentType(foundAabbID) == AabbParentType::MODEL_ENTITY))
				{
					if (arguments[1].getString().empty()) // No specific AABB part
					{
						result = _fe3d.aabbEntity_getParentID(foundAabbID);
					}
					else // Specific AABB part
					{
						// Extract AABB part ID
						string partID = foundAabbID;
						reverse(partID.begin(), partID.end());
						partID = partID.substr(0, partID.find('@'));
						reverse(partID.begin(), partID.end());

						// Check if AABB part ID's match
						if (partID == arguments[1].getString())
						{
							result = _fe3d.aabbEntity_getParentID(foundAabbID);
						}
					}
				}
			}

			// Return
			returnValues.push_back(ScriptValue(_fe3d, SVT::STRING, result));
		}
	}
	else if (functionName == "fe3d:raycast_into_model_distance")
	{
		auto types = { SVT::STRING, SVT::STRING, SVT::BOOLEAN }; // ModelEntityID + aabbPartID + canBeOccluded

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Find aabbEntity ID
			float result = -1.0f;
			auto intersection = _fe3d.raycast_checkCursorInEntities(arguments[0].getString(), arguments[2].getBoolean());
			string foundAabbID = intersection.first;
			float foundDistance = intersection.second;

			// Check if AABB found
			if (!foundAabbID.empty())
			{
				// Check if AABB has modelEntity parent
				if (_fe3d.aabbEntity_hasParent(foundAabbID) && 
					(_fe3d.aabbEntity_getParentType(foundAabbID) == AabbParentType::MODEL_ENTITY))
				{
					if (arguments[1].getString().empty()) // No specific AABB part
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

						// Check if AABB part ID's match
						if (partID == arguments[1].getString())
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
	else if (functionName == "fe3d:raycast_into_models")
	{
		// Validate arguments
		if (_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			// Find aabbEntity ID
			string result = "";
			auto foundAabbID = _fe3d.raycast_checkCursorInAny().first;

			// Check if AABB found
			if (!foundAabbID.empty())
			{
				// Check if AABB has modelEntity parent
				if (_fe3d.aabbEntity_hasParent(foundAabbID) && 
					(_fe3d.aabbEntity_getParentType(foundAabbID) == AabbParentType::MODEL_ENTITY))
				{
					result = _fe3d.aabbEntity_getParentID(foundAabbID);
				}
			}

			// Return
			returnValues.push_back(ScriptValue(_fe3d, SVT::STRING, result));
		}
	}
	else if (functionName == "fe3d:raycast_into_models_distance")
	{
		// Validate arguments
		if (_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			// Find aabbEntity ID
			float result = -1.0f;
			auto intersection = _fe3d.raycast_checkCursorInAny();

			// Check if AABB found
			if (!intersection.first.empty())
			{
				// Check if AABB has modelEntity parent
				if (_fe3d.aabbEntity_hasParent(intersection.first) && 
					(_fe3d.aabbEntity_getParentType(intersection.first) == AabbParentType::MODEL_ENTITY))
				{
					result = intersection.second;
				}
			}

			// Return
			returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
		}
	}
	else if (functionName == "fe3d:raycast_into_billboard")
	{
		auto types = { SVT::STRING, SVT::BOOLEAN }; // BillboardEntityID + canBeOccluded

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Find aabbEntity ID
			string result = "";
			auto foundAabbID = _fe3d.raycast_checkCursorInEntities(arguments[0].getString(), arguments[1].getBoolean()).first;

			// Check if AABB found
			if (!foundAabbID.empty())
			{
				// Check if AABB has billboardEntity parent
				if (_fe3d.aabbEntity_hasParent(foundAabbID) &&
					(_fe3d.aabbEntity_getParentType(foundAabbID) == AabbParentType::BILLBOARD_ENTITY))
				{
					result = _fe3d.aabbEntity_getParentID(foundAabbID);
				}
			}

			// Return
			returnValues.push_back(ScriptValue(_fe3d, SVT::STRING, result));
		}
	}
	else if (functionName == "fe3d:raycast_into_billboards")
	{
		// Validate arguments
		if (_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			// Find aabbEntity ID
			string result = "";
			auto foundAabbID = _fe3d.raycast_checkCursorInAny().first;

			// Check if AABB found
			if (!foundAabbID.empty())
			{
				// Check if AABB has billboardEntity parent
				if (_fe3d.aabbEntity_hasParent(foundAabbID) &&
					(_fe3d.aabbEntity_getParentType(foundAabbID) == AabbParentType::BILLBOARD_ENTITY))
				{
					result = _fe3d.aabbEntity_getParentID(foundAabbID);
				}
			}

			// Return
			returnValues.push_back(ScriptValue(_fe3d, SVT::STRING, result));
		}
	}
	else if (functionName == "fe3d:raycast_into_billboard_distance")
	{
		auto types = { SVT::STRING, SVT::BOOLEAN }; // BillboardEntityID + canBeOccluded

		// Validate arguments
		if (_validateListValueCount(arguments, static_cast<unsigned int>(types.size())) && _validateListValueTypes(arguments, types))
		{
			// Find aabbEntity ID
			float result = -1.0f;
			auto intersection = _fe3d.raycast_checkCursorInEntities(arguments[0].getString(), arguments[1].getBoolean());

			// Check if AABB found
			if (!intersection.first.empty())
			{
				// Check if AABB has billboardEntity parent
				if (_fe3d.aabbEntity_hasParent(intersection.first) &&
					(_fe3d.aabbEntity_getParentType(intersection.first) == AabbParentType::BILLBOARD_ENTITY))
				{
					result = intersection.second;
				}
			}

			// Return
			returnValues.push_back(ScriptValue(_fe3d, SVT::DECIMAL, result));
		}
	}
	else if (functionName == "fe3d:raycast_into_billboards_distance")
	{
		// Validate arguments
		if (_validateListValueCount(arguments, 0) && _validateListValueTypes(arguments, {}))
		{
			// Find aabbEntity ID
			float result = -1.0f;
			auto intersection = _fe3d.raycast_checkCursorInAny();

			// Check if AABB found
			if (!intersection.first.empty())
			{
				// Check if AABB has billboardEntity parent
				if (_fe3d.aabbEntity_hasParent(intersection.first) &&
					(_fe3d.aabbEntity_getParentType(intersection.first) == AabbParentType::BILLBOARD_ENTITY))
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
	if (_fe3d.networkServer_isRunning())
	{
		_throwScriptError("cannot access `fe3d:raycast` functionality as a networking server!");
	}

	return true;
}