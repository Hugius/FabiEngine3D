#include "script_interpreter.hpp"

vector<ScriptValue> ScriptInterpreter::_processEngineFunctionCall(const string& scriptLine)
{
	// Temporary values
	vector<ScriptValue> returnValues;
	auto openingParanthesisFound = std::find(scriptLine.begin(), scriptLine.end(), '(');
	auto closingParanthesisFound = std::find(scriptLine.begin(), scriptLine.end(), ')');

	// Check if function call has opening & closing parentheses
	if (openingParanthesisFound != scriptLine.end() && closingParanthesisFound != scriptLine.end())
	{
		// Check if function call ends with a paranthesis
		if (scriptLine.back() != ')')
		{
			_throwScriptError("function call must end with a paranthesis!");
		}
		else
		{
			// Extract arguments from argument string
			unsigned int parenthesisIndex = std::distance(scriptLine.begin(), openingParanthesisFound);
			string argumentString = scriptLine.substr(parenthesisIndex + 1);
			argumentString.pop_back();
			auto arguments = _extractArguments(argumentString);

			// Check if argument extraction went well
			if (!_hasThrownError)
			{
				auto functionName = scriptLine.substr(0, parenthesisIndex);

				// Determine type of function
				if (functionName == "fe3d:print") // Printing (variable) a value
				{
					if (_validateArgumentAmount(arguments, 1)) // Validate amount of arguments
					{
						// Determine which type of value to print
						if (arguments[0].getType() == ScriptValueType::VEC3)
						{
							_fe3d.logger_throwInfo(_fe3d.misc_vec2str(arguments[0].getVec3()));
						}
						else if (arguments[0].getType() == ScriptValueType::STRING)
						{
							_fe3d.logger_throwInfo(arguments[0].getString());
						}
						else if (arguments[0].getType() == ScriptValueType::DECIMAL)
						{
							_fe3d.logger_throwInfo(arguments[0].getDecimal());
						}
						else if (arguments[0].getType() == ScriptValueType::INTEGER)
						{
							_fe3d.logger_throwInfo(arguments[0].getInteger());
						}
						else if (arguments[0].getType() == ScriptValueType::BOOLEAN)
						{
							_fe3d.logger_throwInfo(arguments[0].getBoolean() ? "true" : "false");
						}

						// Add return value
						returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
					}
				}
				else if (scriptLine.substr(0, parenthesisIndex) == "fe3d:scene_load") // Load specific scene from file
				{
					auto types = { ScriptValueType::STRING };

					if (_validateArgumentAmount(arguments, types.size()) && _validateArgumentTypes(arguments, types))
					{
						_sceneEditor.loadSceneFromFile(arguments[0].getString());
						returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
					}
				}
				else if (scriptLine.substr(0, parenthesisIndex) == "fe3d:scene_clear") // Clear all entities and reset scene
				{
					if (_validateArgumentAmount(arguments, 0) && _validateArgumentTypes(arguments, {}))
					{
						_sceneEditor.clearScene();
						returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
					}
				}
				else if (scriptLine.substr(0, parenthesisIndex) == "fe3d:camera_move") // Move camera
				{
					auto types = { ScriptValueType::DECIMAL, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL };

					if (_validateArgumentAmount(arguments, types.size()) && _validateArgumentTypes(arguments, types))
					{
						_fe3d.camera_translate(Vec3(arguments[0].getDecimal(), arguments[1].getDecimal(), arguments[2].getDecimal()));
						returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
					}
				}
				else if (scriptLine.substr(0, parenthesisIndex) == "fe3d:camera_position_get") // Get camera position
				{
					if (_validateArgumentAmount(arguments, 0) && _validateArgumentTypes(arguments, {}))
					{
						auto result = _fe3d.camera_getPosition();
						returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::VEC3, result));
					}
				}
				else if (scriptLine.substr(0, parenthesisIndex) == "fe3d:camera_position_set") // Set camera position
				{
					auto types = { ScriptValueType::DECIMAL, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL };

					if (_validateArgumentAmount(arguments, types.size()) && _validateArgumentTypes(arguments, types))
					{
						_fe3d.camera_setPosition(Vec3(arguments[0].getDecimal(), arguments[1].getDecimal(), arguments[2].getDecimal()));
						returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
					}
				}
				else if (scriptLine.substr(0, parenthesisIndex) == "fe3d:camera_follow_x") // Follow X direction
				{
					auto types = { ScriptValueType::DECIMAL };

					if (_validateArgumentAmount(arguments, types.size()) && _validateArgumentTypes(arguments, types))
					{
						_fe3d.camera_translateFollowX(arguments[0].getDecimal());
						returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
					}
				}
				else if (scriptLine.substr(0, parenthesisIndex) == "fe3d:camera_follow_z") // Follow Z direction
				{
					auto types = { ScriptValueType::DECIMAL };

					if (_validateArgumentAmount(arguments, types.size()) && _validateArgumentTypes(arguments, types))
					{
						_fe3d.camera_translateFollowZ(arguments[0].getDecimal());
						returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
					}
				}
				else if (scriptLine.substr(0, parenthesisIndex) == "fe3d:camera_follow_zy") // Follow ZY direction
				{
					auto types = { ScriptValueType::DECIMAL };

					if (_validateArgumentAmount(arguments, types.size()) && _validateArgumentTypes(arguments, types))
					{
						_fe3d.camera_translateFollowZY(arguments[0].getDecimal());
						returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
					}
				}
				else if (scriptLine.substr(0, parenthesisIndex) == "fe3d:camera_yaw_set") // Set yaw angle
				{
					auto types = { ScriptValueType::DECIMAL };

					if (_validateArgumentAmount(arguments, types.size()) && _validateArgumentTypes(arguments, types))
					{
						_fe3d.camera_setYaw(arguments[0].getDecimal());
						returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
					}
				}
				else if (scriptLine.substr(0, parenthesisIndex) == "fe3d:camera_yaw_get") // Get yaw angle
				{
					if (_validateArgumentAmount(arguments, 0) && _validateArgumentTypes(arguments, {}))
					{
						auto result = _fe3d.camera_getYaw();
						returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, result));
					}
				}
				else if (scriptLine.substr(0, parenthesisIndex) == "fe3d:camera_pitch_set") // Set pitch angle
				{
					auto types = { ScriptValueType::DECIMAL };

					if (_validateArgumentAmount(arguments, types.size()) && _validateArgumentTypes(arguments, types))
					{
						_fe3d.camera_setPitch(arguments[0].getDecimal());
						returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
					}
				}
				else if (scriptLine.substr(0, parenthesisIndex) == "fe3d:camera_pitch_get") // Get pitch angle
				{
					if (_validateArgumentAmount(arguments, 0) && _validateArgumentTypes(arguments, {}))
					{
						auto result = _fe3d.camera_getPitch();
						returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, result));
					}
				}
				else if (scriptLine.substr(0, parenthesisIndex) == "fe3d:camera_fov_set") // Set FOV angle
				{
					auto types = { ScriptValueType::DECIMAL };

					if (_validateArgumentAmount(arguments, types.size()) && _validateArgumentTypes(arguments, types))
					{
						_fe3d.camera_setFOV(arguments[0].getDecimal());
						returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
					}
				}
				else if (scriptLine.substr(0, parenthesisIndex) == "fe3d:camera_fov_get") // Get FOV angle
				{
					if (_validateArgumentAmount(arguments, 0) && _validateArgumentTypes(arguments, {}))
					{
						auto result = _fe3d.camera_getFOV();
						returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, result));
					}
				}
				else if (scriptLine.substr(0, parenthesisIndex) == "fe3d:camera_lookat_enable") // Enable lookat view
				{
					auto types = { ScriptValueType::DECIMAL, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL };

					if (_validateArgumentAmount(arguments, types.size()) && _validateArgumentTypes(arguments, types))
					{
						_fe3d.camera_enableLookat(Vec3(arguments[0].getDecimal(), arguments[1].getDecimal(), arguments[2].getDecimal()));
						returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
					}
				}
				else if (scriptLine.substr(0, parenthesisIndex) == "fe3d:camera_lookat_disable") // Disable lookat view
				{
					if (_validateArgumentAmount(arguments, 0) && _validateArgumentTypes(arguments, {}))
					{
						_fe3d.camera_disableLookat();
						returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
					}
				}
				else if (scriptLine.substr(0, parenthesisIndex) == "fe3d:camera_firstperson_enable") // Enable first person view
				{
					if (_validateArgumentAmount(arguments, 0) && _validateArgumentTypes(arguments, {}))
					{
						_fe3d.camera_enableFirstPersonView();
						returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
					}
				}
				else if (scriptLine.substr(0, parenthesisIndex) == "fe3d:camera_firstperson_disable") // Disable first person view
				{
					if (_validateArgumentAmount(arguments, 0) && _validateArgumentTypes(arguments, {}))
					{
						_fe3d.camera_disableFirstPersonView();
						returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
					}
				}
				else if (scriptLine.substr(0, parenthesisIndex) == "fe3d:input_key_down") // Hold keyboard key down
				{
					auto types = { ScriptValueType::STRING };

					if (_validateArgumentAmount(arguments, types.size()) && _validateArgumentTypes(arguments, types))
					{
						auto result = _fe3d.input_getKeyDown(_keyInputStringMap.at(arguments[0].getString()));
						returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, result));
					}
				}
				else if (scriptLine.substr(0, parenthesisIndex) == "fe3d:input_key_pressed") // Press keyboard key
				{
					auto types = { ScriptValueType::STRING };

					if (_validateArgumentAmount(arguments, types.size()) && _validateArgumentTypes(arguments, types))
					{
						auto result = _fe3d.input_getKeyPressed(_keyInputStringMap.at(arguments[0].getString()));
						returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, result));
					}
				}
				else if (scriptLine.substr(0, parenthesisIndex) == "fe3d:input_key_toggled") // Togglepress keyboard key
				{
					auto types = { ScriptValueType::STRING };

					if (_validateArgumentAmount(arguments, types.size()) && _validateArgumentTypes(arguments, types))
					{
						auto result = _fe3d.input_getKeyToggled(_keyInputStringMap.at(arguments[0].getString()));
						returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, result));
					}
				}
				else if (scriptLine.substr(0, parenthesisIndex) == "fe3d:input_mouse_down") // Hold mouse button down
				{
					auto types = { ScriptValueType::STRING };

					if (_validateArgumentAmount(arguments, types.size()) && _validateArgumentTypes(arguments, types))
					{
						auto result = _fe3d.input_getMouseDown(_mouseInputStringMap.at(arguments[0].getString()));
						returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, result));
					}
				}
				else if (scriptLine.substr(0, parenthesisIndex) == "fe3d:input_mouse_pressed") // Press mouse
				{
					auto types = { ScriptValueType::STRING };

					if (_validateArgumentAmount(arguments, types.size()) && _validateArgumentTypes(arguments, types))
					{
						auto result = _fe3d.input_getMousePressed(_mouseInputStringMap.at(arguments[0].getString()));
						returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, result));
					}
				}
				else if (scriptLine.substr(0, parenthesisIndex) == "fe3d:input_mouse_toggled") // Togglepress mouse
				{
					auto types = { ScriptValueType::STRING };

					if (_validateArgumentAmount(arguments, types.size()) && _validateArgumentTypes(arguments, types))
					{
						auto result = _fe3d.input_getMouseToggled(_mouseInputStringMap.at(arguments[0].getString()));
						returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, result));
					}
				}
				else if (scriptLine.substr(0, parenthesisIndex) == "fe3d:input_mousewheel_direction") // Mousewheel direction
				{
					if (_validateArgumentAmount(arguments, 0) && _validateArgumentTypes(arguments, {}))
					{
						auto result = _fe3d.input_getMouseWheelY();
						returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::INTEGER, result));
					}
				}
				else if (scriptLine.substr(0, parenthesisIndex) == "fe3d:raycast_in_entity") // Raycasting into a single entity
				{
					auto types = { ScriptValueType::STRING };

					if (_validateArgumentAmount(arguments, types.size()) && _validateArgumentTypes(arguments, types))
					{
						auto result = _fe3d.collision_checkCursorInEntity(arguments[0].getString());
						returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, result));
					}
				}
				else if (scriptLine.substr(0, parenthesisIndex) == "fe3d:raycast_in_entities") // Raycasting into a multiple entities
				{
					auto types = { ScriptValueType::STRING };

					if (_validateArgumentAmount(arguments, types.size()) && _validateArgumentTypes(arguments, types))
					{
						auto result = _fe3d.collision_checkCursorInEntities(arguments[0].getString());
						returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::STRING, result));
					}
				}
				else if (scriptLine.substr(0, parenthesisIndex) == "fe3d:raycast_in_any") // Raycasting into all entities
				{
					if (_validateArgumentAmount(arguments, 0) && _validateArgumentTypes(arguments, {}))
					{
						auto result = _fe3d.collision_checkCursorInAny();
						returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::STRING, result));
					}
				}
				else if (scriptLine.substr(0, parenthesisIndex) == "fe3d:misc_cursor_show") // SHow cursor
				{
					if (_validateArgumentAmount(arguments, 0) && _validateArgumentTypes(arguments, {}))
					{
						_fe3d.misc_showCursor();
						returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
					}
				}
				else if (scriptLine.substr(0, parenthesisIndex) == "fe3d:misc_cursor_hide") // Hide cursor
				{
					if (_validateArgumentAmount(arguments, 0) && _validateArgumentTypes(arguments, {}))
					{
						_fe3d.misc_hideCursor();
						returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
					}
				}
				else if (scriptLine.substr(0, parenthesisIndex) == "fe3d:misc_time_interval") // Time interval
				{
					auto types = { ScriptValueType::STRING, ScriptValueType::INTEGER };

					if (_validateArgumentAmount(arguments, types.size()) && _validateArgumentTypes(arguments, types))
					{
						auto result = _fe3d.misc_checkInterval(arguments[0].getString(), arguments[1].getInteger());
						returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, result));
					}
				}
				else
				{
					_throwScriptError("FE3D function not found!");
				}
			}
		}
	}
	else
	{
		_throwScriptError("invalid parantheses syntax!");
	}

	return returnValues;
}

