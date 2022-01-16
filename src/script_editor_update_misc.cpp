#include "script_editor.hpp"
#include "logger.hpp"

#include <algorithm>

using std::clamp;

void ScriptEditor::_updateGUI()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getID() == "scriptEditorMenuMain")
	{
		if((_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("back")->isHovered()) || (_fe3d->input_isKeyPressed(InputType::KEY_ESCAPE) && !_gui->getOverlay()->isFocused()))
		{
			_gui->getOverlay()->createAnswerForm("back", "Save Changes?", fvec2(0.0f, 0.25f));
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("search")->isHovered())
		{
			_gui->getOverlay()->createValueForm("search", "Search Script", "", fvec2(0.0f, 0.1f), fvec2(0.5f, 0.1f), fvec2(0.0f, 0.1f));
			_isSearchingScriptFile = true;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("create")->isHovered())
		{
			_gui->getOverlay()->createValueForm("scriptCreate", "Create Script", "", fvec2(0.0f, 0.1f), fvec2(0.5f, 0.1f), fvec2(0.0f, 0.1f));
			_isCreatingScriptFile = true;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("edit")->isHovered())
		{
			_gui->getOverlay()->createChoiceForm("scriptFileList", "Edit Script", fvec2(0.0f, 0.1f), _script->getScriptFileIDs());
			_isChoosingScriptFile = true;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("rename")->isHovered())
		{
			_gui->getOverlay()->createValueForm("scriptRename", "Rename Script", "", fvec2(0.0f, 0.1f), fvec2(0.5f, 0.1f), fvec2(0.0f, 0.1f));
			_isRenamingScriptFile = true;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("delete")->isHovered())
		{
			_scriptFileNamesToDelete.push_back(_currentScriptFileID);
			_fe3d->billboard_deleteAll();
			_script->deleteScriptFile(_currentScriptFileID);
			_isWritingScript = false;
			_currentScriptFileID = "";
		}

		if(_fe3d->input_isKeyDown(InputType::KEY_LCTRL) || _fe3d->input_isKeyDown(InputType::KEY_RCTRL))
		{
			if(_fe3d->input_isKeyPressed(InputType::KEY_F) && !_gui->getOverlay()->isFocused())
			{
				_gui->getOverlay()->createValueForm("search", "Search Keyword", "", fvec2(0.0f, 0.1f), fvec2(0.5f, 0.1f), fvec2(0.0f, 0.1f));
			}
		}

		if(_gui->getOverlay()->isAnswerFormConfirmed("back"))
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("main");
			saveScriptFiles();
			unload();
			return;
		}
		if(_gui->getOverlay()->isAnswerFormDenied("back"))
		{
			_gui->getLeftViewport()->getWindow("main")->setActiveScreen("main");
			unload();
			return;
		}

		screen->getButton("rename")->setHoverable(!_currentScriptFileID.empty());
		screen->getButton("delete")->setHoverable(!_currentScriptFileID.empty());

		screen->getTextField("lineCount")->changeTextContent("Lines: " + to_string(_script->getTotalLineCount()));
	}
}

void ScriptEditor::_updateScriptFileCreating()
{
	if(_isCreatingScriptFile)
	{
		string newScriptFileID;

		if(_gui->getOverlay()->checkValueForm("scriptCreate", newScriptFileID))
		{
			if(newScriptFileID.find(' ') != string::npos)
			{
				Logger::throwWarning("Script ID cannot contain any spaces!");
				return;
			}

			if(newScriptFileID.find('@') != string::npos)
			{
				Logger::throwWarning("Script ID cannot contain '@'!");
				return;
			}

			auto existingScriptFileIDs = _script->getScriptFileIDs();
			if(find(existingScriptFileIDs.begin(), existingScriptFileIDs.end(), newScriptFileID) != existingScriptFileIDs.end())
			{
				Logger::throwWarning("Script with ID \"" + newScriptFileID + "\" already exists!");
				return;
			}

			_currentScriptFileID = newScriptFileID;
			_isWritingScript = true;
			_firstSelectedLineIndex = -1;
			_lastSelectedLineIndex = -1;
			_script->createScriptFile(_currentScriptFileID);
			_script->getScriptFile(_currentScriptFileID)->insertNewLine(0, "");
			_reloadScriptTextDisplay(true);

			_isCreatingScriptFile = false;
		}
	}
}

void ScriptEditor::_updateScriptFileChoosing()
{
	if(_isChoosingScriptFile)
	{
		auto selectedButtonID = _gui->getOverlay()->checkChoiceForm("scriptFileList");

		if(!selectedButtonID.empty())
		{
			if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				_currentScriptFileID = selectedButtonID;
				_isWritingScript = true;
				_firstSelectedLineIndex = -1;
				_lastSelectedLineIndex = -1;
				_reloadScriptTextDisplay(true);

				_gui->getOverlay()->deleteChoiceForm("scriptFileList");
				_isChoosingScriptFile = false;
			}
		}
		else if(_gui->getOverlay()->isChoiceFormCancelled("scriptFileList"))
		{
			_gui->getOverlay()->deleteChoiceForm("scriptFileList");
			_isChoosingScriptFile = false;
		}
	}
}

