#include "script_interpreter.hpp"

void ScriptInterpreter::_executeScript(const string& scriptID, ScriptType scriptType)
{
	// Save ID of script currently being executed
	_currentScriptID = scriptID;

	// Retrieve script file
	auto scriptFile = _script.getScriptFile(scriptID);

	// Local variables for this script file's execution
	vector<ScriptVariable> localVariables;

	// Interpret every line from top to bottom in script
	for (size_t lineIndex = 0; lineIndex < scriptFile->getLineCount(); lineIndex++)
	{
		// Save index of line of script currently being executed
		_currentLineIndex = lineIndex;

		// Retrieve line text
		string scriptLine = scriptFile->getLineText(_currentLineIndex);

		// Check if line is not empty or META text
		if (scriptLine.empty() || scriptLine.substr(0, 4) == "META")
		{
			continue;
		}

		// Determine keyword type
		if (scriptLine.substr(0, 4) == "fe3d") // Engine function
		{
			_executeEngineFunction(scriptLine);
		}
		else if (scriptLine.substr(0, 3) == "IF ") // If statement
		{
			// Check if if statement ends with colon
			if (scriptLine.back() != ':')
			{
				if (_checkIfStatement(scriptLine.substr(2, scriptLine.size() - 3)))
				{

				}
				else
				{

				}
			}
			else
			{
				_throwScriptError("if statement must end with colon!");
			}
		}
		else if // Local variable
			(
				scriptLine.substr(0, 4) == "STR " || 
				scriptLine.substr(0, 4) == "DEC " || 
				scriptLine.substr(0, 4) == "INT " || 
				scriptLine.substr(0, 5) == "BOOL "
			)
		{
			_addVariable(scriptLine, ScriptVariableType::LOCAL, localVariables);
		}
		else if (scriptLine.substr(0, 5) == "STAT ") // Static variable
		{
			_addVariable(scriptLine, ScriptVariableType::STATIC, _staticVariables.at(scriptID));
		}
		else if (scriptLine.substr(0, 5) == "GLOB ") // Global variable
		{
			_addVariable(scriptLine, ScriptVariableType::GLOBAL, _globalVariables.at(scriptID));
		}
		else
		{
			_throwScriptError("unknown keyword!");
		}
	}
}

ScriptValue ScriptInterpreter::_executeEngineFunction(const string& scriptLine)
{
	// Check if function call has opening & closing parentheses
	auto openingParanthesisFound = std::find(scriptLine.begin(), scriptLine.end(), '(');
	auto closingParanthesisFound = std::find(scriptLine.begin(), scriptLine.end(), ')');
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

		// Extract arguments from argument string
		auto arguments = _extractArguments(argumentString);
		if (arguments.empty() && !argumentString.empty())
		{
			_throwScriptError("invalid argument(s) syntax!");
		}

		// Determine type of function
		if (scriptLine.substr(0, openIndex) == "fe3d_scene_load") // Load specific scene from file
		{
			if (_validateArguments(arguments, { ScriptValueType::STRING }))
			{
				_sceneEditor.loadScene(arguments[0].getString());
				return ScriptValue(_fe3d, ScriptValueType::EMPTY);
			}
		}
		else if (scriptLine.substr(0, openIndex) == "fe3d_scene_clear") // Clear all entities and reset scene
		{
			if (_validateArguments(arguments, { }))
			{
				_sceneEditor.clearScene();
				return ScriptValue(_fe3d, ScriptValueType::EMPTY);
			}
		}
		else if (scriptLine.substr(0, openIndex) == "fe3d_camera_move")
		{
			if (_validateArguments(arguments, { ScriptValueType::DECIMAL, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL }))
			{
				_fe3d.camera_translate(vec3(arguments[0].getDecimal(), arguments[1].getDecimal(), arguments[2].getDecimal()));
				return ScriptValue(_fe3d, ScriptValueType::EMPTY);
			}
		}
		else if (scriptLine.substr(0, openIndex) == "fe3d_camera_set_pos")
		{
			if (_validateArguments(arguments, { ScriptValueType::DECIMAL, ScriptValueType::DECIMAL, ScriptValueType::DECIMAL }))
			{
				_fe3d.camera_setPosition(vec3(arguments[0].getDecimal(), arguments[1].getDecimal(), arguments[2].getDecimal()));
				return ScriptValue(_fe3d, ScriptValueType::EMPTY);
			}
		}
		else if (scriptLine.substr(0, openIndex) == "fe3d_input_key_down")
		{
			if (_validateArguments(arguments, { ScriptValueType::STRING }))
			{
				return ScriptValue(_fe3d, ScriptValueType::BOOLEAN, _fe3d.input_getKeyDown(_keyInputStringMap.at(arguments[0].getString())));
			}
		}
		else if (scriptLine.substr(0, openIndex) == "fe3d_input_key_pressed")
		{
			if (_validateArguments(arguments, { ScriptValueType::STRING }))
			{
				return ScriptValue(_fe3d, ScriptValueType::BOOLEAN, _fe3d.input_getKeyPressed(_keyInputStringMap.at(arguments[0].getString())));
			}
		}
		else if (scriptLine.substr(0, openIndex) == "fe3d_input_key_toggled")
		{
			if (_validateArguments(arguments, { ScriptValueType::STRING }))
			{
				return ScriptValue(_fe3d, ScriptValueType::BOOLEAN, _fe3d.input_getKeyToggled(_keyInputStringMap.at(arguments[0].getString())));
			}
		}
		else
		{
			_throwScriptError("FE3D function not found!");
		}
	}
	else
	{
		_throwScriptError("invalid parantheses syntax!");
	}

	return ScriptValue(_fe3d, ScriptValueType::NONE);
}