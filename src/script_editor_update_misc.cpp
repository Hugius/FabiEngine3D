#include "script_editor.hpp"
#include "logger.hpp"

#include <algorithm>

using std::clamp;

void ScriptEditor::_updateGUI()
{
	auto screen = _gui->getLeftViewport()->getWindow("main")->getActiveScreen();

	if(screen->getId() == "scriptEditorMenuMain")
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
			_gui->getOverlay()->createChoiceForm("scriptFileList", "Edit Script", fvec2(0.0f, 0.1f), _script->getScriptFileIds());
			_isChoosingScriptFile = true;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("rename")->isHovered())
		{
			_gui->getOverlay()->createValueForm("scriptRename", "Rename Script", "", fvec2(0.0f, 0.1f), fvec2(0.5f, 0.1f), fvec2(0.0f, 0.1f));
			_isRenamingScriptFile = true;
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("clear")->isHovered())
		{
			_clearDisplay();
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("delete")->isHovered())
		{
			_gui->getOverlay()->createAnswerForm("delete", "Are You Sure?", fvec2(0.0f, 0.25f));
			_isDeletingScriptFile = true;
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

		screen->getButton("rename")->setHoverable(!_currentScriptFileId.empty());
		screen->getButton("clear")->setHoverable(!_currentScriptFileId.empty());
		screen->getButton("delete")->setHoverable(!_currentScriptFileId.empty());

		screen->getTextField("lineCount")->changeTextContent("Lines: " + to_string(_script->getTotalLineCount()));
	}
}

void ScriptEditor::_updateScriptFileCreating()
{
	if(_isCreatingScriptFile)
	{
		string newScriptFileId;

		if(_gui->getOverlay()->checkValueForm("scriptCreate", newScriptFileId))
		{
			if(any_of(newScriptFileId.begin(), newScriptFileId.end(), isspace))
			{
				Logger::throwWarning("Script file ID cannot contain any spaces");
				return;
			}

			if(!all_of(newScriptFileId.begin(), newScriptFileId.end(), isalnum))
			{
				Logger::throwWarning("Script file ID cannot contain any specials");
				return;
			}

			if(any_of(newScriptFileId.begin(), newScriptFileId.end(), isupper))
			{
				Logger::throwWarning("Script file ID cannot contain any capitals");
				return;
			}

			auto existingScriptFileIds = _script->getScriptFileIds();
			if(find(existingScriptFileIds.begin(), existingScriptFileIds.end(), newScriptFileId) != existingScriptFileIds.end())
			{
				Logger::throwWarning("Script already exists");
				return;
			}

			_script->createScriptFile(newScriptFileId);
			_script->getScriptFile(newScriptFileId)->insertNewLine(0, "");

			_currentScriptFileId = newScriptFileId;
			_isWritingScript = true;

			_deleteScriptDisplayEntities();
			_createScriptDisplayEntities();
			_fe3d->text3d_setVisible("cursor", true);

			_isCreatingScriptFile = false;
		}
	}
}

void ScriptEditor::_updateScriptFileChoosing()
{
	if(_isChoosingScriptFile)
	{
		auto selectedButtonId = _gui->getOverlay()->checkChoiceForm("scriptFileList");

		if(!selectedButtonId.empty())
		{
			if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT))
			{
				_currentScriptFileId = selectedButtonId;
				_isWritingScript = true;

				_deleteScriptDisplayEntities();
				_createScriptDisplayEntities();
				_fe3d->text3d_setVisible("cursor", true);

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
		string newScriptFileId;

		if(_gui->getOverlay()->checkValueForm("scriptRename", newScriptFileId))
		{
			if(any_of(newScriptFileId.begin(), newScriptFileId.end(), isspace))
			{
				Logger::throwWarning("Script file ID cannot contain any spaces");
				return;
			}

			if(!all_of(newScriptFileId.begin(), newScriptFileId.end(), isalnum))
			{
				Logger::throwWarning("Script file ID cannot contain any specials");
				return;
			}

			if(any_of(newScriptFileId.begin(), newScriptFileId.end(), isupper))
			{
				Logger::throwWarning("Script file ID cannot contain any capitals");
				return;
			}

			auto existingScriptFileIds = _script->getScriptFileIds();
			if(find(existingScriptFileIds.begin(), existingScriptFileIds.end(), newScriptFileId) != existingScriptFileIds.end())
			{
				Logger::throwWarning("Script already exists");
			}

			_script->renameScriptFile(_currentScriptFileId, newScriptFileId);
			_currentScriptFileId = newScriptFileId;
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
				Logger::throwWarning("Keyword not found in scripts");
				return;
			}

			for(const auto& [key, lineNumber] : result)
			{
				Logger::throwInfo("Keyword found in script \"" + key + "\" @ line " + to_string(lineNumber));
			}

			_isSearchingScriptFile = false;
		}
	}
}

