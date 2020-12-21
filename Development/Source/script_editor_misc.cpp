#include "script_editor.hpp"

void ScriptEditor::_reloadScriptTextDisplay(bool reloadAabbs)
{
	if (_isEditorLoaded)
	{
		// Remove all existing BILLBOARD & AABB entities
		_fe3d.billboardEntity_deleteAll();
		_fe3d.aabbEntity_deleteAll();

		// Create line separator BILLBOARD
		float lineCount = static_cast<float>(_script.getScriptFile(_currentScriptFileID)->getLineCount());
		Vec2 separatorSize = Vec2((_textCharacterSize.x / 4.0f), (lineCount * _verticalLineOffset));
		Vec3 separatorPosition = _scriptTextStartingPosition + Vec3(_horizontalLineOffset / 2.0f, -(((lineCount - 1) / 2.0f) * _verticalLineOffset), 0.0f);
		_fe3d.billboardEntity_add("separator", _selectionColor, separatorPosition, Vec3(0.0f), separatorSize, false, false);

		// Create visible billboards for display and invisible billboards for logic
		for (unsigned int lineIndex = 0; lineIndex < lineCount; lineIndex++)
		{
			// Generation values
			string lineNumberID = to_string(lineIndex);
			string lineTextID = "text_" + lineNumberID;
			string lineNumberString = to_string(lineIndex + 1);
			string lineTextString = _script.getScriptFile(_currentScriptFileID)->getLineText(lineIndex);
			Vec2 lineNumberSize = Vec2(lineNumberString.size() * _textCharacterSize.x, _textCharacterSize.y);
			Vec2 lineTextSize = Vec2(lineTextString.size() * _textCharacterSize.x, _textCharacterSize.y);
			Vec3 lineNumberPosition = _scriptTextStartingPosition -
				Vec3((lineNumberString.size() - 1) * (_textCharacterSize.x / 2.0f), _verticalLineOffset * static_cast<float>(lineIndex), 0.0f);
			Vec3 lineTextPosition = _scriptTextStartingPosition +
				Vec3((lineTextString.size() - 1) * (_textCharacterSize.x / 2.0f), -_verticalLineOffset * static_cast<float>(lineIndex), 0.0f) +
				Vec3(_horizontalLineOffset, 0.0f, 0.0f);

			// Create line number BILLBOARD
			_fe3d.billboardEntity_add(lineNumberID, lineNumberString, _fontPath, _lineNumberColor, lineNumberPosition, Vec3(0.0f), lineNumberSize, 0, 0);
			
			// Create line number AABB
			Vec3 aabbPosition = lineNumberPosition - Vec3(0.0f, _textCharacterSize.y / 2.0f, _aabbDepth);
			Vec3 aabbSize = Vec3(_textCharacterSize.x * static_cast<float>(_maxCharactersPerLine * 2) * 1.1f, _textCharacterSize.y, _aabbDepth);
			_fe3d.aabbEntity_add(lineNumberID, aabbPosition, aabbSize, true);
			
			// Create line text display BILLBOARD
			_fe3d.billboardEntity_add(lineTextID, lineTextString, _fontPath, _characterColor, lineTextPosition, Vec3(0.0f), lineTextSize, false, false);

			// Loop over every character
			for (unsigned int charIndex = 0; charIndex < lineTextString.size(); charIndex++)
			{
				// Create new character BILLBOARD for logic
				string characterID = lineNumberID + "_" + to_string(charIndex);
				float characterX = _horizontalLineOffset + (_horizontalCharacterOffset * static_cast<float>(charIndex));
				Vec3 characterPosition = _scriptTextStartingPosition + Vec3(characterX, -_verticalLineOffset * static_cast<float>(lineIndex), 0.0f);
				_fe3d.billboardEntity_add(characterID, Vec3(0.0f), characterPosition, Vec3(0.0f), _textCharacterSize, false, false, false);

				// Create new character AABB for logic
				if (reloadAabbs)
				{
					Vec3 aabbPosition = characterPosition - Vec3(0.0f, _textCharacterSize.y / 2.0f, 0.0f);
					Vec3 aabbSize = Vec3(_textCharacterSize.x, _textCharacterSize.y, _aabbDepth);
					_fe3d.aabbEntity_add(characterID, aabbPosition, aabbSize, true);
				}
			}
		}
	}
}

void ScriptEditor::_copySelectedText()
{
	if (_firstSelectedLineIndex != -1) // Check if anything is selected at all
	{
		_copyClipboard.clear(); // Clear last copy

		if (_lastSelectedLineIndex == -1) // Check if only 1 line selected
		{
			_copyClipboard.push_back(_script.getScriptFile(_currentScriptFileID)->getLineText(_firstSelectedLineIndex));
		}
		else // If multiple selected lines
		{
			// Determine selection direction
			for (int i = ((_firstSelectedLineIndex > _lastSelectedLineIndex) ? _lastSelectedLineIndex : _firstSelectedLineIndex);
				i <= ((_firstSelectedLineIndex > _lastSelectedLineIndex) ? _firstSelectedLineIndex : _lastSelectedLineIndex); i++)
			{
				_copyClipboard.push_back(_script.getScriptFile(_currentScriptFileID)->getLineText(i)); // Copy text lines
			}
		}
	}
}

ScriptExecutor& ScriptEditor::getScriptExecutor(bool reloadScript)
{
	// Load the original script
	if (reloadScript || !_isScriptLoadedFromFile)
	{
		loadScriptsFromFile();
	}
	
	return _scriptExecutor;
}

void ScriptEditor::setCurrentProjectName(const string& projectName)
{
	_currentProjectName = projectName;
}

bool ScriptEditor::isLoaded()
{
	return _isEditorLoaded;
}

bool ScriptEditor::isWritingScript()
{
	return !_currentScriptFileID.empty();
}