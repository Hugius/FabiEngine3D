#include "script_interpreter.hpp"

#include <sstream>

ScriptInterpreter::ScriptInterpreter(FabiEngine3D& fe3d, Script& script) :
	_fe3d(fe3d),
	_script(script)
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
}

void ScriptInterpreter::setSceneEditorInstance(SceneEditor* sceneEditor)
{
	_sceneEditor = sceneEditor;
}

void ScriptInterpreter::_executeScript(const string& ID, ScriptType type)
{
	auto scriptFile = _script.getScriptFile(ID);

	// Interpret every line from top to bottom in script
	for (size_t i = 0; i < scriptFile->getLineCount(); i++)
	{
		string scriptLine = scriptFile->getLineText(i);

		// Check if line is not empty
		if (scriptLine.empty())
		{
			continue;
		}

		std::istringstream iss(scriptLine);

		string firstWord;
		iss >> firstWord;

		// Determine keyword type
		if (scriptLine.substr(0, 4) == "FE3D") // Engine functionality
		{
			// Check if function call has opening & closing parentheses
			auto openingParanthesisFound = std::find(scriptLine.begin(), scriptLine.end(), '(');
			auto closingParanthesisFound = std::find(scriptLine.begin(), scriptLine.end(), ')');
			if (openingParanthesisFound != scriptLine.end() && closingParanthesisFound != scriptLine.end())
			{
				unsigned int openIndex = std::distance(scriptLine.begin(), openingParanthesisFound);
				unsigned int closeIndex = std::distance(scriptLine.begin(), closingParanthesisFound);
				string argumentString = scriptLine.substr(openIndex + 1, scriptLine.size() - closeIndex);

				// Determine type of function
				if (scriptLine.substr(0, openIndex) == "FE3D_SCENE_LOAD")
				{
					_sceneEditor->loadScene(argumentString);
				}
				else if (scriptLine.substr(0, openIndex) == "FE3D_SCENE_CLEAR")
				{
					_sceneEditor->unloadScene();
				}
			}
		}
	}
}