void ScriptEditor::_updateDisplay()
{
	if(!_isWritingScript || _gui->getOverlay()->isFocused())
	{
		return;
	}

	if(_hasTextChanged)
	{
		_deleteScriptDisplayEntities();
		_createScriptDisplayEntities();

		_hasTextChanged = false;
	}
}

void ScriptEditor::_updateCamera()
{
	if(!_isWritingScript || _gui->getOverlay()->isFocused() || !_fe3d->misc_isCursorInsideDisplay())
	{
		return;
	}

	const auto scrollSpeed = static_cast<float>(_fe3d->input_getMouseWheelY());
	const auto lineCount = _script->getScriptFile(_currentScriptFileId)->getLineCount();
	const auto lastLineHeight = _fe3d->text3d_getPosition("number_" + to_string(lineCount - 1)).y;
	const auto minCameraOffset = fvec2(0.0f, min(0.0f, (lastLineHeight + TEXT_STARTING_POSITION.y)));
	const auto maxCameraOffset = fvec2(FLT_MAX, 0.0f);

	auto cameraPosition = _fe3d->camera_getPosition();

	if(_fe3d->input_isKeyDown(InputType::KEY_LSHIFT))
	{
		cameraPosition.x += scrollSpeed;
	}
	else
	{
		cameraPosition.y += scrollSpeed;
	}

	cameraPosition.x = clamp(cameraPosition.x, minCameraOffset.x, maxCameraOffset.x);
	cameraPosition.y = clamp(cameraPosition.y, minCameraOffset.y, maxCameraOffset.y);

	_fe3d->camera_setPosition(cameraPosition);
}

void ScriptEditor::_updateCursor()
{
	if(!_isWritingScript || _gui->getOverlay()->isFocused())
	{
		_fe3d->text3d_setVisible("cursor", false);

		return;
	}

	if(_fe3d->misc_isCursorInsideDisplay())
	{
		_fe3d->quad2d_setDiffuseMap("@@cursor", "engine\\assets\\image\\diffuse_map\\cursor_text.tga");
	}

	if((_fe3d->misc_getPassedUpdateCount() % (_fe3d->misc_getUpdateCountPerSecond() / 2)) == 0)
	{
		if(_fe3d->text3d_getContent("cursor") == "|")
		{
			_fe3d->text3d_setContent("cursor", " ");
		}
		else
		{
			_fe3d->text3d_setContent("cursor", "|");
		}
	}

	const auto cursorLineIndex = _script->getScriptFile(_currentScriptFileId)->getCursorLineIndex();
	const auto cursorCharacterIndex = _script->getScriptFile(_currentScriptFileId)->getCursorCharacterIndex();

	if(cursorCharacterIndex == 0)
	{
		const auto linePosition = _fe3d->aabb_getBasePosition(to_string(_script->getScriptFile(_currentScriptFileId)->getCursorLineIndex()));
		const auto cursorPosition = fvec3((TEXT_STARTING_POSITION.x + HORIZONTAL_LINE_OFFSET - (TEXT_CHARACTER_SIZE.x * 0.5f)), linePosition.y, linePosition.z);

		_fe3d->text3d_setPosition("cursor", cursorPosition);
	}
	else
	{
		const auto characterPosition = _fe3d->aabb_getBasePosition(to_string(cursorLineIndex) + "_" + to_string(cursorCharacterIndex - 1));
		const auto cursorPosition = fvec3((characterPosition.x + (TEXT_CHARACTER_SIZE.x * 0.5f)), characterPosition.y, characterPosition.z);

		_fe3d->text3d_setPosition("cursor", cursorPosition);
	}
}

void ScriptEditor::_updateScriptDeleting()
{
	if(_isDeletingScriptFile)
	{
		if(_gui->getOverlay()->isAnswerFormConfirmed("delete"))
		{
			_script->deleteScriptFile(_currentScriptFileId);
			_clearDisplay();
			_isDeletingScriptFile = false;
		}
		if(_gui->getOverlay()->isAnswerFormDenied("delete"))
		{
			_isDeletingScriptFile = false;
		}
	}
}