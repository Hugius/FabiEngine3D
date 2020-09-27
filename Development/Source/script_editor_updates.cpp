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
		auto mainScreen = _leftWindow->getScreen("scriptEditorMenuMain");
		
		// Check if LMB is pressed
		if (!_gui->getGlobalScreen()->isFocused())
		{
			if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
			{
				if (mainScreen->getButton("createScript")->isHovered())
				{
					if (!_isWritingScript)
					{
						_isWritingScript = true;
						_cursorLineIndex = 0;
						_cursorPlaceIndex = 0;
						_currentScriptFileID = "test";
						_script->addScriptFile(_currentScriptFileID);
						_script->getScriptFile(_currentScriptFileID)->addNewLine("");
						_reloadLineNumbersDisplay();
					}
				}
				else if (mainScreen->getButton("editScript")->isHovered())
				{
					_gui->getGlobalScreen()->addChoiceForm("scriptFileList", "Choose file", vec2(0.0f, 0.0f), _script->getAllScriptFileIDs());
				}
				else if (mainScreen->getButton("deleteScript")->isHovered())
				{
					
				}
				else if (mainScreen->getButton("variables")->isHovered())
				{

				}
				else if (mainScreen->getButton("back")->isHovered())
				{
					_gui->getGlobalScreen()->addAnswerForm("exitScriptEditor", "Save changes?", vec2(0.0f, 0.25f));
				}
			}
		}

		// Check if user wants to save changes
		if (_gui->getGlobalScreen()->isAnswerFormConfirmed("exitScriptEditor"))
		{
			save();
			unload();
			_leftWindow->setActiveScreen("main");
		}
		else if (_gui->getGlobalScreen()->isAnswerFormCancelled("exitScriptEditor"))
		{
			unload();
			_leftWindow->setActiveScreen("main");
		}
	}
}

void ScriptEditor::_updateMiscellaneous()
{
	if (_isLoaded)
	{
		if (!_gui->getGlobalScreen()->isFocused())
		{
			// Camear movement input
			if (_fe3d.input_getMouseWheelY() == -1 && _cursorLineIndex > 12)
			{
				_scrollingAcceleration -= _scrollingSpeed;
			}
			else if (_fe3d.input_getMouseWheelY() == 1)
			{
				_scrollingAcceleration += _scrollingSpeed;
			}
		}

		// Smooth camera movement
		_scrollingAcceleration = std::clamp(_scrollingAcceleration, -_maxScrollingAcceleration, _maxScrollingAcceleration);
		_scrollingAcceleration *= 0.95f;
		
		// Cannot go out of screen
		if (_fe3d.camera_getPosition().y > _cameraStartingPosition.y)
		{
			_scrollingAcceleration = 0.0f;
			_fe3d.camera_setPosition(_cameraStartingPosition);
		}
		else if (_fe3d.billboardEntity_isExisting(to_string(_cursorLineIndex)) && _cursorLineIndex > 12)
		{
			// Check if camera is not seeing the space under the last line of the script
			if (_fe3d.camera_getPosition().y < _fe3d.billboardEntity_getPosition(to_string(_cursorLineIndex)).y + 6.5f)
			{
				_scrollingAcceleration = 0.0f;
				float newY = _fe3d.billboardEntity_getPosition(to_string(_cursorLineIndex)).y + 6.5f;
				_fe3d.camera_setPosition(vec3(_cameraStartingPosition.x, newY, _cameraStartingPosition.z));
			}
		}

		// Move camera
		_fe3d.camera_translate(vec3(0.0f, _scrollingAcceleration, 0.0f));

		// Check if existing script file chosen for viewing
		string selectedButtonID = _gui->getGlobalScreen()->getSelectedChoiceFormButtonID("scriptFileList");
		if (selectedButtonID != "")
		{
			if (_fe3d.input_getMousePressed(Input::MOUSE_BUTTON_LEFT))
			{
				_gui->getGlobalScreen()->removeChoiceForm("scriptFileList");
				_currentScriptFileID = selectedButtonID;
				_isWritingScript = true;
				_cursorLineIndex = 0;
				_cursorPlaceIndex = 0;
			}
		}
		else if (_gui->getGlobalScreen()->isChoiceFormCancelled("scriptFileList"))
		{
			_gui->getGlobalScreen()->removeChoiceForm("scriptFileList");
		}
	}
}