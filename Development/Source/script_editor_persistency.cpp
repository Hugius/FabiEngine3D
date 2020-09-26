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
	string filePath = _fe3d.misc_getRootDirectory() + "User\\projects\\" + _currentProjectName + "\\data\\script.fe3d";

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
			// ScriptLine contents
			shared_ptr<ScriptEvent> event = nullptr;
			shared_ptr<ScriptAction> action = nullptr;

			// Placeholder variables
			string scriptLineID;
			int eventType, actionType;

			// For file extraction
			std::istringstream iss(line);

			// Extract scriptLine ID
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
					// New event
					event = make_shared<ScriptEventInput>(_fe3d, ScriptEventType::INPUT);

					// Placeholders
					int inputType, mouseType, inputElement, inputMethod;

					// Load from file
					iss >> inputType >> mouseType >> inputElement >> inputMethod;

					// Fill the script event
					dynamic_pointer_cast<ScriptEventInput>(event)->setInputType(static_cast<InputEventType>(inputType));
					dynamic_pointer_cast<ScriptEventInput>(event)->setMouseType(static_cast<InputEventMouseType>(mouseType));
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
					// New action
					action = make_shared<ScriptActionCamera>(_fe3d, ScriptActionType::CAMERA);

					// Placeholders
					int cameraType, cameraDirection, cameraFollow, cameraMethod, cameraToggle;
					bool hasVectorArgument, hasfloatArgument;
					vec3 vectorArgument;
					float floatArgument;

					// Load from file
					iss >> cameraType >> cameraDirection >> cameraFollow >> cameraMethod >> cameraToggle >> hasVectorArgument >>
						vectorArgument.x >> vectorArgument.y >> vectorArgument.z >> hasfloatArgument >> floatArgument;

					// Fill the script action
					dynamic_pointer_cast<ScriptActionCamera>(action)->setCameraType(static_cast<CameraActionType>(cameraType));
					dynamic_pointer_cast<ScriptActionCamera>(action)->setCameraDirection(static_cast<CameraActionDirection>(cameraDirection));
					dynamic_pointer_cast<ScriptActionCamera>(action)->setCameraFollow(static_cast<CameraActionFollow>(cameraFollow));
					dynamic_pointer_cast<ScriptActionCamera>(action)->setCameraMethod(static_cast<CameraActionMethod>(cameraMethod));
					dynamic_pointer_cast<ScriptActionCamera>(action)->setCameraToggle(static_cast<CameraActionToggle>(cameraToggle));
					if(hasVectorArgument)dynamic_pointer_cast<ScriptActionCamera>(action)->setVectorArgument(vectorArgument);
					if(hasfloatArgument) dynamic_pointer_cast<ScriptActionCamera>(action)->setFloatArgument(floatArgument);
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
		// Error checking
		if (_currentProjectName == "")
		{
			_fe3d.logger_throwError("Tried to save as empty project!");
		}

		// Create or overwrite models file
		std::ofstream file;
		file.open(_fe3d.misc_getRootDirectory() + "User\\projects\\" + _currentProjectName + "\\data\\script.fe3d");

		// Write model data into file
		for (auto& ID : _script->getAllScriptLineIDs())
		{
			auto scriptLine = _script->getScriptLine(ID);

			// Write scriptLine name
			file << scriptLine.ID << " ";

			// Write event type
			file << to_string(static_cast<int>(scriptLine.event->getType())) << " ";

			// Write event data based on type
			bool noSpace = false;
			switch (scriptLine.event->getType())
			{
				case ScriptEventType::INITIALIZATION:
				{
					// Empty, because init event has no condition
					noSpace = true;
					break;
				}

				case ScriptEventType::INPUT:
				{
					auto inputEvent = dynamic_pointer_cast<ScriptEventInput>(scriptLine.event);
					file <<
						static_cast<int>(inputEvent->getInputType()) << " " <<
						static_cast<int>(inputEvent->getMouseType()) << " " <<
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
			if (!noSpace)
			{
				file << " ";
			}

			// Write action type
			file << to_string(static_cast<int>(scriptLine.action->getType())) << " ";

			// Write action data based on type
			switch (scriptLine.action->getType())
			{
				case ScriptActionType::CAMERA:
				{
					auto cameraAction = dynamic_pointer_cast<ScriptActionCamera>(scriptLine.action);
					file <<
						static_cast<int>(cameraAction->getCameraType()) << " " <<
						static_cast<int>(cameraAction->getCameraDirection()) << " " <<
						static_cast<int>(cameraAction->getCameraFollow()) << " " <<
						static_cast<int>(cameraAction->getCameraMethod()) << " " <<
						static_cast<int>(cameraAction->getCameraToggle()) << " " <<
						cameraAction->hasVectorArgument() << " " <<
						cameraAction->getVectorArgument().x << " " <<
						cameraAction->getVectorArgument().y << " " <<
						cameraAction->getVectorArgument().z << " " <<
						cameraAction->hasFloatArgument() << " " <<
						cameraAction->getFloatArgument();
					break;
				}
			}

			// Next scriptLine
			file << std::endl;
		}

		// Close file
		file.close();

		// Logging
		_fe3d.logger_throwInfo("Script data from project \"" + _currentProjectName + "\" saved!");
	}
}