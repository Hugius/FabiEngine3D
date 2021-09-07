#include "script_editor.hpp"
#include "logger.hpp"

#include <algorithm>

using std::clamp;

void ScriptEditor::update()
{
	if (_isEditorLoaded)
	{
		_updateGUI();
	}
	if (_isEditorLoaded)
	{
		_updateTextWriter();
	}
	if (_isEditorLoaded)
	{
		_updateMiscellaneous();
	}
}

void ScriptEditor::_updateGUI()
{
	// Temporary values
	auto screen = _gui.getViewport("left")->getWindow("main")->getActiveScreen();

	// Screen management
	if (screen->getID() == "scriptEditorMenuMain")
	{
		// Button management
		if ((_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d.input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
		{
			_gui.getGlobalScreen()->createAnswerForm("back", "Save Changes?", Vec2(0.0f, 0.25f));
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("search")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("search", "Search Script", "", Vec2(0.0f, 0.1f), Vec2(0.5f, 0.1f), Vec2(0.0f, 0.1f));
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("create")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("scriptCreate", "Create Script", "", Vec2(0.0f, 0.1f), Vec2(0.5f, 0.1f), Vec2(0.0f, 0.1f));
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("edit")->isHovered())
		{
			auto IDs = _script.getAllScriptFileIDs();
			sort(IDs.begin(), IDs.end());
			_gui.getGlobalScreen()->createChoiceForm("scriptFileList", "Edit Script", Vec2(0.0f, 0.1f), IDs);
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("rename")->isHovered())
		{
			_gui.getGlobalScreen()->createValueForm("scriptRename", "Rename Script", "", Vec2(0.0f, 0.1f), Vec2(0.5f, 0.1f), Vec2(0.0f, 0.1f));
		}
		else if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("delete")->isHovered())
		{
			_scriptFilenamesToDelete.push_back(_currentScriptFileID);
			_fe3d.billboardEntity_deleteAll();
			_script.removeScriptFile(_currentScriptFileID);
			_isWritingScript = false;
			_currentScriptFileID = "";
		}

		// Control key combinations
		if (_fe3d.input_isKeyDown(InputType::KEY_LCTRL) || _fe3d.input_isKeyDown(InputType::KEY_RCTRL))
		{
			// Search hotkey
			if (_fe3d.input_isKeyPressed(InputType::KEY_F) && !_gui.getGlobalScreen()->isFocused())
			{
				_gui.getGlobalScreen()->createValueForm("search", "Search Keyword", "", Vec2(0.0f, 0.1f), Vec2(0.5f, 0.1f), Vec2(0.0f, 0.1f));
			}
		}

		// Update answer forms
		if (_gui.getGlobalScreen()->isAnswerFormConfirmed("back"))
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("main");
			saveScriptFiles();
			unload();
			return;
		}
		if (_gui.getGlobalScreen()->isAnswerFormDenied("back"))
		{
			_gui.getViewport("left")->getWindow("main")->setActiveScreen("main");
			unload();
			return;
		}

		// Update buttons hoverability
		screen->getButton("rename")->setHoverable(_currentScriptFileID != "");
		screen->getButton("delete")->setHoverable(_currentScriptFileID != "");

		// Update button text contents
		screen->getTextField("lineCount")->changeTextContent("Lines: " + to_string(_script.getTotalLineCount()));
	}
}

void ScriptEditor::_updateMiscellaneous()
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
		else if (_fe3d.camera_getPosition().y == CAMERA_POSITION.y && _scrollingAcceleration > 0.0f) // Tried to scroll up
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
			else if (_fe3d.camera_getPosition().y == (lastLineHeight + CAMERA_OFFSET) && _scrollingAcceleration < 0.0f) // Tried to scroll down
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
	_scrollingAcceleration = clamp(_scrollingAcceleration, -MAX_SCROLLING_ACCELERATION, MAX_SCROLLING_ACCELERATION);
	_scrollingAcceleration *= 0.95f;
	_fe3d.camera_move(Vec3(0.0f, _scrollingAcceleration, 0.0f));

	// Check if user filled in a keyword
	string keyword;
	if (_gui.getGlobalScreen()->checkValueForm("search", keyword))
	{
		auto result = _script.findKeyword(keyword);

		// Check if keyword found nowhere
		if (result.empty())
		{
			Logger::throwInfo("Keyword \"" + keyword + "\" not found in scripts!");
			Logger::throwInfo("");
		}
		else
		{
			// Print all lines in which the keyword occurred 
			for (const auto& [fileID, lineNumber] : result)
			{
				Logger::throwInfo("Keyword \"" + keyword + "\" found in script \"" + fileID + "\" @ line " + to_string(lineNumber));
			}
			Logger::throwInfo("");
		}
	}

	// Check if user filled in a new ID
	string newScriptFileID;
	if (_gui.getGlobalScreen()->checkValueForm("scriptCreate", newScriptFileID))
	{
		// Spaces not allowed
		if (newScriptFileID.find(' ') == string::npos)
		{
			// Check if script already exists
			auto existingScriptFileIDs = _script.getAllScriptFileIDs();
			if (find(existingScriptFileIDs.begin(), existingScriptFileIDs.end(), newScriptFileID) == existingScriptFileIDs.end())
			{
				_currentScriptFileID = newScriptFileID;
				_isWritingScript = true;
				_firstSelectedLineIndex = -1;
				_lastSelectedLineIndex = -1;
				_script.createScriptFile(_currentScriptFileID);
				_script.getScriptFile(_currentScriptFileID)->insertNewLine(0, "");
				_reloadScriptTextDisplay(true);
			}
			else
			{
				Logger::throwWarning("Script with ID \"" + newScriptFileID + "\" already exists!");
			}
		}
		else
		{
			Logger::throwWarning("Script ID cannot contain any spaces!");
		}
	}

	// Check if existing script file chosen for viewing
	string selectedButtonID = _gui.getGlobalScreen()->checkChoiceForm("scriptFileList");
	if (!selectedButtonID.empty())
	{
		if (_fe3d.input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
		{
			_gui.getGlobalScreen()->deleteChoiceForm("scriptFileList");
			_currentScriptFileID = selectedButtonID;
			_isWritingScript = true;
			_firstSelectedLineIndex = -1;
			_lastSelectedLineIndex = -1;
			_reloadScriptTextDisplay(true);
		}
	}
	else if (_gui.getGlobalScreen()->isChoiceFormCancelled("scriptFileList"))
	{
		_gui.getGlobalScreen()->deleteChoiceForm("scriptFileList");
	}

	// Check if user filled in a new ID
	if (_gui.getGlobalScreen()->checkValueForm("scriptRename", newScriptFileID))
	{
		auto existingScriptFileIDs = _script.getAllScriptFileIDs();
		if (find(existingScriptFileIDs.begin(), existingScriptFileIDs.end(), newScriptFileID) == existingScriptFileIDs.end())
		{
			_scriptFilenamesToDelete.push_back(_currentScriptFileID);
			_script.renameScriptFile(_currentScriptFileID, newScriptFileID);
			_currentScriptFileID = newScriptFileID;
		}
		else
		{
			Logger::throwWarning("Script with ID \"" + newScriptFileID + "\" already exists!");
		}
	}
}