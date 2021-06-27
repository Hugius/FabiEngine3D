#include "script_editor.hpp"

#include <algorithm>

void ScriptEditor::update()
{
	_updateGUI();
	_updateTextWriter();
	_updateMiscellaneous();
}

void ScriptEditor::_updateGUI()
{
	if (_isEditorLoaded)
	{
		auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

		// GUI management
		if (screen->getID() == "scriptEditorMenuMain")
		{
			if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_isKeyPressed(InputType::KEY_ESCAPE))
			{
				if (screen->getButton("back")->isHovered() || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
				{
					_gui.getGlobalScreen()->addAnswerForm("exitScriptEditor", "Save changes?", Vec2(0.0f, 0.25f));
				}
				else if (screen->getButton("search")->isHovered())
				{
					_gui.getGlobalScreen()->addValueForm("search", "Search keyword", "", Vec2(0.0f), Vec2(0.5f, 0.1f));
				}
				else if (screen->getButton("createScript")->isHovered())
				{
					_gui.getGlobalScreen()->addValueForm("scriptCreate", "New script name", "", Vec2(0.0f), Vec2(0.5f, 0.1f));
				}
				else if (screen->getButton("editScript")->isHovered())
				{
					auto IDs = _script.getAllScriptFileIDs();
					std::sort(IDs.begin(), IDs.end());
					_gui.getGlobalScreen()->addChoiceForm("scriptFileList", "Choose script", Vec2(0.0f), IDs);
				}
				else if (screen->getButton("renameScript")->isHovered())
				{
					_gui.getGlobalScreen()->addValueForm("scriptRename", "New script name", "", Vec2(0.0f), Vec2(0.5f, 0.1f));
				}
				else if (screen->getButton("deleteScript")->isHovered())
				{
					_scriptFileNamesToDelete.push_back(_currentScriptFileID);
					_fe3d.billboardEntity_deleteAll();
					_script.removeScriptFile(_currentScriptFileID);
					_isWritingScript = false;
					_currentScriptFileID = "";
				}
			}
			
			// Control key combinations
			if (_fe3d.input_isKeyDown(InputType::KEY_LCTRL) || _fe3d.input_isKeyDown(InputType::KEY_RCTRL))
			{
				// Search hotkey
				if (_fe3d.input_isKeyPressed(InputType::KEY_F) && !_gui.getGlobalScreen()->isFocused())
				{
					_gui.getGlobalScreen()->addValueForm("search", "Search keyword", "", Vec2(0.0f), Vec2(0.5f, 0.1f));
				}
			}

			// Update total line count text
			auto lineCountID = screen->getTextfield("lineCount")->getEntityID();
			_fe3d.textEntity_setTextContent(lineCountID, "Line count: " + to_string(_script.getTotalLineCount()));

			// Buttons hoverability
			screen->getButton("renameScript")->setHoverable(_currentScriptFileID != "");
			screen->getButton("deleteScript")->setHoverable(_currentScriptFileID != "");

			// Check if user wants to save changes
			if (_gui.getGlobalScreen()->isAnswerFormConfirmed("exitScriptEditor"))
			{
				saveScriptsToFile();
				unload();
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("main");
			}
			else if (_gui.getGlobalScreen()->isAnswerFormDenied("exitScriptEditor"))
			{
				unload();
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("main");
			}
		}
	}
}

