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
			if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT) || _fe3d.input_getKeyPressed(InputType::KEY_ESCAPE))
			{
				if (screen->getButton("back")->isHovered() || (_fe3d.input_getKeyPressed(InputType::KEY_ESCAPE) && !_gui.getGlobalScreen()->isFocused()))
				{
					_gui.getGlobalScreen()->addAnswerForm("exitScriptEditor", "Save changes?", Vec2(0.0f, 0.25f));
				}
				else if (screen->getButton("createScript")->isHovered())
				{
					_gui.getGlobalScreen()->addValueForm("newScriptName", "New script name", "", Vec2(0.0f), Vec2(0.5f, 0.1f));
				}
				else if (screen->getButton("editScript")->isHovered())
				{
					_gui.getGlobalScreen()->addChoiceForm("scriptFileList", "Choose script", Vec2(0.0f), _script.getAllScriptFileIDs());
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

			// Buttons hoverability
			screen->getButton("deleteScript")->setHoverable(_currentScriptFileID != "");

			// Check if user wants to save changes
			if (_gui.getGlobalScreen()->isAnswerFormConfirmed("exitScriptEditor"))
			{
				saveScriptsToFile();
				unload();
				_gui.getViewport("left")->getWindow("main")->setActiveScreen("main");
			}
			else if (_gui.getGlobalScreen()->isAnswerFormCancelled("exitScriptEditor"))
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
				if (_fe3d.input_getMouseWheelY() == -1 && lineCount > (_maxVisibleLines - 1))
				{
					_scrollingAcceleration -= _scrollingSpeed;
				}
				else if (_fe3d.input_getMouseWheelY() == 1)
				{
					_scrollingAcceleration += _scrollingSpeed;
				}
			}

			// Camera must not go out of screen (upwards)
			if (_fe3d.camera_getPosition().y > _cameraStartingPosition.y)
			{
				_scrollingAcceleration = 0.0f;
				_fe3d.camera_setPosition(_cameraStartingPosition);
			}
			else if (_fe3d.camera_getPosition().y == _cameraStartingPosition.y && _scrollingAcceleration > 0.0f) // Trying to scroll up
			{
				_scrollingAcceleration = 0.0f;
			}

			// Check if code is out of screen
			if (lineCount > (_maxVisibleLines - 1))
			{
				if (_fe3d.camera_getPosition().y < (lastLineHeight + _cameraOffset)) // Camera must not go out of screen
				{
					_scrollingAcceleration = 0.0f;
					_fe3d.camera_setPosition(Vec3(_cameraStartingPosition.x, lastLineHeight + _cameraOffset, _cameraStartingPosition.z));
				}
				else if (_fe3d.camera_getPosition().y == (lastLineHeight + _cameraOffset) && _scrollingAcceleration < 0.0f) // Trying to scroll down
				{
					_scrollingAcceleration = 0.0f;
				}
			}
			else // Reset camera position if too little amount of lines
			{
				_scrollingAcceleration = 0.0f;
				_fe3d.camera_setPosition(_cameraStartingPosition);
			}

			// Synchronize camera position whenever writers adds or removes a line
			static unsigned int lastLineIndex = currentLineIndex;
			if ((currentLineIndex > (_maxVisibleLines - 1)) && (currentLineIndex != lastLineIndex) && (currentLineIndex == lineCount - 1))
			{
				_scrollingAcceleration = 0.0f;
				float currentLineHeight = _fe3d.billboardEntity_getPosition(to_string(currentLineIndex)).y;
				_fe3d.camera_setPosition(Vec3(_cameraStartingPosition.x, currentLineHeight + _cameraOffset, _cameraStartingPosition.z));
			}
			lastLineIndex = currentLineIndex;
		}

		// Smooth camera movement
		_scrollingAcceleration = std::clamp(_scrollingAcceleration, -_maxScrollingAcceleration, _maxScrollingAcceleration);
		_scrollingAcceleration *= 0.95f;
		_fe3d.camera_translate(Vec3(0.0f, _scrollingAcceleration, 0.0f));

		// Check if user filled in a new script name
		string newName;
		if (_gui.getGlobalScreen()->checkValueForm("newScriptName", newName))
		{
			auto existingNames = _script.getAllScriptFileIDs();
			if (find(existingNames.begin(), existingNames.end(), newName) == existingNames.end())
			{
				_isWritingScript = true;
				_currentScriptFileID = newName;
				_script.addScriptFile(_currentScriptFileID);
				_script.getScriptFile(_currentScriptFileID)->insertNewLine(0, "");
				_reloadScriptTextDisplay();
			}
			else
			{
				_fe3d.logger_throwWarning("Script name already exists!");
			}
		}

		// Check if existing script file chosen for viewing
		string selectedButtonID = _gui.getGlobalScreen()->getSelectedChoiceFormButtonID("scriptFileList");
		if (selectedButtonID != "")
		{
			if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				_gui.getGlobalScreen()->removeChoiceForm("scriptFileList");
				_currentScriptFileID = selectedButtonID;
				_isWritingScript = true;
				_firstSelectedLineIndex = -1;
				_lastSelectedLineIndex = -1;
				_reloadScriptTextDisplay();
			}
		}
		else if (_gui.getGlobalScreen()->isChoiceFormCancelled("scriptFileList"))
		{
			_gui.getGlobalScreen()->removeChoiceForm("scriptFileList");
		}
	}
}