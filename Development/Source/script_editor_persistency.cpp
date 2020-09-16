#include "script_editor.hpp"

#include <fstream>

void ScriptEditor::_loadScriptFromFile()
{
	// Clear last script
	_unloadScript();

	if (false) // if script save file exists <---
	{
		// Create new script to be filled from savefile
		_script = make_shared<Script>();

		// fill script <---
	}
	else
	{
		// Create new empty script
		_script = make_shared<Script>();
	}

	// Inject into script executor
	_scriptExecutor = make_shared<ScriptExecutor>(_script);
}

void ScriptEditor::_saveScriptToFile()
{
	if (_isLoaded && _script != nullptr)
	{
		// Error checking
		if (_currentProjectName == "")
		{
			_fe3d.logger_throwError("Tried to save as empty project!");
		}

		// Create or overwrite models file
		std::ofstream file;
		file.open(_fe3d.misc_getRootDirectory() + "User\\Projects\\" + _currentProjectName + "\\Data\\script.fe3d");

		// Write model data into file
		for (auto& ID : _script->getAllScriptLineIDs())
		{
			auto scriptLine = _script->getScriptLine(ID);

			// Check if scriptline has an event
			if (scriptLine.event != nullptr)
			{
				// Write event type
				file << std::to_string(static_cast<int>(scriptLine.event->getType())) << " ";

				// Write event data based on type
				switch (scriptLine.event->getType())
				{
					case ScriptEventType::INITIALIZATION:
					{
						break;
					}

					case ScriptEventType::INPUT:
					{
						auto inputEvent = dynamic_pointer_cast<ScriptEventInput>(scriptLine.event);
						file << static_cast<int>(inputEvent->getInputType()) << " " << static_cast<int>(inputEvent->getInputElement()) << " " <<
							static_cast<int>(inputEvent->getInputMethod());
						break;
					}

					case ScriptEventType::COLLISION:
					{
						break;
					}

					case ScriptEventType::TIME:
					{
						break;
					}

					case ScriptEventType::CONDITION:
					{
						break;
					}
				}
			}
			else
			{
				file << "null" << " ";
			}

			// Check if scriptline has an action
			if (scriptLine.action != nullptr)
			{
				// Write event type
				file << std::to_string(static_cast<int>(scriptLine.action->getType())) << " ";

				// Write event data based on type
				switch (scriptLine.action->getType())
				{
					case ScriptActionType::CAMERA:
					{
						break;
					}
				}
			}
			else
			{
				file << "null" << " ";
			}

			file << std::endl;
		}

		// Close file
		file.close();

		// Logging
		_fe3d.logger_throwInfo("Script data from project \"" + _currentProjectName + "\" saved!");
	}
}