vector<ScriptValue> ScriptInterpreter::_processMathematicalFunctionCall(const string& scriptLine)
{
	// Temporary values
	vector<ScriptValue> returnValues;
	auto openingParanthesisFound = std::find(scriptLine.begin(), scriptLine.end(), '(');
	auto closingParanthesisFound = std::find(scriptLine.begin(), scriptLine.end(), ')');

	// Check if function call has opening & closing parentheses
	if (openingParanthesisFound != scriptLine.end() && closingParanthesisFound != scriptLine.end())
	{
		// Check if function call ends with a paranthesis
		if (scriptLine.back() != ')')
		{
			_throwScriptError("function call must end with a paranthesis!");
		}
		else
		{
			// Extract arguments from argument string
			unsigned int parenthesisIndex = std::distance(scriptLine.begin(), openingParanthesisFound);
			string argumentString = scriptLine.substr(parenthesisIndex + 1);
			argumentString.pop_back();
			auto arguments = _extractArguments(argumentString);

			// Check if argument extraction went well
			if (!_hasThrownError)
			{
				// Determine type of function	
				if (scriptLine.substr(0, parenthesisIndex) == "math:tan")
				{
					auto types = { ScriptValueType::DECIMAL };

					if (_validateArgumentAmount(arguments, types.size()) && _validateArgumentTypes(arguments, types))
					{
						float angle = _fe3d.misc_degreesToRadians(arguments[0].getDecimal());
						returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, std::tan(angle)));
					}
				}
				else if (scriptLine.substr(0, parenthesisIndex) == "math:sin")
				{
					auto types = { ScriptValueType::DECIMAL };

					if (_validateArgumentAmount(arguments, types.size()) && _validateArgumentTypes(arguments, types))
					{
						float angle = _fe3d.misc_degreesToRadians(arguments[0].getDecimal());
						returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, std::sin(angle)));
					}
				}
				else if (scriptLine.substr(0, parenthesisIndex) == "math:cos")
				{
					auto types = { ScriptValueType::DECIMAL };

					if (_validateArgumentAmount(arguments, types.size()) && _validateArgumentTypes(arguments, types))
					{
						float angle = _fe3d.misc_degreesToRadians(arguments[0].getDecimal());
						returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, std::cos(angle)));
					}
				}
				else if (scriptLine.substr(0, parenthesisIndex) == "math:pow")
				{
					if (_validateArgumentAmount(arguments, 2))
					{
						if (arguments[0].getType() == ScriptValueType::INTEGER && arguments[1].getType() == ScriptValueType::INTEGER)
						{
							int result = static_cast<int>(std::pow(arguments[0].getInteger(), arguments[1].getInteger()));
							returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::INTEGER, result));
						}
						else if (arguments[0].getType() == ScriptValueType::DECIMAL && arguments[1].getType() == ScriptValueType::INTEGER)
						{
							float result = std::pow(arguments[0].getDecimal(), arguments[1].getInteger());
							returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, result));
						}
						else
						{
							_throwScriptError("wrong argument type(s)!");
						}
					}
				}
				else if (scriptLine.substr(0, parenthesisIndex) == "math:min")
				{
					if (_validateArgumentAmount(arguments, 2))
					{
						if (arguments[0].getType() == ScriptValueType::INTEGER && arguments[1].getType() == ScriptValueType::INTEGER)
						{
							int result = std::min(arguments[0].getInteger(), arguments[1].getInteger());
							returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::INTEGER, result));
						}
						else if (arguments[0].getType() == ScriptValueType::DECIMAL && arguments[1].getType() == ScriptValueType::DECIMAL)
						{
							float result = std::min(arguments[0].getDecimal(), arguments[1].getDecimal());
							returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, result));
						}
						else
						{
							_throwScriptError("wrong argument type(s)!");
						}
					}
				}
				else if (scriptLine.substr(0, parenthesisIndex) == "math:max")
				{
					if (_validateArgumentAmount(arguments, 2))
					{
						if (arguments[0].getType() == ScriptValueType::INTEGER && arguments[1].getType() == ScriptValueType::INTEGER)
						{
							int result = std::max(arguments[0].getInteger(), arguments[1].getInteger());
							returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::INTEGER, result));
						}
						else if (arguments[0].getType() == ScriptValueType::DECIMAL && arguments[1].getType() == ScriptValueType::DECIMAL)
						{
							float result = std::max(arguments[0].getDecimal(), arguments[1].getDecimal());
							returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, result));
						}
						else
						{
							_throwScriptError("wrong argument type(s)!");
						}
					}
				}
				else if (scriptLine.substr(0, parenthesisIndex) == "math:sqrt")
				{
					auto types = { ScriptValueType::DECIMAL };

					if (_validateArgumentAmount(arguments, types.size()) && _validateArgumentTypes(arguments, types))
					{
						returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::DECIMAL, std::sqrtf(arguments[0].getDecimal())));
					}
				}
				else
				{
					_throwScriptError("MATH function not found!");
				}
			}
		}
	}
	else
	{
		_throwScriptError("invalid parantheses syntax!");
	}

	return returnValues;
}

