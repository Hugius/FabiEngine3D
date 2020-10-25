#include "script_interpreter.hpp"

#include <sstream>

ScriptInterpreter::ScriptInterpreter(FabiEngine3D& fe3d, Script& script, SceneEditor& sceneEditor) :
	_fe3d(fe3d),
	_script(script),
	_sceneEditor(sceneEditor)
{

}

void ScriptInterpreter::load()
{
	// For every scriptfile
	for (auto& scriptID : _script.getAllScriptFileIDs())
	{
		auto scriptFile = _script.getScriptFile(scriptID);

		// Loop through every line
		string scriptType = "";
		for (unsigned int i = 0; i < scriptFile->getLineCount(); i++)
		{
			// Extract line content
			std::istringstream iss(scriptFile->getLineText(i));
			string type, name;
			iss >> type >> name;

			// Determine META type
			if (type == "META" && name == "script_type_init")
			{
				_initScriptIDs.push_back(scriptID);
				scriptType = "script_type_init";
			}
			else if (type == "META" && name == "script_type_update")
			{
				_updateScriptIDs.push_back(scriptID);
				scriptType = "script_type_update";
			}
			else if (type == "META" && name == "script_type_destroy")
			{
				_destroyScriptIDs.push_back(scriptID);
				scriptType = "script_type_destroy";
			}
			else if (type == "META" && name == "execution_entry")
			{
				// Check if script type is defined
				if (scriptType == "")
				{
					_fe3d.logger_throwWarning("Entry point defined before type @ script \"" + scriptID + "\"");
					break;
				}
				else
				{
					// Set entry point
					if (scriptType == "script_type_init" && _initEntryID == "")
					{
						_initEntryID = _initScriptIDs.back();
					}
					else if (scriptType == "script_type_update" && _updateEntryID == "")
					{
						_updateEntryID = _updateScriptIDs.back();
					}
					else if (scriptType == "script_type_destroy" && _destroyEntryID == "")
					{
						_destroyEntryID = _destroyScriptIDs.back();
					}
					else
					{
						_fe3d.logger_throwWarning("Entry point already defined @ script \"" + scriptID + "\"");
					}
				}
			}
		}

		// Give warning if no script type META found
		if (scriptType == "")
		{
			_fe3d.logger_throwWarning("No script_type META found @ script \"" + scriptID + "\"");
		}
	}

	// No entry point errors
	if (_initEntryID == "" && !_initScriptIDs.empty())
	{
		_fe3d.logger_throwWarning("No entry script chosen for INIT script(s)!");
	}
	if (_updateEntryID == "" && !_updateScriptIDs.empty())
	{
		_fe3d.logger_throwWarning("No entry script chosen for UPDATE script(s)!");
	}
	if (_destroyEntryID == "" && !_destroyScriptIDs.empty())
	{
		_fe3d.logger_throwWarning("No entry script chosen for DESTROY script(s)!");
	}
}

void ScriptInterpreter::executeInitialization()
{
	if (_initEntryID != "")
	{
		_executeScript(_initEntryID, ScriptType::INIT);
	}
}

void ScriptInterpreter::executeUpdate()
{
	if (_updateEntryID != "")
	{
		_executeScript(_updateEntryID, ScriptType::UPDATE);
	}
}

void ScriptInterpreter::executeDestruction()
{
	if (_destroyEntryID != "")
	{
		_executeScript(_destroyEntryID, ScriptType::DESTROY);
	}
}

void ScriptInterpreter::unload()
{
	_initScriptIDs.clear();
	_updateScriptIDs.clear();
	_destroyScriptIDs.clear();
	_initEntryID = "";
	_updateEntryID = "";
	_destroyEntryID = "";
}

void ScriptInterpreter::_executeScript(const string& scriptID, ScriptType scriptType)
{
	auto scriptFile = _script.getScriptFile(scriptID);

	// Interpret every line from top to bottom in script
	for (size_t lineIndex = 0; lineIndex < scriptFile->getLineCount(); lineIndex++)
	{
		string scriptLine = scriptFile->getLineText(lineIndex);

		// Check if line is not empty
		if (scriptLine.empty())
		{
			continue;
		}

		std::istringstream iss(scriptLine);

		// Determine keyword type
		if (scriptLine.substr(0, 4) == "FE3D") // Engine functionality
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

				// Extract arguments from argument string
				auto arguments = _extractArguments(argumentString);
				if (arguments.empty() && !argumentString.empty())
				{
					_throwSyntaxError(scriptID, lineIndex, "argument(s) syntax!");
					continue;
				}

				// Determine type of function
				if (scriptLine.substr(0, openIndex) == "FE3D_SCENE_LOAD")
				{
					if (arguments.size() == 1)
					{
						if (arguments[0].getType() == ScriptValueType::STRING)
						{
							_sceneEditor.loadScene(arguments[0].getString());
						}
						else
						{
							_throwSyntaxError(scriptID, lineIndex, "wrong argument type!");
						}
					}
					else if (arguments.empty())
					{
						_throwSyntaxError(scriptID, lineIndex, "too little arguments!");
					}
					else
					{
						_throwSyntaxError(scriptID, lineIndex, "too many arguments!");
					}
				}
				else if (scriptLine.substr(0, openIndex) == "FE3D_SCENE_CLEAR")
				{
					if (arguments.empty())
					{
						_sceneEditor.clearScene();
					}
					else
					{
						_throwSyntaxError(scriptID, lineIndex, "too many arguments!");
					}
				}
			}
			else
			{
				_throwSyntaxError(scriptID, lineIndex, "bracket(s) not found!");
				continue;
			}
		}
	}
}

void ScriptInterpreter::_throwSyntaxError(const string& scriptName, unsigned int lineIndex, const string& message)
{
	_fe3d.logger_throwWarning("SYNTAX error @ script \"" + scriptName + "\" @ line " + to_string(lineIndex + 1) + ": " + message);
}