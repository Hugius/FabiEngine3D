#include "script_interpreter.hpp"

vector<ScriptValue> ScriptInterpreter::_executeEngineFunction(const string& scriptLine)
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
				if (scriptLine.substr(0, openIndex) == "fe3d:print") // Print statement
				{
					if (_validateArguments(arguments, { ScriptValueType::STRING }))
					{
						_fe3d.logger_throwInfo(arguments[0].getString());
						returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
					}
				}
				else if (scriptLine.substr(0, openIndex) == "fe3d:scene_load") // Load specific scene from file
				{
					if (_validateArguments(arguments, { ScriptValueType::STRING }))
					{
						_sceneEditor.loadScene(arguments[0].getString());
						returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
					}
				}
				else if (scriptLine.substr(0, openIndex) == "fe3d:scene_clear") // Clear all entities and reset scene
				{
					if (_validateArguments(arguments, { }))
					{
						_sceneEditor.clearScene();
						returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
					}
				}
				else if (scriptLine.substr(0, openIndex) == "fe3d:camera_move")
				{
					if (_validateArguments(arguments, { ScriptValueType::DECIMAL, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL }))
					{
						_fe3d.camera_translate(vec3(arguments[0].getDecimal(), arguments[1].getDecimal(), arguments[2].getDecimal()));
						returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
					}
				}
				else if (scriptLine.substr(0, openIndex) == "fe3d:camera_set_pos")
				{
					if (_validateArguments(arguments, { ScriptValueType::DECIMAL, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL }))
					{
						_fe3d.camera_setPosition(vec3(arguments[0].getDecimal(), arguments[1].getDecimal(), arguments[2].getDecimal()));
						returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::EMPTY));
					}
				}
				else if (scriptLine.substr(0, openIndex) == "fe3d:input_key_down")
				{
					if (_validateArguments(arguments, { ScriptValueType::STRING }))
					{
						returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, _fe3d.input_getKeyDown(_keyInputStringMap.at(arguments[0].getString()))));
					}
				}
				else if (scriptLine.substr(0, openIndex) == "fe3d:input_key_pressed")
				{
					if (_validateArguments(arguments, { ScriptValueType::STRING }))
					{
						returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, _fe3d.input_getKeyPressed(_keyInputStringMap.at(arguments[0].getString()))));
					}
				}
				else if (scriptLine.substr(0, openIndex) == "fe3d:input_key_toggled")
				{
					if (_validateArguments(arguments, { ScriptValueType::STRING }))
					{
						returnValues.push_back(ScriptValue(_fe3d, ScriptValueType::BOOLEAN, _fe3d.input_getKeyToggled(_keyInputStringMap.at(arguments[0].getString()))));
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