void ScriptEditor::_updateMiscellaneous()
{
	if (_isEditorLoaded)
	{
		if (_isWritingScript)
		{
			// Temporary values
			const unsigned int currentLineIndex = _script.getScriptFile(_currentScriptFileID)->getCursorLineIndex();
			const unsigned int lineCount = _script.getScriptFile(_currentScriptFileID)->getLineCount();
			const float lastLineHeight = _fe3d.billboardEntity_getPosition(to_string(lineCount - 1)).y;
			
			//  Check if camera allowed to move
			if (!_gui.getGlobalScreen()->isFocused() && _fe3d.misc_isCursorInsideViewport())
			{
				// Camera movement input
				if (_fe3d.input_getMouseWheelY() == -1 && lineCount > (MAX_VISIBLE_LINES - 1))
				{
					_scrollingAcceleration -= SCROLLING_SPEED;
				}
				else if (_fe3d.input_getMouseWheelY() == 1)
				{
					_scrollingAcceleration += SCROLLING_SPEED;
				}
			}

			// Camera must not go out of screen (upwards)
			if (_fe3d.camera_getPosition().y > CAMERA_POSITION.y)
			{
				_scrollingAcceleration = 0.0f;
				_fe3d.camera_setPosition(CAMERA_POSITION);
			}
			else if (_fe3d.camera_getPosition().y == CAMERA_POSITION.y && _scrollingAcceleration > 0.0f) // Trying to scroll up
			{
				_scrollingAcceleration = 0.0f;
			}

			// Check if code is out of screen
			if (lineCount > (MAX_VISIBLE_LINES - 1))
			{
				if (_fe3d.camera_getPosition().y < (lastLineHeight + CAMERA_OFFSET)) // Camera must not go out of screen
				{
					_scrollingAcceleration = 0.0f;
					_fe3d.camera_setPosition(Vec3(CAMERA_POSITION.x, lastLineHeight + CAMERA_OFFSET, CAMERA_POSITION.z));
				}
				else if (_fe3d.camera_getPosition().y == (lastLineHeight + CAMERA_OFFSET) && _scrollingAcceleration < 0.0f) // Trying to scroll down
				{
					_scrollingAcceleration = 0.0f;
				}
			}
			else // Reset camera position if too little amount of lines
			{
				_scrollingAcceleration = 0.0f;
				_fe3d.camera_setPosition(CAMERA_POSITION);
			}

			// Synchronize camera position whenever writers adds or removes a line
			static unsigned int lastLineIndex = currentLineIndex;
			if ((currentLineIndex > (MAX_VISIBLE_LINES - 1)) && (currentLineIndex != lastLineIndex) && (currentLineIndex == lineCount - 1))
			{
				_scrollingAcceleration = 0.0f;
				float currentLineHeight = _fe3d.billboardEntity_getPosition(to_string(currentLineIndex)).y;
				_fe3d.camera_setPosition(Vec3(CAMERA_POSITION.x, currentLineHeight + CAMERA_OFFSET, CAMERA_POSITION.z));
			}
			lastLineIndex = currentLineIndex;
		}

		// Smooth camera movement
		_scrollingAcceleration = std::clamp(_scrollingAcceleration, -MAX_SCROLLING_ACCELERATION, MAX_SCROLLING_ACCELERATION);
		_scrollingAcceleration *= 0.95f;
		_fe3d.camera_translate(Vec3(0.0f, _scrollingAcceleration, 0.0f));

		// Check if user wants to search a keyword
		string keyword;
		if (_gui.getGlobalScreen()->checkValueForm("search", keyword))
		{
			auto result = _script.findKeyword(keyword);

			// Check if keyword found nowhere
			if (result.empty())
			{
				_fe3d.logger_throwInfo("Keyword \"" + keyword + "\" not found in scripts!");
				_fe3d.logger_throwInfo("");
			}
			else
			{
				// Print all lines in which the keyword occurred 
				for (const auto& [fileID, lineNumber] : result)
				{
					_fe3d.logger_throwInfo("Keyword \"" + keyword + "\" found in script \"" + fileID + "\" @ line " + to_string(lineNumber));
				}
				_fe3d.logger_throwInfo("");
			}
		}

		// Check if user wants to create a new script
		string newScriptName;
		if (_gui.getGlobalScreen()->checkValueForm("scriptCreate", newScriptName))
		{
			// Spaces not allowed
			if (newScriptName.find(' ') == string::npos)
			{
				// Check if name already exists
				auto existingNames = _script.getAllScriptFileIDs();
				if (find(existingNames.begin(), existingNames.end(), newScriptName) == existingNames.end())
				{
					_currentScriptFileID = newScriptName;
					_isWritingScript = true;
					_firstSelectedLineIndex = -1;
					_lastSelectedLineIndex = -1;
					_script.addScriptFile(_currentScriptFileID);
					_script.getScriptFile(_currentScriptFileID)->insertNewLine(0, "");
					_reloadScriptTextDisplay(true);
				}
				else
				{
					_fe3d.logger_throwWarning("Script name \"" + newScriptName + "\" already exists!");
				}
			}
			else
			{
				_fe3d.logger_throwWarning("Script name cannot contain any spaces!");
			}
		}

		// Check if existing script file chosen for viewing
		string selectedButtonID = _gui.getGlobalScreen()->getSelectedChoiceFormButtonID("scriptFileList");
		if (selectedButtonID != "")
		{
			if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				_gui.getGlobalScreen()->removeChoiceForm("scriptFileList");
				_currentScriptFileID = selectedButtonID;
				_isWritingScript = true;
				_firstSelectedLineIndex = -1;
				_lastSelectedLineIndex = -1;
				_reloadScriptTextDisplay(true);
			}
		}
		else if (_gui.getGlobalScreen()->isChoiceFormCancelled("scriptFileList"))
		{
			_gui.getGlobalScreen()->removeChoiceForm("scriptFileList");
		}

		// Check if user wants to rename a script
		if (_gui.getGlobalScreen()->checkValueForm("scriptRename", newScriptName))
		{
			auto existingNames = _script.getAllScriptFileIDs();
			if (find(existingNames.begin(), existingNames.end(), newScriptName) == existingNames.end())
			{
				_scriptFileNamesToDelete.push_back(_currentScriptFileID);
				_script.renameScriptFile(_currentScriptFileID, newScriptName);
				_currentScriptFileID = newScriptName;
			}
			else
			{
				_fe3d.logger_throwWarning("Script name already exists!");
			}
		}
	}
}