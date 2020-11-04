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
	if (_isLoaded)
	{
		// Main screen
		auto leftWindow = _gui.getViewport("left")->getWindow("main");
		auto mainScreen = leftWindow->getScreen("scriptEditorMenuMain");
		
		// Buttons hoverability
		mainScreen->getButton("deleteScript")->setHoverable(_currentScriptFileID != "");

		// Check if LMB is pressed
		if (!_gui.getGlobalScreen()->isFocused())
		{
			if (_fe3d.input_getMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				if (mainScreen->getButton("createScript")->isHovered())
				{
					_gui.getGlobalScreen()->addValueForm("newScriptName", "New script name", "", vec2(0.0f), vec2(0.5f, 0.1f));
				}
				else if (mainScreen->getButton("editScript")->isHovered())
				{
					_gui.getGlobalScreen()->addChoiceForm("scriptFileList", "Choose script", vec2(0.0f), _script.getAllScriptFileIDs());
				}
				else if (mainScreen->getButton("deleteScript")->isHovered())
				{
					_scriptFileNamesToDelete.push_back(_currentScriptFileID);
					_fe3d.billboardEntity_deleteAll();
					_script.removeScriptFile(_currentScriptFileID);
					_isWritingScript = false;
					_currentScriptFileID = "";
				}
				else if (mainScreen->getButton("back")->isHovered())
				{
					_gui.getGlobalScreen()->addAnswerForm("exitScriptEditor", "Save changes?", vec2(0.0f, 0.25f));
				}
			}
		}

		// Check if user wants to save changes
		if (_gui.getGlobalScreen()->isAnswerFormConfirmed("exitScriptEditor"))
		{
			save();
			unload();
			leftWindow->setActiveScreen("main");
		}
		else if (_gui.getGlobalScreen()->isAnswerFormCancelled("exitScriptEditor"))
		{
			unload();
			leftWindow->setActiveScreen("main");
		}
	}
}

void ScriptEditor::_updateMiscellaneous()
{
	if (_isLoaded)
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
					_fe3d.camera_setPosition(vec3(_cameraStartingPosition.x, lastLineHeight + _cameraOffset, _cameraStartingPosition.z));
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
				_fe3d.camera_setPosition(vec3(_cameraStartingPosition.x, currentLineHeight + _cameraOffset, _cameraStartingPosition.z));
			}
			lastLineIndex = currentLineIndex;
		}

		// Smooth camera movement
		_scrollingAcceleration = std::clamp(_scrollingAcceleration, -_maxScrollingAcceleration, _maxScrollingAcceleration);
		_scrollingAcceleration *= 0.95f;
		_fe3d.camera_translate(vec3(0.0f, _scrollingAcceleration, 0.0f));

		// Synchronize AABB's with character billboards (to prevent low framerate when reloading script text fast)
		if (_wasScriptTextReloaded)
		{
			if (_fe3d.misc_checkInterval("billboardAabbSynchronization", 100))
			{
				for (auto& ID : _fe3d.billboardEntity_getAllIDs())
				{
					if (ID.find('_') != string::npos) // String must contain underscore
					{
						// Must be a character billboard
						if (ID.substr(0, string("text_").size()) != "text_" && ID.substr(0, string("selection_").size()) != "selection_")
						{
							if (!_fe3d.aabbEntity_isExisting(ID)) // Check if not already exists
							{
								_fe3d.aabbEntity_bindToBillboardEntity(ID, true); // Add AABB
							}
						}
					}
				}

				_wasScriptTextReloaded = false;
			}
		}

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
				_reloadScriptTextDisplay();
			}
		}
		else if (_gui.getGlobalScreen()->isChoiceFormCancelled("scriptFileList"))
		{
			_gui.getGlobalScreen()->removeChoiceForm("scriptFileList");
		}
	}
}