vector<ScriptValue> ScriptInterpreter::_processMiscellaneousFunctionCall(const string& scriptLine)
{
	// Temporary values
	vector<ScriptValue> returnValues;
	auto openingParanthesisFound = std::find(scriptLine.begin(), scriptLine.end(), '(');
	auto closingParanthesisFound = std::find(scriptLine.begin(), scriptLine.end(), ')');

	// Check if function call has opening & closing parentheses
	if (openingParanthesisFound != scriptLine.end() && closingParanthesisFound != scriptLine.end())
	{
		// Check if function call ends with a paranthesis
		if (scriptLine.back() != ')')
		{
			_throwScriptError("function call must end with a paranthesis!");
		}
		else
		{
			// Extract arguments from argument string
			unsigned int parenthesisIndex = std::distance(scriptLine.begin(), openingParanthesisFound);
			string argumentString = scriptLine.substr(parenthesisIndex + 1);
			argumentString.pop_back();
			auto arguments = _extractArguments(argumentString);

			// Check if argument extraction went well
			if (!_hasThrownError)
			{
				// Determine type of function
				if (scriptLine.substr(0, parenthesisIndex) == "misc:to_string")
				{
					if (_validateArgumentAmount(arguments, 1))
					{
						if (arguments[0].getType() == ScriptValueType::INTEGER)
						{
							returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::STRING, to_string(arguments[0].getInteger())));
						}
						else if (arguments[0].getType() == ScriptValueType::DECIMAL)
						{
							returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::STRING, to_string(arguments[0].getDecimal())));
						}
						else
						{
							_throwScriptError("wrong argument type(s)!");
						}
					}
				}
				else if (scriptLine.substr(0, parenthesisIndex) == "misc:concat_strings")
				{
					auto types = { ScriptValueType::STRING, ScriptValueType::STRING };

					if (_validateArgumentAmount(arguments, types.size()) && _validateArgumentTypes(arguments, types))
					{
						returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::STRING, arguments[0].getString() + arguments[1].getString()));
					}
				}
				else
				{
					_throwScriptError("MISC function not found!");
				}
			}
		}
	}
	else
	{
		_throwScriptError("invalid parantheses syntax!");
	}

	return returnValues;
}