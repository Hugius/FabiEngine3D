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
		// Extract argument string
		unsigned int openIndex = std::distance(scriptLine.begin(), openingParanthesisFound);
		unsigned int closeIndex = std::distance(scriptLine.begin(), closingParanthesisFound);
		string argumentString = scriptLine.substr(openIndex + 1, (closeIndex - openIndex - 1));

		// Check if function call ends with a paranthesis
		if (scriptLine.size() > closeIndex + 1)
		{
			_throwScriptError("no characters allowed after closing paranthesis!");
		}
		else
		{
			// Extract arguments from argument string
			auto arguments = _extractArguments(argumentString);

			// Check if argument extraction went well
			if (!_hasThrownError)
			{
				// Determine type of function
				if (scriptLine.substr(0, openIndex) == "fe3d:print") // Printing (variable) a value
				{
					if (_validateArgumentAmount(arguments, 1)) // Validate amount of arguments
					{
						// Determine which type of value to print
						if (arguments.back().getType() == ScriptValueType::STRING)
						{
							_fe3d.logger_throwInfo(arguments[0].getString());
						}
						else if (arguments.back().getType() == ScriptValueType::DECIMAL)
						{
							_fe3d.logger_throwInfo(arguments[0].getDecimal());
						}
						else if (arguments.back().getType() == ScriptValueType::INTEGER)
						{
							_fe3d.logger_throwInfo(arguments[0].getInteger());
						}
						else if (arguments.back().getType() == ScriptValueType::BOOLEAN)
						{
							_fe3d.logger_throwInfo(arguments[0].getBoolean() ? "true" : "false");
						}
						
						// Add return value
						returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
					}
				}
				else if (scriptLine.substr(0, openIndex) == "fe3d:scene_load") // Load specific scene from file
				{
					auto types = { ScriptValueType::STRING };

					if (_validateArgumentAmount(arguments, types.size()) && _validateArgumentTypes(arguments, types))
					{
						_sceneEditor.loadScene(arguments[0].getString());
						returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
					}
				}
				else if (scriptLine.substr(0, openIndex) == "fe3d:scene_clear") // Clear all entities and reset scene
				{
					if (_validateArgumentAmount(arguments, 0) && _validateArgumentTypes(arguments, {}))
					{
						_sceneEditor.clearScene();
						returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
					}
				}
				else if (scriptLine.substr(0, openIndex) == "fe3d:camera_move") // Move camerea
				{
					auto types = { ScriptValueType::DECIMAL, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL };

					if (_validateArgumentAmount(arguments, types.size()) && _validateArgumentTypes(arguments, types))
					{
						_fe3d.camera_translate(vec3(arguments[0].getDecimal(), arguments[1].getDecimal(), arguments[2].getDecimal()));
						returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
					}
				}
				else if (scriptLine.substr(0, openIndex) == "fe3d:camera_set_pos") // Set camera position
				{
					auto types = { ScriptValueType::DECIMAL, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL };

					if (_validateArgumentAmount(arguments, types.size()) && _validateArgumentTypes(arguments, types))
					{
						_fe3d.camera_setPosition(vec3(arguments[0].getDecimal(), arguments[1].getDecimal(), arguments[2].getDecimal()));
						returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
					}
				}
				else if (scriptLine.substr(0, openIndex) == "fe3d:camera_follow_x") // Follow X direction
				{
					auto types = { ScriptValueType::DECIMAL };

					if (_validateArgumentAmount(arguments, types.size()) && _validateArgumentTypes(arguments, types))
					{
						_fe3d.camera_translateFollowX(arguments[0].getDecimal());
						returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
					}
				}
				else if (scriptLine.substr(0, openIndex) == "fe3d:camera_follow_z") // Follow Z direction
				{
					auto types = { ScriptValueType::DECIMAL };

					if (_validateArgumentAmount(arguments, types.size()) && _validateArgumentTypes(arguments, types))
					{
						_fe3d.camera_translateFollowZ(arguments[0].getDecimal());
						returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
					}
				}
				else if (scriptLine.substr(0, openIndex) == "fe3d:camera_follow_zy") // Follow ZY direction
				{
					auto types = { ScriptValueType::DECIMAL };

					if (_validateArgumentAmount(arguments, types.size()) && _validateArgumentTypes(arguments, types))
					{
						_fe3d.camera_translateFollowZY(arguments[0].getDecimal());
						returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
					}
				}
				else if (scriptLine.substr(0, openIndex) == "fe3d:input_key_down") // Hold keyboard key down
				{
					auto types = { ScriptValueType::STRING };

					if (_validateArgumentAmount(arguments, types.size()) && _validateArgumentTypes(arguments, types))
					{
						auto result = _fe3d.input_getKeyDown(_keyInputStringMap.at(arguments[0].getString()));
						returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, result));
					}
				}
				else if (scriptLine.substr(0, openIndex) == "fe3d:input_key_pressed") // Press keyboard key
				{
					auto types = { ScriptValueType::STRING };

					if (_validateArgumentAmount(arguments, types.size()) && _validateArgumentTypes(arguments, types))
					{
						auto result = _fe3d.input_getKeyPressed(_keyInputStringMap.at(arguments[0].getString()));
						returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, result));
					}
				}
				else if (scriptLine.substr(0, openIndex) == "fe3d:input_key_toggled") // Togglepress keyboard key
				{
					auto types = { ScriptValueType::STRING };

					if (_validateArgumentAmount(arguments, types.size()) && _validateArgumentTypes(arguments, types))
					{
						auto result = _fe3d.input_getKeyToggled(_keyInputStringMap.at(arguments[0].getString()));
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

	// Check if there are return values
	return returnValues;
}