void ScriptEditor::_updateScriptFileRenaming()
{
	if(_isRenamingScriptFile)
	{
		string newScriptFileID;

		if(_gui->getOverlay()->checkValueForm("scriptRename", newScriptFileID))
		{
			if(newScriptFileID.find(' ') != string::npos)
			{
				Logger::throwWarning("Script ID cannot contain any spaces!");
				return;
			}

			if(newScriptFileID.find('@') != string::npos)
			{
				Logger::throwWarning("Script ID cannot contain '@'!");
				return;
			}

			auto existingScriptFileIDs = _script->getScriptFileIDs();
			if(find(existingScriptFileIDs.begin(), existingScriptFileIDs.end(), newScriptFileID) == existingScriptFileIDs.end())
			{
				Logger::throwWarning("Script with ID \"" + newScriptFileID + "\" already exists!");
			}

			_scriptFileNamesToDelete.push_back(_currentScriptFileID);
			_script->renameScriptFile(_currentScriptFileID, newScriptFileID);
			_currentScriptFileID = newScriptFileID;

			_isRenamingScriptFile = false;
		}
	}
}

void ScriptEditor::_updateScriptSearching()
{
	if(_isSearchingScriptFile)
	{
		string keyword;

		if(_gui->getOverlay()->checkValueForm("search", keyword))
		{
			const auto result = _script->findKeyword(keyword);

			if(result.empty())
			{
				Logger::throwInfo("Keyword \"" + keyword + "\" not found in scripts!");
				Logger::throwInfo("");
				return;
			}

			for(const auto& [key, lineNumber] : result)
			{
				Logger::throwInfo("Keyword \"" + keyword + "\" found in script \"" + key + "\" @ line " + to_string(lineNumber));
			}
			Logger::throwInfo("");

			_isSearchingScriptFile = false;
		}
	}
}

void ScriptEditor::_updateMiscellaneous()
{
	if(_isWritingScript)
	{
		const unsigned int currentLineIndex = _script->getScriptFile(_currentScriptFileID)->getCursorLineIndex();
		const unsigned int lineCount = _script->getScriptFile(_currentScriptFileID)->getLineCount();
		const float lastLineHeight = _fe3d->billboard_getPosition(to_string(lineCount - 1)).y;

		if(!_gui->getOverlay()->isFocused() && _fe3d->misc_isCursorInsideViewport())
		{
			if(_fe3d->input_getMouseWheelY() == -1 && lineCount > (MAX_VISIBLE_LINES - 1))
			{
				_scrollingAcceleration -= SCROLLING_SPEED;
			}
			else if(_fe3d->input_getMouseWheelY() == 1)
			{
				_scrollingAcceleration += SCROLLING_SPEED;
			}
		}

		if(_fe3d->camera_getPosition().y > CAMERA_POSITION.y)
		{
			_scrollingAcceleration = 0.0f;
			_fe3d->camera_setPosition(CAMERA_POSITION);
		}
		else if(_fe3d->camera_getPosition().y == CAMERA_POSITION.y && _scrollingAcceleration > 0.0f)
		{
			_scrollingAcceleration = 0.0f;
		}

		if(lineCount > (MAX_VISIBLE_LINES - 1))
		{
			if(_fe3d->camera_getPosition().y < (lastLineHeight + CAMERA_OFFSET))
			{
				_scrollingAcceleration = 0.0f;
				_fe3d->camera_setPosition(fvec3(CAMERA_POSITION.x, lastLineHeight + CAMERA_OFFSET, CAMERA_POSITION.z));
			}
			else if(_fe3d->camera_getPosition().y == (lastLineHeight + CAMERA_OFFSET) && _scrollingAcceleration < 0.0f)
			{
				_scrollingAcceleration = 0.0f;
			}
		}
		else
		{
			_scrollingAcceleration = 0.0f;
			_fe3d->camera_setPosition(CAMERA_POSITION);
		}

		static unsigned int lastLineIndex = currentLineIndex;
		if((currentLineIndex > (MAX_VISIBLE_LINES - 1)) && (currentLineIndex != lastLineIndex) && (currentLineIndex == lineCount - 1))
		{
			_scrollingAcceleration = 0.0f;
			float currentLineHeight = _fe3d->billboard_getPosition(to_string(currentLineIndex)).y;
			_fe3d->camera_setPosition(fvec3(CAMERA_POSITION.x, currentLineHeight + CAMERA_OFFSET, CAMERA_POSITION.z));
		}
		lastLineIndex = currentLineIndex;
	}

	_scrollingAcceleration = clamp(_scrollingAcceleration, -MAX_SCROLLING_ACCELERATION, MAX_SCROLLING_ACCELERATION);
	_scrollingAcceleration *= 0.95f;
	_fe3d->camera_move(fvec3(0.0f, _scrollingAcceleration, 0.0f));
}