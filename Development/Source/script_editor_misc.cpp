#include "script_editor.hpp"

void ScriptEditor::_reloadScriptTextDisplay()
{
	if (_isLoaded)
	{
		// Remove all existing billboards & their respective AABBs
		_fe3d.billboardEntity_deleteAll();
		_fe3d.aabbEntity_deleteAll();

		// Create line separator billboard
		float lineCount = static_cast<float>(_script.getScriptFile(_currentScriptFileID)->getLineCount());
		vec2 separatorSize = vec2((_textCharacterSize.x / 4.0f), (lineCount * _verticalLineOffset));
		vec3 separatorPosition = _scriptTextStartingPosition + vec3(_horizontalLineOffset / 2.0f, -(((lineCount - 1) / 2.0f) * _verticalLineOffset), 0.0f);
		_fe3d.billBoardEntity_add("separator", _selectionColor, separatorPosition, vec3(0.0f), separatorSize, false, false);

		// Create visible billboards for display and invisible billboards for logic
		for (unsigned int lineIndex = 0; lineIndex < lineCount; lineIndex++)
		{
			// Generation values
			string lineNumberID = to_string(lineIndex);
			string lineTextID = "text_" + lineNumberID;
			string lineNumberString = to_string(lineIndex + 1);
			string lineTextString = _script.getScriptFile(_currentScriptFileID)->getLineText(lineIndex);
			vec2 lineNumberSize = vec2(lineNumberString.size() * _textCharacterSize.x, _textCharacterSize.y);
			vec2 lineTextSize = vec2(lineTextString.size() * _textCharacterSize.x, _textCharacterSize.y);
			vec3 lineNumberPosition = _scriptTextStartingPosition -
				vec3((lineNumberString.size() - 1) * (_textCharacterSize.x / 2.0f), _verticalLineOffset * static_cast<float>(lineIndex), 0.0f);
			vec3 lineTextPosition = _scriptTextStartingPosition +
				vec3((lineTextString.size() - 1) * (_textCharacterSize.x / 2.0f), -_verticalLineOffset * static_cast<float>(lineIndex), 0.0f) +
				vec3(_horizontalLineOffset, 0.0f, 0.0f);

			// Create line number billboard
			_fe3d.billBoardEntity_add(lineNumberID, lineNumberString, _fontPath, _lineNumberColor, lineNumberPosition, vec3(0.0f), lineNumberSize, 0, 0);
			vec3 aabbPosition = lineNumberPosition - vec3(0.0f, _textCharacterSize.y / 2.0f, _aabbDepth);
			vec3 aabbSize = vec3(_textCharacterSize.x * static_cast<float>(_maxCharactersPerLine * 2) * 1.1f, _textCharacterSize.y, _aabbDepth);
			_fe3d.aabbEntity_add(lineNumberID, aabbPosition, aabbSize, true);
			
			// Create line text display billboard
			_fe3d.billBoardEntity_add(lineTextID, lineTextString, _fontPath, _characterColor, lineTextPosition, vec3(0.0f), lineTextSize, false, false);

			// Loop over every character
			for (unsigned int charIndex = 0; charIndex < lineTextString.size(); charIndex++)
			{
				// Generation values
				string characterID = lineNumberID + "_" + to_string(charIndex);
				float characterX = _horizontalLineOffset + (_horizontalCharacterOffset * static_cast<float>(charIndex));
				vec3 characterPosition = _scriptTextStartingPosition + vec3(characterX, -_verticalLineOffset * static_cast<float>(lineIndex), 0.0f);
				vec3 aabbPosition = characterPosition - vec3(0.0f, _textCharacterSize.y / 2.0f, 0.0f);
				vec3 aabbSize = vec3(_textCharacterSize.x, _textCharacterSize.y, _aabbDepth);

				// Create new character billboard for logic
				_fe3d.billBoardEntity_add(characterID, vec3(0.0f), characterPosition, vec3(0.0f), _textCharacterSize, false, false, false);
				_fe3d.aabbEntity_add(characterID, aabbPosition, aabbSize, true);
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
	return _isLoaded;
}