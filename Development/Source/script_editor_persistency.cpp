#include "script_editor.hpp"

#include <fstream>
#include <sstream>

void ScriptEditor::_loadScriptFromFile()
{
	// Error checking
	if (_currentProjectName == "")
	{
		_fe3d.logger_throwError("Tried to load as empty project!");
	}

	// Clear last script
	_unloadScript();

	// Compose full script folder path
	string filePath = _fe3d.misc_getRootDirectory() + "User\\Projects\\" + _currentProjectName + "\\Data\\script.fe3d";

	// Check if script file exists
	if (_fe3d.misc_isFileExisting(filePath))
	{
		// Create new script to be filled from savefile
		_script = make_shared<Script>();

		// Load script file
		std::ifstream file(filePath);
		string line;

		// Read script data
		while (std::getline(file, line))
		{
			// Scriptline contents
			shared_ptr<ScriptEvent> event = nullptr;
			shared_ptr<ScriptAction> action = nullptr;

			// Placeholder variables
			string scriptLineID;
			int eventType, actionType;

			// For file extraction
			std::istringstream iss(line);

			// Extract scriptline ID
			iss >> scriptLineID;

			// Extract event data
			iss >> eventType;
			switch (static_cast<ScriptEventType>(eventType))
			{
				case ScriptEventType::INITIALIZATION:
				{
					event = make_shared<ScriptEventInitialization>(_fe3d, ScriptEventType::INITIALIZATION);
					break;
				}

				case ScriptEventType::INPUT:
				{
					event = make_shared<ScriptEventInput>(_fe3d, ScriptEventType::INPUT);
					int inputType, inputElement, inputMethod;
					iss >> inputType >> inputElement >> inputMethod;
					dynamic_pointer_cast<ScriptEventInput>(event)->setInputType(static_cast<InputEventType>(inputType));
					dynamic_pointer_cast<ScriptEventInput>(event)->setInputElement(static_cast<Input>(inputElement));
					dynamic_pointer_cast<ScriptEventInput>(event)->setInputMethod(static_cast<InputEventMethod>(inputMethod));
					break;
				}

				case ScriptEventType::COLLISION:
				{
					event = make_shared<ScriptEventCollision>(_fe3d, ScriptEventType::COLLISION);
					break;
				}

				case ScriptEventType::TIME:
				{
					event = make_shared<ScriptEventTime>(_fe3d, ScriptEventType::TIME);
					break;
				}

				case ScriptEventType::CONDITION:
				{
					event = make_shared<ScriptEventCondition>(_fe3d, ScriptEventType::CONDITION);
					break;
				}
			}

			// Extract action data
			iss >> actionType;
			switch (static_cast<ScriptActionType>(actionType))
			{
				case ScriptActionType::CAMERA:
				{
					action = make_shared<ScriptActionCamera>(_fe3d, ScriptActionType::CAMERA);
					break;
				}
			}

			// Create new script line
			_script->addLine(scriptLineID, event, action);
		}

		// Close file
		file.close();

		// Logging
		_fe3d.logger_throwInfo("Script data from project \"" + _currentProjectName + "\" loaded!");
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
	// Check if project is loaded properly
	if (_isLoaded)
	{
		// Check if script is not empty
		if (_script->getLineCount() != 0)
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

				// Write scriptline name
				file << scriptLine.ID << " ";

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
						file <<
							static_cast<int>(inputEvent->getInputType()) << " " <<
							static_cast<int>(inputEvent->getInputElement()) << " " <<
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

				// Add a space between event and action
				file << " ";

				// Write action type
				file << std::to_string(static_cast<int>(scriptLine.action->getType())) << " ";

				// Write action data based on type
				switch (scriptLine.action->getType())
				{
					case ScriptActionType::CAMERA:
					{
						break;
					}
				}

				// Next scriptline
				file << std::endl;
			}

			// Close file
			file.close();

			// Logging
			_fe3d.logger_throwInfo("Script data from project \"" + _currentProjectName + "\" saved!");
		}
	}
}